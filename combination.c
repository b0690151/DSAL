#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>

#define SWAP(x,y,t)((t) = (x); (x) = (y); (y) = (t))





typedef struct _treenode {
	int data;
	_treenode *parent;
	_treenode *left;
	_treenode *right;
} TREENODE, *PTREENODE;

inline void swap(int *first, int *second)
{
	int temp = *first;
	*first = *second;
	*second = temp;
}

static int count = 0;

void perm(int *ptr, int start, int end){ //list[i] ~ list[n] permutation
  int index;
  
  printf("enter s %d e %d\r\n",start,end);
  if(start == end){ //only one element and only one permutation, show result
    for (index = 0; index <= end; index++){
      printf("%d ", ptr[index]);
    }
    printf("\n");
  }
  else{ //start < end
      for(index = start; index <= end; index++){
        swap(&ptr[start], &ptr[index]); //every one be the first element
		if(start != index)
		{
			printf("swap %d %d\r\n",ptr[start],ptr[index]);
		}
        perm(ptr, start+1, end); 		//Do the remain permutation , list[i+1] ~ list[n] permutation
        swap(&ptr[start], &ptr[index]); //return to the original list
      }
  }
}


  
/* arr[]  ---> Input Array 
   data[] ---> Temporary array to store current combination 
   start & end ---> Staring and Ending indexes in arr[] 
   index  ---> Current index in data[] 
   r ---> Size of a combination to be printed */
void combinationUtil(int arr[], int data[], int start, int end, 
                     int index, int r) 
{
	printf("call S %d e %d i %d r %d\r\n",start,end,index,r);
    // Current combination is ready to be printed, print it 
    if (index == r) 
    { 
        for (int j=0; j<r; j++) 
            printf("%d ", data[j]); 
        printf("\n"); 
        return; 
    } 
  
    // replace index with all possible elements. The condition 
    // "end-i+1 >= r-index" makes sure that including one element 
    // at index will make a combination with remaining elements 
    // at remaining positions 
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        combinationUtil(arr, data, i+1, end, index+1, r); 
    } 
} 

// The main function that prints all combinations of size r 
// in arr[] of size n. This function mainly uses combinationUtil() 
void printCombination(int arr[], int n, int r) 
{ 
    // A temporary array to store all combination one by one 
    int data[r]; 
  
    // Print all combination using temprary array 'data[]' 
    combinationUtil(arr, data, 0, n-1, 0, r); 
} 

int main(void){
	srand (time(NULL));
	
	TREENODE tree;
	PTREENODE *ptree;
	
	int p[5] = {1,2,3,4,5};
	
	//perm(p, 0, 2);
	
	printCombination(p,3,2);
	
	return 0;
}

