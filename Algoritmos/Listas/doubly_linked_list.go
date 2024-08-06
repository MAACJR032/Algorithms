package list

import (
	"errors"
	"fmt"
)

type element interface {
	~int | ~int8 | ~int16 | ~int32 | ~int64 | 
	~uint | ~uint8 | ~uint16 | ~uint32 | ~uint64 |
	~float32 | ~float64 | ~string
}

type node[T element] struct  {
	elem T
	next *node[T]
	prev *node[T]
}

type list[T element] struct {
	size uint
	head *node[T]
	tail *node[T]
}

// Constructors
func New_node[T element] (elem T, next *node[T], prev *node[T]) *node[T] {
	return &node[T] {elem, next, prev}
}

func Create_list[T element]() *list[T] {
	l := list[T] {
		size: 0,
		head: New_node(*new(T), nil, nil),
		tail: New_node(*new(T), nil, nil),
	}

	l.head.next = l.tail
	l.tail.prev = l.head

	return &l
}

// Getters
func (l *list[T]) Begin() *node[T] {
	return l.head.next
}

func (l *list[T]) End() *node[T] {
	return l.tail
}

func (l *list[T]) R_begin() *node[T] {
	return l.tail.prev
}

func (l *list[T]) R_end() *node[T] {
	return l.head
}

func (l *list[T]) Empty() bool {
	return l.head.next == l.tail 
}

// Insert
func (l *list[T]) Push_back(elem T) {
	n := New_node(elem, l.tail, l.tail.prev)

	n.prev.next = n
	l.tail.prev = n

	l.size++
}

func (l *list[T]) Push_front(elem T) {
	n := New_node(elem, l.head.next, l.head)

	n.next.prev = n
	l.head.next = n

	l.size++
}

// Remove
func (l *list[T]) Pop_back() (T, error) {

	if l.Empty() {
		return *new(T), errors.New("list is empty")
	}
	
	elem := l.tail.prev.elem

	l.tail.prev = l.tail.prev.prev
	l.tail.prev.next = l.tail

	l.size--
	return elem, nil
}

func (l *list[T]) Pop_front() (T, error) {

    if l.Empty() {
        return *new(T), errors.New("list is empty")
    }

    val := l.head.next.elem

    l.head.next = l.head.next.next
    l.head.next.prev = l.head
    
	l.size--
    return val, nil
}

func (l *list[T]) Pop_node(n *node[T]) error {

	if n == l.head || n == l.tail {
		return errors.New("especified node is out of range")
	} else if n == nil {
		return errors.New("especified node is nil")
	}

	n.prev.next = n.next
	n.next.prev = n.prev
	l.size--

	return nil
}

func (l *list[T]) Remove(elem T) {

	for n := l.Begin(); n != l.End(); {

		if n.elem == elem {
			n = n.next
			l.Pop_node(n.prev)
		} else {
			n = n.next
		}
	}
}

func (l *list[T]) Clear() {
	for l.size > 0 {
		l.Pop_front()
	}
}

// Output list
func (l *list[T]) Print_list() {

	for n := l.Begin(); n != l.End(); n = n.next {
		fmt.Printf("%v ", n.elem)
	}
	fmt.Println()
}
