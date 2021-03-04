#include <iostream>
#include"read.hpp"
int main()
{
    cout << "Welcome to KoalaOptimizer!\n";

    const char* fileName = "D:/benchmark/markshare_4_0.mps";
    //fileName = "D:/benchmark/square47.mps";
    Read input(fileName);
    input.string2vec("df  df   da");
    input.read();



    return 0;
}
