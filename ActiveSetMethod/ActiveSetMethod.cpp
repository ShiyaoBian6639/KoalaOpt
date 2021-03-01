// ActiveSetMethod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"utils.hpp"
#include"sparse_matrices.hpp"

int main()
{
    cout << "Welcome to Active set method\n";
    test();
    QuadraticProgrammingInstance qp(500, 1200);
    //cout << qp.A << endl;
    ActiveSetMethod ASM(qp.G, qp.c, qp.A, qp.x, qp.b);
    ASM.solve();
}
 