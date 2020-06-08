
#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0


/*
Question 1: Write a function to see if the trees have 
the same structure (but potentially different values). 
*/
// TreeNode node type
typedef struct TreeNode 
{
	int value;           //value
	struct TreeNode* left;    //pointer to left child of the tree
	struct TreeNode* right;   //pointer to right child of the tree
}TreeNode;


// New TreeNode function to easily populate with values on main 
TreeNode* leaf(int data)
{
	TreeNode* leaf = (TreeNode*)malloc(sizeof(TreeNode));
	leaf->value = data;
	leaf->left = NULL;
	leaf->right = NULL;

	return(leaf);
}

// function to check isomorphic trees
int isomorphicCheck(TreeNode* tree1, TreeNode* tree2)
{

	if (tree1 == NULL && tree2 == NULL) // if both tree roots are null tree is empty but isomo vrphic
		return 1;

	if (tree1 == NULL || tree2 == NULL) // if either one of the roots is NULL then there will be no isomorphism
		return 0;

	if (tree1->value != tree2->value) // if the values at the root (root.val) are not the same not isomorphic?
		return 0;

	//if
	(isomorphicCheck(tree1->left, tree2->left) && isomorphicCheck(tree1->right, tree2->right) || // same structure and values
	(isomorphicCheck(tree1->right, tree2->left) && isomorphicCheck(tree1->left, tree2->right))); //same structure different values
	//return 1;
}

/*
Question 2: Write a function to see if the tree is a binary search tree.
*/

// new node allocation  
int newNode(int value)
{
	TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
	new_node->value = value;
	new_node->right = NULL;
	new_node->left = NULL;

	return new_node;
}

int nodeInit(TreeNode* node, int value)
{
	if (node == NULL)
	{
		return newNode(value);
	}
	else
	{
		if (node->value < value)
		{
			node->left = nodeInit(node->left, value);
		}
		else
		{
			node->right = nodeInit(node->right, value);
		}
	}
	return node;
}

// leftward traveral until null element is found (left child is null) to find min element
int findMinimum(TreeNode* root)
{
	if (root == NULL)  // found max stop
	{
		return root;
	}
	while (root->left)
	{
		root = root->left;
	}
	return root;
}
// rightward traveral until null element is found (right child is null) to find max element
int findMaximum(TreeNode* root)
{
	if (root == NULL) // found min so stop
	{
		return root;
	}
	while (root->right)
	{
		root = root->right;
	}
	return root;
}

// function to check conditions of is BinarySearchTree are met
int isBinarySearchTree(TreeNode* node)
{
	if (node == NULL) // base case
	{
		return 1;
	}

	if (findMinimum(node->right) < node->value)  // minimum conditional check
	{
		return 0;
	}

	if (findMaximum(node->left) > node->value)  // maximum conditional check
	{
		return 0;
	}

	if (isBinarySearchTree(node->left) == 0)    // recursive check left subtree value to ensure conditional child <parent
	{
		return 0;
	}

	if (isBinarySearchTree(node->right) == 0)  // recursivve check right subtree value to ensure conditional parent < child
	{
		return 0;
	}

	else
	{
		return 1;
	}
}


/*
Question 3: Given an array representation of a min heap
and create a remove min which removes the minimum value from the min-heap
*/

typedef struct Heap {
	int* array;
	int capacity;   // actual size of the memory
	int size;       //number of elements that are in use

}Heap;

// heap allocation and initialization function
int heapInit(int capacity)
{
	Heap* min_heap = (Heap*)malloc(sizeof(Heap));
	min_heap->array = (int*)malloc(sizeof(int));
	min_heap->size = 0;
	min_heap->capacity = capacity;
	return min_heap;
}

//function to print elements of the heap
void printHeap(Heap* heap)
{
	printf("The values of the Heap are as follows:\n");
	for (int i = 0; i < heap->size; i++)
	{
		printf("%d\t ", heap->array[i]);
	}
	printf("\n");
}
int parent_element(int i) // parent index position
{
	int parent;
	parent = (i - 1) / 2;
	return parent;
}

int left_child_element(int i) // child left index position
{
	int left_child;
	left_child = (2 * i + 1);
	return left_child;
}

int right_child(int i) // child right index postion
{
	int right_child;
	right_child = (2 * i + 2);
	return right_child;
}

void heapInsert(Heap* heap, int element)
{
	heap->size++;
	heap->array[heap->size - 1] = element;
	int curr = heap->size - 1; // element swaping 
	while (curr > 0 && heap->array[parent_element(curr)] > heap->array[curr]) //swap element with parent if  parent <= children 
	{

		int temp = heap->array[parent_element(curr)]; // Swap
		heap->array[parent_element(curr)] = heap->array[curr];
		heap->array[curr] = temp;
		curr = parent_element(curr); // index actualization
	}
}

