#include "test.h"
#include <iostream>
template<class T>
void A<T>::func()
{
  std::cout << "void A<T>::func()"<<std::endl;
}

template
void A<int>::func();

// template<class T>
// void Swap(const T& x,const T& y)
// {
//   std::cout << "Swap(const T& x,const T& y)"<<std::endl;
// }

// template
// void Swap<int>(const int& x,const int& y);
