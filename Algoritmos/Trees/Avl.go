package main

import ("fmt")

// Node structure
type node struct {
	elem int
	height int
	left *node
	right *node
}

func New_node(elem int, left *node, right *node) *node {
	return &node {elem, 0, left, right}
}

// AVL structure
type AVL struct {
	root *node
	size uint
}

func Create_AVL_tree() *AVL {
	return &AVL {nil, 0}
}

// Getters
func (tree *AVL) Root() *node {
	return tree.root
}

func (tree *AVL) Size() uint {
	return tree.size
}

func height(rt *node) int {
	if rt == nil {
		return -1
	}
	
	return 1 + max(height(rt.left), height(rt.right))
}

// Rotations
func right_rotate(rt *node) *node {
	l := rt.left
	lr := l.right

	l.right = rt
	rt.left = lr

	rt.height = 1 + max(height(rt.left), height(rt.right))
	l.height = 1 + max(height(l.left), height(l.right))

	return l
}

func left_rotate(rt *node) *node {
	r := rt.right
	rl := r.left

	r.left = rt
	rt.right = rl

	rt.height = 1 + max(height(rt.left), height(rt.right))
	r.height = 1 + max(height(r.left), height(r.right))

	return r
}

func get_balance(root *node) int {
	if root == nil {
		return 0
	}

	return (height(root.left) - height(root.right))
}

func insert_help(root *node, elem int) *node {
	if root == nil {
		return New_node(elem, nil, nil)
	}

	if (root.elem > elem) {
		root.left = insert_help(root.left, elem);
	} else {
		root.right = insert_help(root.right, elem);
	}	
	
	root.height = 1 + max(height(root.left), height(root.right))
	balance := get_balance(root);

	if (balance < -1) && (elem >= root.right.elem) {
		return left_rotate(root);
	}
	if (balance > 1) && (elem < root.left.elem) {
		return right_rotate(root);
	}
	if (balance > 1) && (elem >= root.left.elem) {
		root.left = left_rotate(root.left);
		return right_rotate(root);
	}
	if (balance < -1) && (elem < root.right.elem) {
		root.right = left_rotate(root.right);
		return left_rotate(root);
	}

	return root;
}

func (t *AVL) Insert(elem int) {
	t.root = insert_help(t.root, elem)
	t.size++
}

// Traverses
func (t *AVL) Preorder(root *node) {
	if root == nil {
		return
	}

	fmt.Printf("%v ", root.elem)
	t.Preorder(root.left)
	t.Preorder(root.right)
}

func (t *AVL) Inorder(root *node) {
	if root == nil {
		return
	}

	t.Inorder(root.left)
	fmt.Printf("%v ", root.elem)
	t.Inorder(root.right)
}

func (t *AVL) Posorder(root *node) {
	if root == nil {
		return
	}

	t.Posorder(root.left)
	t.Posorder(root.right)
	fmt.Printf("%v ", root.elem)
}
