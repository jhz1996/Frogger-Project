#pragma once
#include "Entity.h"
class Frog : public Entity
{
public:
	Frog(int xpos, int ypos);
	~Frog();
	void Update();
	void onIntersect(Entity* otherEnt, char side);
	void CheckBounds(int windowX, int windowY);
	bool isMoving;
	int getLane();
};

