package main

import (
	"errors"
	"fmt"
)

type element interface {
	~int | ~int8 | ~int16 | ~int32 | ~int64 | 
	~uint | ~uint8 | ~uint16 | ~uint32 | ~uint64 |
	~float32 | ~float64 | ~string
}

type vector[T element] struct {
	arr []T
	size uint
	max_size uint
}

/* Creates an empty vector */
func Create_vector[T element]() *vector[T] {
	return &vector[T] {arr: make([]T, 10), size: 0, max_size: 10}
}

/* Creates a vector with specified size and default values */
func Create_vector_size[T element](length uint) *vector[T] {
	return &vector[T] {arr: make([]T, length, length * 2), size: length, max_size: length * 2}
}

/* Creates a vector with specified size and filled with the given element */
func Create_vector_elem[T element](length uint, elem T) *vector[T] {
	vect := &vector[T] {
		arr: make([]T, length * 2),
		size: length,
		max_size: length * 2,
	}

	for i := 0; i < int(vect.size); i++ {
		vect.arr[i] = elem
	}

	return vect
}

/* Creates a copy of another vector */
func Create_vector_copy[T element](v *vector[T]) *vector[T] {
	vect := &vector[T] {
		arr: make([]T, v.size, v.max_size),
		size: v.size,
		max_size: v.max_size,
	}
	copy(vect.arr, v.arr)
	
	return vect
}


/* Copies another vector's contents into this one */
func (v *vector[T]) Copy_vector(other *vector[T]) {
	v.arr = make([]T, other.size, other.max_size)
	copy(v.arr, other.arr)

	v.size = other.size
	v.max_size = other.max_size
}


/* Private function to double the vector size if it is full */
func check_realloc[T element] (v *vector[T]) {

	if v.size == v.max_size {
		v.max_size = v.max_size * 2
		new_arr := make([]T, v.max_size)
		copy(new_arr, v.arr)
		v.arr = new_arr
	}
}


/* Insets an element to the end of the vector */
func (v *vector[T]) Push_back(elem T) {
	check_realloc(v)
	v.arr[v.size] = elem
	v.size++
}

/* Insets an element to the begining of the vector */
func (v *vector[T]) Push_front(elem T) {
	check_realloc(v)
	
	temp := make([]T, v.size + 1, v.max_size)
	copy(temp[1:], v.arr)
	temp[0] = elem

	v.arr = temp
	v.size++
}

/* Removes the last element of the vector */
func (v *vector[T]) Pop_back() (T, error) {
	if v.Empty() {
		return *new(T), errors.New("vector is empty")
	}

	elem := v.arr[v.size-1]
	v.size--
	return elem, nil
}

/* Removes the first element of the vector */
func (v *vector[T]) Pop_front() (T, error) {
	if v.Empty() {
		return *new(T), errors.New("vector is empty")
	}

	elem := v.arr[0]
	v.arr = v.arr[1:v.size]
	v.size--
	return elem, nil
}

func (v *vector[T]) Erase(start uint, end uint) error {
	if start >= v.size || end > v.size || end < start {
		return errors.New("indexes out of range")
	}

	v.arr = append(v.arr[:start], v.arr[end:]...)
	v.size -= end - start
	return nil
}


/* Assigns elem to the vector at the given index */
func (v *vector[T]) Assign_at(elem T, index uint) (error) {
	if index >= v.size {
		return errors.New("index out of range")
	}

	v.arr[index] = elem
	return nil
}


/* Getters */
func (v *vector[T]) Size() uint {
	return v.size
}

func (v *vector[T]) Capacity() uint {
	return v.max_size
}

func (v *vector[T]) Empty() bool {
	return (v.size == 0)
}

func (v *vector[T]) At(index uint) (T, error) {
	if index >= v.size{
		return *new(T), errors.New("index out of range")
	}

	return v.arr[index], nil
}


/* Non-return functions */
func (v *vector[T]) Clear() {
	v.size = 0
	v.max_size = 10
	v.arr = make([]T, 10)
}

func (v *vector[T]) Print_vector() {
	for i := 0; i < int(v.size); i++ {
		fmt.Printf("%v ", v.arr[i])
	}
	fmt.Println()
}
