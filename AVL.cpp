#include <algorithm>
#include <iostream>
#include "AVL.h"
#include <string>

AVLTree::Node::Node(const string& word)
{
	this->word = word;
	height = 1;
	left = NULL;
	right = NULL;
}
void AVLTree::Node::setHeight()
{
	height = max((left == NULL) ? (0) : (left->height), (right == NULL) ? (0) : (right->height)) + 1;
}

void AVLTree::del(const Node* root)
{
	if (root == NULL) return;
	del(root->left);
	del(root->right);
	delete root;
}
void AVLTree::print(ostream& ofs, const Node* root) const
{
	if (root == NULL) return;
	print(ofs, root->left);
	ofs << root->word; ofs << endl;
	print(ofs, root->right);
}
AVLTree::Node* AVLTree::rotateRight(Node* node)
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
AVLTree::Node* AVLTree::rotateLeft(Node* node)
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
AVLTree::Node* AVLTree::insert(Node* node, const string& word)
{
	// insert the new node

	if (node == NULL)
		return new Node(word);
	if (word == node->word) {}
	if (word < node->word)
		node->left = insert(node->left, word);
	else if (word > node->word)
		node->right = insert(node->right, word);

	// rebalance if necessary

	node->setHeight();
	long balance = ((node->left == NULL) ? (0) : (node->left->height)) - ((node->right == NULL) ? (0) : (node->right->height));
	if (balance > -2 && balance < 2)
		return node;
	if (balance > 1)
	{
		if (word <= node->left->word)
			return rotateRight(node);
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	if (word > node->right->word)
		return rotateLeft(node);
	node->right = rotateRight(node->right);
	return rotateLeft(node);
}

AVLTree::AVLTree()
{
	root = NULL;
}
AVLTree::~AVLTree()
{
	del(root);
}
void AVLTree::insert(const string& word)
{
	root = insert(root, word);
}
void AVLTree::print() const
{
	//print(root);
}
void AVLTree::print(ostream& ofs)
{
	print(ofs, root);
}
int AVLTree::getRotationCount()
{
	return rotationCount;
}