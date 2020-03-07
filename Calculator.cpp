#include "Calculator.h"
#include <set>

using namespace std;

Calculator::Calculator(int numJumps, double target, double tolerance)
	: NUM_JUMPS(numJumps), TARGET(target), TOLERANCE(tolerance)
{
	_pos_distribution = uniform_int_distribution<int>(1, 100);
	_ladderNumber_distribution = uniform_int_distribution<int>(3, 4);
	_ladderSize_distribution = uniform_int_distribution<int>(80, 120);
	_snakeSize_distribution = uniform_int_distribution<int>(200, 300);
}

void Calculator::Print(const Vector100& V)
{
	int w = 8;
	cout << fixed;
	cout << setprecision(16);

	cout << setw(w) << "#";
	for (int j = 0; j < V.cols(); ++j)
	{
		cout << setw(w - 1) << j << ":";
	}
	cout << endl;

	for (int i = 0; i < V.rows(); ++i)
	{
		cout << setw(w - 1) << i << ":";
		for (int j = 0; j < V.cols(); ++j)
		{
			cout << setw(w) << V(i, j);
		}
		cout << endl;
	}

}

void Calculator::Print(const Matrix100& M)
{
	int w = 8;
	ostringstream line;
	line << fixed;
	line << setprecision(4);

	line << setw(w) << "#";
	for (int j = 0; j < M.cols(); ++j)
	{
		line << setw(w - 1) << j << ":";
	}
	cout << line.str() << endl;
	line.str("");
	line.clear();

	for (int i = 0; i < M.rows(); ++i)
	{
		line << setw(w - 1) << i << ":";
		for (int j = 0; j < M.cols(); ++j)
		{
			line << setw(w) << M(i, j);
		}
		cout << line.str() << endl;
		line.str("");
		line.clear();
	}

}

void Calculator::Print(const Jumps& jumps)
{
	int downs = 0;
	int ups = 0;
	int snakes = 0;
	int ladders = 0;
	bool isFirst = true;
	for (auto& jump : jumps)
	{
		if (!isFirst)
			cout << ", ";
	
		cout << "[" << setw(3) << jump.first << ", " << setw(3) << jump.second;
		cout << "]";
		isFirst = false;

		if (jump.first < jump.second)
		{
			ups += jump.second - jump.first;
			ladders++;
		}
		else
		{
			downs -= jump.second - jump.first;
			snakes--;
		}
	}

	cout << "  L=" << setw(3) << ladders;
	cout << "  S=" << setw(3) << snakes;
	cout << "  U=" << setw(3) << ups;
	cout << "  D=" << setw(3) << downs;
	cout << "  E=" << Expectation(jumps);
	

	//cout << endl;
}

double Calculator::Expectation(const Jumps & jumps)
{
	Matrix100 T;	//The transition matrix
	Vector100 V;	//The vector of transition

	T = Matrix100::Constant(0.0);
	for (int i = 0; i < T.rows(); i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			if (i + j < T.rows())
				T(i, i + j) = 1.0 / 6;
		}
	}

	// You need to land on 100
	for (int i = 1; i <= 5; i++)
	{
		T(N - 6 + i, N - 6 + i) += (1.0 / 6 * i);
	}


	//Apply transitions
	for (auto& jump : jumps)
	{
		int source = jump.first;
		int dest = jump.second;
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
		if (checkSum(i) > 1.0)
			throw exception("CheckSum failed.");
	}


	V = Vector100::Constant(0.0);
	V(0) = 1.0;

	double cumul_prob = 0.0;
	double expectation = 0.0;
	double proba;
	int counter = 0;

	while (cumul_prob < 0.999999999)
	{
		++counter;
		V = V.transpose()*T;
		proba = V(N);
		cumul_prob += proba;
		expectation += proba * counter;

		if (counter > 10000 || expectation > TARGET + TOLERANCE)
			return 0.0;
	}

	return expectation;


}

Jumps Calculator::RandomJumps()
{
	Jumps jumps;
	set<int> allPositions;
	int source, destination;
	for(int i = 0; i < NUM_JUMPS; ++i)
	{
		do
		{
			source = _pos_distribution(_generator);
		} while (allPositions.find(source) != allPositions.end() || source==100);
		allPositions.insert(source);

		do
		{
			destination = _pos_distribution(_generator);
		} while (allPositions.find(destination) != allPositions.end());
		allPositions.insert(destination);

		jumps[source] = destination;
	}

	return jumps;
}

Jumps Calculator::RandomJumps2()
{
	Jumps jumps;
	set<int> allPositions;
	int source, destination;

	int num_ladders = _ladderNumber_distribution(_generator);
	int num_snakes = NUM_JUMPS - num_ladders;
	int ups = _ladderSize_distribution(_generator);
	int downs = _snakeSize_distribution(_generator);
	int ladder_avg_size = ups / num_ladders;
	int snake_avg_size = downs / num_snakes;

	vector<int> ladder_lengths(num_ladders);
	vector<int> snake_lengths(num_snakes);

	int ladder_sum = 0;
	for (int i = 0; i < num_ladders - 1; ++i)
	{
		ladder_lengths[i] = ladder_avg_size;
		ladder_sum += ladder_avg_size;
	}
	ladder_lengths.back() = ups - ladder_sum;

	for (int i = 0; i < num_ladders; ++i)
	{
		do
		{
			source = _pos_distribution(_generator);
			destination = source + ladder_lengths[i];
		} while (allPositions.find(source) != allPositions.end() 
			|| allPositions.find(destination) != allPositions.end()
			|| source + ladder_lengths[i] >= 100 );
		
		allPositions.insert(source);
		allPositions.insert(destination);

		jumps[source] = destination;
	}

	int snake_sum = 0;
	for (int i = 0; i < num_snakes - 1; ++i)
	{
		snake_lengths[i] = -snake_avg_size;
		snake_sum += snake_avg_size;
	}
	snake_lengths.back() = -(downs - snake_sum);

	for (int i = 0; i < num_snakes; ++i)
	{
		do
		{
			source = _pos_distribution(_generator);
			destination = source + snake_lengths[i];
		} while (allPositions.find(source) != allPositions.end()
			|| allPositions.find(destination) != allPositions.end()
			|| source >= 100
			|| source + snake_lengths[i] < 1);

		allPositions.insert(source);
		allPositions.insert(destination);

		jumps[source] = destination;
	}

	return jumps;
}

Jumps Calculator::SearchJumps()
{
	

	

	long long counter = 0;
	double exp;
	Jumps jumps;
	double bestExp = 0.0;
	double bestError = 100.0;
	double error = 0.0;
	Jumps bestJumps;
	do
	{
		jumps = RandomJumps2();
		exp = Expectation(jumps);
		
		error = abs(exp - TARGET);

		if (error < bestError)
		{
			bestExp = exp;
			bestError = error;
			bestJumps = jumps;
		}

		if (counter % BATCH_SIZE == 0)
		{
			cout << "Counter = " << setw(16) << counter;
			cout << " LastExp  = " << setw(16) << setprecision(12) << exp;
			cout << " BestErr = " << setw(10) << bestError;
			cout << " BestExp  = " << setw(16) << setprecision(12) << bestExp;
			cout << endl;
		}
		if (error < 1E-3)
		{
			Print(jumps);
			cout << endl;
		}

		counter++;

	} while (error > TOLERANCE);
	
	return jumps;
}

