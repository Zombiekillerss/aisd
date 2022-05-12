#include <iostream>
#include "Fulkerson.h"

int main()
{
    Fulkerson f;
    int sum = 0;
    sum = f.maxflow("example1.txt");
    std::cout << endl << "Maximum flow: " << sum << endl;
    sum = f.maxflow("example2.txt");
    std::cout << endl << "Maximum flow: " << sum << endl;
    sum = f.maxflow("example3.txt");
    std::cout << endl << "Maximum flow: " << sum << endl;
}