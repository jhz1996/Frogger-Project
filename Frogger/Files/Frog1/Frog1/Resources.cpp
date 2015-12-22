#include "Resources.h"
#include <iostream>


// Resources constructor. Takes in and attempts to load the files from the folderpath.
Resources::Resources(string folderpath, SDL_Renderer* renderer)
{
	loaded = true;
	this->folderpath = folderpath;
	cars_text = CreateTextureFromBitmap(renderer, folderpath + "/cars2.bmp");
	logs_text = CreateTextureFromBitmap(renderer, folderpath + "/logs2.bmp");
	back_text = CreateTextureFromBitmap(renderer, folderpath + "/board_classic.bmp");
	frog_horz = CreateTextureFromBitmap(renderer, folderpath + "/frog_horz2.bmp");
	frog_vert = CreateTextureFromBitmap(renderer, folderpath + "/frog_vert2.bmp");
	zone_full = CreateTextureFromBitmap(renderer, folderpath + "/zone_full.bmp");
	zone_empty = CreateTextureFromBitmap(renderer, folderpath + "/zone_empty.bmp");
	
	lives_text = CreateTextureFromText(renderer, "-------");
	status_text = CreateTextureFromText(renderer, "START");
	
	InitRects();
}

// Easy function to return a texture from a bitmap.
SDL_Texture* Resources::CreateTextureFromBitmap(SDL_Renderer* renderer, string filepath)
{
	SDL_Surface* tempSurf = SDL_LoadBMP(filepath.c_str());
	if (tempSurf == NULL)
	{
		this->loaded = false;
		return NULL;
	}
	else
	{
		SDL_SetColorKey(tempSurf, SDL_TRUE, SDL_MapRGB(tempSurf->format, 0, 0, 0));
		SDL_Texture* tempText = SDL_CreateTextureFromSurface(renderer, tempSurf);
		SDL_FreeSurface(tempSurf);
		return tempText;
	}
}


// Converts text to a texture using the SDL_TTF library.
SDL_Texture* Resources::CreateTextureFromText(SDL_Renderer* renderer, string words)
{
	if (loaded == false) return NULL;
	gFont = TTF_OpenFont((folderpath + "/latha.ttf").c_str(), 30);
	SDL_Color textColor = { 255, 255, 0 };
	SDL_Surface* tempSurf = TTF_RenderText_Solid(gFont, words.c_str(), textColor);
	SDL_Texture* tempText = SDL_CreateTextureFromSurface(renderer, tempSurf);
	SDL_FreeSurface(tempSurf);
	return tempText;
}

// Initializes the position rectangles. These define the subshapes within textures.
void Resources::InitRects()
{
	car1_rect = new SDL_Rect();
	car1_rect->x = 2;
	car1_rect->y = 0;
	car1_rect->w = 32;
	car1_rect->h = 28;

	car2_rect = new SDL_Rect();
	car2_rect->x = 36;
	car2_rect->y = 0;
	car2_rect->w = 28;
	car2_rect->h = 28;

	car3_rect = new SDL_Rect();
	car3_rect->x = 66;
	car3_rect->y = 0;
	car3_rect->w = 30;
	car3_rect->h = 28;

	car4_rect = new SDL_Rect();
	car4_rect->x = 98;
	car4_rect->y = 0;
	car4_rect->w = 32;
	car4_rect->h = 28;


	car5_rect = new SDL_Rect();
	car5_rect->x = 132;
	car5_rect->y = 0;
	car5_rect->w = 54;
	car5_rect->h = 28;


	log_short = new SDL_Rect();
	log_short->x = 2;
	log_short->y = 0;
	log_short->w = 84;
	log_short->h = 20;


	log_medium = new SDL_Rect();
	log_medium->x = 88;
	log_medium->y = 0;
	log_medium->w = 116;
	log_medium->h = 20;


	log_long = new SDL_Rect();
	log_long->x = 206;
	log_long->y = 0;
	log_long->w = 180;
	log_long->h = 20;

	frog_N = new SDL_Rect();
	frog_N->x = 2;
	frog_N->y = 0;
	frog_N->w = 24;
	frog_N->h = 20;

	frog_S = new SDL_Rect();
	frog_S->x = 2;
	frog_S->y = 36;
	frog_S->w = 24;
	frog_S->h = 20;

	frog_W = new SDL_Rect();
	frog_W->x = 2;
	frog_W->y = 0;
	frog_W->w = 18;
	frog_W->h = 24;

	frog_E = new SDL_Rect();
	frog_E->x = 2;
	frog_E->y = 24;
	frog_E->w = 18;
	frog_E->h = 24;

	zone_rect = new SDL_Rect();
	zone_rect->x = 0;
	zone_rect->y = 0;
	zone_rect->w = 32;
	zone_rect->h = 32;
	//
	lives_text_rect = new SDL_Rect();
	lives_text_rect->x = 0;
	lives_text_rect->y = 0;
	lives_text_rect->w = 100;
	lives_text_rect->h = 30;

	status_rect = new SDL_Rect();
	status_rect->x = 0;
	status_rect->y = 0;
	status_rect->w = 100;
	status_rect->h = 30;

}


Resources::~Resources()
{
}
