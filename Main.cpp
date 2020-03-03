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

	T(N, N) = 1.0;

	// You need to land on 100
	for (int i = 1; i <= 5; i++)
	{
		T(N - 6 + i, N - 6 + i) += (1.0 / 6 * i);
	}


	//Apply transitions
	for (auto& jump : trans)
	{
		int source = jump[0];
		int dest = jump[1];
		for (int i = 0; i <= N; ++i)
		{
			double proba = T(i, source);
			T(i, source) -= proba;
			T(i, dest) += proba;
		}
	}

	Vector100 checkSum = Vector100::Constant(0.0);

	for (int i = 0; i < T.rows(); i++)
	{
		for (int j = 0; j < T.rows(); j++)
			checkSum(i) += T(i, j);
	}
	/*
	
	# The player starts at position 0.
	v = np.zeros(101)
	v[0] = 1

	n, P = 0, []
	cumulative_prob = 0
	expectation = 0
	proba = 0
	# Update the state vector v until the cumulative probability of winning
	# is "effectively" 1
	while cumulative_prob < 0.999999999:
		n += 1
		v = v.dot(T)
		proba = v[100]
		P.append(proba)
		cumulative_prob += proba
		expectation += proba * n

	*/
	
	V = Vector100::Constant(0.0);
	V(0) = 1.0;

	//cout << "T=\n" << T << endl;
	//cout << "checkSum=\n" << checkSum << endl;
	//cout << "V=\n" << V.transpose() << endl;

	
	clock_t t = clock();
	double cumul_prob = 0.0;
	double expectation = 0.0;
	double proba;
	vector<double> probas(1024, 0.0);
	int counter = 0;

	while (cumul_prob < 0.999999999)
	{
		++counter;
		V = V.transpose()*T;
		cout << "V=\n" << V << endl;
		proba = V(N);
		probas[counter] = proba;
		cumul_prob += proba;
		expectation += proba * counter;

		if (counter > 1E4)
		{
			cout << "counter overflow\n";
			break;
		}
	}

	t = clock() - t;


	
	float timing = ((float)t) / CLOCKS_PER_SEC;

	cout << "Counter = " << counter;
	cout << " Timing = " << timing << "s";
	cout << " Expectation = " << expectation << endl;

}

