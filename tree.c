#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>

#define MAX_SIZE 7
#define MAX_DATA 100

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


#if 1 //Queue Lib

typedef struct _queee
{
	int front;
	int rear;
	int size;
	int *ptr;
}QUEUE, *PQUEUE;

PQUEUE createQueue(int size)
{
	PQUEUE pQueue = (PQUEUE) malloc(sizeof(QUEUE));
	
	pQueue->front = 0;
	pQueue->rear  = 0;
	pQueue->size  = size;
	
	pQueue->ptr = (int *)malloc(sizeof(int) * size);
	
	return pQueue;
	
}

int isQueueEmpty(PQUEUE pQueue)
{
	return (pQueue->front == pQueue->rear);
}

int isQueueFull(PQUEUE pQueue)
{
	return (pQueue->front == ((pQueue->rear + 1) % pQueue->size));
}

int enQueue(PQUEUE pQueue, int data)
{
	int ans = 0;
	
	if(!isQueueFull(pQueue))
	{
		pQueue->ptr[pQueue->rear] = data; 
		pQueue->rear = (pQueue->rear + 1) % pQueue->size;
	}
	else
	{
		printf("Queue Full\r\n");
		ans = 1;
	}
	
	return ans;
}

int deQueue(PQUEUE pQueue, int *data)
{
	int ans = 0;
	
	if(!isQueueEmpty(pQueue))
	{
		*data = pQueue->ptr[pQueue->front]; 
		pQueue->front = (pQueue->front + 1) % pQueue->size;
	}
	else
	{
		printf("Queue Empty\r\n");
		ans = 1;
	}
	
	return ans;
}

void deleteQueue(PQUEUE pQueue)
{
	if(pQueue != NULL)
	{
		if(pQueue->ptr != NULL)
		{
			free(pQueue->ptr);
		}
		free(pQueue);
	}
}

void resizeQueue(PQUEUE pQueue, int size)
{
	if(pQueue != NULL)
	{
		if(pQueue->ptr != NULL)
		{
			pQueue->ptr = (int *) realloc(pQueue->ptr, sizeof(int)*size);
			pQueue->size = size;
		}
	}
}

void showQueue(PQUEUE pQueue)
{
	int temp = pQueue->front;
	while(temp != pQueue->rear)
	{
		printf("%2d ",pQueue->ptr[temp]);
		temp = (temp + 1) % pQueue->size;
	}
	
	printf("\r\n");
}

#endif



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

PTREE CreateTree(int size)
{
	PTREE pTree = (PTREE) malloc(sizeof(TREE));
	PTNODE pNode = NULL;
	PTNODE pCurrentNode = NULL;
	pTree->size = size;
	pTree->root = NULL;
	if(size){
		
		pNode = (PTNODE) malloc(sizeof(TNODE));
		setTreeNode(pNode, rand() % MAX_DATA, NULL, NULL, NULL);
		printf("Create Node %x data %3d\r\n", pNode, pNode->data);
		
		pTree->root = pNode;
		size--;
#if 1
		unsigned int *pQueue =(unsigned int *) malloc(sizeof(unsigned int) * size);

#endif
		for(int i = 0; i < size; i++)
		{
			pNode = (PTNODE) malloc(sizeof(TNODE));
			int head = 0;
			int tail = 0;
			pQueue[tail] = (unsigned int)pTree->root;
			tail++;
			// Do level order traversal until we find 
			// an empty place.  
			while(head != tail)
			{
				pCurrentNode = (PTNODE) pQueue[head];
				head++;
				
				if(pCurrentNode->left == NULL)
				{
					setTreeNode(pNode, rand() % MAX_DATA, pCurrentNode, NULL, NULL);
					printf("Create Node %x data %3d parent %x\r\n", pNode, pNode->data, pCurrentNode);
					pCurrentNode->left = pNode;
					break;
				}else
				{
					pQueue[tail] = (unsigned int)pCurrentNode->left;
					tail++;
				}
				
				if(pCurrentNode->right == NULL)
				{
					setTreeNode(pNode, rand() % MAX_DATA, pCurrentNode, NULL, NULL);
					printf("Create Node %x data %3d parent %x\r\n", pNode, pNode->data, pCurrentNode);
					pCurrentNode->right = pNode;
					break;
				}else
				{
					pQueue[tail] = (unsigned int)pCurrentNode->right;
					tail++;
				}
			}
		}
		free(pQueue);
	}
	
	printf("Create Tree %x size %3d\r\n", pTree, pTree->size);
	
	return pTree;
}


PTNODE BSTinsert(PTNODE node, int data) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(data); 
  
    /* Otherwise, recur down the tree */
    if (data < node->data)
	{
		 node->left  = BSTinsert(node->left, data); 
	}
	else //(data >= node->data) 
	{
		node->right = BSTinsert(node->right, data);    
	}
        
    /* return the (unchanged) node pointer */
    return node; 
} 



