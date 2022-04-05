#include <iostream>
#include "Mymap.h"

int main()
{
    int value = 50, key[] = {55,40,65,60,75,57};
    Mymap now;
    for (int i = 0; i < 6; i++) {
        now.insert(key[i], value);
    }
    std::cout << "da";
    now.remove(40);
    now.remove(55);
    now.remove(65);
    now.remove(60);
    now.remove(75);
    now.remove(57);
    std::cout << "net";
}
