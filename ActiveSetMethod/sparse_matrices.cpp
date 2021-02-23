#include"sparse_matrices.hpp"
#include"utils.hpp"

void test()
{
	MatrixXd m = MatrixXd::Random(3, 3);
	m = m + (MatrixXd::Constant(3, 3, 1.2)) * 50;
	cout << "m = " << endl << m << endl;

	// test qr decomposition
	SpMat A;
	A = genSparseConstraint();
	MatrixXd b = MatrixXd::Ones(5,1) ;
	SparseQR<SparseMatrix<double>, COLAMDOrdering<int>> qr(A.transpose());
	SparseMatrix<double> Q, R;
	Q = qr.matrixQ();
	R = qr.matrixR();
	cout << "Matrix A is :" << endl;
	cout << MatrixXd(A) << endl;
	cout << "Matrix Q is :" << endl;
	cout << MatrixXd(Q) << endl;
	cout << "Matrix R is :" << endl;
	cout << MatrixXd(R) << endl;

	cout << "outer index of R: " << endl;
	for (int i = 0; i <= R.outerSize(); i++) {
		cout << R.outerIndexPtr()[i] << endl;
	}

	cout << "inner index of R: " << endl;
	for (int i = 0; i < R.nonZeros(); i++) {
		cout << R.innerIndexPtr()[i] << endl;
	}

	cout << "value of R: " << endl;
	for (int i = 0; i < R.nonZeros(); i++) {
		cout << R.valuePtr()[i] << endl;
	}
	
	cout << "Matrix A dot Y" << endl << MatrixXd(A * Q) << endl;
	MatrixXd x = R.triangularView<Upper>().transpose();
	cout << "matrix x is: " << endl << x << endl;
	cout << "matrix b is: " << endl << b << endl;
	//SparseMatrix<double> Q = QR
	x = solveSparseLowerTriangular(R, b);
	cout << "Matrix x is" << endl << x << endl;

	// sparse cholesky decomposition 
	MatrixXd large = MatrixXd::Random(1000, 1000);
	auto begin = chrono::steady_clock::now();
	LLT<MatrixXd> lltOfA(large);
	MatrixXd L = lltOfA.matrixL();
	auto end = chrono::steady_clock::now();
	chrono::duration<double> elapsed = end - begin;
	cout << "dense cholesky factorization takes " << elapsed.count() << " seconds" << endl;

	// product of sparse matrices and dense matrices 
	MatrixXd D = MatrixXd::Random(12, 12);
	cout << "A * D :" << endl << A * D  << endl;

	SpMat V = A.leftCols(5);
	cout << " Left 5 columns of A is:  " << endl << V << endl;


}

SpMat genSparseConstraint()
{
	vector<T> coefficients;
	int m, n, i;
	m = 5;
	n = 12;

	for (i = 0; i < n; i++) {
		coefficients.push_back({ 0,i,1 });
	}
	coefficients.push_back({ 1,0,1 });
	coefficients.push_back({ 2,1,1 });
	coefficients.push_back({ 3,2,1 });
	coefficients.push_back({ 4,3,1 });
	SpMat A(m, n);
	A.setFromTriplets(coefficients.begin(), coefficients.end());
	return A;
}