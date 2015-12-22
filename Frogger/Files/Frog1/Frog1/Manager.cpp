#include "Manager.h"

using namespace std;

Game* game;
bool isGameOver = false;
bool isGameQuit = false;
bool isLevelComplete = false;
string strLives = "";
string strStatus = "";


// The manager takes in a pointer to the game class. The manager needs access to everything.
Manager::Manager(Game &g)
{
	game = &g;
	lanes.clear();
}



// Polls for an event. Commonly keyboard input.
void Manager::ProcessEvent(SDL_Event e)
{
	// If the SDL event is termination, quit the program.
	if (e.type == SDL_QUIT)
	{
		isGameOver = true;
		return;
	}


	// Otherwise, get the current key states.
	int yvel = 32;
	int xvel = 24;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			Mix_PlayChannel(-1, game->hop, 0);
			player->y = player->y - yvel;
			player->name = "frog_N";
		}
		else if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			Mix_PlayChannel(-1, game->hop, 0);
			player->y = player->y + yvel;
			player->name = "frog_S";
		}
		else if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			Mix_PlayChannel(-1, game->hop, 0);
			player->x = player->x - xvel;
			player->name = "frog_W";
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			Mix_PlayChannel(-1, game->hop, 0);
			player->x = player->x + xvel;
			player->name = "frog_E";
		}
		else if (currentKeyStates[SDL_SCANCODE_ESCAPE])
		{
			// ESCAPE KEY
			cout << "Enter the level to play: ";
			int l;
			cin >> l;
			game->curStage = l;
			BuildLevel(l);
		}
		else if (currentKeyStates[SDL_SCANCODE_GRAVE])
		{
			// Toggles noclip. Only used for debug.
			if (player->isSolid == true)
			{
				player->isSolid = false;
			}
			else
			{
				player->isSolid = true;
			}
		}
		else
		{
			// Some other key was hit (or maybe none).
			player->vx = 0;
			player->vy = 0;
		}
	}
}





// Updates the positions of entities.
void Manager::ProcessEntities()
{
	for (auto lane = lanes.begin(); lane != lanes.end(); lane++)
	{
		lane->Update();
	}
	player->Update();
	player->CheckBounds(game->GetWindowWidth(), 460);
}




// Draws each iteration of the game loop. This includes the background, entities, etc.
void Manager::DrawEntities()
{

	// Draw the background first.
	//
	SDL_Rect livesRect = *game->res->lives_text_rect;
	livesRect.x = 20;
	livesRect.y = 480;

	SDL_Rect statusRect = *game->res->status_rect;
	statusRect.x = 176;
	statusRect.y = 264;
	
	SDL_RenderCopy(game->render, game->res->back_text, NULL, NULL);
	//
	// Display texts to the screen.
	SDL_RenderCopy(game->render, game->res->lives_text, NULL, &livesRect);
	if (strStatus != "")
		SDL_RenderCopy(game->render, game->res->status_text, NULL, &statusRect);
	

	for (auto it = lanes.begin(); it != lanes.end(); it++)
	{
		for (auto ent = it->ents.begin(); ent != it->ents.end(); ent++)
		{
			DrawEntity(*ent);
		}
	}

	// Draw the player.
	DrawEntity(*player);


	// Show all rendering to the screen.
	SDL_RenderPresent(game->render);
}




