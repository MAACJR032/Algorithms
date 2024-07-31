package main

import (
	"errors"
	"fmt"
)

type node struct {
	elem int
	next *node
	prev *node
}

type list struct {
	size uint
	head *node
	tail *node
}

// Constructors
func New_node(elem int, next *node, prev *node) *node {
	return &node {elem, next, prev}
}

func Create_list() *list {
	l := list {
		size: 0,
		head: New_node(0, nil, nil),
		tail: New_node(0, nil, nil),
	}

	l.head.next = l.tail
	l.tail.prev = l.head

	return &l
}

// Getters
func (l *list) Begin() *node {
	return l.head.next
}

func (l *list) End() *node {
	return l.tail
}

func (l *list) R_begin() *node {
	return l.tail.prev
}

func (l *list) R_end() *node {
	return l.head
}

func (l *list) Empty() bool {
	return l.head.next == l.tail 
}

// Insert
func (l *list) Push_back(elem int) {
	n := New_node(elem, l.tail, l.tail.prev)

	n.prev.next = n
	l.tail.prev = n

	l.size++
}

func (l *list) Push_front(elem int) {
	n := New_node(elem, l.head.next, l.head)

	n.next.prev = n
	l.head.next = n

	l.size++
}

// Remove
func (l *list) Pop_back() (int, error) {

	if l.Empty() {
		return 0, errors.New("list is empty")
	}
	
	elem := l.tail.prev.elem

	l.tail.prev = l.tail.prev.prev
	l.tail.prev.next = l.tail

	l.size--
	return elem, nil
}

func (l *list) Pop_front() (int, error) {

    if l.Empty() {
        return 0, errors.New("list is empty")
    }

    val := l.head.next.elem

    l.head.next = l.head.next.next
    l.head.next.prev = l.head
    
	l.size--
    return val, nil
}

func (l *list) Pop_node(n *node) error {

	if n == l.head || n == l.tail {
		return errors.New("especified node is out of range")
	}

	n.prev.next = n.next
	n.next.prev = n.prev
	l.size--

	return nil
}

func (l *list) Remove(elem int) {

	for n := l.Begin(); n != l.End(); {

		if n.elem == elem {
			n = n.next
			l.Pop_node(n.prev)
		} else {
			n = n.next
		}
	}
}

func (l *list) Clear() {
	for l.size > 0 {
		l.Pop_front()
	}
}

// Output list
func (l *list) Print_list() {

	for n := l.Begin(); n != l.End(); n = n.next {
		fmt.Printf("%v ", n.elem)
	}
	fmt.Println()
}
