#include <stdlib.h>
#include <time.h> 
#include <string> 
#include <iostream> 
#include <algorithm> 
#include <queue> 
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
		Node(T item)
		{
			this->item = item;
			height = 1;
			left = NULL;
			right = NULL;
		}
		void setHeight()
		{
			height = max((left == NULL) ? (0) : (left->height), (right == NULL) ? (0) : (right->height)) + 1;
		}
	};
	void del(const Node* root)
	{
		if (root == NULL) return;
		del(root->left);
		del(root->right);
		delete root;
	}
	Node* rotateRight(Node* node)
	{
		if (node->left != NULL) {
			Node* left = node->left;
			Node* leftRight = left->right;
			left->right = node;
			node->left = leftRight;
			node->setHeight();
			left->setHeight();
			return left;
		}
		return node;
	}
	Node* rotateLeft(Node* node)
	{
		if (node->right != NULL) 
		{
			Node* right = node->right;
			Node* rightLeft = right->left;
			right->left = node;
			node->right = rightLeft;
			node->setHeight();
			right->setHeight();
			return right;
		}
		return node;
	}
	Node* insert(Node* node, T item)
	{
		if (node == NULL) 
			return new Node(item);
		if (item <= node->item) 
			node->left = insert(node->left, item);
		else
			node->right = insert(node->right, item);
		
		// rebalance if necessary
		node->setHeight();
		long balance = ((node->left == NULL) ? (0) : (node->left->height)) - ((node->right == NULL) ? (0) : (node->right->height));
		if (balance > -2 && balance < 2)
			return node;
		if (balance > 1)
		{
			if (item <= node->left->item)
				return rotateRight(node);
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		if (item > node->right->item)
			return rotateLeft(node);
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	Node* findMax(Node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}
	Node* remove(T item, Node* node)
	{
		Node* temp;

		// Element not found
		if (node == NULL)
			return NULL;

		// Searching for element
		else if (item < node->item)
			node->left = remove(item, node->left);
		else if (item > node->item)
			node->right = remove(item, node->right);

		// Element found
		// With 2 children
		else if (node->left && node->right)
		{
			temp = findMax(node->left);
			node->item = temp->item;
			node->left = remove(node->item, node->left);
		}
		// With one or zero child
		else
		{
			temp = node;
			if (node->left == NULL)
				node = node->right;
			else if (node->right == NULL)
				node = node->left;
			delete temp;
		}
		if (node == NULL)
			return node;

		node->setHeight();
		long balance = ((node->left == NULL) ? (0) : (node->left->height)) - ((node->right == NULL) ? (0) : (node->right->height));
		if (balance > -2 && balance < 2)
			return node;
		if (balance > 1)
		{
			if (item <= node->left->item)
				return rotateRight(node);
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		if (item > node->right->item)
			return rotateLeft(node);
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	void print(Node* n) 
	{
		// get height first
		int h = n->height;

		// perform  level order traversal
		queue<Node*> queue;

		int level = 0;
		int SPACE = 6;
		int nodePrintLocation = 0;

		// special node for pushing when a node has no left or right child (assumption, say this node is a node with value Integer.MIN_VALUE)
		Node* special = new Node(INT_MIN);

		queue.push(n);
		queue.push(NULL);    // end of level 0
		while (!queue.empty())
		{
			n = queue.front();
			queue.pop();
			if (n == NULL) 
			{
				if (!queue.empty()) 
					queue.push(NULL);
				// start of new level
				cout << "\n";
				level++;
			}
			else 
			{
				nodePrintLocation = ((int)pow(2, h - level)) * SPACE;

				cout << getPrintLine(n, nodePrintLocation);

				if (level < h) {
					// only go till last level
					queue.push((n->left != NULL) ? n->left : special);
					queue.push((n->right != NULL) ? n->right : special);
				}
			}
		}
	}
	string getPrintLine(Node* n, int spaces)
	{
		string sb;

		if (n->item == INT_MIN) {
			// for child nodes, print spaces
			for (int i = 0; i < 2 * spaces; i++) {
				sb += " ";
			}

			return sb;
		}

		int i = 0;
		int to = spaces / 2;

		for (; i < to; i++) {
			sb += " ";
		}
		to += spaces / 2;
		char ch = ' ';
		if (n->left != NULL) {
			ch = '_';
		}
		for (; i < to; i++) {
			sb += ch;
		}

		string value = to_string(n->item);
		sb.append(value);

		to += spaces / 2;
		ch = ' ';
		if (n->right != NULL) {
			ch = '_';
		}
		for (i += value.length(); i < to; i++) {
			sb += ch;
		}

		to += spaces / 2;
		for (; i < to; i++) {
			sb += ' ';
		}

		return sb;
	}
	Node* root;
	Node* trailNode;
	int nodeCount;
public:
	AVLTree()
	{
		root = NULL;
		trailNode = NULL;
		nodeCount = 0;
	}
	~AVLTree()
	{
		del(root);
	}
	void insert(T item)
	{
		root = insert(root, item);
		nodeCount++;
	}
	void print() 
	{
		if (root == NULL)
			cout << "Empty" << endl;
		else 
			print(root);
		cout << endl;
	}
	void remove(T item) 
	{
		root = remove(item, root);
		nodeCount--;
	}
	int getNodeCount()
	{
		return nodeCount;
	}
};

int main()
{
	AVLTree<int> t;
	string input;

	// Try Any Example from the test
	cout << "Enter NA to stop insertion and deletion commands" << endl;

	while (1)
	{
		cout << "Element to insert: ";
		cin >> input;
		if (input == "NA")
			break;
		try 
		{
			t.insert(stoi(input));
			t.print();
		}
		catch(...)
		{
			cout << "Invalid input/command";
		}
		cout << endl;
	}

	while (1)
	{
		cout << "Element to delete: ";
		cin >> input;
		if (input == "NA")
			break;
		try 
		{
			t.remove(stoi(input));
			t.print();
			if (t.getNodeCount() == 0)
				return 0;
		}
		catch (...) 
		{
			cout << "Invalid input/command";
		}
		cout << endl;
	}

	return 0;
}