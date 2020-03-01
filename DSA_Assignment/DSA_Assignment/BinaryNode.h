// BinaryNode.h

typedef int ItemType;

struct BinaryNode
{
	ItemType   item;	// data item
	BinaryNode *left;	// pointer pointing to left subtree
	BinaryNode *right;	// pointer pointing to right subtree
	int height = 0;

	BinaryNode() { item = -1; left = NULL; right = NULL; };
};
