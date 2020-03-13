#include "Calculator.h"


using namespace std;



int main()
{
	const int NUM_JUMPS = 10;
	const double TARGET = 66.978705007555420778;
	const double TOLERANCE = 1.5E-12;
	const int SEARCH_PRECISION = 10;
	const int FULL_PRECISION = 16;
	const int MAX_COUNTER = 6000000;

	Calculator game(NUM_JUMPS, TARGET, TOLERANCE, SEARCH_PRECISION, FULL_PRECISION);
	const int K = 1000;

	clock_t start = clock();


	Jumps myBestJumps = map<int, int>{ {10,  39},{32,  61},{40,   3},{46,   9},{57,  86},{58,  21},{72,  35},{85,  48},{91,  54},{98,  59} };
	cout << "My best jumps\n";
	game.Print(myBestJumps, false);
	game.Print(myBestJumps, true);

	try
	{
		Jumps jumps = game.SearchJumps(MAX_COUNTER);
		cout << "Best solution found:\n";
		game.Print(jumps, false);
		game.Print(jumps, true);
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

