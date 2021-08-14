#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

template<typename T>
class Vector
{
    private:
        T* ptr;
        int len;
        int capacity;
    public:
        class Iterator
        {
            private:
                T* iter;
            public:
                Iterator(T* = nullptr);
                void operator++(); //++Iterator
                void operator--(); //--Iterator
                void operator++(int); //Iterator++
                void operator--(int); //Iterator--
                bool operator==(Iterator);
                bool operator!=(Iterator);
                bool operator>(Iterator);
                bool operator<(Iterator);
                bool operator<=(Iterator);
                bool operator>=(Iterator);
                void operator=(Iterator);
                int operator-(Iterator);
                Iterator operator+(int);
                Iterator operator-(int);
                T& operator*();
        };
        Vector(int = 0);
        ~Vector();
        T Front();
        T Back();
        T& At(int);
        T& operator[](int);
        int Size();
        bool Empty();
        void Push_Back(T data);
        void Push_Back_Old(T);
        void Pop_Back();
        void Insert(Iterator, T);
        void Erase(Iterator);
        void Erase(Iterator,Iterator); //front close end open
        void Clear();
        void Reserve(int);
        void Resize(int);
        Iterator Begin();
        Iterator End();
};

//not class function
template<typename T>
typename Vector<T>::Iterator Find(Vector<T> v, T target){
    for(auto iter = v.Begin();iter!=v.End();iter++){
        if(*iter == target)
            return iter;
    }
    return v.End(); // not found
}

//not class function
template<typename T>
typename Vector<T>::Iterator Remove(Vector<T> v, T target){
    int counts = 0;
    for(auto iter = v.Begin();iter!=v.End();iter++){
        if(*iter == target)
            continue;
        *(v.Begin()+counts) = *iter;
        counts++;
    }
    for(auto iter = (v.Begin()+counts);iter!=v.End();iter++){
        *iter = target;
    }
    return v.Begin()+counts;
}

template<typename T>
Vector<T>::Vector(int length)
{
    if(length)
    {
        len = length;
        capacity = length;
        ptr = (T*) calloc(length,sizeof(T));
    }
    else
    {
        len = 0;
        capacity = 0;
        ptr = nullptr;
    }
}

template<typename T>
Vector<T>::~Vector()
{
    if(ptr)
    {
        free(ptr);
        ptr = nullptr;
        len = 0;
        capacity = 0;
    }
}

template<typename T>
T Vector<T>::Front()
{
    if(ptr)
    {
        return *ptr;
    }
}

template<typename T>
T Vector<T>::Back()
{
    if(ptr)
    {
        return *(ptr + len - 1);
    }
}

template<typename T>
T& Vector<T>::At(int index)
{
    if(ptr)
    {
        return *(ptr + index);
    }
}

template<typename T>
T& Vector<T>::operator[](int index)
{
    if(ptr)
    {
        return *(ptr + index);
    }
}

template<typename T>
int Vector<T>::Size()
{
    return len;
}

template<typename T>
bool Vector<T>::Empty()
{
    return (len == 0);
}

template<typename T>
void Vector<T>::Push_Back_Old(T data)
{
    len++;
    T *tmp = (T*) malloc(sizeof(T) * len);
    for(int i = 0; i < len - 1; i++)
    {
        *(tmp+i) = *(ptr+i);
    }
    
    *(tmp + len - 1) = data;
    free(ptr);
    ptr = tmp;
}

template<typename T>
void Vector<T>::Push_Back(T data){
    if(len == capacity){
        if(capacity == 0)
            Reserve(1);
        else
            Reserve(capacity * 2);
    }
    *(ptr+len) = data;
    len++;
}

template<typename T>
void Vector<T>::Pop_Back()
{
    if(Empty())
    {
        return;    
    }  
    else
    {
        len--;
    }
}

template<typename T>
void Vector<T>::Insert(Iterator iter2, T data)
{
    if(iter2 > End() || iter2 < Begin())
    {
        return;
    }
    else
    {
        if(len == capacity)
        {
            if(capacity == 0)
            {
                Reserve(1);
            }
            else
            {
                Reserve(capacity*2);
            }
        }
        auto temp = iter2;
        for(iter2 = End() - 1; iter2 >= temp; iter2--)
        {
            *(iter2+1) = *(iter2);
        }
        
         *(temp) = data;
        len++;
    }
}

template<typename T>
void Vector<T>::Erase(Iterator iter2)
{
    if(iter2 >= End() || iter2 < Begin())
    {
        return;
    }
    else
    {
        for(; iter2 < End(); iter2++)
        {
            *(iter2) = *(iter2 + 1);
        }
        len--;
    }
}

template<typename T>
void Vector<T>::Erase(Iterator start, Iterator finish){
    
    bool check = false;
    
    check = (Empty() || (finish >= End()) || (finish <= start) || (start < Begin()));
    
    if(check)
    {
        return;
    }
    else
    {
        auto temp = finish;
        for(; temp < End(); temp++)
        {
            *(temp  - (finish-start)) = *(temp);
        }
        len -= finish-start;
    }
    

}

template<typename T>
void Vector<T>::Clear()
{
    if(ptr)
    {
        free(ptr);
        ptr = nullptr;
        len = 0;
        capacity = 0;
    }   
}

template<typename T>
void Vector<T>::Reserve(int n){
    if(n < len)
    {
        return ;
    }
    else
    {
        capacity = n;
        T* tmp = (T*) malloc(sizeof(T)*capacity);
        for(int i=0;i<len;i++){
            *(tmp+i) = *(ptr+i);
        }
        free(ptr); 
        ptr = tmp;
    }
}  

template<typename T>
typename Vector<T>::Iterator Vector<T>::Begin(){
    Iterator result(ptr);
    //cout << "Begin " << ptr <<endl;
    return result;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::End(){
    Iterator result(ptr + len);
    //cout << "End " << (ptr + len) <<endl;
    return result;
}

template<typename T>
Vector<T>::Iterator::Iterator(T* pointer)
{
    iter = pointer;
}

template<typename T>
void Vector<T>::Iterator::operator++(){
    // ++Iterator
    iter++;
}

template<typename T>
void Vector<T>::Iterator::operator--(){
    // --Iterator
    iter--;
}

template<typename T>
void Vector<T>::Iterator::operator++(int){
    // Iterator++
    iter++;
}


template<typename T>
void Vector<T>::Iterator::operator--(int){
    // Iterator--
    iter--;
}

template<typename T>
bool Vector<T>::Iterator::operator==(Iterator iter2){
    return iter == iter2.iter;
}

template<typename T>
bool Vector<T>::Iterator::operator!=(Iterator iter2){
    return iter != iter2.iter;
}

template<typename T>
bool Vector<T>::Iterator::operator>=(Iterator iter2){
    return iter >= iter2.iter;
}

template<typename T>
bool Vector<T>::Iterator::operator<=(Iterator iter2){
    return iter <= iter2.iter;
}

template<typename T>
bool Vector<T>::Iterator::operator>(Iterator iter2){
    return iter > iter2.iter;
}

template<typename T>
bool Vector<T>::Iterator::operator<(Iterator iter2){
    return iter < iter2.iter;
}


template<typename T>
void Vector<T>::Iterator::operator=(Iterator iter2){
     iter = iter2.iter;
}

template<typename T>
T& Vector<T>::Iterator::operator*(){
     return *iter;
}

template<typename T>
int Vector<T>::Iterator::operator-(Iterator iter2){
     return (iter - iter2.iter);
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+(int offset){
    Iterator result(iter+offset);
    return result;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator-(int offset){
    Iterator result(iter-offset);
    return result;
}
               


#endif