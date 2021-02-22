#pragma once
#ifndef ASM_UTILS
#define ASM_UTILS

#include<iostream>
#include<Eigen/Dense>
#include<Eigen/Sparse>
#include<Eigen/SparseQR>
#include<vector>
#include"sparse_matrices.hpp"

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

using namespace std;
using namespace Eigen;

class QuadraticProgrammingInstance {
	/*
	*    min 1/2 x^T G x + c^T x
	* st Aeq x = beq (equality constraints)
	*    A x <= b (inequality constraints)
	*/
public:
	MatrixXd G; // quadratic objective coefficient 
	VectorXd c; // linear objective coefficient
	SpMat A; // sparse constraint matrix 
	VectorXd b; // dense rhs vector (m * 1)
	VectorXd x; // dense vector representing initial feasible solution

	QuadraticProgrammingInstance(int n){ /* constructor */
		G = genPSDMat(n);
		c = MatrixXd::Random(n, 1);
		A = genSparseConstraint();
		//b = genRHS(n);
	}

	/* class methods */
	MatrixXd genPSDMat(int n);
	VectorXd genRHS(int n);

};

class ActiveSetMethod {
public:
	MatrixXd G; // quadratic objective coefficient 
	MatrixXd c; // linear objective coefficient
	SpMat A; // sparse constraint matrix 
	MatrixXd b; // dense rhs vector (m * 1)
	MatrixXd x; // dense vector representing initial feasible solution
	SpMat q;
	SpMat y;
	SpMat z;
	SpMat r;
	int m, n;
	ActiveSetMethod(MatrixXd G, VectorXd c, SpMat A, VectorXd x, VectorXd b) {
		m = A.rows(); n = A.cols();
		
		
		SparseQR<SparseMatrix<double>, COLAMDOrdering<int>> qr(A.transpose()); // compute sparse qr factors
		q = qr.matrixQ();
		r = qr.matrixR();
	}

	void solveEquConQP(); // solve the equality constrained Quadratic program using the "null space method"
};

MatrixXd solveSparseLowerTriangular(SpMat A, MatrixXd b);


#endif // !ASM_UTILS

