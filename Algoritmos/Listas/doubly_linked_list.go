/*

This Package implements a doubly linked list

To iterate over a list (where l is a *List):

for n := l.Begin(); n != l.End().next; n = n.Next() {
	// do something with n.Elem
}

*/

package list

import (
	"errors"
)

type node struct  {
	Elem any
	next *node
	prev *node
	list *List
}

// Returns a new and initialized node
func NewNode(elem any, next *node, prev *node, list *List) *node {
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
func NewList() *List {
	l := &List {
		size: 0,
		head: nil,
		tail: nil,
	}

	l.head = NewNode(nil, nil, nil, l)
	l.tail = NewNode(nil, nil, nil, l)
	
	l.head.next = l.tail
	l.tail.prev = l.head

	return l
}

// Checks if the node n is in the list
func (l *List) InList(n *node) bool {
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
func (l *List) PushBack(elem any) {
	n := NewNode(elem, l.tail, l.tail.prev, l)

	n.prev.next = n
	l.tail.prev = n
	l.size++
}

// Inserts the element in the begining of the list
func (l *List) PushFront(elem any) {
	n := NewNode(elem, l.head.next, l.head, l)

	n.next.prev = n
	l.head.next = n

	l.size++
}

// Inserts a copy of another list at the back of list l.
func (l *List) PushBackList(other *List) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}
	
	var n *node = other.Begin()
	for n != other.tail {
		l.PushBack(n.Elem)
		n = n.next
	}

	l.size += other.size
	return nil
}

// Inserts a copy of another list at the front of list l.
func (l *List) PushFrontList(other *List) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}
	
	var n *node = other.End()
	for n != other.head {
		l.PushFront(n.Elem)
		n = n.prev
	}

	l.size += other.size
	return nil
}

// Inserts a another list at the back of list l
// The other list becomes empty
func (l *List) PushBack_ClearList(other *List) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}

	// Update the list reference for nodes
	for n := other.head.next; n != other.tail; n = n.next {
		n.list = l
	}
	
	l.tail.prev.next = other.head.next
	other.head.next.prev = l.tail.prev

	l.tail.prev = other.tail.prev
	other.tail.prev.next = l.tail
	l.size += other.size
	
	// Empty the other list
	other.head.next = other.tail
	other.tail.prev = other.head
	other.size = 0

	return nil
}

// Inserts a another list at the front of list l
// The other list becomes empty
func (l *List) PushFront_ClearList(other *List) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}

	// Update the list reference for nodes
	for n := other.head.next; n != other.tail; n = n.next {
		n.list = l
	}
	
	l.head.next.prev = other.tail.prev
	other.tail.prev.next = l.head.next

	l.head.next = other.head.next
	other.head.next.prev = l.head
	l.size += other.size
	
	// Empty the other list
	other.head.next = other.tail
	other.tail.prev = other.head
	other.size = 0

	return nil
}

// Inserts the element after the specified node
func (l *List) InsertAfter(elem any, n *node) error {
	if n == l.tail {
		return errors.New("insertion is out of list range")
	} else if !l.InList(n) {
		return errors.New("the node is not on the list")
	}
	
	new_node := NewNode(elem, n.next, n, l)
	n.next.prev = new_node
	n.next = new_node

	return nil
}

// Inserts the element before the specified node
func (l *List) InsertBefore(elem any, n *node) error {
	if n == l.head {
		return errors.New("insertion is out of list range")
	} else if !l.InList(n) {
		return errors.New("the node is not on the list")
	}
	
	new_node := NewNode(elem, n, n.prev, l)
	n.prev.next = new_node
	n.prev = new_node

	return nil
}


// Removes the last element of the list
func (l *List) PopBack() (any, error) {
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
func (l *List) PopFront() (any, error) {

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
func (l *List) PopNode(n *node) (*node, error) {

	if n == l.head || n == l.tail {
		return nil, errors.New("node is out of range")
	} else if n == nil {
		return nil, errors.New("node is nil")
	} else if !l.InList(n) {
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
			l.PopNode(n.prev)
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
func (l *List) MoveAfter(n *node, mark *node) {
	if n == mark || n == l.head || n == l.tail || 
		mark == l.tail || !l.InList(n) || !l.InList(mark) {
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
func (l *List) MoveBefore(n *node, mark *node) {
	if n == mark || n == l.head || n == l.tail ||
	   	mark == l.head || !l.InList(n) || !l.InList(mark) {
		return
	}

	n.prev.next = n.next
	n.next.prev = mark.prev

	n.next = mark
	n.prev = mark.prev

	mark.prev.next = n
	mark.prev = n
}

// Moves the node n of the list to the back 
func (l *List) MoveToBack(n *node) {
	if n == l.head || n == l.tail || !l.InList(n) {
		return
	}

	n.next.prev = n.prev
	n.prev.next = n.next

	n.next = l.head.next
	n.prev = l.head

	l.head.next = n
	n.next.prev = n
}

// Moves the node n of the list to the front 
func (l *List) MoveToFront(n *node) {
	if n == l.head || n == l.tail || !l.InList(n) {
		return
	}

	n.next.prev = n.prev
	n.prev.next = n.next

	n.next = l.tail
	n.prev = l.tail.prev

	l.tail.prev.next = n
	l.tail.prev = n
}