// Assigning a texture to each entitiy based upon entity name.
// This function could probably be improved for efficency.
void Manager::DrawEntity(Entity ent)
{
	string name = ent.getName();
	SDL_Rect posRect;
	posRect.x = ent.xpos();
	posRect.y = ent.ypos();
	posRect.w = ent.width();
	posRect.h = ent.height();
	if (name == "")
	{


	}
	else if (name == "car1")
	{
		SDL_RenderCopy(game->render, game->res->cars_text, game->res->car1_rect, &posRect);
	}
	else if (name == "car2")
	{
		SDL_RenderCopy(game->render, game->res->cars_text, game->res->car2_rect, &posRect);
	}
	else if (name == "car3")
	{
		SDL_RenderCopy(game->render, game->res->cars_text, game->res->car3_rect, &posRect);
	}
	else if (name == "car4")
	{
		SDL_RenderCopy(game->render, game->res->cars_text, game->res->car4_rect, &posRect);
	}
	else if (name == "car5")
	{
		SDL_RenderCopy(game->render, game->res->cars_text, game->res->car5_rect, &posRect);
	}
	else if (name == "log_short")
	{
		SDL_RenderCopy(game->render, game->res->logs_text, game->res->log_short, &posRect);
	}
	else if (name == "log_medium")
	{
		SDL_RenderCopy(game->render, game->res->logs_text, game->res->log_medium, &posRect);
	}
	else if (name == "log_long")
	{
		SDL_RenderCopy(game->render, game->res->logs_text, game->res->log_long, &posRect);
	}
	else if (name == "frog_N")
	{
		posRect = *game->res->frog_N;
		posRect.x = ent.xpos();
		posRect.y = ent.ypos();
		SDL_RenderCopy(game->render, game->res->frog_vert, game->res->frog_N, &posRect);
	}
	else if (name == "frog_S")
	{
		posRect = *game->res->frog_S;
		posRect.x = ent.xpos();
		posRect.y = ent.ypos();
		SDL_RenderCopy(game->render, game->res->frog_vert, game->res->frog_S, &posRect);
	}
	else if (name == "frog_E")
	{
		posRect = *game->res->frog_E;
		posRect.x = ent.xpos();
		posRect.y = ent.ypos();
		SDL_RenderCopy(game->render, game->res->frog_horz, game->res->frog_E, &posRect);
	}
	else if (name == "frog_W")
	{
		posRect = *game->res->frog_W;
		posRect.x = ent.xpos();
		posRect.y = ent.ypos();
		SDL_RenderCopy(game->render, game->res->frog_horz, game->res->frog_W, &posRect);
	}
	else if (name == "zone")
	{
		if (ent.isSolid == true)
		{
			SDL_RenderCopy(game->render, game->res->zone_full, game->res->zone_rect, &posRect);
		}
		else
		{
			SDL_RenderCopy(game->render, game->res->zone_empty, game->res->zone_rect, &posRect);
		}
	}
	else if (name == "text")
	{
		posRect = *game->res->lives_text_rect;
		posRect.x = 100;
		posRect.y = 100;
		SDL_RenderCopy(game->render, game->res->lives_text, game->res->lives_text_rect, &posRect);
	}
	else
	{
	}
}



// Checks collisiions between the player and other entities.
// Essentially checks to see if the player is dead.
void Manager::ProcessCollisions()
{

	// Best part! We only need to check collisions between the upper, lower, and current lanes!.
	int curLane = player->getLane();
	int upLane = curLane - 1;
	int downLane = curLane + 1;
	bool collided = false;

	for (int i = downLane; i >= upLane; i--)
	{
		if (i >= 13 || i < 0) continue;
		
		
		Lane* tempLane = &lanes[i];
		for (auto ent = tempLane->ents.begin(); ent != tempLane->ents.end(); ent++)
		{
			char hitSide = player->isIntersect(&*ent);
			if (hitSide != 'F' && player->isSolid == true)
			{
				collided = true;
				bool cannotRide = ent->isSolid;
				player->onIntersect(&*ent, hitSide);
				
				// Aw darn, we couldn't ride the log because its not a log its a car so we died rip in peace.
				if (cannotRide == true)
				{
					HandleDeath(player->centerX(), player->centerY());
				}
				else if (ent->name == "zone")
				{
					ent->isSolid = true;
					HandleRespawn();
				}

			}
		}
	}
	if (collided == false)
	{
		player->vx = 0;
		player->vy = 0;
	}


	// Now we check and see if the player is in the water region and it isn't collided.
	if (player->centerY() >= 0 && player->centerY() < 258 && collided == false && player->isSolid == true)
	{
		HandleDeath(player->centerX(), player->centerY());
	}
}




// Refreshes the screen and reupdates nesc. variables.
// Refresh is the last command called in the gameloop.
void Manager::Refresh()
{
	strLives = "Lives: " + to_string(lives);
	if (strStatus != "")
	{
		SDL_Delay(1800);
		strStatus = "";
	}

	bool areZonesFilled = true;
	for (int i = 0; i < 5; i++)
		if (lanes[0].ents[i].isSolid == false)
			areZonesFilled = false;

	if (areZonesFilled)
	{
		isLevelComplete = true;
		isGameOver = true;
	}

	SDL_RenderClear(game->render);
	SDL_Delay(1000 / game->FPS);
}


void Manager::BuildFrog()
{
	int voff = 32;
	player = new Frog(game->GetWindowWidth() / 2 - 12, game->GetWindowHeight() - 2 * voff + 2);
}


