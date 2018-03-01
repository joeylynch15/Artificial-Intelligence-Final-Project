// CS 4318, spring 2017
// AI Final Project: Mini Mine Sweeper
//
// Here are the functions available to each agent.

#include "mms.h"

Minefield::Minefield(int newSize)
{
	size = newSize;

	publicField = new int *[size];
	privateField = new int *[size];
	
	for (int i = 0; i < size; i += 1)
	{
		publicField[i] = new int[size];
		privateField[i] = new int[size];
	}
	
	// Number of mines
	count = size * size * 15 / 100;
	
	// Initialize matrices to 0 and 9
	for (int i = 0; i < size; i += 1)
	{
		for (int j = 0; j < size; j += 1)
		{
			publicField[i][j] = 9;
			privateField[i][j] = 0;
		}
	}
	
	// Put the bombs in the private field
	for (int i = 0; i < count; i += 1)
	{
		bool bombPlaced = false;
		do
		{
			// generate random coordinate
			int row = randomInt(size);
			int column = randomInt(size);
			// see if there is already a mine
			// if not, put a mine there
			// if there is, generate another coordinate and try again
			if (privateField[row][column] != 9)
			{
				privateField[row][column] = 9;
				bombPlaced = true;
			}
		}
		while (bombPlaced == false);
	}
	
	// Fill in numbers for adjacent mines
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			if(privateField[i][j] == 9)
			{
				if (i-1 > -1 && j-1 > -1)
				{
					if(privateField[i-1][j-1] != 9)
					{
						privateField[i-1][j-1] += 1;
					}
				}
				if (j-1 > -1)
				{
					if(privateField[i][j-1] !=9)
					{
						privateField[i][j-1] += 1;
					}
				}
				if (i+1 < size && j-1 > -1)
				{
					if (privateField[i+1][j-1] !=9)
					{
						privateField[i+1][j-1] += 1;
					}
				}
				if (i+1 < size)
				{
					if(privateField[i+1][j]!=9)
					{
						privateField[i+1][j] += 1;
					}
				}
				if (i-1 >-1)
				{
					if(privateField[i-1][j]!=9)
					{
						privateField[i-1][j] += 1;
					}
				}
				if (i+1 < size && j+1 < size)
				{
					if(privateField[i+1][j+1]!=9)
					{
						privateField[i+1][j+1] += 1;
					}
				}
				if (j+1 < size)
				{
					if(privateField[i][j+1]!=9)
					{
						privateField[i][j+1] += 1;
					}
				}
				if (i-1 >-1 && j+1 < size)
				{
					if(privateField[i-1][j+1]!=9)
					{
						privateField[i-1][j+1] += 1;
					}
				}
			}
		}
	}
}

Minefield::~Minefield()
{
	for (int i = 0; i < size; i += 1)
	{
		delete[] publicField[i];
		delete[] privateField[i];
	}
	
	delete[] publicField;
	delete[] privateField;
}

int Minefield::randomInt(int n) const
{
   // Return a random integer between 0 and n - 1.
   int r;
   if (n <= 0)
   {
      return 0;
   }
   do
   {
      r = random();
   }
   while (r >= INT_MAX / n * n);
   return r / (INT_MAX / n);
}

void Minefield::printInitialMinefield() const
{
	cout << "Answer Key:\n";
	for (int k = 0; k < size * 4 + 1; k += 1)
	{
		cout << "-";
	}
	cout << "\n";
	for (int i = size - 1; i >= 0; i -= 1)
	{
		cout << "| ";
		for (int j = 0; j < size; j += 1)
		{
			if (privateField[j][i] == 9)
			{
				cout << "*" << " | ";
			}
			else if (privateField[j][i] == 0)
			{
				cout << " " << " | ";
			}
			else
			{
				cout << privateField[j][i] << " | ";
			}
		}
		cout << "\n";
		for (int k = 0; k < size * 4 + 1; k += 1)
		{
			cout << "-";
		}
		cout << "\n";
	}
}

void Minefield::printFinalMinefield() const
{
	cout << "Agent Results:\n";
	for (int k = 0; k < size * 4 + 1; k += 1)
	{
		cout << "-";
	}
	cout << "\n";
	for (int i = size - 1; i >= 0; i -= 1)
	{
		cout << "| ";
		for (int j = 0; j < size; j += 1)
		{
			if (publicField[j][i] == 9)
			{
				cout << "." << " | ";
			}
			else if (publicField[j][i] == 0)
			{
				cout << " " << " | ";
			}
			else if (publicField[j][i] == 10)
			{
				cout << "*" << " | ";
			}
			else
			{
				cout << publicField[j][i] << " | ";
			}
		}
		cout << "\n";
		for (int k = 0; k < size * 4 + 1; k += 1)
		{
			cout << "-";
		}
		cout << "\n";
	}
}

int Minefield::getValue(int row, int column)
{
	return publicField[row][column];
}

SweepLocation::SweepLocation()
{
	this->setRow(0);
	this->setColumn(0);
}

SweepLocation::SweepLocation(int newRow, int newColumn)
{
	this->setRow(newRow);
	this->setColumn(newColumn);
}

void SweepLocation::setRow(int newRow)
{
	this->row = newRow;
}

void SweepLocation::setColumn(int newColumn)
{
	this->column = newColumn;
}