/*
Not BST tree method, just level order insertion
*/
void insertNode(PTREE pTree, int data)
{
	PTNODE pNode = newNode(data);
	PTNODE pTreeNode = NULL;
	PQUEUE pQueue = createQueue(pTree->size);
	enQueue(pQueue, (int)pTree->root);
	
	while(!isQueueEmpty(pQueue))
	{

		deQueue(pQueue, (int *)&pTreeNode);

		//printf("get QNode %x with data %x\r\n", pTreeNode, pTreeNode->data);

		if(pTreeNode->left)
		{
			enQueue(pQueue, (int)pTreeNode->left);
			//printf("push QNode %x in Queue\r\n", pTreeNode->left);
		}
		else
		{
			pNode->parent = pTreeNode;
			pTreeNode->left = pNode;
			pTree->size++;
			//printf("insert QNode %x with parent %x left\r\n", pNode, pTreeNode);
			break;
		}
		if(pTreeNode->right)
		{
			enQueue(pQueue, (int)pTreeNode->right);
			//printf("push QNode %x in Queue\r\n", pTreeNode->right);
		}
		else
		{
			pNode->parent = pTreeNode;
			pTreeNode->right = pNode;
			pTree->size++;
			//printf("insert QNode %x with parent %x right\r\n", pNode, pTreeNode);
			break;
		}

	}

	deleteQueue(pQueue);
}


PTREE CreateBSTree(int size)
{
	PTREE pTree = (PTREE) malloc(sizeof(TREE));
	PTNODE pNode = NULL;
	PTNODE pCurrentNode = NULL;
	pTree->size = size;
	pTree->root = NULL;
	
	if(size > 1)
	{
		pTree->root = BSTinsert(pTree->root, rand() %100) ;
		size--;
		
		while(size)
		{
			pNode = BSTinsert(pTree->root, rand() %100) ;
			size--;
		}
		
	}else if (size == 1)
	{
		pTree->root = BSTinsert(pTree->root, rand() %100) ;
	}
	
	printf("Create BST Tree %x size %3d\r\n", pTree, pTree->size);
	
	return pTree;
}


/*  This function traverses tree in post order to to delete each and every node of the tree */
void subDeleteTree(PTNODE pNode)  
{ 
    if (pNode == NULL) return; 
  
    /* first delete both subtrees */
    subDeleteTree(pNode->left); 
    subDeleteTree(pNode->right); 
    
    /* then delete the node */
    printf(" Deleting node %x: %3d\n", pNode, pNode->data); 
    free(pNode); 
}  

void DeleteTree(PTREE pTree)
{
	if(pTree){
		subDeleteTree(pTree->root);
		printf("Delete Tree %x size %3d\r\n", pTree, pTree->size);
		free(pTree);
	}
	else{
		printf("NULL tree\r\n");
	}
}


/*!
	traversal
*/

void inorder(PTNODE pNode)
{

	
	if(pNode)
	{
		inorder(pNode->left);
		printf(" %3d", pNode->data);
		inorder(pNode->right);
	}

}

void preorder(PTNODE pNode)
{
	
	if(pNode)
	{
		printf(" %3d", pNode->data);
		preorder(pNode->left);
		preorder(pNode->right);
	}
}

void postorder(PTNODE pNode)
{
	
	
	if(pNode)
	{
		postorder(pNode->left);
		postorder(pNode->right);
		printf(" %3d", pNode->data);
	}
	
}

void levelorder(PTREE pTree)
{
	int *queue = (int *) malloc(sizeof(TNODE) * pTree->size);
	PTNODE pNode;
	int tail = 0;
	int head = 0;
   if(pTree->root)
   {
     
     queue[tail] = (int) pTree->root; /* 根指針入隊 */
	 tail++;
	 //printf(" %x %d ", pTree->root, pTree->root->data);
	 while(head != tail)
	 {
		 pNode = (PTNODE) queue[head];
		 
		 printf(" %3d", pNode->data);
		 head++;
#if 1
		 if(pNode->left)
		 {
			 queue[tail] = (int) pNode->left;
			 tail++;
		 }
		 if(pNode->right)
		 {
			 queue[tail] = (int) pNode->right;
			 tail++;
		 }
#endif
	 }


     printf("\n");
   }
   
   free(queue);
}

PTNODE invertTree(PTNODE root){
    if(root)
    {
        PTNODE temp = root->left;
        root->left = root->right;
        root->right = temp;
        invertTree(root->left);
        invertTree(root->right);
    }
    return root;
}

int main(void){
	srand (time(NULL));
	
	PTREE pTree = NULL;
	
	pTree = CreateTree(MAX_SIZE);


#if 1
	printf("In   Order: ");
	inorder(pTree->root);
	printf("\r\n");
	
	printf("Pre  Order: ");
	preorder(pTree->root);
	printf("\r\n");
	
	printf("Post Order: ");
	postorder(pTree->root);
	printf("\r\n");

	printf("levelOrder: ");
	levelorder(pTree);
	printf("\r\n");
#endif

	invertTree(pTree->root);

#if 1
	printf("In   Order: ");
	inorder(pTree->root);
	printf("\r\n");
	
	printf("Pre  Order: ");
	preorder(pTree->root);
	printf("\r\n");
	
	printf("Post Order: ");
	postorder(pTree->root);
	printf("\r\n");

	printf("levelOrder: ");
	levelorder(pTree);
	printf("\r\n");
#endif

	DeleteTree(pTree);

	return 0;
}

