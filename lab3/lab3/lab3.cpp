#include <iostream>
#include "Floyd.h"

int main()
{
    Floyd f;
    string str = f.cheapway("4", "1", "data.txt");
    cout << str;
    return 0;
}
