#include <iostream>
#include "windows.h"
#include <vector>
#include "GameTwentyOne.h"

using namespace std;

int main()
{
	try
	{
		system("title BlackJack");
		GameTwentyOne G (10,4);
		G.Game();
	}
	catch (...)
	{
		cerr << "Error" << endl;
	}
	return 0;
}