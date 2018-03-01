// CS 4318, spring 2017
// AI Final Project: Mini Mine Sweeper
//
// Here's the main function that plays all agents against each other and
// summarizes the results.

#include "mms.h"

extern const int numAgents;
extern SweepLocation (*agentFunc[])(Minefield &, bool);
extern string agentStr[];

int main()
{
	const int numberOfBoards = 100;
	int i, j, numSolved[numAgents], numSquaresUncovered[numAgents], currentValue, squaresLeft, squaresClickedThisGame,
		order[numAgents], temp;
	bool bombClicked = false, solved = false, invalidMove = false;
	Minefield *minefield;
	SweepLocation move;
	vector<SweepLocation> moveVector;
	
	srandom(time(0));
	
	cout << "AI Final Project: Mini Mine Sweeper\n"
		 << "Iteration results\n\n";
		
	// Set counts for results to 0 for each agent
	for (i = 0; i < numAgents; i += 1)
	{
		numSolved[i] = 0;
		numSquaresUncovered[i] = 0;
	}
	
	// Play the game
	for (i = 0; i < numberOfBoards; i += 1)
	{
		minefield = new Minefield(10 + ((i % 3) * 5));
		cout << "Minefield " << i + 1 << ":\n";
		minefield->printInitialMinefield();
		cout << "\n";
		int size = minefield->getSize();
		for (j = 0; j < numAgents; j += 1)
		{
			// Reset public minefield to unclicked in all squares
			for (int k = 0; k < size; k += 1)
			{
				for (int l = 0; l < size; l += 1)
				{
					minefield->publicField[k][l] = 9;
				}
			}
			
			// Reset bools
			bombClicked = false;
			solved = false;
			invalidMove = false;
			
			moveVector.clear();
			squaresClickedThisGame = 0;
			(*agentFunc[j])(*minefield, true);
			
			do
			{
				move = (*agentFunc[j])(*minefield, false);
				moveVector.push_back(move);
				squaresLeft = 0;
				
				// Determine if the agent made a valid move
				if (move.getRow() < 0 || 
					move.getRow() > (size - 1) || 
					move.getColumn() < 0 || 
					move.getColumn() > (size - 1))
				{
					invalidMove = true;
				}
				
				if (minefield->getValue(move.getRow(), move.getColumn()) != 9)
				{
					invalidMove = true;
				}
				
				if (!invalidMove)
				{
					currentValue = minefield->privateField[move.getRow()][move.getColumn()];
					// determine if they clicked a bomb
					// update public board
					// If they clicked an empty square
					if (currentValue == 0)
					{
						minefield->publicField[move.getRow()][move.getColumn()] = 0;
						numSquaresUncovered[j] += 1;
						squaresClickedThisGame += 1;
					}
					// If they clicked a bomb
					else if (currentValue == 9)
					{
						bombClicked = true;
						minefield->publicField[move.getRow()][move.getColumn()] = 10;
					}
					// If they clicked a 1 through 8 square
					else
					{
						minefield->publicField[move.getRow()][move.getColumn()] = currentValue;
						numSquaresUncovered[j] += 1;
						squaresClickedThisGame += 1;
					}
					
					// Count the number of unclicked squares remaining
					squaresLeft = size * size - squaresClickedThisGame;
					
					// If the number of unclicked squares equals the number of bombs, the game is solved
					if (squaresLeft == minefield->getCount())
					{
						solved = true;
					}
				}
			}
			while (!bombClicked && !solved && !invalidMove);
			// Print final map
			minefield->printFinalMinefield();
			// Print agent name and squares picked
			cout << setw(20) << left << agentStr[j] << " ";
			if (!moveVector.empty())
			{
				for (uint k = 0; k < moveVector.size(); k += 1)
				{
					cout << "(" << moveVector[k].getRow() << ", " << moveVector[k].getColumn() << ") ";
				}
			}
			// Print either solved or clicked bomb based on results
			if (bombClicked)
			{
				cout << " clicked bomb";
			}
			if (solved)
			{
				cout << " solved";
			}
			if (invalidMove)
			{
				cout << " invalid move";
			}
			cout << "\n\n";
		}
		delete minefield;
	}
	
	// Rank the agents based on results
	for (i = 0; i < numAgents; i += 1)
	{
		order[i] = i;
	}
	for (i = 0; i < numAgents - 1; i += 1)
	{
		for (j = i + 1; j < numAgents; j += 1)
		{
			if (numSolved[order[i]] < numSolved[order[j]] || numSolved[order[i]] == numSolved[order[j]] &&
				(numSquaresUncovered[order[i]] < numSquaresUncovered[order[j]] || numSquaresUncovered[order[i]] == numSquaresUncovered[order[j]] &&
				 agentStr[order[i]] > agentStr[order[j]]))
			{
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
			}
		}
	}
	
	// Output results
	cout << "\n"
		 << "Overall standings:     boards      squares\n"
		 << "                       solved      uncovered\n";
	for (i = 0; i < numAgents; i += 1)
	{
		cout << setw(20) << left << agentStr[order[i]]
		<< " " << setw(8) << right << numSolved[order[i]]
		<< " " << setw(14) << right << numSquaresUncovered[order[i]] << "\n";
	}
   
	return 0;
}
