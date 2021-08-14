#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>


#define MAX_NUMBER 100
#define LENGTH     10
#define TEST_ROUND 1000
#define ASCENDING	(0x01)
#define DESCENDING	(0x02)

#define MIN_HEAP	(0x01)
#define MAX_HEAP	(0x02)

#define CASE_BEST	(0x01)
#define CASE_WORST  (0x02)
#define CASE_RANDOM (0)

typedef unsigned char (*CmpPtr_t)(int, int);

void generateCase(int length, int *arrat, int option, int type);
void generateRandomSequence(int length, int *ptr);
void print_array(int *ptr, int length);


inline void swap(int *first, int *second);
inline unsigned char compareA(int first, int second);
inline unsigned char compareD(int first, int second);
CmpPtr_t selOperation(int option);

void bubbleSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr);
void selectionSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr);
void insertionSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr);
void heapSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr);
void quickSort(int number[], int left, int right);
void quickSort2(int number[], int left, int right);
void mergeSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr);

void sort_heap(int *ptr,int length);
void sort_heap2(int *ptr,int length);

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main() {

	

	
	int numOfByte  = sizeof(int) * LENGTH;
	int *pSequence = (int*) malloc (numOfByte);
	int *buffer    = (int*) malloc (numOfByte);
	generateRandomSequence(LENGTH, pSequence);
	CmpPtr_t condition;
#if 0
	generateCase(LENGTH, pSequence, ASCENDING, CASE_BEST);
	//print_array(pSequence, LENGTH);
	//generateCase(LENGTH, pSequence, ASCENDING, CASE_WORST);
	//print_array(pSequence, LENGTH);
#endif

#if 0
	clock_t start,end;
	double dur;
	int exetime;
	
	condition = selOperation(ASCENDING);
	
	start = clock();

	for(exetime = TEST_ROUND; exetime > 0; exetime--){
		generateRandomSequence(LENGTH, buffer);
		//generateCase(LENGTH, pSequence, ASCENDING, CASE_BEST);
		quickSort(buffer, 0, LENGTH-1);		
	}
		
	//print_array(buffer, LENGTH);
	
	end = clock();
	
    dur = (double)(end - start);
    printf("Quick Sort Use Time:%f\n",(dur/CLOCKS_PER_SEC));

	start = clock();
	
	for(exetime = TEST_ROUND; exetime > 0; exetime--){
		generateRandomSequence(LENGTH, buffer);
		qsort(buffer, LENGTH, sizeof(int), compare);
	}
		
	//print_array(buffer, LENGTH);
	
	end = clock();
	
    dur = (double)(end - start);
    printf("qsort ---- Use Time:%f\n",(dur/CLOCKS_PER_SEC));
#endif


#if 1

	print_array(pSequence, LENGTH);

	memcpy((void *)buffer, (void *)pSequence, numOfByte);
	condition = selOperation(ASCENDING); 
	quickSort(buffer, 0, LENGTH-1);
	print_array(buffer, LENGTH);

	memcpy((void *)buffer, (void *)pSequence, numOfByte);
	condition = selOperation(ASCENDING); 
	quickSort2(buffer, 0, LENGTH-1);
	print_array(buffer, LENGTH);

	memcpy((void *)buffer, (void *)pSequence, numOfByte);
	condition = selOperation(ASCENDING); 
	//selectionSort(buffer, LENGTH, condition);
	qsort(buffer, LENGTH, sizeof(int), compare);
	print_array(buffer, LENGTH);

#endif


	free(pSequence);
	free(buffer);
	
    return 0;
}

void bubbleSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr)
{	
	int count = 0;

	for(int i = 0; i < length - 1; i++)
	{
		for(int j = i + 1; j < length; j++)
		{
			if(cmpfunc_ptr(ptr[i], ptr[j]))
			{
				swap(&ptr[i], &ptr[j]);
				count++;
			}
		}
	}
	printf("bubble swap count %d\n",count);
}

void selectionSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr)
{	
	int save_index;
	int count = 0;

	for(int i = 0; i < length - 1; i++)
	{
		save_index = i;
		for(int j = i+1; j < length; j++)
		{
			if(cmpfunc_ptr(ptr[save_index], ptr[j]))
			{
				save_index = j;
			}			
		}
		
		if(save_index != i){
			swap(&ptr[i], &ptr[save_index]);
			count++;
		}
	
	}
	
	printf("select swap count %d\n",count);
}

void insertionSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr)
{	
	int count = 0;
	int save_index;

	for(int i = 0; i < length; i++)
	{
		for(int j = i; j > 0; j--)
		{
			if(cmpfunc_ptr(ptr[j-1], ptr[j]))
			{
				swap(&ptr[j-1], &ptr[j]);
				count++;
			}	
		}


	}
	
	printf("insert swap count %d\n",count);
}

#if 1 // Quick Sort function  Lomuto partition scheme  has trouble when the sequence has been sort or all equal
int partition(int number[], int left, int right) { 
    int i = left; 
    int j;
#if 1  //Median-of-three  much better when sorted or reverse-sorted case
	int middle = (left + right) / 2; 
	if(number[middle] < number[left]) 
	{
		swap(&number[middle], &number[left]);  //make sure middle >= left
	}
	if(number[right] < number[left])
	{
		swap(&number[left], &number[right]); //make sure right >= left
	}
	if(number[middle] < number[right])       //make sure right >= middle
	{
		swap(&number[middle], &number[right]);  //if right > middle it means middle is median, move it to the rightmost
	}
	else
	{
		//the rightmost already the median value
	}
	
	//there for the middle is the Median of three
#else
	//always use right as pivot index
#endif
    for(j = left; j < right; j++) { 
        if(number[j] < number[right]) { 
			swap(&number[i], &number[j]); 
            i++;
        } 
    } 

    swap(&number[i], &number[right]); 

    return i; 
} 


void quickSort(int number[], int left, int right) { 
	//printf("left %d right %d --",left, right);
	//print_array(number, LENGTH);
	if(left < right) { 
        int q = partition(number, left, right); 
        quickSort(number, left, q-1); 
        quickSort(number, q+1, right); 
    } 
} 

void quickSort_iterative(int number[], int left, int right)
{
	
}

#endif




#if 1 //Hoare partition scheme
int partition2(int number[], int left, int right) { 

	int pivot = number[(left + right) / 2];

	while(left <= right)
	{

		while(number[left] < pivot)
		{
			left++;
		}
		while(number[right] > pivot)
		{
			right--;
		}
		if(left <= right)					
		{
			swap(&number[left], &number[right]); 
			left++;
			right--;
		}

	}
	//final round , the left is on the side >= pivot
    return left; 
} 

void quickSort2(int number[], int left, int right) { 
	//printf("left %d right %d --",left, right);
	//print_array(number, LENGTH);
	int q = partition2(number, left, right);

	if(left < right) { 
        quickSort2(number, left, q - 1);  //sort minor pivot side
	}
	if(q < right)
	{
		quickSort2(number, q, right); //sort >= pivot side
    } 

} 
#endif


#if 1 //Heap sort 1'based

