#include "Calculator.h"






int main()
{
	const int NUM_JUMPS = 10;
	const double TARGET = 66.978705007555420778;
	const double TOLERANCE = 1E-6;

	Calculator game(NUM_JUMPS, TARGET, TOLERANCE);
	const int K = 1000;
	vector<Jumps> results;

	clock_t start = clock();
	

	try
	{
		Jumps jumps = game.SearchJumps();
		results.push_back(jumps);
		game.Print(jumps);

		//for (int i = 0; i < 250; ++i)
		//{
		//	Jumps jumps = game.RandomJumps2();
		//	game.Print(jumps);
		//	cout << endl;
		//}
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

