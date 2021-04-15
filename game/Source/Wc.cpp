#include "Wc.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Map.h"

#include "Speak.h"

#include "Defs.h"
#include "Log.h"



// Constructor
Wc::Wc(Window* win, Input* input, Render* render, Textures* tex, EntityManager* entityManager, Collision* collision, Audio* audio, SceneType* previousScene, Font* font, Speak* speak) : Scene()
{
	this->win = win;
	this->input = input;
	this->render = render;
	this->tex = tex;
	this->entityManager = entityManager;
	this->audio = audio;

	this->collision = collision;
	this->speak = speak;

	this->previousScene = previousScene;

	map = new Map(tex);

	// L03: DONE: Load map
	// L12b: Create walkability map on map loading
	if (map->Load("world_cantina_wc.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	xMark = tex->Load("assets/sprites/UI/X_mark.png");

	name.Create("cantina");
}
// Destructor
Wc::~Wc()
{}

bool Wc::Load() /*EntityManager entityManager)*/
{
	render->camera.x = 530;
	render->camera.y = 130;

	entityManager->CreateEntity(EntityType::HERO)->position = iPoint(64, 285);

	wcFx = audio->LoadFx("assets/audio/fx/toilet.wav");

	//map = new Map(tex);

	// L03: DONE: Load map
	// L12b: Create walkability map on map loading
	/*if (map->Load("platformer.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}*/

	// Load music
	//AudioManager::PlayMusic("Assets/Audio/Music/music_spy.ogg");

	// Load game entities
	//Player* player = (Player*)entityManager->CreateEntity(EntityType::PLAYER);
	//player->SetTexture(tex->Load("Assets/Textures/player.png"));
	//entityManager->CreateEntity(EntityType::ENEMY);
	//entityManager->CreateEntity(EntityType::ENEMY);
	//entityManager->CreateEntity(EntityType::ITEM);
	//entityManager->CreateEntity(EntityType::ITEM);
	//entityManager->CreateEntity(EntityType::ITEM);

	// Initialize player

	//player = new Player();
	//player->position = iPoint(200, 400);

	return false;
}

// Called each loop iteration
inline bool CheckCollision(SDL_Rect rec1, SDL_Rect rec2)
{
	if ((rec1.x < (rec2.x + rec2.w) && (rec1.x + rec1.w) > rec2.x) &&
		(rec1.y < (rec2.y + rec2.h) && (rec1.y + rec1.h) > rec2.y)) return true;
	else return false;
}

bool Wc::Update(float dt)
{
	collision->CheckCollision(map);

	// L02: DONE 3: Request Load / Save when pressing L/S
	//if (input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) app->LoadGameRequest();
	//if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) app->SaveGameRequest();

	if (input->GetKey(SDL_SCANCODE_F8) == KEY_UP)
		map->drawColliders = !map->drawColliders;

	if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		win->ToggleFullscreen(win->window);

	if (collision->currentInteraction != '/0')
	{
		SDL_Rect temp = collision->interactRect;
		temp.x -= 10;
		temp.w += 20;
		temp.y -= 10;
		temp.h += 20;

		SDL_Rect playerRect;
		playerRect.x = entityManager->CreateEntity(EntityType::HERO)->position.x;
		playerRect.y = entityManager->CreateEntity(EntityType::HERO)->position.y;
		playerRect.w = playerRect.h = 32;

		if (entityManager->CreateEntity(EntityType::HERO)->interacting == true)
		{
			if (collision->currentInteraction == "flush" && collision->Detect(temp, playerRect))
			{
				if (!audio->IsPlaying(wcFx))
				{
					audio->PlayFx(wcFx);
					toDrawX = false;
				}

				collision->currentInteraction = '/0';
			}
		}

		else if (!audio->IsPlaying(wcFx))toDrawX = true;

		if (!collision->Detect(temp, playerRect)) toDrawX = false;
	}

	if (map->doorHit)
	{
		audio->FadeOutFx(100);
		TransitionToScene(SceneType::CANTINA);
		map->doorHit = false;
	}

	return true;
}

bool Wc::Draw()
{
	// Draw map
	map->Draw(render);

	//player->Draw(render);

	entityManager->Draw();

	if(toDrawX) render->DrawTexture(xMark, collision->interactRect.x - 25, collision->interactRect.y + 5);

	return false;
}

bool Wc::Unload()
{
	// TODO: Unload all resources
	*previousScene = SceneType::WC;

	map->Unload();
	delete map;
	map = nullptr;

	audio->UnloadFx(wcFx - 1);

	tex->UnLoad(xMark);

	return true;
}