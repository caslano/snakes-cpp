#include "Calculator.h"






int main()
{
	const double TARGET = 66.978705007555420778;

	Calculator game(10, TARGET);
	const int K = 1000;
	vector<Jumps> results;

	clock_t start = clock();
	double tolerance = 1E-6;

	try
	{

		Jumps jumps = game.SearchJumps(tolerance);
		results.push_back(jumps);
		game.Print(jumps);
	}
	catch(exception& ex)
	{
		cout << ex.what() << endl;
	}
	catch (...)
	{
		cout << "Unknown Exception\n";
	}
	
	clock_t elapsed = clock() - start;
	
	float timing = ((float)elapsed) / CLOCKS_PER_SEC;
	cout << " Timing = " << timing << "s";

}

