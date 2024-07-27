package main

import ("fmt")

type node struct {
	elem int
	height int
	left *node
	right *node
}

func New_node(elem int, left *node, right *node) *node {
	return &node {elem, 0, left, right}
}

type AVL struct {
	root *node
	size uint
}

func Create_AVL_tree() *AVL {
	return &AVL {nil, 0}
}

func (tree *AVL) Root() *node {
	return tree.root
}

func (tree *AVL) Size() uint {
	return tree.size
}

func (t *AVL) insert(elem int) {
	if t.root == nil {
		t.root = New_node(elem, nil, nil)
		return
	}

	temp := t.root
	var aux *node

	for temp != nil {
		aux = temp

		if temp.elem > elem {
			temp = temp.left	
		} else {
			temp = temp.right
		}
	}

	n := New_node(elem, nil, nil)
	if aux.elem > elem {
		aux.left = n
	} else {
		aux.right = n
	}

	// n.height = 1 + max()
}

func (t *AVL) Inorder(root *node) {
	if root == nil {
		return
	}

	t.Inorder(root.left)
	fmt.Printf("%v ", root.elem)
	t.Inorder(root.right)
}
