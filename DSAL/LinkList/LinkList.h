#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED
#include <iostream>
#include "Funciton.h"

using namespace std;

template <typename T>
struct Node{
    T Data;
    Node*  Prev;
    Node*  Next;
};

template <typename T>
class Linked_List{
    private:
        Node<T>* Head;
        Node<T>* Tail;
    public:
        class Iterator
        {
            friend Linked_List;
            private:
                Node<T>* iter;
            public:
                Iterator(Node<T>* = nullptr);
                void operator++(); //++Iterator
                void operator--(); //--Iterator
                void operator++(int); //Iterator++
                void operator--(int); //Iterator--
                bool operator==(Iterator);
                bool operator!=(Iterator);
                void operator=(Iterator);
                Iterator operator+(int);
                Iterator operator-(int);
                T& operator*();
        };
        Linked_List();
        void Print_List();
        int Search_List(T);
        void Push_Front(T);
        void Pop_Front();
        void Push_Back(T);
        void Pop_Back();
        void Clear();
        void Reverse();
        void Insert(Iterator, const T &);
        void Erase(Iterator);
        void Remove(T);
        Iterator Begin();
        Iterator End();
        Iterator Head_Iter();
        Iterator Tail_Iter();
        //template <typename T2> friend typename Linked_List<T2>::Iterator Find(Linked_List<T2> List, T2 data);

};

template<typename T>
typename Linked_List<T>::Iterator Linked_List<T>::Head_Iter()
{
    return Iterator(Head);
}

template<typename T>
typename Linked_List<T>::Iterator Linked_List<T>::Tail_Iter()
{
    return Iterator(Tail);
}

template<typename T>
typename Linked_List<T>::Iterator Linked_List<T>::Begin()
{
    return Iterator(Head);
}

template<typename T>
typename Linked_List<T>::Iterator Linked_List<T>::End()
{
    return Iterator(nullptr);
}

template<typename T>
void Linked_List<T>::Insert(Iterator it, const T& value)
{

    if (it == Begin())
    {
        Push_Front(value);
        return;
    }
    if(it == End()){
        Push_Back(value);
        return;
    }
    //here cannot use to push front/tail
    Node<T> *new_node = new Node<T>{value, it.iter->Prev, it.iter};
    it.iter->Prev->Next = new_node;
    it.iter->Prev = new_node;
}

template<typename T>
void Linked_List<T>::Erase(Iterator it)
{
    if (it == Begin())
    {
        Pop_Front();
        return;
    }
    if(it == End()|| it == Iterator(Tail)){
        Pop_Back();
        return;
    }
    //here cannot use to pop front/tail
    it.iter->Prev->Next = it.iter->Next;
    it.iter->Next->Prev = it.iter->Prev;
    delete it.iter;
}

template<typename T>
void Linked_List<T>::Remove(T value)
{
    for (auto iter = Begin(); iter != End(); iter++)
    {
        if(*iter == value)
        {
            if(iter == Begin())
            {
                Pop_Front();
            }
            else
            {
                auto tmp = iter;
                tmp--;
                Erase(iter);
                iter = tmp;
            }

        }
    }
}

template <typename T>
typename Linked_List<T>::Iterator Find(Linked_List<T> List, T data){
    typename Linked_List<T>::Iterator null_iter(nullptr);

    if(List.Begin() == nullptr)
    {
        return null_iter;
    }
    else
    {
        auto current = List.Begin();
        while(current != null_iter)
        {
            if(*current == data)
            {
                return current;
            }
            else
            {
                 current++;
            }
        }

         return current;
    }
}

template <typename T>
void Linked_List<T>::Reverse(){
    if(Head == nullptr || Head == Tail)
    {
        return;
    }
    else
    {
        Node<T> *previous = nullptr;
        Node<T> *current = Head;
        Node<T> *preceding = Head->Next;
        Tail = Head;
        while(preceding != nullptr)
        {
            current->Next = previous;
            current->Prev = preceding;
            previous = current;
            current = preceding;
            preceding = preceding->Next;
        }

        current->Next = previous;
        current->Prev = preceding;
        Head = current;
    }
}

template <typename T>
void Linked_List<T>::Clear(){
    Node<T> *current = nullptr;
    while(Head != nullptr)
    {
        current = Head; //record node
        Head = Head->Next; //move to next
        delete current; //delete node
    }
    Tail = nullptr;
}

template <typename T>
Linked_List<T>::Linked_List(){
    Head = nullptr;
    Tail = nullptr;
}

