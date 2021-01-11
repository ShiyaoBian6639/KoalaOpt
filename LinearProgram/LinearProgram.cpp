#include <iostream>
#include"read.hpp"

int main()
{
    cout << "Welcome to KoalaOptimizer!\n";

    string fileName = "D:/benchmark/markshare_4_0.mps";
    Read input(fileName);
    input.read();
    return 0;
}
