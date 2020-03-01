// BST.cpp

#include "stdafx.h"
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
#define MAX_Q_SIZE 500
using namespace std;

#include <cstddef>  // for NULL
#include <new>      // for bad_alloc
#include "BST.h"

#define max(x,y) ((x > y)? x:y)

// constructor
BST::BST()
{
	root = NULL;
}

// search an item in the binary search tree
BinaryNode* BST::search(ItemType target)
{
	if (root != NULL)
		cout << "root";
	else
		cout << "There is no data added";
	return search(root, target);
}

BinaryNode* BST::search(BinaryNode* t, ItemType target)
{
	if (t == NULL)	// item not found
		return NULL;
	else
	{
		if (t->item == target)	// item found
			return t;
		else
		if (target < t->item)	// search in left subtree
		{
			cout << " L";
			return search(t->left, target);
		}
		else // search in right subtree
		{
			cout << " R";
			return search(t->right, target);
		}
	}
}

// compute the height of the binary search tree
int BST::getHeight()
{
	return getHeight(root);
}

int BST::getHeight(BinaryNode* t)
{
	int h = 0;
	if (t != NULL)
	{
		int leftHeight = getHeight(t->left);
		int rightHeight = getHeight(t->right);
		int max_height = max(leftHeight, rightHeight);
		h = max_height + 1;
	}
	return h;
}

int BST::diff(BinaryNode * t)
{
	int leftHeight = getHeight(t->left);
	int rightHeight = getHeight(t->right);
	int bal = leftHeight - rightHeight;
	return bal;
}


BinaryNode* BST::rightright(BinaryNode* parent)
{
	BinaryNode * t;
	t = parent->right;
	parent->right = t->left;
	t->left = parent;
	return t;
}


BinaryNode* BST::leftleft(BinaryNode *parent)
{
	BinaryNode *t;
	t = parent->left;
	parent->left = t->right;
	t->right = parent;
	return t;
}


BinaryNode* BST::leftright(BinaryNode *parent)
{
	BinaryNode *t;
	t = parent->left;
	parent->left = rightright(t);
	return leftleft(parent);
}


BinaryNode*  BST::rightleft(BinaryNode *parent)
{
	BinaryNode *t;
	t = parent->right;
	parent->right = leftleft(t);
	return rightright(parent);
}

BinaryNode* BST::rebalance(BinaryNode* t)
{
	int bal = diff(t);
	if (bal > 1)
	{
		if (diff(t->left) > 0)
			t = leftleft(t);
		else
			t = leftright(t);
	}
	else if (bal < -1)
	{
		if (diff(t->right) > 0)
			t = rightleft(t);
		else
			t = rightright(t);
	}
	return t;
}
BinaryNode* BST::check(ItemType target)
{
	if (root != NULL)
	return check(root, target);
}

BinaryNode* BST::check(BinaryNode* t, ItemType target)
{
	if (t == NULL)	// item not found
		return NULL;
	else
	{
		if (t->item == target)	// item found
			return t;
		else
			if (target < t->item)	// search in left subtree
				return check(t->left, target);
			else // search in right subtree
				return check(t->right, target);
	}
}
// insert an item to the binary search tree
void BST::insert(ItemType item)
{
	insert(root, item);
}

void BST::insert(BinaryNode* &t, ItemType item)
{
	if (t == NULL)
	{
		BinaryNode *newNode = new BinaryNode;
		newNode->item = item;
		newNode->left = NULL;
		newNode->right = NULL;
		t = newNode;
	}
	else if(check(item) == NULL)
	{
		if (item < t->item)
		{
			insert(t->left, item);  // insert in left subtree
			t = rebalance(t);
		}
		else
		{
			insert(t->right, item); // insert in right subtree
			t = rebalance(t);
		}
	}
	else if (check(item) != NULL)
	{
		cout << "The number already exist in the BST";
		cout << endl;
	}
}

// delete an item from the binary search tree
void BST::remove(ItemType target)
{
	remove(root, target);
}

