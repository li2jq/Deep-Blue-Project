#include <iostream>
#include <cstdio>
#include <limits>
#include <type_traits>
namespace namespce1
{
        void func()
        {}
}

namespace namespae2
{
        void func()
        {}
}

void func()
{
    }
int main()
{
//    int x = 10;
//    char y = 'a';
//    
//    std::cout << std::numeric_limits<unsigned int>::min() << std::endl;
//    std::cout << std::numeric_limits<unsigned int>::max() << std::endl;
//    
//    int a = std::numeric_limits<int>::max();
//    
//    a = a + 1;
//    
//    std::cout << "a = " << a << std::endl;
//    
//    int min_int = std::numeric_limits<int>::min();
//    
//    min_int -= 1;
//    
//    std::cout << "min_int = " << min_int << std::endl;
//    
//    std::cout << alignof(int) << std::endl;

//    int x=10;
//    char a = 'a';
//    
//    char* pa = &a;
//    int* px = &x;
//    
//    std::cout << "pa address " << &pa << std::endl;
//    std::cout << "px address" << &px << std::endl;
//    
//    std::cout << sizeof(pa) << std::endl;
//    std::cout << sizeof(px) << std::endl;

//    int x = 10;
//    
//    int y = 11;
//    
//    const int* ptr = &x; // The pointer points to x, cannot be changed by *ptr, 
//    
//    std::cout << "* ptr: " << *ptr << "\n";
//    x = 101;
//    
//    std::cout << "x = 101: " << *ptr << "\n";
//    *ptr = 1101;
//    int* const pptr = &x; // The direction is fixed, the contents can be changed
//    *pptr = 1001;
//    std::cout << "*pptr " << *pptr << "\n";
    int x = 3;
    constexpr const int* ptr = nullptr;
    
    std::cout << std::is_same<decltype(ptr), const int* const>::value ;
    
}
