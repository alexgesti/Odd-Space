#include "Cantina.h"

#include "SceneManager.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"



// Constructor
Cantina::Cantina(SceneManager* sceneManager) : Scene()
{
	this->sceneManager = sceneManager;

	map = new Map(sceneManager->tex);

	// L03: DONE: Load map
	// L12b: Create walkability map on map loading
	if (map->Load("world_cantina_interior.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	texBarman = sceneManager->tex->Load("assets/sprites/npcs/npc_barman_v01_w.png");

	animBarmanIdle->loop = true;
	animBarmanIdle->speed = 0.05f;
	animBarmanIdle->PushBack({ 0,0,48,96 });
	animBarmanIdle->PushBack({ 48,0,48,96 });


	name.Create("cantina");
}
// Destructor
Cantina::~Cantina()
{}

bool Cantina::Load() /*EntityManager entityManager)*/
{

	if (*sceneManager->previousScene == SceneType::WC)
	{
		sceneManager->render->camera.x = 80;
		sceneManager->render->camera.y = TOP_CAMERA_LIMIT;

		sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(128, 195);
	}

	/*else if (*sceneManager->previousScene == SceneType::BATTLE)
	{
		sceneManager->render->camera.x = 80;
		sceneManager->render->camera.y = TOP_CAMERA_LIMIT;

		sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = sceneManager->entityManager->CreateEntity(EntityType::HERO)->temPos;
	}*/

	else
	{
		sceneManager->render->camera.x = 80;
		sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;

		sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(768, 750);
	}

	sceneManager->render->camera.w = sceneManager->win->screenSurface->w;
	sceneManager->render->camera.h = sceneManager->win->screenSurface->h;

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

bool Cantina::Update(float dt)
{

	sceneManager->collision->CheckCollision(map);

	// L02: DONE 3: Request Load / Save when pressing L/S
	//if (input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) app->LoadGameRequest();
	//if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) app->SaveGameRequest();

	if (sceneManager->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) sceneManager->speak->SayText("This is a very very long sample", true);

	if (sceneManager->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) sceneManager->speak->SayText("This is another very long sample", true);

	if (sceneManager->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) TransitionToScene(SceneType::BATTLE);

	if (sceneManager->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		map->drawColliders = !map->drawColliders;

	if (sceneManager->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) map->noClip = !map->noClip;

	if (sceneManager->collision->currentInteraction != '/0')
	{

		SDL_Rect playerRect;
		playerRect.x = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.x;
		playerRect.y = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y;
		playerRect.w = playerRect.h = 32;

		if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->interacting == true)
		{
			if (sceneManager->collision->currentInteraction == "barman" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{
				// If player talks with barman again before talking to old captain
				if (barmanConv1 && !oldCapConv)
				{
					sceneManager->dialogueSystem->SetConversation(5);
					sceneManager->dialogueSystem->inConversation = true;
				}

				// Triggers second conversation with barman & battle event
				else if (barmanConv1 && oldCapConv && !barmanConv2)
				{
					sceneManager->dialogueSystem->SetConversation(6);
					sceneManager->dialogueSystem->inConversation = true;
					barmanConv2 = true;
				}

				// First time player talks with barman
				else
				{
					sceneManager->dialogueSystem->SetConversation(2);
					sceneManager->dialogueSystem->inConversation = true;
					barmanConv1 = true;
				}

				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';
				barmanConv1 = true;
			}

			if (sceneManager->collision->currentInteraction == "captain" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{
				sceneManager->dialogueSystem->SetConversation(4);
				sceneManager->dialogueSystem->inConversation = true;

				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';
				oldCapConv = true;
			}

			if (sceneManager->collision->currentInteraction == "legendary" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect) && !oldCapConv)
			{
				sceneManager->dialogueSystem->SetConversation(3);
				sceneManager->dialogueSystem->inConversation = true;

				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';
			}
		}

		if (!sceneManager->dialogueSystem->inConversation) sceneManager->toDrawX = true;

		if (!sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect)) sceneManager->toDrawX = false;
	}

	else if (sceneManager->toDrawX == true) sceneManager->toDrawX = false;

	// If legendary pirate conversation has been deactivated don't draw the X
	if(sceneManager->collision->currentInteraction == "legendary" && oldCapConv) sceneManager->toDrawX = false;

	// Second barman conversation can trigger a battle event
	if (barmanConv2 && !sceneManager->dialogueSystem->inConversation)
	{
		barmanConv2 = false;
		if (sceneManager->dialogueSystem->triggerEvent)
		{
			sceneManager->dialogueSystem->triggerEvent = false;
			TransitionToScene(SceneType::BATTLE);
		}
	}
	
	// Camera moves with player when it is at the middle of the screen
	sceneManager->render->camera.y = -sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y + sceneManager->render->camera.h / 2;

	// Camera stops at limits
	if (sceneManager->render->camera.y < BOTTOM_CAMERA_LIMIT) sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;
	else if (sceneManager->render->camera.y > TOP_CAMERA_LIMIT) sceneManager->render->camera.y = TOP_CAMERA_LIMIT;

	if (map->doorHit)
	{
		if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y < UPPER_DOOR) TransitionToScene(SceneType::WC);
		else TransitionToScene(SceneType::EXTERIOR);
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

	animBarmanIdle->Update();

	return true;
}

bool Cantina::Draw()
{
	// Draw map
	map->Draw(sceneManager->render);

	//player->Draw(render);

	sceneManager->entityManager->Draw();


	SDL_Rect rect = animBarmanIdle->GetCurrentFrame();
	sceneManager->render->DrawTexture(texBarman, 31 * 32, 16 * 32 - 16, &rect);

	return false;
}

bool Cantina::Unload()
{
	// TODO: Unload all resources
	*sceneManager->previousScene = SceneType::CANTINA;

	enemyEncounter = 0;

	map->Unload();
	delete map;
	map = nullptr;

	return true;
}