template <typename T>
void Linked_List<T>::Print_List(){
    if(Head == nullptr)
    {
        cout << "This list is empty!" <<endl;
    }
    else
    {
        Node<T> *current = Head;
        cout <<  "Data:";
        while(current->Next != nullptr)
        {
            cout<< current->Data <<" ";
            current = current->Next;
        }
        cout<< current->Data <<" "<<endl;
    }
}

template <typename T>
int Linked_List<T>::Search_List(T target){
    if(Head == nullptr)
    {
       return -1;
    }
    else
    {
        Node<T> *current = Head;
        int index = 0;
        while(current->Next != nullptr)
        {
            if(current->Data == target)
            {
                return index;
            }
            current = current->Next;
            index++;
        }
        if(current->Data == target)
        {
            return index;
        }
        else
        {
            return -1;
        }
    }
}

template <typename T>
void Linked_List<T>::Push_Back(T value){
    if(Head == nullptr)
    {
        // Empty
        Node<T>* new_node = new Node<T>{value, nullptr, nullptr};
        // new_node->Data = value;
        // new_node->Next = Head;
        Head = new_node;
        Tail = new_node;
    }
    else
    {
        Tail->Next = new Node<T>{value, Tail, nullptr}; //value prev next
        Tail = Tail->Next;
    }
}

template <typename T>
void Linked_List<T>::Pop_Back(){
    if(Head == nullptr)
    {   //empty
        return;
    }
    else if (Head == Tail)
    {
        //one entry
        delete Tail;
        Head = nullptr;
        Tail = nullptr;
    }
    else
    {
        Tail = Tail->Prev;
        delete Tail->Next;
        Tail->Next = nullptr;
    }
}

template <typename T>
void Linked_List<T>::Push_Front(T value){
    if(Head == nullptr)
    {
        // Empty
        Node<T>* new_node = new Node<T>{value, nullptr, nullptr};
        // new_node->Data = value;
        // new_node->Next = Head;
        Head = new_node;
        Tail = new_node;
    }
    else
    {
        Head->Prev = new Node<T>{value, nullptr, Head}; //value prev next
        Head = Head->Prev;
    }
}

template <typename T>
void Linked_List<T>::Pop_Front(){
    if(Head == nullptr)
    {   //empty
        return;
    }
    else if (Head == Tail)
    {
        //one entry
        delete Tail;
        Head = nullptr;
        Tail = nullptr;
    }
    else
    {
        Head = Head->Next;
        delete Head->Prev;
        Head->Prev = nullptr;
    }
}

template<typename T>
Linked_List<T>::Iterator::Iterator(Node<T> *pointer)
{
    iter = pointer;
}

template<typename T>
void Linked_List<T>::Iterator::operator++(){
    // ++Iterator
    if(iter != nullptr)
    {
        iter = iter->Next;
    }
}

template<typename T>
void Linked_List<T>::Iterator::operator--(){
    // --Iterator
    if(iter != nullptr)
    {
        iter = iter->Prev;
    }
}

template<typename T>
void Linked_List<T>::Iterator::operator++(int){
    // Iterator++
    if(iter != nullptr)
    {
        iter = iter->Next;
    }
}


template<typename T>
void Linked_List<T>::Iterator::operator--(int){
    // Iterator--
    if(iter != nullptr)
    {
        iter = iter->Prev;
    }
}

template<typename T>
bool Linked_List<T>::Iterator::operator==(Iterator iter2){
    return iter == iter2.iter;
}

template<typename T>
bool Linked_List<T>::Iterator::operator!=(Iterator iter2){
    return iter != iter2.iter;
}

template<typename T>
void Linked_List<T>::Iterator::operator=(Iterator iter2){
     iter = iter2.iter;
}

template<typename T>
T& Linked_List<T>::Iterator::operator*(){
     return iter->Data;
}


template<typename T>
typename Linked_List<T>::Iterator Linked_List<T>::Iterator::operator+(int offset){
    Iterator result(iter);
    for(int i = 0; i < offset; i++)
    {
        if(result->iter == nullptr)
        {
            break;
        }
        else
        {
            result->iter = result->iter->Next;
        }

    }
    return result;
}

template<typename T>
typename Linked_List<T>::Iterator Linked_List<T>::Iterator::operator-(int offset){
    Iterator result(iter);
    for(int i = 0; i < offset; i++)
    {
        if(result->iter == nullptr)
        {
            break;
        }
        else
        {
            result->iter = result->iter->Prev;
        }

    }
    return result;
}

#endif // LINKED_LIST_H_INCLUDED
