#include "SceneManager.h"

#include "Logo.h"
#include "Title.h"
#include "Cantina.h"
#include "Wc.h"
#include "Battle.h"
#include "Exterior.h"
#include "PauseMenu.h"

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
	xMark = tex->Load("assets/sprites/UI/X_mark.png");

	previousScene = new SceneType;
	entityManager->previousScene = previousScene;
	//current = new Logo(input, render, tex);
	current = new Title(this);
	currentscenetype = SceneType::TITLE;
	//current = new Battle(win, input, render, tex, entityManager, font, speak);
	//current = new Cantina(this);
	//current = new Wc(this);
	//current = new Exterior(this);
	current->Load();

	pause = new PauseMenu(this);
	pause->Load();

	dialogueSystem->speak = speak;
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
		if (input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
			win->ToggleFullscreen(win->window);

		if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN) isPause = !isPause;

		if (isPause)
		{
			pause->Update(dt);
			entityManager->CreateEntity(EntityType::HERO)->isPause = true;
		}
		else
		{
			current->Update(dt);
			entityManager->CreateEntity(EntityType::HERO)->isPause = false;
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

	// L12b: Debug pathfinding
	/*
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	const DynArray<iPoint>* path = app->pathFinding->GetLastPath();

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
		case SceneType::LOGO: next = new Logo(input, render, tex); break;
		case SceneType::TITLE: next = new Title(this); break;
		case SceneType::CANTINA: next = new Cantina(this); break;
		case SceneType::WC: next = new Wc(this); break;
		case SceneType::EXTERIOR: next = new Exterior(this); break;
		case SceneType::BATTLE: next = new Battle(win, input, render, tex, entityManager, font, speak); break;
		default: break;
		}

		current->transitionRequired = false;
	}

	if(isPause) pause->Draw();

	if (input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) dialogueSystem->inConversation = !dialogueSystem->inConversation;

	//if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) gameIsWorking = false;

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

	tex->UnLoad(xMark);

	return true;
}