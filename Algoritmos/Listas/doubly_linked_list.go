/*

This Package implements a doubly linked list

To iterate over a list (where l is a *List[T]):

for n := l.Begin(); n != l.End().Next(); n = n.Next() {
	// do something with n.Elem
}

*/

package list

import (
	"errors"
)

type node[T any] struct  {
	Elem T
	next *node[T]
	prev *node[T]
	list *List[T]
}

// Returns a new and initialized node
func NewNode[T any](elem T, next *node[T], prev *node[T], list *List[T]) *node[T] {
	return &node[T] {elem, next, prev, list}
}

// Returns the next node or nil
func (n *node[T]) Next() *node[T] {
	if n == nil {
		return nil
	}
	return n.next
}

// Returns the previous node or nil
func (n *node[T]) Prev() *node[T] {
	if n == nil {
		return nil
	}
	return n.prev
}


type List[T any] struct {
	size uint
	head *node[T]
	tail *node[T]
}

// Returns a new list
func NewList[T any]() *List[T] {
	l := &List[T] {
		size: 0,
		head: nil,
		tail: nil,
	}

	l.head = NewNode(*new(T), nil, nil, l)
	l.tail = NewNode(*new(T), nil, nil, l)
	
	l.head.next = l.tail
	l.tail.prev = l.head

	return l
}

// Checks if the node n is in the list
func (l *List[T]) InList(n *node[T]) bool {
	return n.list == l
}

// Returns the first node of the list
func (l *List[T]) Begin() *node[T] {
	return l.head.next
}

// Returns the last node of the list
func (l *List[T]) End() *node[T] {
	return l.tail.prev
}

// Returns true if the list is empty, otherwise, it will return false
func (l *List[T]) Empty() bool {
	return l.head.next == l.tail 
}


// Inserts the element in the end of the list
func (l *List[T]) PushBack(elem T) {
	n := NewNode(elem, l.tail, l.tail.prev, l)

	n.prev.next = n
	l.tail.prev = n
	l.size++
}

// Inserts the element in the begining of the list
func (l *List[T]) PushFront(elem T) {
	n := NewNode(elem, l.head.next, l.head, l)

	n.next.prev = n
	l.head.next = n

	l.size++
}

// Inserts a copy of another list at the back of list l.
func (l *List[T]) PushBackList(other *List[T]) error {
	if other == nil {
		return errors.New("other list is nil")
	} else if other.size == 0 {
		return nil
	}
	
	var n *node[T] = other.Begin()
	for n != other.tail {
		l.PushBack(n.Elem)
		n = n.next
	}

	l.size += other.size
	return nil
}

// Inserts a copy of another list at the front of list l.
func (l *List[T]) PushFrontList(other *List[T]) error {
	if other == nil {
		return errors.New("other list is nil")
	} else if other.size == 0 {
		return nil
	}
	
	var n *node[T] = other.End()
	for n != other.head {
		l.PushFront(n.Elem)
		n = n.prev
	}

	l.size += other.size
	return nil
}

// Inserts a another list at the back of list l
// The other list becomes empty
func (l *List[T]) PushBack_ClearList(other *List[T]) error {
	if other == nil {
		return errors.New("other list is nil")
	} else if other.size == 0 {
		return nil
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
func (l *List[T]) PushFront_ClearList(other *List[T]) error {
	if other == nil {
		return errors.New("other list is nil")
	} else if other.size == 0 {
		return nil
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
func (l *List[T]) InsertAfter(elem T, n *node[T]) error {
	if n == nil {
		return errors.New("node is nil")
	} else if n == l.tail {
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
func (l *List[T]) InsertBefore(elem T, n *node[T]) error {
	if n == nil {
		return errors.New("node is nil")
	} else if n == l.head {
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
func (l *List[T]) PopBack() (T, error) {
	if l.Empty() {
		return *new(T), errors.New("list is empty")
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
func (l *List[T]) PopFront() (T, error) {
    if l.Empty() {
        return *new(T), errors.New("list is empty")
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
func (l *List[T]) PopNode(n *node[T]) (*node[T], error) {
	if n == nil {
		return nil, errors.New("node is nil")
	} else if n == l.head || n == l.tail {
		return nil, errors.New("node is out of range")
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

// Removes all ocurrences of elem using the provided comparison function
func (l *List[T]) Remove(elem T, compFunc func(T, T) bool) {
	for n := l.Begin(); n != l.End().next; {
		if compFunc(n.Elem, elem) {
			n = n.next
			l.PopNode(n.prev)
		} else {
			n = n.next
		}
	}
}

// Removes all the elements of the list
func (l *List[T]) Clear() {
	l.head.next = l.tail
	l.tail.prev = l.head
	l.size = 0
}

// Moves the n node to after mark node
func (l *List[T]) MoveAfter(n *node[T], mark *node[T]) {
	if n == nil || mark == nil || n == mark || n == l.head || n == l.tail || 
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
func (l *List[T]) MoveBefore(n *node[T], mark *node[T]) {
	if n == nil || mark == nil || n == mark || n == l.head || n == l.tail ||
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
func (l *List[T]) MoveToBack(n *node[T]) {
	if n == nil || n == l.head || n == l.tail || !l.InList(n) {
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
func (l *List[T]) MoveToFront(n *node[T]) {
	if n == nil || n == l.head || n == l.tail || !l.InList(n) {
		return
	}

	n.next.prev = n.prev
	n.prev.next = n.next

	n.next = l.tail
	n.prev = l.tail.prev

	l.tail.prev.next = n
	l.tail.prev = n
}

// Reverses the order of elements in the list
func (l *List[T]) Reverse() {
	if l.size <= 1 {
		return
	}

	n := l.head.next
	l.head.next = l.tail.prev
	l.tail.prev = n

	for ; n != l.tail; n = n.prev {
		n.next, n.prev = n.prev, n.next
	}
}
