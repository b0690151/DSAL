#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>

#define MAX_SIZE 7
#define MAX_DATA 10

typedef struct _treenode {
    int data;
	struct _treenode *parent;
    struct _treenode *left;
	struct _treenode *right;
} TNODE, *PTNODE;

typedef struct _tree {
    int size;
	PTNODE root;
} TREE, *PTREE;

void setTreeNode(PTNODE pNode, int data, PTNODE parent, PTNODE left, PTNODE right)
{
	pNode->data = data;
	pNode->parent = parent;
	pNode->left = left;
	pNode->right = right;
	
}

PTNODE newNode(int data)
{
	PTNODE pNode = (PTNODE) malloc(sizeof(TNODE));
	setTreeNode(pNode, data, NULL, NULL, NULL);
	return pNode;
}

PTNODE searchBSTData(PTNODE pRoot, int data)
{
	PTNODE pNode = pRoot;
	
	while(pNode)
	{
		if(pNode->data > data)
		{
			pNode = pNode->left;
		}
		else if (pNode->data < data)
		{
			pNode = pNode->right;
		}
		else
		{
			break;
		}
	}
	
	return pNode;
}
