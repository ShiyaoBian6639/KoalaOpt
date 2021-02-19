#include"utils.hpp"

void test()
{
	MatrixXd m = MatrixXd::Random(3, 3);
	m = m + (MatrixXd::Constant(3, 3, 1.2)) * 50;
	cout << "m = " << endl << m << endl;
	/// <summary>
	/// sparse matrix triplet representation
	/// </summary>

	const Triplet<double> A_triplets[] = { { 0, 0, 0 }, { 0, 1, 2 },{ 1, 1, 1 } };
	SparseMatrix<double> A(3, 2);
	A.setFromTriplets(&A_triplets[0], &A_triplets[3]);
	SparseQR<SparseMatrix<double>, COLAMDOrdering<int>> qr(A);
	SparseMatrix<double> Q, R;
	Q = qr.matrixQ();
	R = qr.matrixR();
	cout << "Matrix A is :" << endl;
	cout << MatrixXd(A) << endl;
	cout << "Matrix Q is :" << endl;
	cout << MatrixXd(Q) << endl;
	cout << "Matrix R is :" << endl;
	cout << MatrixXd(R) << endl;
	//SparseMatrix<double> Q = QR


}

void gen_sparse_constraint()
{

}