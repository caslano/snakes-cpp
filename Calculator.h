#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <Eigen\Dense>
#include <time.h>
#include <random>


/*Snakes and ladders*/

using namespace std;
using namespace Eigen;

const int N = 100;
const long long BATCH_SIZE = 1000;
typedef Matrix<double, N + 1, N + 1> Matrix100;
typedef Matrix<double, N + 1, 1> Vector100;
typedef map<int,int> Jumps;

struct Expectation_t
{
	double expectation;
	double error;
	int counter;
	int precision;
	Expectation_t();
};

ostream& operator <<(ostream& out, Expectation_t e);

class Calculator
{
private:
	const int NUM_JUMPS;
	const double TARGET;
	const int SEARCH_PRECISION;
	const int FULL_PRECISION;
	const double TOLERANCE;
	const double SEARCH_PRECISION_LIMIT;
	const double FULL_PRECISION_LIMIT;
	random_device _generator;
	uniform_int_distribution<int> _pos_distribution;
	uniform_int_distribution<int> _ladderNumber_distribution;
	uniform_int_distribution<int> _ladderSize_distribution;
	uniform_int_distribution<int> _snakeSize_distribution;
public:
	string LogFilename;
	
public:
	Calculator(int numJumps, double target, double tolerance, int searchPrecision, int fullPrecision);
	void Print(const Vector100 & V);
	void Print(const Matrix100 & M);
	void Print(const Jumps & jumps, bool isFullPrecision);
	Expectation_t Expectation(const Jumps& jumps, bool isFullPrecision);
	Jumps RandomJumps();
	Jumps RandomJumps2();
	Jumps SearchJumps(int maxCounter=0);

};

