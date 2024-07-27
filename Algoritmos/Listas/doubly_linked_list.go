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

func new_node(elem int, next *node, prev *node) *node {
	return &node {elem, next, prev}
}

func create_list() *list {
	l := list {
		size: 0,
		head: new_node(0, nil, nil),
		tail: new_node(0, nil, nil),
	}

	l.head.next = l.tail
	l.tail.prev = l.head

	return &l
}

func (l *list) begin() *node {
	return l.head.next
}

func (l *list) end() *node {
	return l.tail
}

func (l *list) r_begin() *node {
	return l.tail.prev
}

func (l *list) r_end() *node {
	return l.head
}

func (l *list) push_back(elem int) {
	n := new_node(elem, l.tail, l.tail.prev)

	n.prev.next = n
	l.tail.prev = n

	l.size++
}

func (l *list) push_front(elem int) {
	n := new_node(elem, l.head.next, l.head)

	n.next.prev = n
	l.head.next = n

	l.size++
}

func (l *list) pop_back(error) int {
	elem := l.tail.prev.elem

	l.tail.prev = l.tail.prev.prev
	l.tail.prev.next = l.tail

	l.size--
	return elem
}

func (l *list) pop_front() int {
	elem := l.head.next.elem

	l.head.next = l.head.next.next
	l.head.next.prev = l.head

	l.size--
	return elem
}

func (l *list) pop_node(n *node) {
	n.prev.next = n.next
	n.next.prev = n.prev
	l.size--
}

func (l *list) empty() bool {
	return l.head.next == l.tail 
}

func (l *list) remove(elem int) {

	for n := l.begin(); n != l.end(); {

		if n.elem == elem {
			n = n.next
			l.pop_node(n.prev)
		} else {
			n = n.next
		}
	}
}

func (l *list) clear() {
	for l.size > 0 {
		l.pop_front()
	}
}

func (l *list) print_list() {

	for n := l.begin(); n != l.end(); n = n.next {
		fmt.Printf("%v ", n.elem)
	}
	fmt.Println()
}

func main() {
	var l list = *create_list()

	l.push_back(10)
	l.push_back(11)
	l.push_back(12)
	l.push_front(9)
	l.push_back(10)
	l.push_back(21)

	l.remove(10)
	l.print_list()

	l.clear()
	l.print_list()
}
