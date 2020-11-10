#pragma once

#include"BSTNode.h"
#include<iostream>


template<typename T>
class BST{
public:
	BSTNode<T>* root;


	BST();
	BSTNode<T>* search(BSTNode<T>* root, T key);
	BSTNode<T>* iterative_search(BSTNode<T>* node, T key);
	BSTNode<T>* minimum(BSTNode<T>* root);
	BSTNode<T>* maximum(BSTNode<T>* root);
	BSTNode<T>* successor(BSTNode<T>* node);
	BSTNode<T>* insert(BSTNode<T>* &root, T key);
	void transplant(BSTNode<T>* root, BSTNode<T>* u, BSTNode<T>* v);
	void remove(BSTNode<T>* root, BSTNode<T>* z);
	void inorder(BSTNode<T>* root);
	void inorder_iterators(BSTNode<T>* root);

	//funkcje opakowuj¹ce:
	BSTNode<T>* search(T key);
	BSTNode<T>* iterative_search(T key);
	BSTNode<T>* minimum();
	BSTNode<T>* maximum();
	BSTNode<T>* insert(T key);
	void remove(BSTNode<T>* z);
	void inorder();
	
	//konstruktor kopiuj¹cy
	BST(const BST<T>& bst);


private:
	


};


template<typename T>
BST<T>::BST() {
	
}


template<typename T>
BST<T>::BST(const BST<T>& bst) {
	root = bst.root;
}


template<typename T>
BSTNode<T>* BST<T>::search(BSTNode<T>* root, T key) {
	if (root == nullptr || key == root->key) return root;

	if (key < root->key) {
		return search(root->left, key);
	}
	else {
		return search(root->right, key);
	}
}

template<typename T>
BSTNode<T>* BST<T>::iterative_search(BSTNode<T>* node, T key) {
	while ((key != node->key) && (node != nullptr)) {
		if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return node;
}

template<typename T>
BSTNode<T>* BST<T>::minimum(BSTNode<T>* root) {
	while (root->left != nullptr) {
		root = root->left;
	}
	return root;
}

template<typename T>
BSTNode<T>* BST<T>::maximum(BSTNode<T>* root) {
	while (root->right != nullptr) {
		root = root->right;
	}
	return root;
}

template<typename T>
BSTNode<T>* BST<T>::successor(BSTNode<T>* node) {
	if (node->right != nullptr) {
		return minimum(node->right);
	}
	auto y = node->parent;
	while ((y != nullptr) && (node == y->right)) {
		node = y;
		y = y->parent;
	}
}

template<typename T>
BSTNode<T>* BST<T>::insert(BSTNode<T>* &root, T key) {
		
	if (root == nullptr) {
		root = new BSTNode<T>(key);
		return root;
	}

	if (key < root->key) {
		BSTNode<T>* leftchild = insert(root->left, key);
		root->left = leftchild;
		leftchild->parent = root;
	}else if(key> root->key){
		BSTNode<T>* rightchild = insert(root->right, key);
		root->right = rightchild;
		rightchild->parent = root;
	}

	return root;
	
}

template<typename T>
void BST<T>::inorder(BSTNode<T>* root){
	if (root != nullptr) {
		inorder(root->left);
		std::cout << root->key << std::endl;
		inorder(root->right);
	}
}

template<typename T>
BSTNode<T>* BST<T>::search(T key)
{
	return search(root,key);
}

template<typename T>
BSTNode<T>* BST<T>::iterative_search(T key)
{
	return iterative_search(root,key);
}

template<typename T>
BSTNode<T>* BST<T>::minimum()
{
	return minimum(root);
}

template<typename T>
BSTNode<T>* BST<T>::maximum()
{
	return maximum(root);
}

template<typename T>
BSTNode<T>* BST<T>::insert(T key)
{
	return insert(root,key);
}

template<typename T>
void BST<T>::remove(BSTNode<T>* z){
	remove(root, z);
}

template<typename T>
void BST<T>::inorder() {
	inorder(root);
}



template<typename T>
void BST<T>::transplant(BSTNode<T>* root, BSTNode<T>* u, BSTNode<T>* v) {
	if (u->parent == nullptr) {
		root = v;
	}else if (u == u->parent->left){
		u->parent->left = v;
	}else {
		u->parent->right = v;
	}

	if (v != nullptr) {
		v->parent = u->parent;
	}
}

template<typename T>
void BST<T>::remove(BSTNode<T>* root, BSTNode<T>* z) {
	if (z->left == nullptr) {
		transplant(root, z, z->left);
	}else if (z->right == nullptr) {
		transplant(root, z, z->left);
	}else {
		BSTNode<T>* y = minimum(z->right);
		if (y->parent != z) {
			transplant(root, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(root, z, y);
		y->left = z->left;
		y->left->parent = y;
	}
	//delete z;
}