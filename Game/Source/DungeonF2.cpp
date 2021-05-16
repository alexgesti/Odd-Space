#include "DungeonF2.h"

#include "SceneManager.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

// Constructor
DungeonF2::DungeonF2(SceneManager* sceneManager) : Scene()
{
	this->sceneManager = sceneManager;

	map = new Map(sceneManager->tex);

	if (map->Load("world_dungeon_interiorpart2.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	name.Create("dungeon_f2");

	this->leverTex = sceneManager->tex->Load("maps/prop_dungeon_v01_w.png");
	this->fakeWall = sceneManager->tex->Load("maps/world_dungeon_false_wall.png");

	this->leverFx = sceneManager->audio->LoadFx("audio/fx/world_lever.wav");
	this->winFx = sceneManager->audio->LoadFx("audio/fx/battle_win.wav");
	this->bigdoor = sceneManager->audio->LoadFx("audio/fx/world_big_door_open.wav");
	this->itempick = sceneManager->audio->LoadFx("audio/fx/world_itempick_fx.wav");
}

// Destructor
DungeonF2::~DungeonF2()
{}

bool DungeonF2::Load()
{
	if (*sceneManager->previousScene == SceneType::DUNGEON_F1)
	{
		sceneManager->render->camera.x = 160;
		sceneManager->render->camera.y = -808;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(848, 1168);
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;
	}
	else if (sceneManager->wasBattle == true)
	{

		sceneManager->render->camera.x = 160;
		sceneManager->render->camera.y = sceneManager->render->prevCam.y;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos;
		else sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos = false;

		sceneManager->wasBattle = false;
	}
	else
	{
		sceneManager->render->camera.x = 160;
		sceneManager->render->camera.y = -808;

		if (!sceneManager->entityManager->CreateEntity(EntityType::HERO)->loadedPos) sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(848, 1168);
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

bool DungeonF2::Update(float dt)
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

	if (sceneManager->collision->currentInteraction != '/0')
	{
		SDL_Rect playerRect;
		playerRect.x = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.x;
		playerRect.y = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position.y;
		playerRect.w = playerRect.h = 32;

		if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->interacting == true)
		{
			if (sceneManager->collision->currentInteraction == "palanca_1" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{
				if (sceneManager->p1 == false) sceneManager->p1 = true;
				else sceneManager->p1 = false;

				sceneManager->audio->PlayFx(leverFx);
				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';
			}
			if (sceneManager->collision->currentInteraction == "palanca_2" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{

				if (sceneManager->p2 == false) sceneManager->p2 = true;
				else sceneManager->p2 = false;

				sceneManager->audio->PlayFx(leverFx);


				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';

			}
			if (sceneManager->collision->currentInteraction == "palanca_3" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{

				if (sceneManager->p3 == false) sceneManager->p3 = true;
				else sceneManager->p3 = false;

				sceneManager->audio->PlayFx(leverFx);


				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';

			}
			if (sceneManager->collision->currentInteraction == "palanca_4" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{

				if (sceneManager->p4 == false) sceneManager->p4 = true;
				else sceneManager->p4 = false;

				sceneManager->audio->PlayFx(leverFx);


				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';

			}
			if (sceneManager->collision->currentInteraction == "palanca_5" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{

				if (sceneManager->p5 == false) sceneManager->p5 = true;
				else sceneManager->p5 = false;

				sceneManager->audio->PlayFx(leverFx);


				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';

			}
			if (sceneManager->collision->currentInteraction == "palanca_6" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{

				if (sceneManager->p6 == false) sceneManager->p6 = true;
				else sceneManager->p6 = false;

				sceneManager->audio->PlayFx(leverFx);


				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';

			}
			if (sceneManager->collision->currentInteraction == "palanca_7" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{

				if (sceneManager->p7 == false) sceneManager->p7 = true;
				else sceneManager->p7 = false;

				sceneManager->audio->PlayFx(leverFx);


				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';

			}
			if (sceneManager->collision->currentInteraction == "palanca_8" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{

				if (sceneManager->p8 == false) sceneManager->p8 = true;
				else sceneManager->p8 = false;

				sceneManager->audio->PlayFx(leverFx);


				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';

			}
			if (sceneManager->collision->currentInteraction == "treasure_bonus" && sceneManager->collision->Detect(sceneManager->collision->interactRect, playerRect))
			{
				if (sceneManager->chestopen == false)
				{
					sceneManager->chestopen = true;

					sceneManager->entityManager->CreateEntity(EntityType::ITEM);

					sceneManager->audio->PlayFx(itempick);
				}

				sceneManager->toDrawX = false;

				sceneManager->collision->currentInteraction = '/0';
			}
		}
		// If conversation and WCfx ended draw X to interact again
		if (!sceneManager->dialogueSystem->inConversation) sceneManager->toDrawX = true;
	}

	// If there's no interaction and X is being drawn, stop drawing it
	else if (sceneManager->toDrawX == true) sceneManager->toDrawX = false;

	// Lever Checker
	// Plus 

	if (sceneManager->seq1 == false && sceneManager->seq2 == false && sceneManager->seq3 == false)
	{
		if (sceneManager->p1 == false && sceneManager->p2 == true && sceneManager->p3 == false && sceneManager->p4 == true && sceneManager->p5 == false && sceneManager->p6 == true && sceneManager->p7 == false && sceneManager->p8 == true)
		{
			sceneManager->seq1 = true;
			sceneManager->audio->PlayFx(winFx);

			// Reset
			sceneManager->p1 = false;
			sceneManager->p2 = false;
			sceneManager->p3 = false;
			sceneManager->p4 = false;
			sceneManager->p5 = false;
			sceneManager->p6 = false;
			sceneManager->p7 = false;
			sceneManager->p8 = false;
		}
	}

	// Triangle

	if (sceneManager->seq1 == true && sceneManager->seq2 == false && sceneManager->seq3 == false)
	{
		if (sceneManager->p1 == false && sceneManager->p2 == true && sceneManager->p3 == false && sceneManager->p4 == false && sceneManager->p5 == true && sceneManager->p6 == false && sceneManager->p7 == true && sceneManager->p8 == false)
		{
			sceneManager->seq2 = true;
			sceneManager->audio->PlayFx(winFx);

			// Reset
			sceneManager->p1 = false;
			sceneManager->p2 = false;
			sceneManager->p3 = false;
			sceneManager->p4 = false;
			sceneManager->p5 = false;
			sceneManager->p6 = false;
			sceneManager->p7 = false;
			sceneManager->p8 = false;
		}
	}

	// Square

	if (sceneManager->seq1 == true && sceneManager->seq2 == true && sceneManager->seq3 == false)
	{
		if (sceneManager->p1 == true && sceneManager->p2 == false && sceneManager->p3 == true && sceneManager->p4 == false && sceneManager->p5 == true && sceneManager->p6 == false && sceneManager->p7 == true && sceneManager->p8 == false)
		{
			sceneManager->seq3 = true;
			sceneManager->audio->PlayFx(winFx);

			// Reset
			sceneManager->p1 = false;
			sceneManager->p2 = false;
			sceneManager->p3 = false;
			sceneManager->p4 = false;
			sceneManager->p5 = false;
			sceneManager->p6 = false;
			sceneManager->p7 = false;
			sceneManager->p8 = false;
		}
	}

	// Star

	if (sceneManager->seq1 == true && sceneManager->seq2 == true && sceneManager->seq3 == true)
	{
		sceneManager->door2Open = true;
		sceneManager->entityManager->CreateEntity(EntityType::HERO)->canCross2Door = true;
		if (sceneManager->door2Opening == false)
		{
			sceneManager->audio->PlayFx(sceneManager->doorClose);
			sceneManager->door2Opening = true;
		}

		if (sceneManager->p1 == false && sceneManager->p2 == true && sceneManager->p3 == false &&
			sceneManager->p4 == true && sceneManager->p5 == true && sceneManager->p6 == false &&
			sceneManager->p7 == true && sceneManager->p8 == true && sceneManager->seqESP == false)
		{
			sceneManager->seqESP = true;
			sceneManager->entityManager->CreateEntity(EntityType::HERO)->canCrossESPDoor = true;
			sceneManager->audio->PlayFx(bigdoor);

			// Reset
			sceneManager->p1 = false;
			sceneManager->p2 = false;
			sceneManager->p3 = false;
			sceneManager->p4 = false;
			sceneManager->p5 = false;
			sceneManager->p6 = false;
			sceneManager->p7 = false;
			sceneManager->p8 = false;
		}
	}
	
	if (map->doorHit)
	{
		// DUNGEON KEY -->  && (sceneManager->dungeonKey == true)
		// Añadir feedback text y X button
		sceneManager->audio->PlayFx(sceneManager->stairsFx);
		TransitionToScene(SceneType::DUNGEON_F1);

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

bool DungeonF2::Draw()
{
	SDL_Rect leverTopUpRect = { 480,128,32, 64 };
	SDL_Rect leverTopDownRect = { 544,128,32, 64 };

	SDL_Rect leverRUpRect = { 304,160,48, 64 };
	SDL_Rect leverRDownRect = { 432,160,48, 64 };

	SDL_Rect leverLUpRect = { 96,160,48, 64 };
	SDL_Rect leverLDownRect = { 224,160,48, 64 };

	SDL_Rect leverBotUpRect = { 64,160,32, 64 };
	SDL_Rect leverBotDownRect = { 32,160,32, 64 };

	SDL_Rect chestClose = {480, 192, 128, 64};
	SDL_Rect chestOpen = {608, 192, 128, 64 };

	SDL_Rect wall = { 0, 0, 960, 1824 };

	// Draw map
	map->Draw(sceneManager->render);
	
	// Lever Draw

	if (!sceneManager->seqESP)
	{
		sceneManager->render->DrawTexture(fakeWall, 0, 0, &wall);

		if (sceneManager->p2 == false) sceneManager->render->DrawTexture(leverTex, 432, 912, &leverTopUpRect);
		else sceneManager->render->DrawTexture(leverTex, 432, 912, &leverTopDownRect);
	}

	if(sceneManager->p1 == false) sceneManager->render->DrawTexture(leverTex, 208, 912, &leverTopUpRect);
	else sceneManager->render->DrawTexture(leverTex, 208, 912, &leverTopDownRect);

	if (sceneManager->p3 == false) sceneManager->render->DrawTexture(leverTex, 656, 912, &leverTopUpRect);
	else sceneManager->render->DrawTexture(leverTex, 656, 912, &leverTopDownRect);

	if (sceneManager->p4 == false) sceneManager->render->DrawTexture(leverTex, 912, 1392, &leverRUpRect);
	else sceneManager->render->DrawTexture(leverTex, 912, 1392, &leverRDownRect);

	if (sceneManager->p5 == false) sceneManager->render->DrawTexture(leverTex, 656, 1760, &leverBotUpRect);
	else sceneManager->render->DrawTexture(leverTex, 656, 1760, &leverBotDownRect);

	if (sceneManager->p6 == false) sceneManager->render->DrawTexture(leverTex, 432, 1760, &leverBotUpRect);
	else sceneManager->render->DrawTexture(leverTex, 432, 1760, &leverBotDownRect);

	if (sceneManager->p7 == false) sceneManager->render->DrawTexture(leverTex, 208, 1760, &leverBotUpRect);
	else sceneManager->render->DrawTexture(leverTex, 208, 1760, &leverBotDownRect);

	if (sceneManager->p8 == false) sceneManager->render->DrawTexture(leverTex, 0, 1392, &leverLUpRect);
	else sceneManager->render->DrawTexture(leverTex, 0, 1392, &leverLDownRect);

	if (sceneManager->chestopen == false) sceneManager->render->DrawTexture(leverTex, 256 + chestClose.w, 224, &chestClose);
	else sceneManager->render->DrawTexture(leverTex, 256 + chestOpen.w, 224, &chestOpen);

	sceneManager->entityManager->Draw();

	return false;
}

bool DungeonF2::Unload()
{
	*sceneManager->previousScene = SceneType::DUNGEON_F2;

	sceneManager->tex->UnLoad(leverTex);
	sceneManager->tex->UnLoad(fakeWall);

	sceneManager->audio->UnloadFx(leverFx);
	sceneManager->audio->UnloadFx(winFx);
	sceneManager->audio->UnloadFx(bigdoor);

	enemyEncounter = 0;

	map->Unload();
	RELEASE(map);

	sceneManager = nullptr;

	return true;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool DungeonF2::OnGuiMouseClickEvent(GuiControl* control)
{
	if (sceneManager->dialogueSystem->inConversation)
	{
		sceneManager->dialogueSystem->OnGuiMouseClickEvent(control);
	}

	return true;
}