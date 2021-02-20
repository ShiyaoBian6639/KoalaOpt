#pragma once
#ifndef ASM_UTILS
#define ASM_UTILS

#include<iostream>
#include<Eigen/Dense>
#include<Eigen/Sparse>
#include<Eigen/SparseQR>
#include<vector>

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

using namespace std;
using namespace Eigen;

MatrixXd solveSparseLowerTriangular(SpMat A, MatrixXd b);


#endif // !ASM_UTILS

