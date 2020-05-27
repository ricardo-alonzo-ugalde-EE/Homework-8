
#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

// TreeNode node type
typedef struct TreeNode 
{
	int val;           //value
	struct TreeNode* left;    //pointer to left child of the tree
	struct TreeNode* right;   //pointer to right child of the tree
}TreeNode;


// New TreeNode function to easily populate with values on main 
TreeNode* newnode(int data)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->val = data;
	node->left = NULL;
	node->right = NULL;

	return(node);
}

// function to check isomorphic trees
bool isomorphicCheck(TreeNode* tree1, TreeNode* tree2)
{

	if (tree1 == NULL && tree2 == NULL) // if both tree roots are null tree is empty but isomo vrphic
		return 1;

	if (tree1 == NULL || tree2 == NULL) // if either one of the roots is NULL then there will be no isomorphism
		return 0;

	if (tree1->val != tree2->val) // if the values at the root (root.val) are not the same not isomorphic?
		return 0;

	if (isomorphicCheck(tree1->left, tree2->left) && isomorphicCheck(tree1->right, tree2->right)) // same structure and values
		return 1;

	if (isomorphicCheck(tree1->right, tree2->left) && isomorphicCheck(tree1->left, tree2->right)); //same structure different values
		return 1;
}

int main()
{
	// level 0 of tree 1
	TreeNode* tree1 = newnode(1);  // root
	// level 1 of tree 1
	tree1->left = newnode(2);	//root.left
	tree1->right = newnode(3); //root.right
	// level 2 of tree 1
	tree1->right->right = newnode(4); // root.right.right
	tree1->right->left = newnode(5); // root.right.left
	tree1->left->right = newnode(6); //root.left.right

	// level 0 of tree 2
	TreeNode* tree2 = newnode(1);
	// level 1 of tree 2
	tree2->left = newnode(2); // root.left
	tree2->right = newnode(3);	// root.right
	// level 2 of tree 2
	tree2->right->right = newnode(4);	// root.right.right
	tree2->right->left = newnode(5); // root.right.left
	tree2->left->right = newnode(65); // root.left

	// level 0 of tree 3
	TreeNode* tree3 = newnode(1);
	// level 1 of tree 3
	tree3->left = newnode(2);
	tree3->right = newnode(5);
	// level 2 of tree 3
	tree3->right->right = newnode(8);
	tree3->right->left = newnode(4);



	if (isomorphicCheck(tree1, tree2) == 1)
		printf("Tree 1 and tree 2 are indeed isomorphic.\n");

	else
		printf("Tree 1 and tree 2 in fact not isomorphic.\n");

	if (isomorphicCheck(tree2, tree3) == 1)
		printf("Tree 2 and tree 3 are indeed isomorphic.\n");

	else
		printf("Tree 2 and tree 3 in fact not isomorphic.\n");




	return 0;
}
