#include "DungeonExt.h"

#include "SceneManager.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

// Constructor
DungeonExt::DungeonExt(SceneManager* sceneManager) : Scene()
{
	this->sceneManager = sceneManager;

	map = new Map(sceneManager->tex);

	if (map->Load("world_dungeon_exterior.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	name.Create("dungeon_ext");
}

// Destructor
DungeonExt::~DungeonExt()
{}

bool DungeonExt::Load()
{


	if (*sceneManager->previousScene == SceneType::EXTERIOR)
	{
		sceneManager->render->camera.x = -32;
		sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(656, 665);
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;
	}
	// When DUNGEON F1 Ready change CANTINA TO DUNGEON
	else if (*sceneManager->previousScene == SceneType::DUNGEON_F1)
	{
		sceneManager->render->camera.x = -32;
		sceneManager->render->camera.y = 0;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(656, 400);
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;
	}
	else if (sceneManager->wasBattle == true)
	{
		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos;
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;

		sceneManager->wasBattle = false;
	}
	else
	{
		sceneManager->render->camera.x = -32;
		sceneManager->render->camera.y = 0;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(656, 390);
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

bool DungeonExt::Update(float dt)
{
	sceneManager->collision->CheckCollision(map);

	if (sceneManager->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position;
		sceneManager->render->prevCam.y = sceneManager->render->camera.y;
		TransitionToScene(SceneType::BATTLE);
	}

	if (sceneManager->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) map->drawColliders = !map->drawColliders;
	
	// Camera moves with player when it is at the middle of the screen
	sceneManager->render->camera.y = -sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y + sceneManager->render->camera.h / 2;

	// Camera stops at limits
	if (sceneManager->render->camera.y < BOTTOM_CAMERA_LIMIT) sceneManager->render->camera.y = BOTTOM_CAMERA_LIMIT;
	else if (sceneManager->render->camera.y > TOP_CAMERA_LIMIT) sceneManager->render->camera.y = TOP_CAMERA_LIMIT;

	if (map->doorHit)
	{
		// DUNGEON KEY -->  && (sceneManager->dungeonKey == true)
		// Añadir feedback text y X button
		if ((sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y < UPPER_DOOR)) TransitionToScene(SceneType::DUNGEON_F1);
		else if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y > UPPER_DOOR) TransitionToScene(SceneType::EXTERIOR);

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
			sceneManager->render->prevCam.y = sceneManager->render->camera.y;
			TransitionToScene(SceneType::BATTLE);
		}
	}
	
	return true;
}

bool DungeonExt::Draw()
{
	// Draw map
	map->Draw(sceneManager->render);

	sceneManager->entityManager->Draw();

	return false;
}

bool DungeonExt::Unload()
{
	*sceneManager->previousScene = SceneType::DUNGEON_EXT;

	enemyEncounter = 0;

	map->Unload();
	RELEASE(map);
	
	sceneManager = nullptr;

	return true;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool DungeonExt::OnGuiMouseClickEvent(GuiControl* control)
{
	if (sceneManager->dialogueSystem->inConversation)
	{
		sceneManager->dialogueSystem->OnGuiMouseClickEvent(control);
	}

	return true;
}