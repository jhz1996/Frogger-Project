#include "Game.h"


const int WINDOW_WIDTH(448);
const int WINDOW_HEIGHT(512);
const int GAME_WIDTH(448);
const int GAME_HEIGHT(432);

const int windowX(300);
const int windowY(150);
const int levels = 100;

// Resource surfaces
//Resources* res;


using namespace std;



// Game constructor. Takes in the filepath and passes it to resources.
Game::Game(string folderpath)
{
	window = NULL;
	screen = NULL;
	render = NULL;
	FPS = 60;
	curStage = 0;
	stageCount = 3;
	this->folderpath = folderpath;
}

// Returns window height.
int Game::GetWindowHeight()
{
	return WINDOW_HEIGHT;
}

// Returns window width.
int Game::GetWindowWidth()
{
	return WINDOW_WIDTH;
}

// Initalizes and loads the SDL, SDL_Mixer, and SDL_TTF libraries.
bool Game::Initalize()
{
	bool result = true;
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL could not be initalized." << endl << SDL_GetError();
		return false;
	}

	// Assuming all is well. Proceeding.
	window = SDL_CreateWindow("Frogger", windowX, windowY, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface(window);


	// Renderer
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	TTF_Init();

	cout << "SDL initalized!" << endl;
	cout << "Window size: " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << "." << endl;
	cout << "FPS capped to " << FPS << "." << endl;
	
	return result;
}

// Loads the images and sounds necessary for the game.
bool Game::LoadAssets()
{
	bool result = true;
	try
	{
		res = new Resources(folderpath, render);
		if (res->loaded == true)
		{
			cout << "Assets Loaded!" << endl;
		}
		else
		{
			result = false;
			cout << "Asset loading failed!" << endl;
		}
	}
	catch (exception)
	{
		cout << "An error occured loading assets" << endl;
	}
	
	// Cristian's sounds.
	froggerTheme = Mix_LoadMUS((folderpath + "/sounds/theme.wav").c_str());
	hop = Mix_LoadWAV((folderpath + "/sounds/hop.wav").c_str());
	finish = Mix_LoadWAV((folderpath + "/sounds/finished.wav").c_str());
	dead = Mix_LoadWAV((folderpath + "/sounds/dead.wav").c_str());
	start = Mix_LoadWAV((folderpath + "/sounds/startup.wav").c_str());
	SDL_Color textColor = { 0, 0, 0 };

	return result;
}

// The gameloop function. This is where the game class enters in to the primary loop.
void Game::GameLoop()
{
	for (curStage = 0; curStage < stageCount; curStage++)
	{
		Manager m = Manager(*this);
		m.BuildLevel(curStage);
		Mix_PlayChannel(-1, start, 0);
		Mix_VolumeMusic(35);
		Mix_VolumeChunk(hop, 60);
		Mix_PlayMusic(froggerTheme, -1);
		if (m.isGameOver){
			Mix_PauseMusic();
		}
		SDL_Event e;
		while (m.isGameOver != true)
		{
			if (SDL_PollEvent(&e) != 0)
				m.ProcessEvent(e);
			m.ProcessEntities();
			m.ProcessCollisions();
			m.DrawEntities();
			m.Refresh();
		}

		// If the game is over but the level is incomplete, the user rage quit.
		if (m.isLevelComplete == false) break; // Break out!
		cout << "Level " << curStage + 1 << " complete!" << endl;
		cout << "Level " << curStage + 2 << " starting in 5 seconds..." << endl;

		SDL_Delay(2000);
	}
}

// Game's over. Clean up resources.
void Game::Close()
{
	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


Game::~Game()
{
}
