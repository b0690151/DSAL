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


    List.Push_Front(1);
    List.Push_Front(2);
    List.Push_Front(3);
    List.Print_List();
    List.Pop_Front();
    List.Pop_Front();
    List.Print_List();
    List.Pop_Front();
    List.Pop_Front();
    List.Print_List();

    return 0;
}
