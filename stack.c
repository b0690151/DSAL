#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>

#define MAX_SIZE 10

typedef struct _stack{
	int size;
	int *BaseAdr;
	int top;
}STACK, *PSTACK;

PSTACK createStack(int max_size){
	PSTACK pStack = (PSTACK) malloc(sizeof(STACK));
	
	pStack->top = 0;
	pStack->size = max_size;
	pStack->BaseAdr = (int *) malloc(sizeof(int) * max_size);
	
	printf("Stack Create base %x size %d top %d\r\n", pStack->BaseAdr, pStack->size, pStack->top);
	
	return pStack;
}

void deleteStack(PSTACK pStack){
	
	if(pStack != NULL){
		printf("Stack delete base %x size %d top %d\r\n", pStack->BaseAdr, pStack->size, pStack->top);
		if(pStack->BaseAdr != NULL)
		{
			free(pStack->BaseAdr);
		}
		free(pStack);
	}
	else
	{
		printf("NULL\r\n");
	}
}

bool IsStackFull(PSTACK pStack)
{
	return (pStack->top == pStack->size);
}

bool IsStackEmpty(PSTACK pStack)
{
	return (pStack->top == 0);
}

void StackPush(PSTACK pStack, int data)
{

	if(IsStackFull(pStack))	{
		printf("Stack %x is Full\r\n",pStack->BaseAdr);
	}
	else
	{
		*(pStack->BaseAdr + pStack->top) = data;
		pStack->top++;
		printf("Push %3d in\r\n",data);
	}
}

int StackPop(PSTACK pStack)
{
	int data;
	if(!IsStackEmpty(pStack)){
		pStack->top--;
		data = *(pStack->BaseAdr + pStack->top);
		printf("Pop %3d out\r\n",data);
	}
	else
	{
		printf("Stack %x is empty\r\n",pStack->BaseAdr);
	}

	
	return data;
}

void StackPrint(PSTACK pStack)
{
	for(int i = 0; i < pStack->top; i++){
		printf("%3d ", *(pStack->BaseAdr + i));
		
	}
	printf("\r\n");
}

int main(void){
	srand (time(NULL));
	PSTACK pStack = NULL;
	
	pStack = createStack(MAX_SIZE);
	
	for(int i = 0;  i < 12; i++){
		StackPush(pStack, rand() % 100);
	}
	
	StackPrint(pStack);

	for(int i = 0;  i < 12; i++){
		StackPop(pStack);
	}
	
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
			StackPush(pStack, rand() % 100);
			push_count--;
		}
		else{
			if(pop_count != 0)
			{
				StackPop(pStack);
				pop_count--;
			}
		}
		
	}
	StackPrint(pStack);
	

	
	deleteStack(pStack);
	
	return 0;
}