// Heap sort implemtation to ensure min heap conditions met
int heapSort(Heap* heap, int index_position)
{
	if (heap->size <= 1)
	{
		return 0; // base case
	}

	int smallest_element = index_position; // set smallest element as index position [0]
	int left_element = left_child_element(index_position);
	int right_element = right_child(index_position);

	if (left_element < heap->size && heap->array[left_element] < heap->array[index_position]) // if left child < smallest, leftchild = smallest
	{
		smallest_element = left_element;
	}

	if (right_element < heap->size && heap->array[right_element] < heap->array[smallest_element])// if rightchild < smallest, rightchild = smallest
	{
		smallest_element = right_element;
	}
	if (smallest_element != index_position)
	{
		int temp = heap->array[index_position];
		heap->array[index_position] = heap->array[smallest_element];
		heap->array[smallest_element] = temp;
		heap = heapSort(heap, smallest_element); // recursive case to ensure min heap property met on all subtrees
	}
	return 0;
}

void removeMinHeap(Heap* heap_min)
{
	if (heap_min->size == 0 || heap_min == NULL) //base case
	{
		return;
	}
	int size = heap_min->size;
	int last_element = heap_min->array[size - 1];
	heap_min->array[0] = last_element; //  root updated with the last element value
	heap_min->size--; // heap size reduction via element removal
	size--;
	heap_min = heapSort(heap_min, 0); // funciton call to maintain parent < child property
}

int main()
{
	/*
	Question 1 main:
	*/
	printf("**********QUESTION 1 ***************\n");
	// level 0 of tree 1
	TreeNode* tree1 = leaf(1);  // root
	// level 1 of tree 1
	tree1->left = leaf(2);	//root.left
	tree1->right = leaf(3); //root.right
	// level 2 of tree 1
	tree1->right->right = leaf(4); // root.right.right
	tree1->right->left = leaf(5); // root.right.left
	tree1->left->right = leaf(6); //root.left.right

	// level 0 of tree 2
	TreeNode* tree2 = leaf(1); //root
	// level 1 of tree 2
	tree2->left = leaf(2); // root.left
	tree2->right = leaf(3);	// root.right
	// level 2 of tree 2
	tree2->right->right = leaf(4);	// root.right.right
	tree2->right->left = leaf(5); // root.right.left
	tree2->left->right = leaf(6); // root.left

	// level 0 of tree 3
	TreeNode* tree3 = leaf(1);
	// level 1 of tree 3
	tree3->left = leaf(2);
	tree3->right = leaf(5);
	// level 2 of tree 3
	tree3->right->right = leaf(8);
	tree3->right->left = leaf(4);

	if (isomorphicCheck(tree1, tree2) )//== 1)
	{
		printf("Tree 1 and tree 2 are indeed isomorphic.\n");
	}
	else
	{
		printf("Tree 1 and tree 2 are not isomorphic.\n");
	}
	
	if (isomorphicCheck(tree2, tree3)) // == 1)
	{
		printf("Tree 2 and tree 3 are indeed isomorphic.\n");
	}
	else
	{
		printf("Tree 2 and tree 3 are not isomorphic.\n");
	}
		
	if (isomorphicCheck(tree1, tree3))//== 1)
	{
		printf("Tree 1 and tree 3 are indeed isomorphic.\n");
	}
	else
	{
		printf("Tree 1 and tree 3 are not isomorphic.\n");
	}
	
	/*
	Question 2 main:
	*/
	printf("\n**********QUESTION 2 ***************\n");
	TreeNode* tree = NULL;
	tree = nodeInit(tree, 10);
	tree = nodeInit(tree, 5);
	tree = nodeInit(tree, 7);
	tree = nodeInit(tree, 3);
	tree = nodeInit(tree, 15);
	if (isBinarySearchTree(tree) == 1)
	{
		printf("The tree is a BST.");
	}
	else
	{
		printf("The Tree is not a BST");
	}

	/*
	Question 3 main:
	*/
	printf("\n**********QUESTION 3 ***************\n");
	Heap* heap_min = heapInit(4); // initialization with 4 elments

	heapInsert(heap_min, 6);
	heapInsert(heap_min, 27);
	heapInsert(heap_min, 19);
	heapInsert(heap_min, 84);
	printHeap(heap_min);
	removeMinHeap(heap_min); // function call to delete min
	removeMinHeap(heap_min); // function call to delete min
	removeMinHeap(heap_min); // function call to delete min
	removeMinHeap(heap_min); // function call to delete min
	printHeap(heap_min);
	heapInsert(heap_min, 7);
	heapInsert(heap_min, 20);
	heapInsert(heap_min, 19);
	heapInsert(heap_min, 69);
	printHeap(heap_min);
	removeMinHeap(heap_min); // function call to delete min
	printHeap(heap_min);




	return 0;
}
