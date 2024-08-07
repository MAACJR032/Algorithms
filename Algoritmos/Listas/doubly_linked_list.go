package list

import (
	"errors"
	"fmt"
	"sync"
)

type node struct  {
	elem any
	next *node
	prev *node
}

func (n *node) Next() *node {
	if n == nil {
		return nil
	}
	return n.next
}

func (n *node) Prev() *node {
	if n == nil {
		return nil
	}
	return n.prev
}

type list struct {
	size uint
	head *node
	tail *node
}

// Constructors
func New_node(elem any, next *node, prev *node) *node {
	return &node {elem, next, prev}
}

// Returns a new empty list
func New_list() *list {
	l := list {
		size: 0,
		head: New_node(*new(any), nil, nil),
		tail: New_node(*new(any), nil, nil),
	}

	l.head.next = l.tail
	l.tail.prev = l.head

	return &l
}

// Checks if the specified node is in the list
func (l *list) In_list(n *node) bool {
	for i := l.Begin(); i != l.End(); i = i.next {
		if i == n {
			return true
		}
	}

	return false
}

func (l *list) in_list(n *node, result_chan chan<- bool, wg *sync.WaitGroup) {
	for i := l.Begin(); i != l.End(); i = i.next {
		if i == n {
			result_chan <- true
			wg.Done()
			return
		}
	}

	result_chan <- false
	wg.Done()
}

/* Getters */
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

/* Insertion functions */

// Inserts the element in the end of the list
func (l *list) Push_back(elem any) {
	n := New_node(elem, l.tail, l.tail.prev)

	n.prev.next = n
	l.tail.prev = n

	l.size++
}

// Inserts the other list in the end of this list
func (l *list) Push_back_list(other *list) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}
	
	l.End().prev.next = other.Begin()
	other.Begin().prev = l.End().prev

	l.tail.prev = other.End().prev
	other.End().prev.next = l.tail

	other.head.next = other.tail
	other.tail.prev = other.head

	return nil
}

// Inserts the element in the begining of the list
func (l *list) Push_front(elem any) {
	n := New_node(elem, l.head.next, l.head)

	n.next.prev = n
	l.head.next = n

	l.size++
}

// Inserts the other list in the begining of this list
func (l *list) Push_front_list(other *list) error {
	if other.size == 0 {
		return nil
	} else if other == nil {
		return errors.New("other list is nil")
	}

	l.Begin().prev = other.End().prev
	other.End().prev.next = l.Begin()

	l.head.next = other.Begin()
	other.Begin().prev = l.head

	other.head.next = other.tail
	other.tail.prev = other.head

	return nil
}

// Inserts the element after the specified node
func (l *list) Insert_after(elem any, n *node) {
	if n == l.tail {
		return
	} else if !l.In_list(n) {
		return
	}
	
	new_node := New_node(elem, n.next, n)
	n.next.prev = new_node
	n.next = new_node
}

// Inserts the element before the specified node
func (l *list) Insert_before(elem any, n *node) {
	if n == l.head {
		return
	} else if !l.In_list(n) {
		return
	}
	
	new_node := New_node(elem, n, n.prev)
	n.prev.next = new_node
	n.prev = new_node
}

/* Remove functions*/

// Removes the last element of the list
func (l *list) Pop_back() (any, error) {

	if l.Empty() {
		return *new(any), errors.New("list is empty")
	}
	
	elem := l.tail.prev.elem

	l.tail.prev = l.tail.prev.prev
	l.tail.prev.next = l.tail

	l.size--
	return elem, nil
}

// Removes the first node of the list
func (l *list) Pop_front() (any, error) {

    if l.Empty() {
        return *new(any), errors.New("list is empty")
    }

    val := l.head.next.elem

    l.head.next = l.head.next.next
    l.head.next.prev = l.head
    
	l.size--
    return val, nil
}

// Removes the specified node of the list
func (l *list) Pop_node(n *node) error {

	if n == l.head || n == l.tail {
		return errors.New("especified node is out of range")
	} else if n == nil {
		return errors.New("especified node is nil")
	} else if !l.In_list(n) {
		return nil
	}

	n.prev.next = n.next
	n.next.prev = n.prev
	l.size--

	return nil
}

// Removes all ocurrences of elem
func (l *list) Remove(elem any) {

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
func (l *list) Clear() {
	for l.size > 0 {
		l.Pop_front()
	}
}

/* Move functions */

// Moves the e node to after n node
func (l *list) Move_after(e *node, n *node) {

	if e == n || e == l.head || e == l.tail || n == l.tail {
		return
	}

	var wg sync.WaitGroup
	chan_result_e := make(chan bool, 1)
	chan_result_n := make(chan bool, 1)
	
	wg.Add(2)

	go l.in_list(e, chan_result_e, &wg)
	go l.in_list(n, chan_result_n, &wg)

	wg.Wait()
	close(chan_result_e)
	close(chan_result_n)

	result_e := <- chan_result_e
	result_n := <- chan_result_n

	if !result_e || !result_n {
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
func (l *list) Move_before(e *node, n *node) {

	if e == n || e == l.head || e == l.tail || n == l.head {
		return
	}

	var wg sync.WaitGroup
	chan_result_e := make(chan bool, 1)
	chan_result_n := make(chan bool, 1)
	
	wg.Add(2)

	go l.in_list(e, chan_result_e, &wg)
	go l.in_list(n, chan_result_n, &wg)

	wg.Wait()
	close(chan_result_e)
	close(chan_result_n)

	result_e := <- chan_result_e
	result_n := <- chan_result_n

	if !result_e || !result_n {
		fmt.Println("Num ta")
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
func (l *list) Print_list() {

	for n := l.Begin(); n != l.End(); n = n.next {
		fmt.Printf("%v ", n.elem)
	}
	fmt.Println()
}
