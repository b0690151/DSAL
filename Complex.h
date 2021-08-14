#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

#include <iostream>
using namespace std;

template<class T>
class Complex
{
  template<class T2> friend ostream & operator<<(ostream &, Complex<T2> &); 
  template<class T2> friend istream & operator>>(istream &, Complex<T2> &); 

  private:
    T Real;
    T Imaginary;
  public:
    Complex<T>(T = 0, T = 0); 
    Complex<T>(const Complex<T>&); //Done
    ~Complex<T>(); //Done
    

    Complex<T> operator+(const Complex<T>&); 
    Complex<T> operator-(const Complex<T>&); 
    Complex<T> operator*(const Complex<T>&); 
    Complex<T> operator/(const Complex<T>&); 
    bool operator==(Complex<T>&); 
    bool operator!=(Complex<T>&); 
    
    T norm(); 
    Complex<T> conjugate();  
};

#endif