void max_heapify(int arr[], int start, int end) {
    // 建立父節點指標和子節點指標
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { // 若子節點指標在範圍內才做比較
        if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
            son++;
        if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
            return;
        else { // 否則交換父子內容再繼續子節點和孫節點比较
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void min_heapify(int arr[], int start, int end) {
    // 建立父節點指標和子節點指標
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { // 若子節點指標在範圍內才做比較
        if (son + 1 <= end && arr[son] > arr[son + 1]) // 先比較兩個子節點大小，選擇最小的
            son++;
        if (arr[dad] < arr[son]) //如果父節點小於子節點代表調整完畢，直接跳出函數
            return;
        else { // 否則交換父子內容再繼續子節點和孫節點比较
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heapSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr)
{	

    int i;
    // 初始化，i從最後一個父節點開始調整
    for (i = length / 2 - 1; i >= 0; i--)
        max_heapify(ptr, i, length - 1);
    // 先將第一個元素和已排好元素前一位做交換，再重新調整，直到排序完畢
    for (i = length - 1; i > 0; i--) {
        swap(&ptr[0], &ptr[i]);
        max_heapify(ptr, 0, i - 1);
    }
}
#endif


#if 1 //Heap sort 0'based
//parent = floor[(i -1)/2]
//leftchild = 2*1 + 1
//rightchild = 2*i + 2
//index from zero
void heapify2(int *ptr, int parent_index, int length, CmpPtr_t cmpfunc_ptr)
{
	int child_index; 
	int check_index;  
	for(child_index = 2*parent_index+1; child_index < length; child_index = 2*parent_index+1)  //loop when child_index exists
	{
		check_index = child_index; //check from left child
		if((child_index + 1) < length) //if there is a right child
		{
			if(ptr[child_index] < ptr[child_index + 1]) //compare left and right child first
			{
				check_index = child_index + 1; //set check index to largest child 
			}
		}
		if(ptr[parent_index] < ptr[check_index]) //check parent and child relation
		{
			swap(&ptr[parent_index], &ptr[check_index]); //swap parent and child if need
		}
		else
		{
			break;
		}
		parent_index = check_index; //keep check the next child index
	}
}

void sort_heap2(int *ptr,int length)
{
    int i;
    for(i = length/2 - 1;i >= 0; i--){ //build first Max-heap
        heapify2(ptr,i,length, NULL);
    }
    for(i = 1; i < length; i++)		//Put the max item to latest index and heapify again and again in the remain node
    {
		swap(&ptr[0], &ptr[length - i]);
        heapify2(ptr, 0, length-i, NULL);
    }   
}

#endif


#if 1 //Merge Sort recursively  version
void merge(int* ptr, int* ptr_helper, int start, int middle, int end)
{
	for(int i = start; i <= end; i++) //Copy to temp buffer
	{
		ptr_helper[i] = ptr[i];
	}
	
	//spilt to two part
	int helperLeft = start;
	int helperRight = middle + 1;
	int current = start;
	
	while(helperLeft <= middle && helperRight <= end) //select the entry by order back
	{
		if(ptr_helper[helperLeft] <= ptr_helper[helperRight])
		{
			ptr[current] = ptr_helper[helperLeft];
			helperLeft++;
		}else{
			ptr[current] = ptr_helper[helperRight];
			helperRight++;
		}
		current++;
	}
	
	int remaining = middle - helperLeft;	//right remain already in there position
	for(int i = 0; i <= remaining; i++)
	{
		ptr[current + i] = ptr_helper[helperLeft + i];
	}
}

void _mergeSort(int* ptr, int* ptr_helper, int start, int end)
{
	if(start < end)
	{
		int middle = (start + end) / 2;
		_mergeSort(ptr, ptr_helper, start, middle);
		_mergeSort(ptr, ptr_helper, middle+1, end);
		merge(ptr, ptr_helper, start, middle,end);
	}
}

void mergeSort(int* ptr, int length, CmpPtr_t cmpfunc_ptr)
{	
	int *ptr_helper = (int*) malloc (length * sizeof(int));
	
	_mergeSort(ptr, ptr_helper, 0, length - 1);
	
	free(ptr_helper);
}

void mergeSort2(int* ptr, int length, CmpPtr_t cmpfunc_ptr)
{	
	int *ptr_helper = (int*) malloc (length * sizeof(int));
	
	int compare_entryCnt = 1;
	
	while(compare_entryCnt < length)
	{
		
		for(int i = 0; i < length; i += compare_entryCnt)
		{
			merge(ptr, ptr_helper, i, (i + compare_entryCnt)/2, i + compare_entryCnt);
		}
		
		compare_entryCnt *= 2;
	}
	
	free(ptr_helper);
}

#endif

#if 0 //Merge Sort itervation version

void merge2(int* ptr, int* ptr_helper, int length, int middle, int end)
{
	for(int i = start; i <= end; i++) //Copy to temp buffer
	{
		ptr_helper[i] = ptr[i];
	}
	
	//spilt to two part
	int helperLeft = start;
	int helperRight = middle + 1;
	int current = start;
	
	while(helperLeft <= middle && helperRight <= end) //select the entry by order back
	{
		if(ptr_helper[helperLeft] <= ptr_helper[helperRight])
		{
			ptr[current] = ptr_helper[helperLeft];
			helperLeft++;
		}else{
			ptr[current] = ptr_helper[helperRight];
			helperRight++;
		}
		current++;
	}
	
	int remaining = middle - helperLeft;	//right remain already in there position
	for(int i = 0; i <= remaining; i++)
	{
		ptr[current + i] = ptr_helper[helperLeft + i];
	}
}

void mergeSort2(int* ptr, int length)
{
	int s = 1;
	int *ptr_helper = (int*) malloc (length * sizeof(int));
	
	while(s < n)
	{
		mergePass(ptr, ptr_helper, length, s);
		
		s *= 2;
		
		mergePass(ptr, ptr_helper, length, s);
		
		s *= 2;
	}
	
	free(ptr_helper);
}
#endif


#if 1 //Radix Sort
void radixSort(int data[]) {
    int temp[10][10] = {0}; 
    int order[10] = {0}; 
    
    int n = 1; 
    while(n <= 10) { 
        
        int i;
        for(i = 0; i < 10; i++) { 				//put into different 10 bucket
            int lsd = ((data[i] / n) % 10); 
            temp[lsd][order[lsd]] = data[i]; 
            order[lsd]++; 
        } 
        
        // 重新排列
        int k = 0;
        for(i = 0; i < 10; i++) { 
            if(order[i] != 0)  {
                int j;
                for(j = 0; j < order[i]; j++, k++) { 
                    data[k] = temp[i][j]; 
                } 
            }
            order[i] = 0; 
        } 

        n *= 10; 
    }     
}

#endif

CmpPtr_t selOperation(int option)
{
	if(option & ASCENDING == ASCENDING)
	{
		return compareA;
	}
	else
	{
		return compareD;
	}	
}

inline unsigned char compareA(int first, int second)
{
	return (first > second) ? true : false;
}

inline unsigned char compareD(int first, int second)
{
	return (first < second) ? true : false;
}

inline void swap(int *first, int *second)
{
	int temp = *first;
	*first = *second;
	*second = temp;
}

/*!
	@param[in] length the length of rangom sequence
	@return the pointer to the random sequence
	@note the pointer should be free
*/
void generateRandomSequence(int length, int *array ){
    /* initialize random seed: */
		srand (time(NULL));
		for(int i = 0; i < length; i++)
		{
			array[i] = rand() % MAX_NUMBER;
		}
}

void generateCase(int length, int *array, int option, int type)
{
	if((type == CASE_BEST && option == ASCENDING) || (type == CASE_WORST && option == DESCENDING) )
	{
		for(int i = 0; i < length; i++)
		{
			array[i] = i;
		}
	}
	
	if((type == CASE_WORST && option == ASCENDING) || (type == CASE_BEST && option == DESCENDING) )
	{
		for(int i = 0; i < length; i++)
		{
			array[i] = length - (i + 1);
		}
	}
}

/*!
	@param[in] length the length of rangom sequence
*/
void print_array(int *ptr, int length){
	
	for(int i = 0; i < length; i++){
		printf("%04d ",ptr[i]);
		if((i % 10) == 9)
		{
			printf("\r\n");
		}
	}
	printf("\r\n");
}

void compare(int *ptrA, int *ptrB, int length)
{	
	for(int i = 0; i < length; i++){
		if(ptrA[i] != ptrB[i])
		{
			printf("%03d, A %03d != B %03d", i, ptrA[i], ptrB[i]);
			break;
		}
	}
}