#include "SceneManager.h"

#include "Logo.h"
#include "Title.h"
#include "Cantina.h"
#include "Wc.h"
#include "Battle.h"
#include "Exterior.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Window.h"
#include "EntityManager.h"
#include "DialogSystem.h"
#include "Audio.h"

#include "Defs.h"
#include "Log.h"

#include "Collision.h"
#include "Speak.h"

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
	speak = new Speak(audio, render, font, input);

	previousScene = new SceneType;
	entityManager->previousScene = previousScene;
	//current = new Logo(input, render, tex);
	//current = new Title(win, input, render, tex);
	//current = new Battle(win, input, render, tex, entityManager, previousScene, font, speak);
	current = new Cantina(win, input, render, tex, entityManager, collision, previousScene, font, speak);
	//current = new Wc(win, input, render, tex, entityManager, collision, audio, previousScene, font, speak);
	//current = new Exterior(win, input, render, tex, entityManager, collision, previousScene, font, speak);
	current->Load();

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

	if (!onTransition)
	{
		//General Debug Keys
		if (input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
			win->ToggleFullscreen(win->window);

		current->Update(dt);
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

	if (dialogueSystem->inConversation)
	{
		speak->Update(dt);
		dialogueSystem->Draw();
	}

	// Draw full screen rectangle in front of everything
	if (onTransition)
	{
		render->DrawRectangle({ -render->camera.x, -render->camera.y, 1280, 720 }, 0, 0, 0, (unsigned char)(255.0f * transitionAlpha));
	}

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
		case SceneType::TITLE: next = new Title(win, input, render, tex); break;
		case SceneType::CANTINA: next = new Cantina(win, input, render, tex, entityManager, collision, previousScene, font, speak); break;
		case SceneType::WC: next = new Wc(win, input, render, tex, entityManager, collision, audio, previousScene, font, speak); break;
		case SceneType::EXTERIOR: next = new Exterior(win, input, render, tex, entityManager, collision, previousScene, font, speak); break;
		case SceneType::BATTLE: next = new Battle(win, input, render, tex, entityManager, font, speak); break;
		default: break;
		}

		current->transitionRequired = false;
	}

	if (input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) dialogueSystem->inConversation = !dialogueSystem->inConversation;
	if (input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) dialogueSystem->SetConversation(1);
	if (input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) dialogueSystem->SetConversation(0);

	if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) return false;
	return true;
}

// Called each loop iteration
bool SceneManager::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	if (current != nullptr) current->Unload();

	return true;
}