/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "LinkList.h"

using namespace std ;

int main()
{
    Linked_List<int> List;


    List.Push_Back(1);
    List.Push_Back(2);
    List.Push_Back(3);
    List.Push_Back(4);
    List.Push_Back(5);
    List.Push_Back(6);
    List.Push_Back(7);
    List.Push_Back(8);
    List.Push_Back(9);
    List.Print_List();

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

    return 0;
}
