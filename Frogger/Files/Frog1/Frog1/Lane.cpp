#include "Lane.h"

/*
	Lanes are structures that hold the entities that will travel across the screen.
	When a lane is created, it is given a entity to generate. 
	Depending on the entity type, other properties of the lane are determined.
*/


// Constructor. Takes in entity types and creates essentially a vector to hold all entities per lane.
Lane::Lane(Entity ent, int width, int height, int count, int speed, int y)
{
	this->laneWidth = width;
	this->laneHeight = height;
	this->entCount = count;
	this->entSpeed = speed;
	this->entType = &ent;
	// For log offset.
	this->y = ent.y + y;


	if (ent.name == "zone")
	{
		// Zones require specific formatting.
		BuildZones();
	}
	else
	{
		BuildLane();
	}
}


// Construct the vector from the template entity.
void Lane::BuildLane()
{
	// Adds the entities 
	int r = rand() % 100 + 2;


	for (int i = 1; i <= entCount; i++)
	{
		double xpos = ((double)i * ((double)224.0 + (entType->width()/r) /entCount));
		//double xpos = ((double)i * ((double)224.0 / entCount));

		if (entType->name.find("log") != string::npos)
		{
			xpos = ((double)i * ((double)224.0 + (entType->width() / (r/2)) / entCount));

		}


		xpos += r;

		Entity* tempEnt = new Entity(*entType);
			//entType;
		tempEnt->x = xpos;
		tempEnt->y = y;
		tempEnt->vx = entSpeed;
		tempEnt->vy = 0;
		ents.push_back(*tempEnt);
	}
}


// This is called when building the victory zones where the player must reach and deposit a frog.
void Lane::BuildZones()
{
	// Adds the entities 
	// First at 16, 64;
	// Second at 112, 64;
	// Third at 208, 64;
	for (int i = 0; i < 5; i++)
	{
		double xpos = 16 + 96 * i;
		Entity* tempEnt = new Entity(*entType);
		tempEnt->x = xpos;
		tempEnt->y = 64;
		tempEnt->vx = 0;
		tempEnt->vy = 0;
		ents.push_back(*tempEnt);
	}
}



// Updates all entities within the lane.
void Lane::Update()
{
	for (auto it = ents.begin(); it != ents.end(); it++)
	{
		it->Update();
		it->CheckBounds(laneWidth, laneHeight);
	}
}


Lane::~Lane()
{
}
