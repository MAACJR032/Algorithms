package main

import "fmt"

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

func (l *list) Pop_back(error) int {
	elem := l.tail.prev.elem

	l.tail.prev = l.tail.prev.prev
	l.tail.prev.next = l.tail

	l.size--
	return elem
}

func (l *list) Pop_front() int {
	elem := l.head.next.elem

	l.head.next = l.head.next.next
	l.head.next.prev = l.head

	l.size--
	return elem
}

func (l *list) Pop_node(n *node) {
	n.prev.next = n.next
	n.next.prev = n.prev
	l.size--
}

func (l *list) Empty() bool {
	return l.head.next == l.tail 
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

func (l *list) Print_list() {

	for n := l.Begin(); n != l.End(); n = n.next {
		fmt.Printf("%v ", n.elem)
	}
	fmt.Println()
}

func main() {
	var l list = *Create_list()

	l.Push_back(10)
	l.Push_back(11)
	l.Push_back(12)
	l.Push_front(9)
	l.Push_back(10)
	l.Push_back(21)

	l.Remove(10)
	l.Print_list()

	l.Clear()
	l.Print_list()
}
