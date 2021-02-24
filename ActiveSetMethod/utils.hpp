#pragma once
#ifndef ASM_UTILS
#define ASM_UTILS

static const double TOL = 1e-5; // numerical tolerance

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

	QuadraticProgrammingInstance(int m, int n); 

	/* class methods */
	MatrixXd genPSDMat(int n);
	VectorXd genRHS(int m);
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
	SpMat q; // orthogonal matrix (n * n)
	SpMat y; // first m columns of q (n * m)
	SpMat z; // null space (n * (n - m))
	SpMat r; // sparse upper triangular matrix (n * m with first m rows fill-ins (m * m upper triangular) and the rest are 0s)
	int m, n; // dimensions of A, m constraints and n variables 

private:
	VectorXd h; // h = Ax - b
	VectorXd g; // g = c + Gx 
	VectorXd py;
	VectorXd pz;
	MatrixXd zTG;
	MatrixXd pz_lhs;
	MatrixXd pz_rhs;
	VectorXd lmd_rhs;
	VectorXd direction; // p
	VectorXd multiplier; // lambda
	VectorXi activeSet; // activeSet[i] = 1 indicates the i-th constraint is active
	double stepLength; // double between 0 and 1
	int blockingConstraint; // -1 indicates no blocking constraint exists, non-negative integers indicates the index of blocking constraint

public:
	ActiveSetMethod(MatrixXd pG, VectorXd pc, SpMat pA, VectorXd px, VectorXd pb);
	void getQrFactors(); // get qr factors of matrix A 
	void solveForDirection(); // solve the equality constrained Quadratic program using "null space method" and modify direction
	void solveForDirectionY();
	void solveForDirectionZ();
	void solveForMultiplier();
	int getMaxMultiplierIndex();
	void dropActiveSet();
	void appendActiveSet();
	void getStepLength();
	void solve();
};

MatrixXd solveSparseLowerTriangular(SpMat A, MatrixXd b);


#endif // !ASM_UTILS

