#include"sparse_matrices.hpp"

void test()
{
	MatrixXd m = MatrixXd::Random(3, 3);
	m = m + (MatrixXd::Constant(3, 3, 1.2)) * 50;
	cout << "m = " << endl << m << endl;
	/*
	* sparse matrix triplet representation
	*/

	/*
	const Triplet<double> A_triplets[] = { { 0, 0, 0 }, { 0, 1, 2 },{ 1, 1, 1 } };
	SparseMatrix<double> A(3, 2);
	A.setFromTriplets(&A_triplets[0], &A_triplets[3]);
	*/
	SpMat A;
	A = gen_sparse_constraint();
	MatrixXd b = MatrixXd::Random(5, 1);
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

	cout << "Matrix A dot Y" << endl << MatrixXd(A * Q) << endl;
	MatrixXd x = R.triangularView<Upper>().transpose();
	cout << "matrix x is: " << endl << x << endl;
	cout << "matrix b is: " << endl << b << endl;
	//SparseMatrix<double> Q = QR


}

SpMat gen_sparse_constraint()
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