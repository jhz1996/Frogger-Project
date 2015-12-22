#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Game.h"
#include "Lane.h"
#include "Stage.h"
#include "Frog.h"
#include <vector>

class Game;
class Manager
{
public:
	Game* game;
	Manager(Game &);
	~Manager();
	Frog* player;
	//

	//
	vector<Lane> lanes;
	int lives;

	
	void BuildLevel(int level);
	void BuildFrog();
	void ProcessEvent(SDL_Event e);
	void ProcessEntities();
	void DrawEntities();
	void DrawEntity(Entity ent);
	void Refresh();
	Entity Manager::EntFromString(string rawLaneData);
	void ProcessCollisions();
	void HandleDeath(int x, int y);
	void HandleRespawn();


	bool isGameOver;
	bool isGameQuit;
	bool isLevelComplete;
};

