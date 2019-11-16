#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include <string>
#include <string.h>

using namespace std;

class AVLTree
{
private:
	class Node
	{
	public:
		string word;
		unsigned long height;
		Node* left;
		Node* right;
		Node(const string& word);
		void setHeight();
	};

	void del(const Node* root);
	void print(ostream& out, const Node* root) const;
	Node* rotateRight(Node* node);
	Node* rotateLeft(Node* node);
	Node* insert(Node* node, const string& word);
	int rotationCount = 0;
	Node* root;
public:
	AVLTree();
	~AVLTree();
	void insert(const string& word);
	void print() const;
	void print(ostream & ofs);
	int getRotationCount();
};

#endif