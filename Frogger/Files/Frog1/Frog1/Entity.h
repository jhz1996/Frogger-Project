#pragma once
#include <SDL.h>
#include <string>
using namespace std;
class Entity
{
public:
	//Entity(int x, int y, int w, int h, float vx, float vy);
	Entity(int x, int y, int w, int h, float vx, float vy, string name);
	~Entity();


	// Methods for getting the vars of entity.
	int xpos();
	int ypos();
	int width();
	int height();
	int left();
	int right();
	int top();
	int bottom();
	double velx();
	double vely();
	int centerX();
	int centerY();
	string getName();

	char isIntersect(Entity* otherEnt);
	virtual void onIntersect(Entity* otherEnt);
	virtual void CheckBounds(int windowX, int windowY);
	virtual void Update();


	// The vars that define the shape.
	// Yes, the vars are public because they need to be modified by other classes.
	int x;
	int y;
	int w;
	int h;
	float vx;
	float vy;
	string name;
	bool isSolid;
	bool isActive;

protected:
	void Move();
};