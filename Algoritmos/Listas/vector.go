package main

import (
	"errors"
	"fmt"
)

type vector struct {
	arr []int
	size uint
	max_size uint
}

/* Creates an empty vector */
func Create_vector() *vector {
	return &vector {arr: make([]int, 10), size: 0, max_size: 10}
}

/* Creates a vector with specified size and default values */
func Create_vector_size(length uint) *vector {
	return &vector {arr: make([]int, length, length * 2), size: length, max_size: length * 2}
}

/* Creates a vector with specified size and filled with the given element */
func Create_vector_elem(length uint, elem int) *vector {
	vect := &vector {
		arr: make([]int, length * 2),
		size: length,
		max_size: length * 2,
	}

	for i := 0; i < int(vect.size); i++ {
		vect.arr[i] = elem
	}

	return vect
}

/* Creates a copy of another vector */
func Create_vector_copy(v *vector) *vector {
	vect := &vector{
		arr: make([]int, v.size, v.max_size),
		size: v.size,
		max_size: v.max_size,
	}
	copy(vect.arr, v.arr)
	
	return vect
}


/* Copies another vector's contents into this one */
func (v *vector) Copy_vector(other *vector) {
	v.arr = make([]int, other.size, other.max_size)
	copy(v.arr, other.arr)

	v.size = other.size
	v.max_size = other.max_size
}


/* Private function to double the vector size if it is full */
func check_realloc(v *vector) {
	if v.size == v.max_size {
		v.max_size = v.max_size * 2
		new_arr := make([]int, v.max_size)
		copy(new_arr, v.arr)
		v.arr = new_arr
	}
}


/* Insets an element to the end of the vector */
func (v *vector) Push_back(elem int) {
	check_realloc(v)
	v.arr[v.size] = elem
	v.size++
}

/* Insets an element to the begining of the vector */
func (v *vector) Push_front(elem int) {
	check_realloc(v)
	temp := make([]int, v.size + 1, v.max_size)
	
	copy(temp[1:], v.arr)
	temp[0] = elem

	v.arr = temp
	v.size++
}

/* Removes the last element of the vector */
func (v *vector) Pop_back() (int, error) {
	if v.Empty() {
		return -1, errors.New("vector is empty")
	}

	elem := v.arr[v.size-1]
	v.size--
	return elem, nil
}

/* Removes the first element of the vector */
func (v *vector) Pop_front() (int, error) {
	if v.Empty() {
		return -1, errors.New("vector is empty")
	}

	elem := v.arr[0]
	v.arr = v.arr[1:v.size]
	v.size--
	return elem, nil
}

func (v *vector) Erase(start uint, end uint) error {
	if start >= v.size || end > v.size || end < start {
		return errors.New("indexes out of range")
	}

	v.arr = append(v.arr[:start], v.arr[end:]...)
	v.size -= end - start
	return nil
}


/* Assigns elem to the vector at the given index */
func (v *vector) Assign_at(elem int, index uint) (error) {
	if index >= v.size {
		return errors.New("index out of range")
	}

	v.arr[index] = elem
	return nil
}

/* Getters */
func (v *vector) Size() uint {
	return v.size
}

func (v *vector) Capacity() uint {
	return v.max_size
}

func (v *vector) Empty() bool {
	return (v.size == 0)
}

func (v *vector) At(index uint) (int, error) {
	if index >= v.size{
		return 0, errors.New("index out of range")
	}

	return v.arr[index], nil
}


/* Non-return functions */
func (v *vector) Clear() {
	v.size = 0
	v.max_size = 10
	v.arr = make([]int, 10)
}

func (v *vector) Print_vector() {
	for i := 0; i < int(v.size); i++ {
		fmt.Printf("%d ", v.arr[i])
	}
	fmt.Println()
}
