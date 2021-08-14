#include <math.h>		/* pow */
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, srand, rand  */
#include <time.h>       /* time */
#include <string.h>    /* memset */

#define MAX_SLOT (10)
#define MAX_NUM  (100)

typedef struct element HashTableEntry;
typedef HashTableEntry *pHashTableEntry;
struct element
{
	int key;
	int data;
	pHashTableEntry next;
};


int hashfunction(int data)
{
	if(data >= 0)
	{
		return data % MAX_SLOT;
	}
	else
	{
		data ^= ~0;
		data += 1;
		return data % MAX_SLOT;
	}
	
}

inline void setHashTableEntry(pHashTableEntry entry, int key, int data, pHashTableEntry next)
{
	entry->key = key;
	entry->data = data;
	entry->next = next;
}


void insertHashEntry(pHashTableEntry *pHashTable, int key, int data)
{
	int index = hashfunction(data);
	
	pHashTableEntry hashEntry = (pHashTableEntry) malloc(sizeof(HashTableEntry));
	
	if(pHashTable[index] == NULL)
	{
		setHashTableEntry(hashEntry, key, data, NULL);
		pHashTable[index] = hashEntry;
		//printf("1 pHashTable[%d] = %x\r\n", index, hashEntry);
	}
	else
	{
		
		
		setHashTableEntry(hashEntry, key, data, pHashTable[index]);
		pHashTable[index] = hashEntry;
		//printf("2 pHashTable[%d] = %x\r\n", index, pHashTable[index]);
	}
}


pHashTableEntry SearchHashEntry(pHashTableEntry *pHashTable, int data)
{
	int index = hashfunction(data);
	
	pHashTableEntry hashEntry = NULL;
	
	if(pHashTable[index] != NULL)
	{
		hashEntry = pHashTable[index];
		while(hashEntry != NULL)
		{
			if(hashEntry->data != data)
			{
				hashEntry = hashEntry->next;
			}
			else
			{
				printf("found (k, v)=(%2d,%2d) at slot %d entry %x \r\n", hashEntry->key, hashEntry->data, index, hashEntry);
				return hashEntry;
			}
		}
		
		if(pHashTable[index] != NULL)
		{
			printf("2 data %2d not found\r\n",data);
		}
	}
	else
	{
		printf("1 data %2d not found\r\n",data);
	}
	
	return hashEntry;
}


void DisplayHashTable(pHashTableEntry *pHashTable)
{
	pHashTableEntry hashEntry = NULL;
	
	for(int i = 0; i < MAX_SLOT; i++)
	{
		printf("S%d ", i);
		hashEntry = pHashTable[i];
		while(hashEntry != NULL)
		{
			printf("(k, v)=(%2d,%2d) ", hashEntry->key, hashEntry->data);
			hashEntry = hashEntry->next;
		}
		printf("\r\n");
	}
}


void DeleteHashEntry(pHashTableEntry *pHashTable, int data)
{
	int index = hashfunction(data);
	
	pHashTableEntry hashEntry = pHashTable[index];
	pHashTableEntry PreviousEntry = NULL;
	
	if(hashEntry != NULL)
	{
		if(hashEntry->data == data)
		{
			printf("Remove (k, v)=(%2d,%2d) from pHashTable[%d] head\r\n",hashEntry->key, hashEntry->data, index);
			pHashTable[index] = pHashTable[index]->next;
			free(hashEntry);
		}
		else
		{	
			do 
			{
				PreviousEntry = hashEntry;
				hashEntry = hashEntry->next;
				if(hashEntry != NULL)
				{
					if(hashEntry->data == data)
					{
						printf("Remove (k, v)=(%2d,%2d) from pHashTable[%d]\r\n",hashEntry->key, hashEntry->data, index);
						PreviousEntry->next = hashEntry->next;
						free(hashEntry);
						break;
					}
				}

			}while(hashEntry != NULL);
			
			if(hashEntry == NULL)
			{
				printf("1 data %2d not found\r\n",data);
			}
		}
	}
	

}


void DeleteHashTable(pHashTableEntry *pHashTable)
{
	pHashTableEntry hashEntry = NULL;
	pHashTableEntry PreviousEntry = NULL;
	
	if(pHashTable != NULL)
	{
		for(int i = 0; i < MAX_SLOT; i++)
		{
			hashEntry = pHashTable[i];
			while(hashEntry != NULL)
			{
				PreviousEntry = hashEntry;
				hashEntry = hashEntry->next;
				free(PreviousEntry);
			}
		}
		
		free(pHashTable);
	}
}


int main(void)
{
	srand (time(NULL));
	
	pHashTableEntry *hashTable = (pHashTableEntry *) malloc(sizeof(pHashTableEntry) * MAX_SLOT);
	memset((void*)hashTable, 0, sizeof(pHashTableEntry) * MAX_SLOT);
#if 0
	int data[ MAX_SLOT*2] ={0};
	

	for(int i =  0; i < MAX_SLOT*2; i++)
	{
		data[i] = rand() % MAX_NUM;
		insertHashEntry(hashTable, i, data[i]);
	}


	for(int i =  0; i < MAX_SLOT*2; i++)
	{
		if((i % 2) == 0)
		{
			SearchHashEntry(hashTable,  (rand() % MAX_NUM));
		}
		else
		{
			SearchHashEntry(hashTable,  data[i]);
		}
	}


	DisplayHashTable(hashTable);



	for(int i =  0; i < MAX_SLOT*2; i++)
	{
		if((i % 2) == 0)
		{
			DeleteHashEntry(hashTable,  (rand() % MAX_NUM));
		}
		else
		{
			DeleteHashEntry(hashTable,  data[i]);
		}
	}
#endif

	int twosum[5] ={-1,-2,-3,-4,-5};
	int k = -8;
	
	printf("%d\r\n",twosum[0]);

	for(int i =  0; i < 5; i++)
	{
		insertHashEntry(hashTable, i, twosum[i]);
	}

	DisplayHashTable(hashTable);

	pHashTableEntry foundEntry;

	for(int i = 0; i < 5; i++)
	{
		foundEntry = NULL;
		
		
		foundEntry = SearchHashEntry(hashTable, k - twosum[i]);
		
		
		if(foundEntry && (foundEntry->key != i))
		{
			break;
		}
	}


	DeleteHashTable(hashTable);

	return 0;
}