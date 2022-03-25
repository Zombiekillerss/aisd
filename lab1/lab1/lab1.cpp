#include <iostream>

int main()
{
    int* a, *b;
    a = new int(89);
    b = a;
    std::cout << a << "  " << b << "  " << (a == b);
}
