#include"utils.hpp"


ActiveSetMethod::ActiveSetMethod(MatrixXd pG, VectorXd pc, SpMat pA, VectorXd px, VectorXd pb) // constructor of ActiveSetMethod
{
	G = pG;
	c = pc;
	A = pA;
	b = pb;
	x = px;
	m = A.rows(); n = A.cols();
}

void ActiveSetMethod::getQrFactors()
{
	auto begin = chrono::steady_clock::now(); 
	//Eigen::SPQR< Eigen::SparseMatrix < double > > spqrsolver(A);
	SparseQR<SparseMatrix<double>, COLAMDOrdering<int>> qr(A.transpose()); // compute sparse qr factors
	q = qr.matrixQ(); // access matrix Q (Q: n * m)
	y = q.leftCols(m); // y is the top m rows of Q (y: n * m)
	z = q.rightCols(n - m); // z is the bottom (n - m) rows of Q  (z: n * (n - m))
	r = qr.matrixR().topRows(m);  // access top m rows of matrix R (r: m * m)
	auto end = chrono::steady_clock::now();
	chrono::duration<double> elapsed = end - begin;
	cout << "factorizing sparse constraint coefficient A takes " << elapsed.count() << " seconds" << endl;
}

void ActiveSetMethod::solveForDirection()
{
	h = A * x - b;
	cout << " a * x is: " << endl << A * x << endl;
	g = c + G * x;
	solveForDirectionY(); // solve for py
	solveForDirectionZ(); // solve for pz 
	direction = y * py + z * pz;
	cout << "direction is : " << endl << direction << endl;
}

void ActiveSetMethod::solveForDirectionY() 
{
	py = r.transpose().triangularView<Lower>().solve(-h);
	cout << "r transpose is :" << endl << r << endl;
	cout << "-h is : " << endl << -h << endl;
	cout << "py is: " << endl << py << endl;
}

void ActiveSetMethod::solveForDirectionZ()
{
	zTG = z.transpose() * G;
	pz_lhs = zTG * z;
	pz_rhs = zTG * y * py - z.transpose() * g;
	pz = pz_lhs.llt().solve(pz_rhs);
	cout << "pz is: " << endl << pz << endl;
}

void ActiveSetMethod::solveForMultiplier()
{
	lmd_rhs = y.transpose() * (g + G * direction);
	multiplier = r.triangularView<Upper>().solve(lmd_rhs);
	cout << "multiplier is: " << endl << multiplier << endl;
}

int ActiveSetMethod::getMaxMultiplierIndex()
{
	int MaxMultiplierIndex = -1;
	return MaxMultiplierIndex;
}

void ActiveSetMethod::dropActiveSet()
{

}

void ActiveSetMethod::appendActiveSet()
{

}

void ActiveSetMethod::getStepLength()
{
	// compute both step length and the blocking constraint
	VectorXd numerator = b - A.transpose() * x;
	VectorXd denominator = A.transpose() * direction;
	double den, num, ratio;
	stepLength = INTMAX_MAX;
	cout << "denum is: " << endl << denominator << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "i is: " << i << endl;
		den = denominator(i);
		if (den < 0)
		{
			ratio = numerator(i) / denominator(i);
			if (ratio < stepLength)
			{
				stepLength = ratio;
			}
		}
	}
}

void ActiveSetMethod::solve() 
{
	int MaxMultiplierIndex;
	getQrFactors();

	while (1) 
	{
		solveForDirection();
		if (direction.norm() < TOL) 
		{
			solveForMultiplier();
			if (getMaxMultiplierIndex() >= 0) 
			{
				break;
			}
			else 
			{
				dropActiveSet();
			}
		}
		else
		{
			getStepLength();
			x += stepLength * direction;
			if (blockingConstraint >= 0)
			{
				appendActiveSet();
			}
		}
	}
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

QuadraticProgrammingInstance::QuadraticProgrammingInstance(int m, int n) /* constructor of QP instance  */
{
	G = genPSDMat(n);
	c = VectorXd::Random(n, 1);
	A = genSparseConstraint(m, n);
	x = genInitialSolution(n);
	b = genRHS(m);
}

MatrixXd QuadraticProgrammingInstance::genPSDMat(int n) {
	MatrixXd temp = MatrixXd::Random(n, 5);
	return temp * temp.transpose();
}

VectorXd QuadraticProgrammingInstance::genRHS(int m) {
	return VectorXd::Zero(m);
};

VectorXd QuadraticProgrammingInstance::genInitialSolution(int n)
{
	VectorXd x = (VectorXd::Random(n) + VectorXd::Constant(n, 1.)) / 2.;
	x /= x.sum();
	return x;
}

SpMat QuadraticProgrammingInstance::genSparseConstraint(int m, int n)
{
	vector<T> coefficients;
	int i;

	for (i = 0; i < n; i++) 
		coefficients.push_back({ 0,i,1 });

	for (i = 1; i < m; i++)
		coefficients.push_back({ i, i - 1, 1 });
	SpMat A(m, n);
	A.setFromTriplets(coefficients.begin(), coefficients.end());
	return A;
}