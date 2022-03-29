#include <iostream>
#include "Mymap.h"

int main()
{
    int value = 50, key[] = {21,33,13,11,15,20,31,53,41,61};
    Mymap now;
    for (int i = 0; i < 10; i++) {
        now.insert(key[i], value);
    }
    std::cout << "da";
}
