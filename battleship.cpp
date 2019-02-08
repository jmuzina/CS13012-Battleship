// Function definitions for battleship game
// Lab 9 Game
// CS 13012
// Joseph Muzina
// 11/5/2018

#include "battleship.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::cin; using std::endl;

// Initializes the object's coordinates
Location::Location()
{
	x = -1;
	y = '*';
}

// Assigns the object random coordinates
void Location::pick()
{
	srand(time(nullptr));

	// Generate a randum number between 1 and fieldSize and assigns this to x coordinate.
	x = rand() % fieldSize + 1;

	// Letter to start letter range from - ASCII char 97 = 'a'
	const char startChar = 97;

	// Generate a random number from 0 to fieldSize
	int charAdd = rand() % fieldSize;

	// Adds a random number from 0 to fieldSize to the random character's
	// ASCII value, generating a random character from a to the end of fieldsize. 
	y = startChar + charAdd;
}

// Gets user input for next shot
void Location::fire()
{
	cout << endl << "Ready to fire!" << endl;

	cout << "X Coordinate: ";
	cin >> x;

	cout << "Y Coordinate: ";
	cin >> y;
}

// Prints object coordinates in format "a1"
void Location::print() const
{
	cout << y << x << endl;
}

// Sets object location
void Location::set(int locX, char locY)
{
	x = locX;
	y = locY;
}

// Returns object x coordinate
int Location::getX() const
{
	return x;
}

// Returns object y coordinate
char Location::getY() const
{
	return y;
}

// Returns whether two locations are the same
bool compare(const Location &spot1, const Location &spot2)
{
	bool matched = false;

	// If the ship is at the specified board location, returns true
	if ((spot1.x == spot2.x) && (spot1.y == spot2.y))
		matched = true;

	return matched;
}

// Initializes a ship object as afloat
Ship::Ship()
{
	sunk = false;
}

// Returns whether object coordinates and parameter coordinates match
bool Ship::match(const Location &mySpot) const
{
	bool matched = false;

	if (compare(mySpot, loc))
		matched = true;

	return matched;
}

// Sinks the object
void Ship::sink()
{
	sunk = true;
}

// Sets ship object location
void Ship::setLocation(const Location &myLoc)
{
	loc.set(myLoc.getX(), myLoc.getY());
}

// Prints information about ship object
void Ship::printShip() const
{
	cout << endl << "Ship coordinates: " << loc.getX() << loc.getY() << endl;

	if (sunk)
		cout << "Sunk" << endl;
	else
		cout << "Afloat" << endl;

	cout << endl;
}

// Returns location of object
Location Ship::getLoc() const
{
	return loc;
}

// Returns whether the object is sunk
bool Ship::getSunk() const
{
	return sunk;
}

// Randomly deploys ships
void Fleet::deployFleet()
{
	cout << "Please wait... deploying fleet." << endl;
	int matchLoc;

	// Tracker variable
	int deployed = 0;

	while (deployed < fleetSize)
	{
		// Randomly generated coordinates
		Location getCoords;
		getCoords.pick();

		// Index of matched ship, -1 if none
		matchLoc = check(getCoords);

		// If location is unoccupied, deploys ship, marks it not sunk, increments number deployed
		if (matchLoc == -1)
		{
			ships[deployed].setLocation(getCoords);
			++deployed;
		}
	}
}

// Returns whether at least one ship is still afloat
bool Fleet::operational() const
{
	// Whether at least one ship is afloat
	bool oneAfloat = false;

	for (int i = 0; i < fleetSize; ++i)
	{
		if (ships[i].getSunk() == false)
		{
			oneAfloat = true;
			break;
		}
	}
	return oneAfloat;
}

// Checks if there is a ship at a location, and sinks it if it is there
bool Fleet::isHitNSink(const Location &checkLoc)
{
	// Index of matched ship
	int matchIndex = check(checkLoc);

	// Whether a match was found
	bool matched = false;

	if (matchIndex != -1)
	{
		ships[matchIndex].sink();
		matched = true;
	}

	return matched;
}

// Returns index of a ship if its location matches the parameter, or returns -1.
int Fleet::check(const Location &checkLoc) const
{
	// Index of matched ship
	int matchLoc = -1;

	for (int i = 0; i < fleetSize; ++i)
	{
		if (ships[i].match(checkLoc))
		{
			matchLoc = i;
			break;
		}
	}
	return matchLoc;
}

// Prints information about every ship in fleet
void Fleet::printFleet() const
{
	for (int i = 0; i < fleetSize; ++i)
	{
		ships[i].printShip();
	}
}

// Game implementation - fires and sinks ships
void Fleet::firingSequence()
{
	Location shot;

	shot.fire(); // User input for firing coordinates

	// If a ship is at input coordinates, sinks it.
	// Return value is whether a ship was present
	bool matched = isHitNSink(shot);

	if (matched)
		cout << "Hit! Ship sunk!" << endl;
	else
		cout << "Miss! Fire again! " << endl;
}