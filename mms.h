// CS 4318, spring 2017
// AI Final Project: Mini Mine Sweeper
//
// Here are the #includes and definitions available to each agent.

#ifndef MMS_H
#define MMS_H

#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Minefield 
{
    private:
        int size; // length/width of minefield
        int randomInt(int n) const; // Random number generator for map size
        int count; // Number of mines on the field 
    public:
        Minefield(int newSize); // Sets the size of the Minefield with the constructor
		~Minefield();
        int getSize() { return size; } // Returns the size of the minefield
        void printInitialMinefield() const; // Void function to output the minefield with just bombs, before the agent plays the game
		void printFinalMinefield() const; // Void function to output the final minefield after the agent plays the game
		int **publicField; // Field that agent can access; is initially set to unclicked
		int **privateField; // Answer key field
		int getCount() { return count; } // Return the number of mines
		int getValue(int row, int column); // Return the public minefield value at coordinate (row, column)
};

class SweepLocation
{
    private:
        int row; // Row of the selected location
        int column; // Row of the column location
    public:
        SweepLocation(int newRow, int newColumn); // Constructor; sets row to row and column to column
		SweepLocation(); // Default constructor; sets row and column to 0
		int getRow() { return row; } // Returns the row 
		int getColumn() { return column; } // Returns the column
		void setRow(int newRow); // Set the row value
		void setColumn(int newColumn); // Set the column value
};

#endif // #ifndef MMS_H
