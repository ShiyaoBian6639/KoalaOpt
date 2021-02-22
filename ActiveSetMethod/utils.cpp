#include"utils.hpp"

void solveEqualityConstrinedQP(SpMat A, SpMat y, SpMat z, SpMat r, VectorXd x, VectorXd b, MatrixXd G, VectorXd c)
{
	MatrixXd h = A * x - b;
	MatrixXd g = c + G * x;
	int nrow = A.rows(); 
}

void ActiveSetMethod::solveEquConQP(){

}

MatrixXd solveSparseLowerTriangular(SpMat A, MatrixXd b) 
/*
* solves Ax = b where A is a sparse colomn compressed upper triangular matrix
* Null space method: (AY)p_y = -h, solve for p_y
*/
{
	MatrixXd x(b.rows(), 1);
	int colIndex, outerIndex, row, col, count;
	double val;
	count = 0;
	for (outerIndex = 0; outerIndex < A.outerSize(); outerIndex++) { // iterate over outerIndex of sparse matrices
		for (colIndex = A.outerIndexPtr()[outerIndex]; colIndex < A.outerIndexPtr()[outerIndex + 1]; colIndex++) { //
			col = outerIndex;
			row = A.innerIndexPtr()[count];
			val = A.valuePtr()[count];
			if (row == col) {
				x(col, 0) = b(col, 0) / val;
			}
			else {
				b(col, 0) -= val;
			}
			count++;
		}
	}
	return x;
}

MatrixXd QuadraticProgrammingInstance::genPSDMat(int n) {
	MatrixXd temp = MatrixXd::Random(n, 5);
	return temp * temp.transpose();
}

VectorXd QuadraticProgrammingInstance::genRHS(int n) {
	return VectorXd::Zero(n);
};