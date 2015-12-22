#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;
class Resources
{
public:
	string folderpath;
	bool loaded;
	Resources(string folderpath, SDL_Renderer* renderer);
	SDL_Texture* Resources::CreateTextureFromBitmap(SDL_Renderer* renderer, string filepath);
	//
	SDL_Texture* Resources::CreateTextureFromText(SDL_Renderer* renderer, string words );
	//
	~Resources();
	void InitRects();
	//
	SDL_Texture* lives_text;
	SDL_Texture* status_text;
	SDL_Texture* back_text;
	SDL_Texture* cars_text;
	SDL_Texture* logs_text;
	SDL_Texture* zone_full;
	SDL_Texture* zone_empty;
	//
	SDL_Rect* car1_rect;
	SDL_Rect* car2_rect;
	SDL_Rect* car3_rect;
	SDL_Rect* car4_rect;
	SDL_Rect* car5_rect;
	SDL_Rect* log_short;
	SDL_Rect* log_medium;
	SDL_Rect* log_long;
	SDL_Rect* lives_text_rect;
	SDL_Rect* status_rect;
	SDL_Rect* frog_W;
	SDL_Rect* frog_E;
	SDL_Rect* frog_N;
	SDL_Rect* frog_S;
	SDL_Rect* zone_rect;
	//
	SDL_Texture* frog_horz;
	SDL_Texture* frog_vert;
	//
	TTF_Font* gFont = NULL;
	//
};

