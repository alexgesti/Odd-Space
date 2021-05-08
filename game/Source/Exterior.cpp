#include "Exterior.h"

#include "SceneManager.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"



// Constructor
Exterior::Exterior(SceneManager* sceneManager) : Scene()
{
	this->sceneManager = sceneManager;

	name.Create("cantina");


	map = new Map(sceneManager->tex);

	// L03: DONE: Load map
	// L12b: Create walkability map on map loading
	if (map->Load("world_cantina_exterior.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}


	animCrazyManIdle->loop = true;
	animCrazyManIdle->speed = 0.05f;
	for (int i = 0; i < 2; ++i)
		animCrazyManIdle->PushBack({ 60 * i, 0, 60, 96 });

	animCrazyManWalkLeft->loop = true;
	animCrazyManWalkLeft->speed = 0.05f;
	for (int i = 0; i < 3; ++i)
		animCrazyManWalkLeft->PushBack({ 60 * i, 96, 60, 96 });
	animCrazyManWalkLeft->PushBack({ 60, 96, 60, 96 });

	currentAnimation = animCrazyManIdle;


	texCrazyManCantina = sceneManager->tex->Load("assets/sprites/npcs/npc_crazymancantina_v01_w.png");
}
// Destructor
Exterior::~Exterior()
{}

bool Exterior::Load() /*EntityManager entityManager)*/
{

	if (*sceneManager->previousScene == SceneType::CANTINA)
	{
		sceneManager->render->camera.x = -32;
		sceneManager->render->camera.y = TOP_CAMERA_LIMIT;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(990, 325);
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;
	}

	else
	{
		sceneManager->render->camera.x = -32;
		sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint (990, 550);
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;
	}

	sceneManager->render->camera.w = sceneManager->win->screenSurface->w;
	sceneManager->render->camera.h = sceneManager->win->screenSurface->h;

	if (!sceneManager->initialTextSaid)
	{
		sceneManager->dialogueSystem->SetConversation(0);
		sceneManager->dialogueSystem->inConversation = true;
		sceneManager->initialTextSaid = true;
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
	sceneManager->collision->CheckCollision(map);

	// L02: DONE 3: Request Load / Save when pressing L/S
	//if (input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) app->LoadGameRequest();
	//if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) app->SaveGameRequest();

	if (sceneManager->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) TransitionToScene(SceneType::BATTLE);

	if (sceneManager->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) map->drawColliders = !map->drawColliders;

	if (sceneManager->collision->currentInteraction != '/0' && sceneManager->crazyManActive == true)
	{

		SDL_Rect playerRect;
		playerRect.x = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.x;
		playerRect.y = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y;
		playerRect.w = playerRect.h = 32;

		if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->interacting == true)
		{
			if (sceneManager->collision->currentInteraction == "crazyman" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{
				sceneManager->dialogueSystem->SetConversation(1);
				sceneManager->dialogueSystem->inConversation = true;

				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';

				crazyManTalking = true;
			}
		}

		if(!sceneManager->dialogueSystem->inConversation) sceneManager->toDrawX = true;

		if (!sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect)) sceneManager->toDrawX = false;
	}

	else if (sceneManager->toDrawX == true) sceneManager->toDrawX = false;


	if (sceneManager->dialogueSystem->currentNode->nodeId == 12)
	{
		flagMoving = true;
		sceneManager->crazyManActive = false;
	}
	if (sceneManager->dialogueSystem->inConversation == false)
	{
		crazyManTalking = false;
	}


	// Camera moves with player when it is at the middle of the screen
	sceneManager->render->camera.y = -sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y + sceneManager->render->camera.h / 2;

	// Camera stops at limits
	if (crazyManTalking == true)
	{
		sceneManager->render->camera.y = -140;
	}
	else
	{
		if (sceneManager->render->camera.y < BOTTOM_CAMERA_LIMIT) sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;
		else if (sceneManager->render->camera.y > TOP_CAMERA_LIMIT) sceneManager->render->camera.y = TOP_CAMERA_LIMIT;
	}

	if (map->doorHit)
	{
		TransitionToScene(SceneType::CANTINA);
		map->doorHit = false;
	}

	if (sceneManager->collision->currentInteraction != '/0')
	{
		if (sceneManager->collision->currentInteraction == "crazyman")
		{
			if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->interacting == true)
			{
				// Cambiar funcion, dialogo con loco
				TransitionToScene(SceneType::CANTINA);
				sceneManager->collision->currentInteraction = '/0';
				sceneManager->entityManager->CreateEntity(EntityType::HERO)->interacting = false;
			}
		}
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


	if (flagMoving == true)
	{
		currentAnimation = animCrazyManWalkLeft;

		if (posCrazyMan.x > -100)
		{
			posCrazyMan.x -= 200 * dt;
		}
		else
		{
			sceneManager->crazyManDrawable = false;
		}
	}


	currentAnimation->Update();

	return true;
}

bool Exterior::Draw()
{
	// Draw map
	map->Draw(sceneManager->render);

	//player->Draw(render);
	if (sceneManager->crazyManActive == true || sceneManager->crazyManDrawable == true)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		sceneManager->render->DrawTexture(texCrazyManCantina, posCrazyMan.x, posCrazyMan.y, &rect);
	}

	sceneManager->entityManager->Draw();

	return false;
}

bool Exterior::Unload()
{
	// TODO: Unload all resources
	*sceneManager->previousScene = SceneType::EXTERIOR;

	enemyEncounter = 0;

	sceneManager->tex->UnLoad(texCrazyManCantina);

	delete animCrazyManIdle;
	animCrazyManIdle = nullptr;
	delete animCrazyManWalkLeft;
	animCrazyManWalkLeft = nullptr;

	map->Unload();
	delete map;
	map = nullptr;

	return true;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool Exterior::OnGuiMouseClickEvent(GuiControl* control)
{
	if (sceneManager->dialogueSystem->inConversation)
	{
		sceneManager->dialogueSystem->OnGuiMouseClickEvent(control);
	}

	return true;
}