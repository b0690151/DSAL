#include "Complex.h"

template<typename T> //typename and class is OK
ostream& operator<<(ostream& os, Complex<T>& c)
{
  os << "R:" << c.Real << " I:" << c.Imaginary << endl;

  return os;
}

template<typename T>
istream& operator>>(istream& is, Complex<T>& c)
{
  is >> c.Real >> c.Imaginary;

  return is;
}

template<typename T>
Complex<T>::Complex(T r, T i)
:Real(r),Imaginary(i)
{
    //Simple constructor that initializes the resource.
}

template<typename T>
Complex<T>::Complex(const Complex<T>& c)
:Real(c.Real),Imaginary(c.Imaginary)
{
    //Copy constructor that initializes the resource.
}

template<typename T>
Complex<T>::~Complex()
{
  cout<<"Destructor Called"<<endl;
}

template<typename T>
Complex<T> Complex<T>::operator+(const Complex<T>& c){

    return Complex(Real + c.Real, Imaginary + c.Imaginary);
}

template<typename T>
Complex<T> Complex<T>::operator-(const Complex<T>& c){

    return Complex(Real - c.Real, Imaginary - c.Imaginary);
}

template<typename T>
Complex<T> Complex<T>::operator*(const Complex<T>& c){

    return Complex( (Real * c.Real) - (Imaginary * c.Imaginary),  (Imaginary * c.Real) + (Real * c.Imaginary));
}

template<typename T>
Complex<T> Complex<T>::operator/(const Complex<T>& c){

    T denominator = c.Real *  c.Real + c.Imaginary * c.Imaginary;

    return Complex( (Real * c.Real + Imaginary * c.Imaginary) / denominator,  (Imaginary * c.Real - Real * c.Imaginary) / denominator);
}


template<typename T>
bool Complex<T>::operator==(Complex<T>& c){

    return ((Real == c.Real) && (Imaginary == c.Imaginary));
}

template<typename T>
bool Complex<T>::operator!=(Complex<T>& c){

    return !((Real == c.Real) && (Imaginary == c.Imaginary));
}

template<typename T>
T Complex<T>::norm(){

    return Real * Real + Imaginary * Imaginary;
}

template<typename T>
Complex<T> Complex<T>::conjugate(){

    return Complex(Real, -Imaginary);
}

int main() {
    Complex<float> test(2,3);
    Complex<float> test2(2);
    Complex<float> test3(test2);
    //cin>>test2;
    cout<<test;
    cout<<test2;
    cout<<test3;
    test3 = test.conjugate();
    cout<<test3;
    test3 = test + test2;
    cout<<test3;
    test3 = test - test2;
    cout<<test3;
    test3 = test * test2;
    cout<<test3;
    test3 = test / test2;
    cout<<test3;
    cout<<(test == test2)<<endl;
    cout<<(test != test2)<<endl;
    cout<<test.norm()<<endl;
    cout<<test2.norm()<<endl;
    return 0;
}