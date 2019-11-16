#ifndef __AVLTREE_H__
#define __AVLTREE_H__

using namespace std;

template<class T>
class AVLTree
{
private:
	class Node
	{
	public:
		T item;
		unsigned long height;
		Node* left;
		Node* right;
		Node(const T& item);
		void setHeight();
	};

	void del(const Node* root);
	void print(const Node* root) const;
	Node* rotateRight(Node* node);
	Node* rotateLeft(Node* node);
	Node* insert(Node* node, const T& item);
	int rotationCount = 0;
	Node* root;
public:
	AVLTree();
	~AVLTree();
	void insert(const T& item);
	void print() const;
	int getRotationCount();
};

#endif
