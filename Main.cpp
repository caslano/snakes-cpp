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


	Jumps myBestJumps = map<int, int>{ {10,  39},{32,  61},{40,   3},{46,   9},{57,  86},{58,  21},{72,  35},{85,  48},{91,  54},{98,  59} };
	cout << "My best jumps\n";
	game.Print(myBestJumps);
	cout << endl;

	return 101;

	try
	{
		Jumps jumps = game.SearchJumps();
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

	return 0;

}

