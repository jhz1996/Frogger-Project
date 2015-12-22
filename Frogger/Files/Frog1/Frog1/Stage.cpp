#include "Stage.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}

// This is how levels are designed and stored. A 3d array of level design.
const string Stage::stages[3][13][3] = {
	// Level 1. 
	// NAME, COUNT, SPEED
	{
		{ "zone", "5", "0" },
		{ "log_medium", "3", "1" },
		{ "log_medium", "3", "-1" },
		{ "log_long", "2", "1" },
		{ "log_medium", "3", "-1" },
		{ "log_short", "3", "1" },
		{ "", "0", "0" },
		{ "car5", "3", "-1" },
		{ "car4", "2", "2" },
		{ "car3", "3", "-2" },
		{ "car2", "2", "1" },
		{ "car1", "3", "-3" },
		{ "", "0", "0" }

	},
	{
		{ "zone", "5", "0" },
		{ "log_long", "3", "2" },
	    { "log_medium", "2", "-2" },
		{ "log_long", "1", "2" },
		{ "log_medium", "2", "-2" },
		{ "log_short", "3", "2" },
		{ "", "0", "0" },
		{ "car5", "3", "-2" },
		{ "car4", "2", "3" },
		{ "car3", "3", "-3" },
		{ "car2", "2", "2" },
		{ "car1", "3", "-4" },
		{ "", "0", "0" }
	},
		{
		{ "zone", "5", "0" },
		{ "log_medium", "3", "2" },
		{ "log_medium", "2", "-3" },
		{ "log_long", "1", "3" },
	    { "log_medium", "2", "-3" },
		{ "log_short", "3", "3" },
	    { "", "0", "0" },
		{ "car5", "3", "-3" },
		{ "car4", "2", "4" },
		{ "car3", "3", "-4" },
		{ "car2", "2", "3" },
		{ "car1", "3", "-5" },
		{ "", "0", "0" }
		}

};
