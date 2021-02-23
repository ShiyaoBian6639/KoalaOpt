#pragma once
#ifndef ASM_UTILS
#define ASM_UTILS

#include<iostream>
#include<Eigen/Dense>
#include<Eigen/Sparse>
#include<Eigen/SparseQR>
#include<Eigen/SPQRSupport>
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
	VectorXd x; // dense vector representing initial feasible solution
	VectorXd b; // dense rhs vector (m * 1)

	QuadraticProgrammingInstance(int m, int n){ /* constructor */
		G = genPSDMat(n);
		c = VectorXd::Random(n, 1);
		A = genSparseConstraint(m, n);
		x = genInitialSolution(n);
		b = genRHS(n);
	}

	/* class methods */
	MatrixXd genPSDMat(int n);
	VectorXd genRHS(int n);
	VectorXd genInitialSolution(int n);
	SpMat genSparseConstraint(int m, int n);

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
	ActiveSetMethod(MatrixXd pG, VectorXd pc, SpMat pA, VectorXd px, VectorXd pb) {
		G = pG;
		c = pc;
		A = pA;
		b = pb;
		x = px;
		m = A.rows(); n = A.cols();
		computeQrFactors();
		
	}

	void solveForDirection(); // solve the equality constrained Quadratic program using "null space method"
	void solveForMultiplier();
	void computeQrFactors();
	void solve();
};

MatrixXd solveSparseLowerTriangular(SpMat A, MatrixXd b);


#endif // !ASM_UTILS