void BST::remove(BinaryNode* &t, ItemType target)
{
	// search for the node to be deleted
	
	BinaryNode* current = t;
	BinaryNode* parent = NULL;
	bool isLeftChild = false;
	bool found = false;
	while ( (!found) && (current != NULL) )
	{
		if (target == current->item)
		{
			found = true;
		}
		else
		{
			parent = current;
			if (target < current->item)
			{
				current = current->left;	// go to left subtree
				isLeftChild = true;
			}
			else
			{
				current = current->right;	// go to right subtree
			    isLeftChild = false;
			}
		}
	}

	if (found)
	{
		// -----------------------  case 1 : node is a leaf ------------------------
		if (current->left == NULL && current->right == NULL)
		{
			if (current == t)	// node to be deleted is a root
				t = NULL;
			else
				if (isLeftChild)
					parent->left = NULL;
				else
					parent->right = NULL;
		}
		else
		// -----------------------  case 2 : node has only 1 child  ----------------
		if (current->left == NULL)
		{
			if (isLeftChild)
				parent->left = current->right;
			else
				parent->right = current->right;;
		}
		else
		if (current->right == NULL)
		{
			if (isLeftChild)
				parent->left = current->left;
			else
				parent->right = current->left;;
		}
		else
		// -----------------------  case 3 : node has 2 children  ------------------
		{
			// find the successor ( rightmost child in the node’s left subtree)
			BinaryNode* successor = current->left;
			while (successor->right != NULL)
				successor = successor->right;
			// replace the node’s item with that of the successor
			int n = successor->item;
			// delete the successor (either case 1 or case 2)
			remove(t, n);
			// replace the node’s item with that of the successor
			current->item = n;
		}
		t = rebalance(t);
	}
	else
	{
		cout << "The number doesn't exist in the BST";
		cout << endl;
	}
}

// traverse the binary search tree in inorder
void BST::inorder()
{
	if ( isEmpty() )
		cout << "No item found" << endl;
	else
		inorder(root);
}

void BST::inorder(BinaryNode* t)
{
	if (t != NULL)
	{
		inorder(t->left);
		cout << t->item << endl;
		inorder(t->right);
	}
}
// traverse the binary search tree in preorder
void BST::preorder()
{
	if ( isEmpty() )
		cout << "No item found" << endl;
	else
		preorder(root);
}

void BST::preorder(BinaryNode* t)
{
	if (t != NULL)
	{
		cout << t->item << endl;
		preorder(t->left);
		preorder(t->right);
	}
}

// traverse the binary search tree in postorder
void BST::postorder()
{
	if ( isEmpty() )
		cout << "No item found" << endl;
	else
		postorder(root);
}

void BST::postorder(BinaryNode* t)
{
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		cout << t->item << endl;
	}
}

// count the number of nodes in the binary search tree
int BST::countNodes()
{
	return countNodes(root);
}

int BST::countNodes(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + countNodes(t->left) + countNodes(t->right);
}

// check if the binary search tree is empty
bool BST::isEmpty()
{
	return (root == NULL);
}

void BST::levelOrder(int target)
{
	levelOrder(root, target);
}

void BST::levelOrder(BinaryNode* t, int target) 
{
	int rear, front;
	struct BinaryNode **queue = createQueue(&front, &rear);
	struct BinaryNode *temp_node = t;
	int count = 0;
	while (temp_node)
	{
		count++;
		if (target == count)
		{
			cout << temp_node->item;
			break;
		}
		
		/*Enqueue left child */
		if (temp_node->left)
			enQueue(queue, &rear, temp_node->left);

		/*Enqueue right child */
		if (temp_node->right)
			enQueue(queue, &rear, temp_node->right);

		/*Dequeue node and make it temp_node*/
		temp_node = deQueue(queue, &front);
	}
}

BinaryNode** BST::createQueue(int *front, int *rear)
{
	BinaryNode** queue =
		(BinaryNode**)malloc(sizeof(BinaryNode*)*MAX_Q_SIZE);

	*front = *rear = 0;
	return queue;
}

void  BST::enQueue(BinaryNode **queue, int *rear, BinaryNode *new_node)
{
	queue[*rear] = new_node;
	(*rear)++;
}

BinaryNode* BST::deQueue(BinaryNode **queue, int *front)
{
	(*front)++;
	return queue[*front - 1];
}
BinaryNode* BST::newNode(int data)
{
	struct BinaryNode* node = (BinaryNode*)
		malloc(sizeof(BinaryNode));
	node->item = data;
	node->left = NULL;
	node->right = NULL;

	return(node);
}
string printLevel(BinaryNode *root, int level, string gap)
{
	if (level == 1) 
	{
		if (root == 0) 
		{
			return gap + "-" + gap;
		}
		stringstream out;
		out << root->item;
		return gap + out.str() + gap;
	}
	else if (level>1) {
		string leftStr = printLevel(root ? root->left : 0, level-1, gap);
		string rightStr = printLevel(root ? root->right : 0, level-1, gap);

		return leftStr + " " + rightStr;
	}
	else return "";
}
void BST::printLevelOrder(int depth)
{
	printLevelOrder(root, depth);
}
void BST::printLevelOrder(BinaryNode* root, int depth)
{
	for (int i = 1; i <= depth; i++) {
		string gap = "";
		for (int j = 0; j<pow(2, depth - i) - 1; j++) {
			gap += " ";
		}
		string levelNodes = printLevel(root, i, gap);
		cout << levelNodes << endl;
	}
}