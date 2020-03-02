#include <vector>
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
	
	vector < vector<int>> trans = {{1, 38}, {4, 14}, {9, 31}, {21, 42}, {28, 84}, {36, 44}, {51, 67}, {71, 91}, {80, 100}, {16, 6}, {47, 26},
		{49, 11}, {56, 53}, {62, 19}, {64, 60, }, {87, 24}, {93, 73}, {95, 75}, {98, 78}};

	
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

	//for[i1, i2] in trans :
	//iw = np.where(T[:, i1] > 0)
	//	T[:, i1] = 0
	//	T[iw, i2] += 1 / 6

	for (auto& pair : trans)
	{
		for (int i = 0; i <= N; ++i)
		{
			T(i, pair[0]) = 0.0;
			if (T(i, pair[0]) > 0.0)
			{
				T(i, pair[1]) += 1.0 / 6;
			}
		}

		if (pair[0] > pair[1])
		{
			T(pair[0], 100) = 0.0;
		}

	}

	T(N, N) = 1.0;

	// You need to land on 100
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
	//cout << "checkSum=\n" << checkSum.transpose() << endl;
	//cout << "V=\n" << V.transpose() << endl;

	
	clock_t t = clock();

	for (int i = 0; i < 100; i++)
	{
		T = T * T;
	}

	t = clock() - t;


	
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

}

