/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "Circular_Linked_List.h"

using namespace std ;

int main()
{

#if 1
    Linked_List<int> List;


    List.Push_Back(1);
    List.Push_Back(2);
    List.Push_Back(3);
    List.Push_Back(4);
    List.Push_Back(5);
    List.Push_Back(6);
    List.Push_Back(7);
    List.Push_Back(8);
    List.Push_Back(8);
    List.Remove(8);
    List.Print_List();

    auto iter = Begin(List);
    Advance(iter,3);
    cout << *iter <<endl;


    Linked_List<int>::Iterator iter1 = Find(List,3);
    Linked_List<int>::Iterator iter2 = Find(List,7);

    List.Insert(Find(List,4),100);
    for(; iter1 != iter2; iter1++){
        cout<< *iter1 <<endl;
    }
    List.Erase(Find(List,4));

    iter1 = Find(List,3);
    iter2 = Find(List,7);

    for(; iter1 != iter2; iter1++){
        cout<< *iter1 <<endl;
    }
#else //Circular Link List testing

#endif
    return 0;
}
