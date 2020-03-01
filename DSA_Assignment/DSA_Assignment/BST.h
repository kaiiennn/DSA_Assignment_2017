// BST.h

#include "BinaryNode.h"

typedef int ItemType;

class BST
{
  private:
	  BinaryNode* root;// root of the BST

  public:
	
    // constructor
	  BST();

	// search an item in the binary search tree
	BinaryNode* search(ItemType target);
	BinaryNode* search(BinaryNode* root, ItemType target);
	
	// compute the height of the binary search tree
	int getHeight();
	int getHeight(BinaryNode* t);
	int BST::diff(BinaryNode * t);

	BinaryNode* BST::rightright(BinaryNode* parent);
	BinaryNode* BST::leftleft(BinaryNode *parent);
	BinaryNode* BST::leftright(BinaryNode *parent);
	BinaryNode* BST::rightleft(BinaryNode *parent);
	BinaryNode* BST::rebalance(BinaryNode* t);

	BinaryNode* check(ItemType target);
	BinaryNode* check(BinaryNode* root, ItemType target);

	// insert an item to the binary search tree
	void insert(ItemType item);
	void BST::insert(BinaryNode* &t, ItemType item);

	// delete an item from the binary search tree
	void remove(ItemType target);
	void remove(BinaryNode* &root, ItemType target);

	// traverse the binary search tree in inorder
	void inorder();
	void inorder(BinaryNode* t);

	// traverse the binary search tree in preorder
	void preorder();
	void preorder(BinaryNode* t);

	// traverse the binary search tree in postorder
	void postorder();
	void postorder(BinaryNode* t);

	// count the number of nodes in the binary search tree
	int countNodes();
	int countNodes(BinaryNode* t);

	// check if the binary search tree is empty
	bool isEmpty();

	void BST::levelOrder(int target);
	void BST::levelOrder(BinaryNode* n, int target);

	BinaryNode** BST::createQueue(int *front, int *rear);
	void BST::enQueue(BinaryNode **queue, int *rear, BinaryNode *new_node);
	BinaryNode* BST::deQueue(BinaryNode **queue, int *front);
	BinaryNode* BST::newNode(int data);

	void BST::printLevelOrder(int depth);
	void BST::printLevelOrder(BinaryNode* root, int depth);
};
