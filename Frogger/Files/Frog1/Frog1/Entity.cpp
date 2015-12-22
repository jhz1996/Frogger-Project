#include "Entity.h"
#include <SDL.h>

// Shape contains position, width, and height.
bool isSolid = true;
bool isActive = true;


// Constructor of an entity.
Entity::Entity(int x, int y, int w, int h, float vx, float vy, string name)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->vx = vx;
	this->vy = vy;
	this->name = name;
	this->isActive = true;
	this->isSolid = true;

}


Entity::~Entity()
{
}

// Updates the entity position. Could eventually incorporate animations.
void Entity::Update()
{
	Move();
}

// Moves the entity based upon x and y velocity.
void Entity::Move()
{
	this->x = this->x + (int)vx;
	this->y = this->y + (int)vy;
}



// Checks to see if the owning entity has collided with the parameter entity. If not 'F', char indicates side of parameter that the entity collided.
char Entity::isIntersect(Entity* otherEnt)
{
	char result = 'F';

	// We want to detect if ANY of the dimensions overlap.
	if ((this->bottom() >= otherEnt->top() && this->top() <= otherEnt->top()) && (this->right() >= otherEnt->left() && this->left() <= otherEnt->right()))
	{
		// This entity collided with the top of an entity.
		result = 'T';
	}
	else if ((this->top() <= otherEnt->bottom() && this->bottom() >= otherEnt->bottom()) && (this->right() >= otherEnt->left() && this->left() <= otherEnt->right()))
	{
		// This entity collided with the bottom of an entity.
		result = 'B';
	}
	else if ((this->right() >= otherEnt->left() && this->left() <= otherEnt->left()) && (this->top() <= otherEnt->bottom() && this->bottom() >= otherEnt->top()))
	{
		// This entity collided with the left side of an entity.
		result = 'L';
	}
	else if ((this->left() <= otherEnt->right() && this->right() >= otherEnt->right()) && (this->top() <= otherEnt->bottom() && this->bottom() >= otherEnt->top()))
	{
		// This entity collided with the right side of an entity.
		result = 'R';
	}

	// NEW!
	// Test if the entity's center is literally inside the other.
	else if ((this->centerX() > otherEnt->left() && this->centerX() < otherEnt->right()) && (this->centerY() > otherEnt->top() && this->centerY() < otherEnt->bottom())) 
	{
		result = 'I';
	}
	return result;
}


// Virtual function. Inherited by each child entity, as the actions change per child.
void Entity::onIntersect(Entity* otherEnt)
{
	//We generally only do something if both entities are solids.
}


int Entity::xpos() 			{ return this->x; }
int Entity::ypos() 			{ return this->y; }
int Entity::width()			{ return this->w; }
int Entity::height()		{ return this->h; }
int Entity::left()			{ return xpos(); }
int Entity::right() 		{ return xpos() + this->w; }
int Entity::top() 			{ return ypos(); }
int Entity::bottom() 		{ return ypos() + this->h; }
int Entity::centerX()		{ return right() - (right() - left()) / 2; }
int Entity::centerY()		{ return bottom() - (bottom() - top()) / 2; }
double Entity::velx()		{ return vx; }
double Entity::vely()		{ return vy; }
string Entity::getName()	{ return this->name; }


void Entity::CheckBounds(int windowX, int windowY)
{
	// Checks to see if an entity is within the boundaries of a window.
	// If it's not, negate it's velocity components.
	// Thus putting the shape back in the window.


	// OLD BOUNDARY CODE. 
	// IT'S STILL HERE AS A REFERENCE TO THE CODER.
	/*
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
	*/


	

	// NEW BOUNDARY CODE.
	// Moving Left
	if ((this->right() + this->width()) <= 0 && this->vx < 0)
	{
		this->x = windowX + this->width();
	}


	// Moving Right
	if ((this->left() - this->width()) >= windowX && this->vx > 0)
	{
		this->x = -2 * this->width();
	}
}