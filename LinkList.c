#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>

#define MAX_SIZE 10

typedef struct LNode {
    int data;
    struct LNode *next;
} LNODE, *PLNODE;

typedef struct _linklist{
	int size;
	PLNODE head;
} LINKLIST, *PLINKLIST;

PLINKLIST createLinkList(void){
	PLINKLIST pList = (PLINKLIST) malloc(sizeof(LINKLIST));
	
	pList->size = 0;
	pList->head = NULL;
	printf("Create Linklist %x size %d\r\n", pList, pList->size);
	
	return pList;
}

void deleteLinkList(PLINKLIST pList){
	
	if(pList != NULL){
		printf("Delete Linklist %x size %d\r\n", pList, pList->size);
		PLNODE pNode = pList->head;
		while(pNode != NULL)
		{
			pNode = pNode->next;
			free(pList->head);
			
			pList->head = pNode;
		}
		free(pList);
	}
	else
	{
		printf("NULL\r\n");
	}
}

bool IsLinkListEmpty(PLINKLIST pList)
{
	return (pList->head == NULL);
}

int getLinkListLength(PLINKLIST pList)
{
	return (pList->size);
}

void addNode(PLINKLIST pList, int data)
{
	PLNODE pNode = (PLNODE) malloc(sizeof(LNODE));
	
	pNode->data = data;
	
	//Always add node in the front O(1);
	pNode->next = pList->head;
	pList->head = pNode;
	
	pList->size++;
	printf("Add Node %x data %3d  Link list size %d\r\n", pNode, pNode->data, pList->size);
}

void removeNode(PLINKLIST pList, int data)
{
	if(pList != NULL){
		PLNODE pNode = pList->head;
		PLNODE pPreviousNode = NULL;
		if(pNode->data == data)
		{
			printf("Remove Node %x data %3d from head\r\n",pNode, pNode->data);
			pList->head = pNode->next;
			free(pNode);
		}
		else
		{	
			
			do 
			{
				pPreviousNode = pNode;
				pNode = pNode->next;
				if(pNode->data == data)
				{
					printf("Remove Node %x data %3d in the list\r\n",pNode, pNode->data);
					pPreviousNode->next = pNode->next;
					free(pNode);
					break;
				}
			}while(pNode != NULL);
		}

	}
	else
	{
		printf("NULL\r\n");
	}
}

PLNODE searchNode(PLINKLIST pList, int data)
{
	if(pList != NULL){
		PLNODE pNode = pList->head;
		while(pNode != NULL)
		{
			if(pNode->data == data)
			{
				return pNode;
			}
			pNode = pNode->next;
		}
	}
	else
	{
		printf("NULL\r\n");
	}
	
	return NULL;
}

void listTravel(PLINKLIST pList)
{
	if(pList != NULL){
		PLNODE pNode = pList->head;
		while(pNode != NULL)
		{
			printf("Node %x data %d\r\n",pNode, pNode->data);
			pNode = pNode->next;
		}
	}
	else
	{
		printf("NULL\r\n");
	}
}

#if 0







int deQueue(PQUEUE pQueue)
{
	int data;
	if(!IsQueueEmpty(pQueue)){
		data = *(pQueue->BaseAdr + pQueue->readHeadptr);
		pQueue->readHeadptr = (pQueue->readHeadptr + 1) % pQueue->size;
		printf("Dequeue %3d out\r\n",data);
	}
	else
	{
		printf("Queue %x is empty\r\n",pQueue->BaseAdr);
	}

	
	return data;
}

void QueuePrint(PQUEUE pQueue)
{
	int offset = 0;
	for(int i = 0; i < getQueueLength(pQueue); i++){
		offset = (pQueue->readHeadptr + i) % pQueue->size;
		printf("%3d ", *(pQueue->BaseAdr + offset));
		
	}
	printf("\r\nQueue Length %d\r\n", getQueueLength(pQueue));
}





#endif

int main(void){
	srand (time(NULL));
	PLINKLIST pList = NULL;
	PLNODE pNode = NULL;
	int data[10];
	pList = createLinkList();

	for(int i = 0;  i < 8; i++){
		data[i] = rand() % 100;
	}
	

	for(int i = 0;  i < 8; i++){
		if((i % 2) == 0)
		{
			addNode(pList, data[i]);
		}
		else
		{
			addNode(pList, rand() % 100);
		}
	}
	

	
	listTravel(pList);

	for(int i = 0;  i < 8; i++){
		pNode = searchNode(pList, data[i]);
		if(pNode)
		{
			printf("found data %3d in the list at %x\r\n", data[i], pNode);
			removeNode(pList, data[i]);
			listTravel(pList);
		}else
		{
			printf("Not found data %3d in the list\r\n", data[i]);
		}
	}
	
	
	
#if 0



	for(int i = 0;  i < 12; i++){
		deQueue(pQueue);
	}
	
	QueuePrint(pQueue);

	for(int i = 0;  i < 10; i++){
		enQueue(pQueue, rand() % 100);
	}
	
	QueuePrint(pQueue);

	for(int i = 0;  i < 2; i++){
		deQueue(pQueue);
	}
	
	QueuePrint(pQueue);
	int push_count = rand() % 15;
	int pop_count = rand() % 15;
	int DoPush = 0;
	printf("push %d pop %d\r\n",push_count, pop_count);
	
	for(int i = 0; i < (push_count + pop_count); i++)
	{	
		printf("%d Round : ",i);
		DoPush = rand() % 2;
		
		if(push_count != 0 && DoPush)
		{
			enQueue(pQueue, rand() % 100);
			push_count--;
		}
		else{
			if(pop_count != 0)
			{
				deQueue(pQueue);
				pop_count--;
			}
		}
		
	}
	QueuePrint(pQueue);
#endif

	
	deleteLinkList(pList);
	
	return 0;
}

