#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED
#include <iostream>
using namespace std;

template <typename T>
struct Node{
    T Data;
    Node*  Next;
};

template <typename T>
class Linked_List{
    private:
        Node<T>* First;
    public:
        Linked_List();
        void Print_List();
        int Search_List(T);
        void Push_Front(T);
        void Pop_Front();
        void Push_Back(T);
        void Pop_Back();
};

template <typename T>
Linked_List<T>::Linked_List(){
    First = nullptr;
}

template <typename T>
void Linked_List<T>::Print_List(){
    if(First == nullptr)
    {
        cout << "This list is empty!" <<endl;
    }
    else
    {
        Node<T> *current = First;
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
    if(First == nullptr)
    {
       return -1;
    }
    else
    {
        Node<T> *current = First;
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
void Linked_List<T>::Push_Front(T value){
    Node<T> *new_node = new Node<T>{value,First};
    First = new_node;
}

template <typename T>
void Linked_List<T>::Pop_Front(){
    if(First == nullptr)
    {
        Node<T> *tmp = First;
        First = First->Next;
        delete tmp;
    }
}

template <typename T>
void Linked_List<T>::Push_Back(T value){
    if(First == nullptr)
    {
        // Push_Front(value);
        Node<T>* new_node = new Node<T>{value, First};
        // new_node->Data = value;
        // new_node->Next = First;
        First = new_node;
    }
    else
    {
        Node<T> *current = First;
        while(current->Next != nullptr)
        {
            current = current->Next;
        }
        current->Next = new Node<T>{value,nullptr};
    }
}

template <typename T>
void Linked_List<T>::Pop_Back(){
    if(First == nullptr)
    {
        return;
    }
    else
    {
        Node<T> *current = First;
        if(current->Next == nullptr)
        {
            delete First;
            First = nullptr;
            return;
        }
        while(current->Next->Next != nullptr){
            current = current->Next;
        }
        delete current->Next;
        current->Next = nullptr;
    }
}

#endif // LINKED_LIST_H_INCLUDED
