#include <iostream>
#include "Floyd.h"

int main()
{
    Floyd f;
    string str = f.cheapway("3", "3");
    f.print_matrix();
    cout << str;
    return 0;
}
