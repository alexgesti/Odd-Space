#include "SceneManager.h"

#include "Logo.h"
#include "Title.h"
#include "Cantina.h"
#include "Wc.h"
#include "Battle.h"
#include "Exterior.h"
#include "PauseMenu.h"
#include "OptionsMenu.h"
#include "ItemsMenu.h"
#include "DungeonExt.h"
#include "DungeonF1.h"
#include "DungeonF2.h"

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL.h"

#define FADEOUT_TRANSITION_SPEED	2.0f
#define FADEIN_TRANSITION_SPEED		2.0f

SceneManager::SceneManager(Input* input, Render* render, Textures* tex, Window* win, EntityManager* entityManager, Audio* audio, DialogueSystem* dialogueSystem) : Module()
{
	name.Create("scenemanager");

	onTransition = false;
	fadeOutCompleted = false;
	transitionAlpha = 0.0f;
	volumeMusic = 128;
	volumeFx = 128;

	this->input = input;
	this->render = render;
	this->tex = tex;
	this->win = win;
	this->entityManager = entityManager;
	this->dialogueSystem = dialogueSystem;
	this->audio = audio;

	this->collision = &entityManager->collision;
}

// Destructor
SceneManager::~SceneManager()
{}

// Called before render is available
bool SceneManager::Awake()
{
	LOG("Loading Scene manager");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneManager::Start()
{
	font = new Font("assets/typo/Adore64.xml", tex);
	speak = new Speak(audio, render, font, input, tex);
	dialogueSystem->speak = speak;
	xMark = tex->Load("assets/sprites/UI/ui_xmark.png");

	doorClose = audio->LoadFx("assets/audio/fx/world_door_close.wav");
	doorOpen = audio->LoadFx("assets/audio/fx/world_door_open.wav");
	leverFx = audio->LoadFx("assets/audio/fx/world_lever.wav");

	previousScene = new SceneType;
	entityManager->previousScene = previousScene;
	current = new Logo(this);
	//current = new Title(this);
	//current = new Battle(win, input, render, tex, entityManager, font, speak);
	//current = new Cantina(this);
	//current = new Wc(this);
	//current = new Exterior(this);
	current = new DungeonF1(this);
	//current = new DungeonF2(this);
	currentscenetype = SceneType::DUNGEON_F1;
	current->Load();

	options = new OptionsMenu(this);
	items = new ItemsMenu(this);
	pause = new PauseMenu(this);
	pause->Load();

	dialogueSystem->speak = speak;
	dialogueSystem->GetObserver(current);
	next = nullptr;

	return true;
}

// Called each loop iteration
bool SceneManager::PreUpdate()
{
	/*
	// L12b: Debug pathfing
	static iPoint origin;
	static bool originSelected = false;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);

	if(app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(originSelected == true)
		{
			app->pathFinding->CreatePath(origin, p);
			originSelected = false;
		}
		else
		{
			origin = p;
			originSelected = true;
		}
	}
	*/

	return true;
}

// Called each loop iteration
bool SceneManager::Update(float dt)
{
	GamePad& pad = input->pads[0];

	if (!onTransition)
	{
		//General Debug Keys
		if (input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) dialogueSystem->inConversation = !dialogueSystem->inConversation;

		if (input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
			win->ToggleFullscreen(win->window);

		if (input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		{
			entityManager->CreateEntity(EntityType::HERO)->noClip = !entityManager->CreateEntity(EntityType::HERO)->noClip;
		}

		if (entityManager->CreateEntity(EntityType::HERO)->noClip == true)
		{
			for (int p = 0; p < entityManager->entities[0].Count(); p++)
				entityManager->entities[0].At(p)->data->infoEntities.info.HP = entityManager->entities[0].At(p)->data->infoEntities.info.maxHP;
		}

		if ((input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN) &&
			(currentscenetype != SceneType::BATTLE && currentscenetype != SceneType::LOGO && currentscenetype != SceneType::TITLE))
		{
			isPause = !isPause;
			if (!isPause)
			{
				items->Unload();
				options->Unload();
				entityManager->CreateEntity(EntityType::HERO)->transitioning = false;
			}
			else entityManager->CreateEntity(EntityType::HERO)->transitioning = true;
			
		}

		if (isPause) pause->Update(dt);
		else
		{
			if (pauseMusicFaded)
			{
				audio->FadeInMusic(0.5f);
				pauseMusicFaded = false;
			}

			current->Update(dt);
		}
	}
	else
	{
		if (!fadeOutCompleted)
		{
			transitionAlpha += (FADEOUT_TRANSITION_SPEED * dt);

			// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
			// For that reason we compare against 1.01f, to avoid last frame loading stop
			if (transitionAlpha > 1.01f)
			{
				transitionAlpha = 1.0f;

				currentscenetype = current->nextScene;
				current->Unload();	// Unload current screen
				next->Load();	// Load next screen

				RELEASE(current);	// Free current pointer
				current = next;		// Assign next pointer
				next = nullptr;

				dialogueSystem->GetObserver(current);

				// Activate fade out effect to next loaded screen
				fadeOutCompleted = true;
			}
		}
		else  // Transition fade out logic
		{
			transitionAlpha -= (FADEIN_TRANSITION_SPEED * dt);

			if (transitionAlpha < -0.01f)
			{
				transitionAlpha = 0.0f;
				fadeOutCompleted = false;
				onTransition = false;
				entityManager->CreateEntity(EntityType::HERO)->transitioning = false;
			}
		}
	}

	// Draw current scene
	current->Draw();
	if (toDrawX) render->DrawTexture(xMark, entityManager->CreateEntity(EntityType::HERO)->position.x + 6, entityManager->CreateEntity(EntityType::HERO)->position.y - 85);

	if (dialogueSystem->inConversation)
	{
		if (!entityManager->CreateEntity(EntityType::HERO)->inConversation) entityManager->CreateEntity(EntityType::HERO)->inConversation = true;
		speak->Update(dt);
		dialogueSystem->Draw();
	}
	else if(entityManager->CreateEntity(EntityType::HERO)->inConversation) entityManager->CreateEntity(EntityType::HERO)->inConversation = false;

	// Draw full screen rectangle in front of everything
	if (onTransition) render->DrawRectangle({ -render->camera.x, -render->camera.y, 1280, 720 }, 0, 0, 0, (unsigned char)(255.0f * transitionAlpha));

	if (isPause) pause->Draw();

	// L12b: Debug pathfinding
	/*
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	const 
	<iPoint>* path = app->pathFinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		app->render->DrawTexture(debugTex, pos.x, pos.y);
	}
	*/

	if (current->transitionRequired)
	{
		entityManager->CreateEntity(EntityType::HERO)->transitioning = true;
		onTransition = true;
		fadeOutCompleted = false;
		transitionAlpha = 0.0f;

		switch (current->nextScene)
		{
		case SceneType::LOGO: next = new Logo(this); break;
		case SceneType::TITLE: next = new Title(this); break;
		case SceneType::CANTINA: next = new Cantina(this); break;
		case SceneType::WC: next = new Wc(this); break;
		case SceneType::EXTERIOR: next = new Exterior(this); break;
		case SceneType::BATTLE: next = new Battle(this); break;
		case SceneType::DUNGEON_EXT: next = new DungeonExt(this); break;
		case SceneType::DUNGEON_F1: next = new DungeonF1(this); break;
		case SceneType::DUNGEON_F2: next = new DungeonF2(this); break;
		default: break;
		}

		current->transitionRequired = false;
	}

	return true;
}

// Called each loop iteration
bool SceneManager::PostUpdate()
{
	return gameIsWorking;
}

// Called before quitting
bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	if (current != nullptr) current->Unload();

	pause->Unload();
	options->Unload();
	items->Unload();

	tex->UnLoad(xMark);

	return true;
}