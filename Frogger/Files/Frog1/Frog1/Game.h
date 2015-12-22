#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Manager.h"
#include "Resources.h"
class Game
{
public:
	Game(string folderpath);
	~Game();

	bool Initalize();
	bool LoadAssets();
	void GameLoop();
	void Close();
	int GetWindowHeight();
	int GetWindowWidth();


	int FPS;
	int curStage;
	int stageCount;
	string folderpath;
	Resources* res;
	SDL_Window* window;
	SDL_Surface* screen;
	SDL_Renderer* render;
	Mix_Music *froggerTheme = NULL;
	Mix_Chunk *hop = NULL;
	Mix_Chunk *finish = NULL;
	Mix_Chunk *dead = NULL;
	Mix_Chunk *start = NULL;
	TTF_Font* font = NULL;
	SDL_Texture* text = NULL;

private:
};

