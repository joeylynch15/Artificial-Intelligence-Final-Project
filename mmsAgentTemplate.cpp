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

SweepLocation mmsAgentTemplate(Minefield &minefield, bool shouldReset)
{
	// Define static variables here
	SweepLocation click;

	// Reset static variables here
	if (shouldReset)
	{
		
	}
	// Decide which square to click
	else
	{
		
	}
	
	return click;
}
