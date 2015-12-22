#include "Frog.h"

// The player child class of entity. The player class is distinct, as it can move across lanes.
Frog::Frog(int xpos, int ypos) : Entity(x, y, w, h, vx, vy, "")
{
	this->x = xpos;
	this->y = ypos;
	this->w = 12;
	this->h = 10;
	this->vx = 0;
	this->vy = 0;
	this->name = "frog_N";
	this->isMoving = false;
}

// Returns the lane that the player is in.
int Frog::getLane()
{
	int lane = (this->ypos() - 64) / 32;
	return lane;


	// Get 12.

}


// Updates the frog's position.
void Frog::Update()
{
	Move();
}



Frog::~Frog()
{
}

// Function is called onIntersect with another entity. The char denotes the side.
// Sides are either 'T'op, 'B'ottom, 'L'eft, 'R'ight, 'I'nside, or 'F'alse.
void Frog::onIntersect(Entity* otherEnt, char side)
{
	if (side == 'F') 
	{
		return;
	}

	// We really dont care what side the player was hit on.
	// However, if the entity is a non-solid entity, we can ride on it.
	if (otherEnt->isSolid == false)
	{
		this->vx = otherEnt->velx();
	}
}


// Checks the boundaries of the frog to make sure it is within the region of the screen.
void Frog::CheckBounds(int windowX, int windowY)
{
	
	if (this->left() <= 0)
	{
		this->vx = -this->vx;
		this->x = 0;
	}
	else if (this->right() >= windowX)
	{
		this->vx = -this->vx;
		this->x = windowX - (this->right() - this->left());
	}

	if (this->top() <= 0)
	{
		this->vy = -this->vy;
		this->y = 0;
	}
	else if (this->bottom() >= windowY)
	{
		this->vy = -this->vy;
		this->y = windowY - (this->bottom() - this->top());
	}
	


}
