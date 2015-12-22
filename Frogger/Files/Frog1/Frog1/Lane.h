#pragma once
#include <SDL.h>
#include "Entity.h"
#include <vector>
class Lane
{
public:


	Lane(Entity ent, int width, int height, int count, int speed, int y);
	~Lane();
	void Update();
	vector<Entity> ents;

private:
	int y;
	string entName;
	int entCount;
	int entSpeed;
	int laneWidth;
	int laneHeight;
	Entity* entType;
	void BuildLane();
	void BuildZones();
	SDL_Surface* surf;
};

