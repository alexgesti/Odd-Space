#include "Exterior.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Map.h"
#include "Font.h"

#include "Speak.h"

#include "Defs.h"
#include "Log.h"



// Constructor
Exterior::Exterior(Window* win, Input* input, Render* render, Textures* tex, EntityManager* entityManager, Collision* collision, SceneType* previousScene, Font* font, Speak* speak) : Scene()
{
	this->win = win;
	this->input = input;
	this->render = render;
	this->tex = tex;
	this->entityManager = entityManager;

	this->collision = collision;
	this->speak = speak;

	this->previousScene = previousScene;

	this->font = font;

	map = new Map(tex);

	// L03: DONE: Load map
	// L12b: Create walkability map on map loading
	if (map->Load("world_cantina_exterior.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	name.Create("cantina");
}
// Destructor
Exterior::~Exterior()
{}

bool Exterior::Load() /*EntityManager entityManager)*/
{

	if (*previousScene == SceneType::CANTINA)
	{
		render->camera.x = -32;
		render->camera.y = TOP_CAMERA_LIMIT;

		entityManager->CreateEntity(EntityType::HERO)->position = iPoint (990, 325);
	}

	else
	{
		render->camera.x = -32;
		render->camera.y = BOTTOM_CAMERA_LIMIT;

		entityManager->CreateEntity(EntityType::HERO)->position = iPoint (900, 650);
	}

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

bool Exterior::Update(float dt)
{
	collision->CheckCollision(map);

	// L02: DONE 3: Request Load / Save when pressing L/S
	//if (input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) app->LoadGameRequest();
	//if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) app->SaveGameRequest();

	if (input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) TransitionToScene(SceneType::BATTLE);

	if (input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		map->drawColliders = !map->drawColliders;

	if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) map->noClip = !map->noClip;

	// Camera moves with player when it is at the middle of the screen
	render->camera.y = -entityManager->CreateEntity(EntityType::HERO)->position.y + render->camera.h / 2;

	// Camera stops at limits
	if (render->camera.y < BOTTOM_CAMERA_LIMIT) render->camera.y = BOTTOM_CAMERA_LIMIT;
	else if (render->camera.y > TOP_CAMERA_LIMIT) render->camera.y = TOP_CAMERA_LIMIT;

	if (map->doorHit)
	{
		TransitionToScene(SceneType::CANTINA);
		map->doorHit = false;
	}

	if (collision->currentInteraction != '/0')
	{
		if (collision->currentInteraction == "crazyman")
		{
			if (entityManager->CreateEntity(EntityType::HERO)->interacting == true)
			{
				// Cambiar funcion, dialogo con loco
				TransitionToScene(SceneType::CANTINA);
				collision->currentInteraction = '/0';
				entityManager->CreateEntity(EntityType::HERO)->interacting = false;
			}
		}
	}

	//Enemy Encounter
	if (entityManager->CreateEntity(EntityType::HERO)->position != entityManager->CreateEntity(EntityType::HERO)->temPos)
	{
		enemyEncounter += rand() % 5;
		if (enemyEncounter > rand() % (8500) + 1500)
		{
			enemyEncounter = 0;
			TransitionToScene(SceneType::BATTLE);
		}
	}

	return true;
}

bool Exterior::Draw()
{
	// Draw map
	map->Draw(render);

	//player->Draw(render);

	entityManager->Draw();

	return false;
}

bool Exterior::Unload()
{
	// TODO: Unload all resources
	*previousScene = SceneType::EXTERIOR;

	enemyEncounter = 0;

	map->Unload();
	delete map;
	map = nullptr;

	return true;
}