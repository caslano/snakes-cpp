#include <iostream>
#include <iomanip>
#include <Eigen\Dense>
#include <time.h>


/*Snakes and ladders*/

using namespace std;
using namespace Eigen;

const int N = 100;
typedef Matrix<double, N + 1, N + 1> Matrix100;
typedef Matrix<double, N + 1, 1> Vector100;

int main()
{
	


	
	Matrix100 T;	//The transition matrix
	Vector100 V;

	T = Matrix100::Constant(0.0);
	for (int i = 0; i < T.rows(); i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			if(i+j < T.rows())
				T(i, i+j) = 1.0 / 6;
		}
	}
	T(N, N) = 1.0;

	for (int i = 1; i <= 5; i++)
	{
		T(N - 6 + i, N - 6 + i) += (1.0 / 6 * i);
	}

	Vector100 checkSum = Vector100::Constant(0.0);

	for (int i = 0; i < T.rows(); i++)
	{
		for (int j = 0; j < T.rows(); j++)
			checkSum(i) += T(i, j);
	}

	
	V = Vector100::Constant(0.0);
	V(0) = 1.0;

	cout << "T=\n" << T << endl;
	cout << "checkSum=\n" << checkSum.transpose() << endl;
	//cout << "V=\n" << V.transpose() << endl;

	
	clock_t t = clock();

	for (int i = 0; i < 100; i++)
	{
		T = T * T;
	}

	t = clock() - t;


	
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

}

