#include "DungeonF1.h"

#include "SceneManager.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

// Constructor
DungeonF1::DungeonF1(SceneManager* sceneManager) : Scene()
{
	this->sceneManager = sceneManager;

	map = new Map(sceneManager->tex);

	if (map->Load("world_dungeon_interiorpart1.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	name.Create("dungeon_f1");

	this->door1Tex = sceneManager->tex->Load("assets/maps/prop_dungeon_v02_w.png");

	this->stairsFx = sceneManager->audio->LoadFx("assets/audio/fx/world_stairs.wav");
	this->leverFx = sceneManager->audio->LoadFx("assets/audio/fx/world_lever.wav");

}

// Destructor
DungeonF1::~DungeonF1()
{}

bool DungeonF1::Load()
{
	if (*sceneManager->previousScene == SceneType::DUNGEON_EXT)
	{
		sceneManager->render->camera.x = RIGHT_CAMERA_LIMIT;
		sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(2873, 1712);
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;
	}
	// When DUNGEON F1 Ready change CANTINA TO DUNGEON
	else if (*sceneManager->previousScene == SceneType::DUNGEON_F2)
	{
		sceneManager->render->camera.x = LEFT_CAMERA_LIMIT;
		sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(80, 1776);
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;
	}
	else if (sceneManager->wasBattle == true)
	{
		sceneManager->render->camera.x = sceneManager->render->prevCam.x;
		sceneManager->render->camera.y = sceneManager->render->prevCam.y;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos;
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;

		sceneManager->wasBattle = false;
	}
	else
	{
		sceneManager->render->camera.x = RIGHT_CAMERA_LIMIT;
		sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(2873, 1712);
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;
	}




	sceneManager->render->camera.w = sceneManager->win->screenSurface->w;
	sceneManager->render->camera.h = sceneManager->win->screenSurface->h;

	return false;

}

// Called each loop iteration
inline bool CheckCollision(SDL_Rect rec1, SDL_Rect rec2)
{
	if ((rec1.x < (rec2.x + rec2.w) && (rec1.x + rec1.w) > rec2.x) &&
		(rec1.y < (rec2.y + rec2.h) && (rec1.y + rec1.h) > rec2.y)) return true;
	else return false;
}

bool DungeonF1::Update(float dt)
{
	sceneManager->collision->CheckCollision(map);

	if (sceneManager->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position;
		sceneManager->render->prevCam.x = sceneManager->render->camera.x;
		sceneManager->render->prevCam.y = sceneManager->render->camera.y;
		TransitionToScene(SceneType::BATTLE);
	}

	if (sceneManager->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) map->drawColliders = !map->drawColliders;

	// Camera moves with player when it is at the middle of the screen
	sceneManager->render->camera.x = -sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.x + sceneManager->render->camera.w / 2;
	sceneManager->render->camera.y = -sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y + sceneManager->render->camera.h / 2;

	// Camera stops at limits
	if (sceneManager->render->camera.x < RIGHT_CAMERA_LIMIT) sceneManager->render->camera.x = RIGHT_CAMERA_LIMIT;
	else if (sceneManager->render->camera.x > LEFT_CAMERA_LIMIT) sceneManager->render->camera.x = LEFT_CAMERA_LIMIT;
	if (sceneManager->render->camera.y < BOTTOM_CAMERA_LIMIT) sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;
	else if (sceneManager->render->camera.y > TOP_CAMERA_LIMIT) sceneManager->render->camera.y = TOP_CAMERA_LIMIT;

	if (sceneManager->collision->currentInteraction != '/0')
	{
		SDL_Rect playerRect;
		playerRect.x = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.x;
		playerRect.y = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y;
		playerRect.w = playerRect.h = 32;

		if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->interacting == true)
		{
			if (sceneManager->leverCro == false)
			{
				if (sceneManager->collision->currentInteraction == "cross_lever" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
				{

					//Lever Feedback
					if (sceneManager->leverCro == false)
					{
						if ((sceneManager->levers.size() >= 0) && (sceneManager->levers.size() <= 3))
						{
							sceneManager->levers.push_back(1);
						}
						sceneManager->leverCro = true;
					}

					sceneManager->toDrawX = false;

					sceneManager->collision->currentInteraction = '/0';

				}
			}
			if (sceneManager->leverTri == false)
			{
				if (sceneManager->collision->currentInteraction == "triangular_lever" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
				{

					//Lever Feedback
					if (sceneManager->leverTri == false)
					{
						if ((sceneManager->levers.size() >= 0) && (sceneManager->levers.size() <= 3))
						{
							sceneManager->levers.push_back(2);
						}
						sceneManager->leverTri = true;
					}

					sceneManager->toDrawX = false;

					sceneManager->collision->currentInteraction = '/0';

				}
			}
			if (sceneManager->leverCir == false)
			{
				if (sceneManager->collision->currentInteraction == "circular_lever" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
				{

					//Lever Feedback
					if (sceneManager->leverCir == false)
					{
						if ((sceneManager->levers.size() >= 0) && (sceneManager->levers.size() <= 3))
						{
							sceneManager->levers.push_back(3);
						}
						sceneManager->leverCir = true;
					}

					sceneManager->toDrawX = false;

					sceneManager->collision->currentInteraction = '/0';

				}
			}
		}

		// If conversation and WCfx ended draw X to interact again
		if (!sceneManager->dialogueSystem->inConversation) sceneManager->toDrawX = true;
	}

	// If there's no interaction and X is being drawn, stop drawing it
	else if (sceneManager->toDrawX == true) sceneManager->toDrawX = false;

	//Lever Checker

	if (sceneManager->leverCro == true || sceneManager->leverTri == true || sceneManager->leverCir == true)
	{
		if (sceneManager->levers.size() == 1)
		{
			if (sceneManager->levers[0] != 1)
			{
				sceneManager->levers.clear();
				//audio feedback

				sceneManager->leverCro = false;
				sceneManager->leverTri = false;
				sceneManager->leverCir = false;

				sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position;
				sceneManager->render->prevCam.x = sceneManager->render->camera.x;
				sceneManager->render->prevCam.y = sceneManager->render->camera.y;
				TransitionToScene(SceneType::BATTLE);

			}
		}
		if (sceneManager->levers.size() == 2)
		{
			if (sceneManager->levers[1] != 2)
			{
				sceneManager->levers.clear();
				//audio feedback

				sceneManager->leverCro = false;
				sceneManager->leverTri = false;
				sceneManager->leverCir = false;

				sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position;
				sceneManager->render->prevCam.x = sceneManager->render->camera.x;
				sceneManager->render->prevCam.y = sceneManager->render->camera.y;
				TransitionToScene(SceneType::BATTLE);
			}
		}
		if (sceneManager->levers.size() == 3)
		{
			if (sceneManager->levers[2] != 3)
			{
				sceneManager->levers.clear();
				//audio feedback

				sceneManager->leverCro = false;
				sceneManager->leverTri = false;
				sceneManager->leverCir = false;

				sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position;
				sceneManager->render->prevCam.x = sceneManager->render->camera.x;
				sceneManager->render->prevCam.y = sceneManager->render->camera.y;
				TransitionToScene(SceneType::BATTLE);
			}
		}
	}

	// Door 1 correct

	if (sceneManager->levers == sceneManager->door1Sol)
	{
		sceneManager->door1Open = true;
		// audio feedback

	}

	if (map->doorHit)
	{
		// Swap WC -> End Scene
		sceneManager->audio->PlayFx(stairsFx);
		if ((sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y < END_DOOR)) TransitionToScene(SceneType::WC);
		else if ((sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.x > HORIZONTAL_DOOR)) TransitionToScene(SceneType::DUNGEON_EXT);
		else if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.x < HORIZONTAL_DOOR) TransitionToScene(SceneType::DUNGEON_F2);

		
		map->doorHit = false;
	}

	//Enemy Encounter
	if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->position != sceneManager->entityManager->CreateEntity(EntityType::HERO)->temPos)
	{
		enemyEncounter += rand() % 5;
		if (enemyEncounter > rand() % (8500) + 1500)
		{
			enemyEncounter = 0;
			sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position;
			sceneManager->render->prevCam.x = sceneManager->render->camera.x;
			sceneManager->render->prevCam.y = sceneManager->render->camera.y;
			TransitionToScene(SceneType::BATTLE);
		}
	}

	return true;
}

bool DungeonF1::Draw()
{
	SDL_Rect rect = { 0, 0, 192,192 };

	// Draw map
	map->Draw(sceneManager->render);
	
	if (sceneManager->door1Open == false) sceneManager->render->DrawTexture(door1Tex, 384, 1152, &rect);

	sceneManager->entityManager->Draw();

	return false;
}

bool DungeonF1::Unload()
{
	*sceneManager->previousScene = SceneType::DUNGEON_F1;

	enemyEncounter = 0;

	map->Unload();
	delete map;
	map = nullptr;

	return true;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool DungeonF1::OnGuiMouseClickEvent(GuiControl* control)
{
	if (sceneManager->dialogueSystem->inConversation)
	{
		sceneManager->dialogueSystem->OnGuiMouseClickEvent(control);
	}

	return true;
}