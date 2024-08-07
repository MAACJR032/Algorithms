package list

import (
	"errors"
	"fmt"
)

type node struct  {
	Elem any
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

// Checks if the node n is in the list
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
		l.Push_back(n.Elem)
		n = n.next
	}

	l.size += other.size
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
		l.Push_front(n.Elem)
		n = n.prev
	}

	l.size += other.size
	return nil
}

// Inserts a another list at the back of list l
// The other list becomes empty
func (l *List) Push_back_clear_list(other *List) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}
	
	l.tail.prev.next = other.head.next
	other.head.next.prev = l.tail.prev

	l.tail.prev = other.tail.prev
	other.tail.prev.next = l.tail

	// Update the list reference for nodes
	for n := other.head.next; n != other.tail; n = n.next {
		n.list = l
	}

	// Empty the other list
	other.head.next = other.tail
	other.tail.prev = other.head
	other.size = 0

	l.size += other.size
	return nil
}

// Inserts a another list at the front of list l
// The other list becomes empty
func (l *List) Push_front_clear_list(other *List) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}

	l.head.next.prev = other.tail.prev
	other.tail.prev.next = l.head.next

	l.head.next = other.head.next
	other.head.next.prev = l.head

	// Update the list reference for nodes
	for n := other.head.next; n != other.tail; n = n.next {
		n.list = l
	}

	// Empty the other list
	other.head.next = other.tail
	other.tail.prev = other.head
	other.size = 0

	l.size += other.size
	return nil
}

// Inserts the element after the specified node
func (l *List) Insert_after(elem any, n *node) error {
	if n == l.tail {
		return errors.New("insertion is out of list range")
	} else if !l.In_list(n) {
		return errors.New("the node is not on the list")
	}
	
	new_node := New_node(elem, n.next, n, l)
	n.next.prev = new_node
	n.next = new_node

	return nil
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

	return n.Elem, nil
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

    return n.Elem, nil
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
		if n.Elem == elem {
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

// Moves the n node to after mark node
func (l *List) Move_after(n *node, mark *node) {
	if n == mark || n == l.head || n == l.tail || 
		mark == l.tail || !l.In_list(n) || !l.In_list(mark) {
		return
	}

	n.prev.next = n.next
	n.next.prev = mark.prev
	
	n.next = mark.next
	n.prev = mark

	mark.next.prev = n
	mark.next = n
}

// Moves the n node to before mark node
func (l *List) Move_before(n *node, mark *node) {
	if n == mark || n == l.head || n == l.tail ||
	   	mark == l.head || !l.In_list(n) || !l.In_list(mark) {
		return
	}

	n.prev.next = n.next
	n.next.prev = mark.prev

	n.next = mark
	n.prev = mark.prev

	mark.prev.next = n
	mark.prev = n
}

// Output list
func (l *List) Print_list() {

	for n := l.Begin(); n != l.tail; n = n.next {
		fmt.Printf("%v ", n.Elem)
	}
	fmt.Println()
}
