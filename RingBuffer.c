#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>

#define MAX_SIZE 10

typedef struct _queue{
	int size;
	int *BaseAdr;
	int writeTailptr;
	int readHeadptr;
}QUEUE, *PQUEUE;

PQUEUE createRingQueue(int max_size){
	PQUEUE pQueue = (PQUEUE) malloc(sizeof(QUEUE));
	
	
	pQueue->size = max_size;
	pQueue->BaseAdr = (int *) malloc(sizeof(int) * max_size);
	pQueue->writeTailptr = 0;
	pQueue->readHeadptr  = 0;
	printf("Queue Create base %x size %d Tailptr %d, Headptr %d\r\n", pQueue->BaseAdr, pQueue->size, pQueue->writeTailptr, pQueue->readHeadptr);
	
	return pQueue;
}

void deleteRingQueue(PQUEUE pQueue){
	
	if(pQueue != NULL){
		printf("Queue delete base %x size %d Tailptr %d, Headptr %d\r\n", pQueue->BaseAdr, pQueue->size, pQueue->writeTailptr, pQueue->readHeadptr);
	
		if(pQueue->BaseAdr != NULL)
		{
			free(pQueue->BaseAdr);
		}
		free(pQueue);
	}
	else
	{
		printf("NULL\r\n");
	}
}


bool IsQueueEmpty(PQUEUE pQueue)
{
	return (pQueue->writeTailptr == pQueue->readHeadptr);
}

int IsQueueFull(PQUEUE pQueue)
{
	return (pQueue->readHeadptr == ((pQueue->writeTailptr + 1) % pQueue->size));
}

int getQueueLength(PQUEUE pQueue)
{
	if(pQueue->writeTailptr > pQueue->readHeadptr) 
	{
		return  pQueue->writeTailptr  -  pQueue->readHeadptr;
	}
	else
	{
		return  (pQueue->writeTailptr + pQueue->size  -  pQueue->readHeadptr) % pQueue->size;
	}
	
}

void enQueue(PQUEUE pQueue, int data)
{

	if(IsQueueFull(pQueue))	{
		printf("Queue %x is Full\r\n",pQueue->BaseAdr);
	}
	else
	{
		*(pQueue->BaseAdr + pQueue->writeTailptr) = data;
		pQueue->writeTailptr = (pQueue->writeTailptr + 1) % pQueue->size;
		printf("Enqueue %3d\r\n",data);
	}
}


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

#if 0



#endif

int main(void){
	srand (time(NULL));
	PQUEUE pQueue = NULL;
	
	pQueue = createRingQueue(MAX_SIZE);


	for(int i = 0;  i < 12; i++){
		enQueue(pQueue, rand() % 100);
	}
	
	QueuePrint(pQueue);

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
	
#if 1
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

	
	deleteRingQueue(pQueue);
	
	return 0;
}

