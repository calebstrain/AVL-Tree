#include <algorithm>
#include <iostream>
#include "AVL.h"
#include <string>

template<class T>
AVLTree<T>::Node::Node(const T& item)
{
	this->T = T;
	height = 1;
	left = NULL;
	right = NULL;
}

template<class T>
void AVLTree<T>::Node::setHeight()
{
	height = max((left == NULL) ? (0) : (left->height), (right == NULL) ? (0) : (right->height)) + 1;
}

template<class T>
void AVLTree<T>::del(const Node* root)
{
	if (root == NULL) return;
	del(root->left);
	del(root->right);
	delete root;
}

template<class T>
void AVLTree<T>::print(const Node* root) const
{
	if (root == NULL) return;
	print(root->left);
	ocout << root->word << endl;
	print(root->right);
}

template<class T>
AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* node)
{
	rotationCount++;
	Node* left = node->left;
	Node* leftRight = left->right;

	left->right = node;
	node->left = leftRight;

	node->setHeight();
	left->setHeight();

	return left;
}

template<class T>
AVLTree<T>::Node* AVLTree:<T>:rotateLeft(Node* node)
{
	rotationCount++;
	Node* right = node->right;
	Node* rightLeft = right->left;

	right->left = node;
	node->right = rightLeft;

	node->setHeight();
	right->setHeight();

	return right;
}

template<class T>
AVLTree<T>::Node* AVLTree::insert(Node* node, const T& item)
{
	if (node == NULL)
		return new Node(item);
	if (word == node->item) {}
	if (word < node->item)
		node->left = insert(node->left, item);
	else if (item > node->item)
		node->right = insert(node->right, item);

	// rebalance if necessary

	node->setHeight();
	long balance = ((node->left == NULL) ? (0) : (node->left->height)) - ((node->right == NULL) ? (0) : (node->right->height));
	if (balance > -2 && balance < 2)
		return node;
	if (balance > 1)
	{
		if (word <= node->left->item)
			return rotateRight(node);
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	if (word > node->right->item)
		return rotateLeft(node);
	node->right = rotateRight(node->right);
	return rotateLeft(node);
}

template<class T>
AVLTree<T>::AVLTree()
{
	root = NULL;
}

template<class T>
AVLTree<T>::~AVLTree()
{
	del(root);
}

template<class T>
void AVLTree<T>::insert(const T item)
{
	root = insert(root, item);
}

template<class T>
void AVLTree<T>::print() const
{
	print(root);
}

template<class T>
int AVLTree<T>::getRotationCount()
{
	return rotationCount;
}
