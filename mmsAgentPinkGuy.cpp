// Joseph Lynch
// AI Final Project: Mini Mine Sweeper

/*	

	nice bash mmsBuild.bash

 and then

	nice ./mmsRunSim

*/

#include "mms.h"

/* The functions available to the agent are:

minefield.getSize()					Returns the size of the minefield (either length or width)
minefield.getCount()				Returns the total number of mines in the field
minefield.getValue(row, column)		Returns the number of bombs adjacent to a square
	
		0 = empty; no adjacent mines
		1 - 8 = corresponding number of adjacent mines
		9 = uncovered square
		
SweepLocation sample

sample.setRow(row)					Sets the row of the SweepLocation to row
sample.setColumn(column)			Sets the column of the SweepLocation to column

Your agent must return a SweepLocation with coordinates that are within the valid range
of the minefield:

	(0 <= row < size) and (0 <= column < size)
	
If you click a location that has already been clicked, it will be considered an
invalid move.

Any invalid move will immediately end the current game.
	
*/

int mmsAgentPinkGuyRandomInt(int n);

SweepLocation mmsAgentPinkGuy(Minefield &minefield, bool shouldReset)
{
	// Define static variables here
	
	//A vector of vectors to keep track of coordinates that I know are bombs.
	static vector<vector<bool> > flags;
	static int mineCount, size;
	
	SweepLocation click;
	
	int row, column, unclicked, mines;
	
	bool allSafe, allMines;

	// Reset static variables here
	if (shouldReset)
	{
		//Reset mineCount
		mineCount = 0;
		
		//Initialize size
		size = minefield.getSize();
		
		//Match flags vector size to the game board's size
		flags.resize(size);
		
		//Initialize and reset flags vector
		for (int i = 0; i < size; i += 1)
		{
			flags[i].resize(size);
			for (int j = 0; j < size; j += 1)
				flags[i][j] = 0;
		}
		
		// Dosen't matter what I return here
		return click;
	}
	// Decide which square to click
	else
	{
		//If my mineCount == the amount of mines on the field, go through and click each unclicked square that I have not flagged
		if (mineCount == minefield.getCount())
		{
			for (int i = 0; i < size; i += 1)
			{
				for (int j = 0; j < size; j += 1)
				{
					if (minefield.getValue(i, j) == 9 && flags[i][j] != 1)
					{
						click.setRow(i);
						click.setColumn(j);
						return click;
					}
				}
			}
		}
		
		//Check each square in order, starting from (0,0).
		for (int i = 0; i < size; i += 1)
		{
			for (int j = 0; j < size; j += 1)
			{
				// If we have revealed a value for this square
				if (minefield.getValue(i, j) != 9)
				{					
					// Reset counts and bools for current square
					unclicked = 0;
					mines = 0;
					allMines = false;
					allSafe = false;
					
					if (i - 1 > -1 && j - 1 > -1)
					{
						if (minefield.getValue(i - 1, j - 1) == 9)
							unclicked += 1;
						
						if (flags[i - 1][j - 1] == 1)
							mines += 1;
					}
					if (j - 1 > -1)
					{
						if (minefield.getValue(i, j - 1) == 9)
							unclicked += 1;
						
						if (flags[i][j - 1] == 1)
							mines += 1;
					}
					if (i + 1 < size && j - 1 > -1)
					{
						if (minefield.getValue(i + 1, j - 1) == 9)
							unclicked += 1;
						
						if (flags[i + 1][j - 1] == 1)
							mines += 1;
					}
					if (i + 1 < size)
					{
						if (minefield.getValue(i + 1, j) == 9)
							unclicked += 1;
						
						if (flags[i + 1][j] == 1)
							mines += 1;
					}
					if (i - 1 > -1)
					{
						if (minefield.getValue(i - 1, j) == 9)
							unclicked += 1;
						
						if (flags[i - 1][j] == 1)
							mines += 1;
					}
					if (i + 1 < size && j + 1 < size)
					{
						if (minefield.getValue(i + 1, j + 1) == 9)
							unclicked += 1;
						
						if (flags[i + 1][j + 1] == 1)
							mines += 1;
					}
					if (j + 1 < size)
					{
						if (minefield.getValue(i, j + 1) == 9)
							unclicked += 1;

						if (flags[i][j + 1] == 1)
							mines += 1;
					}
					if (i - 1 > -1 && j + 1 < size)
					{
						if (minefield.getValue(i - 1, j + 1) == 9)
							unclicked += 1;
						
						if (flags[i - 1][j + 1] == 1)
							mines += 1;
					}
					
					//If the value in the square matches the amount of unclicked quares, then they are all mines.
					if (unclicked == minefield.getValue(i, j))
						allMines = true;
					
					//If the number of mines I have flagged around this square is equal to the square's value, then all other
					//unclicked squares are safe.
					if (mines == minefield.getValue(i, j))
						allSafe = true;
					
					if (i - 1 > -1 && j - 1 > -1)
					{
						// Flag adjacent mines
						if (minefield.getValue(i - 1, j - 1) == 9 && allMines)
						{
							flags[i - 1][j - 1] = 1;
							mineCount += 1;
						}
						// Click adjacent squares
						if (minefield.getValue(i - 1, j - 1) == 9 && flags[i - 1][j - 1] != 1 && allSafe)
						{
							click.setRow(i - 1);
							click.setColumn(j - 1);
							return click;
						}
					}
					if (j - 1 > -1)
					{
						if (minefield.getValue(i, j - 1) == 9 && allMines)
						{
							flags[i][j - 1] = 1;
							mineCount += 1;
						}
						if (minefield.getValue(i, j - 1) == 9 && flags[i][j - 1] != 1 && allSafe)
						{
							click.setRow(i);
							click.setColumn(j - 1);
							return click;
						}
					}
					if (i + 1 < size && j - 1 > -1)
					{
						if (minefield.getValue(i + 1, j - 1) == 9 && allMines)
						{
							flags[i + 1][j - 1] = 1;
							mineCount += 1;
						}
						if (minefield.getValue(i + 1, j - 1) == 9 && flags[i + 1][j - 1] != 1 && allSafe)
						{
							click.setRow(i + 1);
							click.setColumn(j - 1);
							return click;
						}
					}
					if (i + 1 < size)
					{
						if (minefield.getValue(i + 1, j) == 9 && allMines)
						{
							flags[i + 1][j] = 1;
							mineCount += 1;
						}
						if (minefield.getValue(i + 1, j) == 9 && flags[i + 1][j] != 1 && allSafe)
						{
							click.setRow(i + 1);
							click.setColumn(j);
							return click;
						}
					}
					if (i - 1 > -1)
					{
						if (minefield.getValue(i - 1, j) == 9 && allMines)
						{
							flags[i - 1][j] = 1;
							mineCount += 1;
						}
						if (minefield.getValue(i - 1, j) == 9 && flags[i - 1][j] != 1 && allSafe)
						{
							click.setRow(i - 1);
							click.setColumn(j);
							return click;
						}
					}
					if (i + 1 < size && j + 1 < size)
					{
						if (minefield.getValue(i + 1, j + 1) == 9 && allMines)
						{
							flags[i + 1][j + 1] = 1;
							mineCount += 1;
						}
						if (minefield.getValue(i + 1, j + 1) == 9 && flags[i + 1][j + 1] != 1 && allSafe)
						{
							click.setRow(i + 1);
							click.setColumn(j + 1);
							return click;
						}
					}
					if (j + 1 < size)
					{
						if (minefield.getValue(i, j + 1) == 9 && allMines)
						{
							flags[i][j + 1] = 1;
							mineCount += 1;
						}
						if (minefield.getValue(i, j + 1) == 9 && flags[i][j + 1] != 1 && allSafe)
						{
							click.setRow(i);
							click.setColumn(j + 1);
							return click;
						}
					}
					if (i - 1 > -1 && j + 1 < size)
					{
						if (minefield.getValue(i - 1, j + 1) == 9 && allMines)
						{
							flags[i - 1][j + 1] = 1;
							mineCount += 1;
						}
						if (minefield.getValue(i - 1, j + 1) == 9 && flags[i - 1][j + 1] != 1 && allSafe)
						{
							click.setRow(i - 1);
							click.setColumn(j + 1);
							return click;
						}
					}
				}
			}
		}
		
		//If I cannot determine the best click from the previous code, then generat random locations.
		//Keep generating random moves until it finds a location that is unclicked and one I have not flagged.
		do
		{
			row = mmsAgentPinkGuyRandomInt(size);
			column = mmsAgentPinkGuyRandomInt(size);
		}
		while (minefield.getValue(row, column) != 9 || flags[row][column] == 1);
		
		click.setRow(row);
		click.setColumn(column);
		
		/*
		
		for (int i = 0; i < size; i += 1)
		{
			for (int j = 0; j < size; j += 1)
			{
				if (minefield.getValue(i, j) == 9 && flags[i][j] != 1)
				{
					click.setRow(i);
					click.setColumn(j);
					return click;
				}
			}
		}
		*/
	}
	
	// Return the chosen location
	return click;
}

//Copied from main code
int mmsAgentPinkGuyRandomInt(int n)
{
   // Return a random integer between 0 and n - 1.
   int r;
   if (n <= 0)
      return 0;
  
   do
   {
      r = random();
   }
   while (r >= INT_MAX / n * n);
   return r / (INT_MAX / n);
}
