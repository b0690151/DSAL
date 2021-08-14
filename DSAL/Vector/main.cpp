/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "Vector.h"

using namespace std ;

int main()
{
#if 0
    Vector<int> v;
    v.Push_Back(1);
    v.Push_Back(2);
    v.Push_Back(3);
    v.Push_Back(4);
    v.Push_Back(5);

    for(int i=0;i<v.Size();i++)
        cout << v[i] << " ";
    cout << endl;

    Vector<int>::Iterator iter = v.Begin();


    v.Insert(iter + 5, 100);
    for(int i=0;i<v.Size();i++)
        cout << v[i] << " ";
    cout << endl;

    //cout << "erase(int)" <<endl;
    v.Erase(iter + 2);
    for(int i=0;i<v.Size();i++)
        cout << v[i] << " ";
    cout << endl;
    //cout << "erase(int, int)" <<endl;
    v.Erase(iter+2, iter+4);
    for(int i=0;i<v.Size();i++)
        cout << v[i] << " ";
    cout << endl;


    //cout << "Clear" <<endl;
    v.Clear();
    cout << v.Size() << endl;
    for(int i=0;i<v.Size();i++)
        cout << v[i] << " ";
    cout << endl;
#else
    Vector<int> v;
    v.Push_Back(1);
    v.Push_Back(2);
    v.Push_Back(3);
    v.Push_Back(2);
    v.Push_Back(2);
    v.Push_Back(6);
    v.Push_Back(2);

    for(int i=0;i<v.Size();i++)
        cout << v[i] << " ";
    cout << endl;

    Vector<int>::Iterator iter = Find(v, 2);



#endif


    return 0;
}
