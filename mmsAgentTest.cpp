#include "mms.h"

SweepLocation mmsAgentTest(Minefield &minefield, bool shouldReset)
{	
	static int x = -1, y = 0;
	SweepLocation click;

	if (shouldReset)
	{
		x = -1;
		y = 0;
	}
	else
	{
		x++;
		if (x == minefield.getSize())
		{
			x = 0;
			y++;
		}
		
		click.setRow(x);
		click.setColumn(y);
	}
	
	return click;
}
