// Battleship game
// Lab 9 Game
// CS 13012
// Joseph Muzina
// 11/5/2018

#include "battleship.h"
#include <iostream>

using std::cout; using std::cin; using std::endl;

int main()
{
	Fleet myFleet;
	myFleet.deployFleet();

	cout << "Fleet deployed!" << endl;

	// While there is still at least 1 ship operational, continue firing sequence
	do
		myFleet.firingSequence();
	while (myFleet.operational());

	cout << "Congratulations! All ships destroyed!" << endl << endl;
	cout << "Press any key to see ship locations!" << endl << endl;
	system("pause");

	myFleet.printFleet();

	cout << "Thanks for playing! Have a good day!" << endl << endl;
	
	system("pause");
}