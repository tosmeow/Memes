#include <iostream>

void square(){
    std::cout << "Enter two numbers:" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The square of " << v1// << " and " << v2
    << " is " << v1 * v1 << "\n";// << std::endl;//v1 + v2 << std::endl;
}

void hello_world(){
    std::cout << "Hello world" << std::endl;
}

void square_eff(){
    int v1=0, v2=0;
    std::cout << "Enter two numbers:" << std::endl;
    std::cin >> v1 >> v2;
    std::cout << "The sum of ";
    std::cout << v1;
    std::cout << " and ";
    std::cout << v2;
    std::cout << " is ";
    std::cout << v1 + v2;
    std::cout << "." << std::endl;
}

void error_eff(){
    int v1 = 0, v2 = 0;
    std::cout << "Enter 2 numbers:" << std::endl;
    std::cin >> v1 >> v2;
    std::cout << "The sum of " << v1;
    << " and " << v2;
    << " is " << v1 + v2 << std::endl;
}


int main()
{
    error_eff();
    return 0;
}



/* std::endl is equivalent to "\n" it seems.*/
/* std::cout ... seems equivalent to printf(...)*/