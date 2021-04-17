#include "Wc.h"

#include "SceneManager.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"



// Constructor
Wc::Wc(SceneManager* sceneManager) : Scene()
{
	this->sceneManager = sceneManager;

	map = new Map(sceneManager->tex);

	// L03: DONE: Load map
	// L12b: Create walkability map on map loading
	if (map->Load("world_cantina_wc.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	name.Create("cantina");
}
// Destructor
Wc::~Wc()
{}

bool Wc::Load() /*EntityManager entityManager)*/
{
	sceneManager->render->camera.x = 530;
	sceneManager->render->camera.y = 130;

	sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(64, 285);

	wcFx = sceneManager->audio->LoadFx("assets/audio/fx/toilet.wav");

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
	sceneManager->collision->CheckCollision(map);

	// L02: DONE 3: Request Load / Save when pressing L/S
	//if (input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) app->LoadGameRequest();
	//if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) app->SaveGameRequest();

	if (sceneManager->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) TransitionToScene(SceneType::BATTLE);

	if (sceneManager->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) map->drawColliders = !map->drawColliders;

	if (sceneManager->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) map->noClip = !map->noClip;

	if (sceneManager->collision->currentInteraction != '/0')
	{

		SDL_Rect playerRect;
		playerRect.x = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.x;
		playerRect.y = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y;
		playerRect.w = playerRect.h = 32;

		if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->interacting == true)
		{
			if (sceneManager->collision->currentInteraction == "flush" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{
				if (!sceneManager->audio->IsPlaying(wcFx))
				{
					sceneManager->audio->PlayFx(wcFx);
					sceneManager->toDrawX = false;
					enemyEncounter += 1500;

				}

				sceneManager->collision->currentInteraction = '/0';
			}
		}

		else if (!sceneManager->audio->IsPlaying(wcFx)) sceneManager->toDrawX = true;

		if (!sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect)) sceneManager->toDrawX = false;
	}

	else if (sceneManager->toDrawX == true) sceneManager->toDrawX = false;

	if (map->doorHit)
	{
		sceneManager->audio->FadeOutFx(100);
		TransitionToScene(SceneType::CANTINA);
		map->doorHit = false;
	}

	//Enemy Encounter
	if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->position != sceneManager->entityManager->CreateEntity(EntityType::HERO)->temPos)
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

bool Wc::Draw()
{
	// Draw map
	map->Draw(sceneManager->render);

	//player->Draw(render);

	sceneManager->entityManager->Draw();

	return false;
}

bool Wc::Unload()
{
	// TODO: Unload all resources
	*sceneManager->previousScene = SceneType::WC;

	enemyEncounter = 0;

	map->Unload();
	delete map;
	map = nullptr;

	sceneManager->audio->UnloadFx(wcFx - 1);

	return true;
}