// Handles a player death. Hosts a funeral and everything. It's really sad.
void Manager::HandleDeath(int x, int y)
{
	// Remove a life.
	--lives;
	strLives = "Lives: " + to_string(lives);
	game->res->lives_text = game->res->CreateTextureFromText(game->render, strLives);

	if (lives > 0)
	{
		Mix_PlayChannel(-1, game->dead, 0);
		cout << "Player killed - (" << lives << ") lives remain" << endl;
		BuildFrog();
	}
	else
	{
		strStatus = "GAME OVER";
		game->res->status_text = game->res->CreateTextureFromText(game->render, strStatus);
		DrawEntities();

		SDL_Event e;
		SDL_PollEvent(&e);
		while (e.type != SDL_QUIT)
		{
			SDL_PollEvent(&e);
		}


		isGameQuit = true;
		isGameOver = true;
		isLevelComplete = false;
	}
}


// Hooray! The player scored! Put the player back at the start.
void Manager::HandleRespawn()
{
	// Respawns occur when the player has filled up a zone.
	Mix_PlayChannel(-1, game->finish, 0);
	cout << "Player scored a zone!" << endl;
	BuildFrog();
}


// Construct initial entity positions based upon the level design in the Stage.cpp class.
void Manager::BuildLevel(int level)
{
	lives = 4;
	isGameOver = false;
	isLevelComplete = false;
	BuildFrog();
	int voff = 32;

	Stage s = Stage();
	for (int i = 0; i < s.rows; i++)
	{
		int ylevel = i*voff + 64;
		string entName = s.stages[level][i][0];
		int count = atoi(s.stages[level][i][1].c_str());
		int speed = atoi(s.stages[level][i][2].c_str());
		Lane* l = new Lane(EntFromString(entName), game->GetWindowWidth(), game->GetWindowHeight(), count, speed, ylevel);
		lanes.push_back(*l);
	}

	cout << "Level " << level + 1 << " loaded!" << endl;
	strLives = "Lives: " + to_string(lives);
	strStatus = "Level: " + to_string(level + 1);
	game->res->lives_text = game->res->CreateTextureFromText(game->render, strLives);
	game->res->status_text = game->res->CreateTextureFromText(game->render, strStatus);
}



// Constructs and entity from the string specified in the Stage.cpp 3d array.
// Could be improved for efficency.
Entity Manager::EntFromString(string entName)
{
	// This is where we bind the resources with the entity which we send to the lane. Do this tomorrow.
	Entity* ent;
	string name = entName;
	

	if (name == "")
	{
		ent = new Entity(0, 0, 0, 0, 0, 0, entName);
	}
	else if (name == "car1")
	{
		ent = new Entity(0, 0, game->res->car1_rect->w, game->res->car1_rect->h, 0, 0, entName);
	}
	else if (name == "car2")
	{
		ent = new Entity(0, 0, game->res->car2_rect->w, game->res->car2_rect->h, 0, 0, entName);
	}
	else if (name == "car3")
	{
		ent = new Entity(0, 0, game->res->car3_rect->w, game->res->car3_rect->h, 0, 0, entName);

	}
	else if (name == "car4")
	{
		ent = new Entity(0, 0, game->res->car4_rect->w, game->res->car4_rect->h, 0, 0, entName);

	}
	else if (name == "car5")
	{
		ent = new Entity(0, 0, game->res->car5_rect->w, game->res->car5_rect->h, 0, 0, entName);

	}
	else if (name == "log_short")
	{
		ent = new Entity(0, 3, game->res->log_short->w, game->res->log_short->h, 0, 0, entName);
		ent->isSolid = false;
	}
	else if (name == "log_medium")
	{
		ent = new Entity(0, 3, game->res->log_medium->w, game->res->log_medium->h, 0, 0, entName);
		ent->isSolid = false;
	}
	else if (name == "log_long")
	{
		ent = new Entity(0, 3, game->res->log_long->w, game->res->log_long->h, 0, 0, entName);
		ent->isSolid = false;
	}
	else if (name == "zone")
	{
		ent = new Entity(0, 0, game->res->zone_rect->w, game->res->zone_rect->h, 0, 0, entName);
		ent->isSolid = false;
	}
	else
	{
		ent = new Entity(0, 0, 0, 0, 0, 0, entName);
	}
	return *ent;
}



Manager::~Manager()
{
}
