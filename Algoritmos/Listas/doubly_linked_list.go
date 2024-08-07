package list

import (
	"errors"
	"fmt"
)

type node struct  {
	elem any
	next *node
	prev *node
	list *List
}

// Returns a new and initialized node
func New_node(elem any, next *node, prev *node, list *List) *node {
	return &node {elem, next, prev, list}
}

// Returns the next node or nil
func (n *node) Next() *node {
	if n == nil {
		return nil
	}
	return n.next
}

// Returns the previous node or nil
func (n *node) Prev() *node {
	if n == nil {
		return nil
	}
	return n.prev
}

type List struct {
	size uint
	head *node
	tail *node
}

// Returns a new and initialized list
func New_list() *List {
	l := &List {
		size: 0,
		head: nil,
		tail: nil,
	}

	l.head = New_node(*new(any), nil, nil, l)
	l.tail = New_node(*new(any), nil, nil, l)
	
	l.head.next = l.tail
	l.tail.prev = l.head

	return l
}

// Checks if the node 'n' is in the list
func (l *List) In_list(n *node) bool {
	return n.list == l
}

// Returns the first node of the list
func (l *List) Begin() *node {
	return l.head.next
}

// Returns the last node of the list
func (l *List) End() *node {
	return l.tail.prev
}

// Returns true if the list is empty, otherwise, it will return false
func (l *List) Empty() bool {
	return l.head.next == l.tail 
}

// Inserts the element in the end of the list
func (l *List) Push_back(elem any) {
	n := New_node(elem, l.tail, l.tail.prev, l)

	n.prev.next = n
	l.tail.prev = n
	l.size++
}

// Inserts the element in the begining of the list
func (l *List) Push_front(elem any) {
	n := New_node(elem, l.head.next, l.head, l)

	n.next.prev = n
	l.head.next = n

	l.size++
}

// Inserts a copy of another list at the back of list l.
func (l *List) Push_back_list(other *List) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}
	
	var n *node = other.Begin()
	for n != other.tail {
		l.Push_back(n.elem)
		n = n.next
	}

	return nil
}

// Inserts a copy of another list at the front of list l.
func (l *List) Push_front_list(other *List) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}
	
	var n *node = other.End()
	for n != other.head {
		l.Push_front(n.elem)
		n = n.prev
	}

	return nil
}

// Inserts the element after the specified node
func (l *List) Insert_after(elem any, n *node) {
	if n == l.tail || !l.In_list(n) {
		return
	}
	
	new_node := New_node(elem, n.next, n, l)
	n.next.prev = new_node
	n.next = new_node
}

// Inserts the element before the specified node
func (l *List) Insert_before(elem any, n *node) {
	if n == l.head || !l.In_list(n) {
		return
	}
	
	new_node := New_node(elem, n, n.prev, l)
	n.prev.next = new_node
	n.prev = new_node
}

// Removes the last element of the list
func (l *List) Pop_back() (any, error) {
	if l.Empty() {
		return *new(any), errors.New("list is empty")
	}
	
	n := l.tail.prev

	l.tail.prev = l.tail.prev.prev
	l.tail.prev.next = l.tail
	l.size--

	n.next = nil
	n.prev = nil

	return n.elem, nil
}

// Removes the first node of the list
func (l *List) Pop_front() (any, error) {

    if l.Empty() {
        return *new(any), errors.New("list is empty")
    }

    n := l.head.next

    l.head.next = l.head.next.next
    l.head.next.prev = l.head
	l.size--

	n.next = nil
	n.prev = nil

    return n.elem, nil
}

// Removes the specified node of the list
func (l *List) Pop_node(n *node) (*node, error) {

	if n == l.head || n == l.tail {
		return nil, errors.New("node is out of range")
	} else if n == nil {
		return nil, errors.New("node is nil")
	} else if !l.In_list(n) {
		return nil, nil
	}

	n.prev.next = n.next
	n.next.prev = n.prev
	l.size--

	n.next = nil
	n.prev = nil
	n.list = nil

	return n, nil
}

// Removes all ocurrences of elem
func (l *List) Remove(elem any) {

	for n := l.Begin(); n != l.End(); {
		if n.elem == elem {
			n = n.next
			l.Pop_node(n.prev)
		} else {
			n = n.next
		}
	}
}

// Removes all the elements of the list
func (l *List) Clear() {
	l.head.next = l.tail
	l.tail.prev = l.head
	l.size = 0
}

/* Move functions */

// Moves the e node to after n node
func (l *List) Move_after(e *node, n *node) {
	if e == n || e == l.head || e == l.tail || 
	   n == l.tail || !l.In_list(e) || !l.In_list(n) {
		return
	}

	e.prev.next = e.next
	e.next.prev = n.prev
	
	e.next = n.next
	e.prev = n

	n.next.prev = e
	n.next = e
}

// Moves the e node to before n node
func (l *List) Move_before(e *node, n *node) {
	if e == n || e == l.head || e == l.tail ||
	   n == l.head || !l.In_list(e) || !l.In_list(n) {
		return
	}

	e.prev.next = e.next
	e.next.prev = n.prev

	e.next = n
	e.prev = n.prev

	n.prev.next = e
	n.prev = e
}

// Output list
func (l *List) Print_list() {

	for n := l.Begin(); n != l.tail; n = n.next {
		fmt.Printf("%v ", n.elem)
	}
	fmt.Println()
}
