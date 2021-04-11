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

#include "Defs.h"
#include "Log.h"

#include "Collision.h"

#include "SDL/include/SDL.h"

#define FADEOUT_TRANSITION_SPEED	2.0f
#define FADEIN_TRANSITION_SPEED		2.0f

SceneManager::SceneManager(Input* input, Render* render, Textures* tex, Window* win, EntityManager* entityManager) : Module()
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

	previousScene = new SceneType;
	entityManager->previousScene = previousScene;
	//current = new Logo(input, render, tex);
	//current = new Title(win, input, render, tex);
	current = new Battle(win, input, render, tex, entityManager, font);
	//current = new Cantina(win, input, render, tex, entityManager, collision, previousScene, font);
	//current = new Wc(win, input, render, tex, entityManager, collision, previousScene, font);
	//current = new Exterior(win, input, render, tex, entityManager, collision, previousScene, font);
	current->Load();

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
		//if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) render->camera.y -= 1;
		//if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) render->camera.y += 1;
		//if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) render->camera.x -= 1;
		//if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) render->camera.x += 1;

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
				entityManager->CreateEntity(EntityType::PLAYER)->transitioning = false;
			}
		}
	}

	// Draw current scene
	current->Draw();

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
		entityManager->CreateEntity(EntityType::PLAYER)->transitioning = true;
		onTransition = true;
		fadeOutCompleted = false;
		transitionAlpha = 0.0f;

		switch (current->nextScene)
		{
		case SceneType::LOGO: next = new Logo(input, render, tex); break;
		case SceneType::TITLE: next = new Title(win, input, render, tex); break;
		case SceneType::CANTINA: next = new Cantina(win, input, render, tex, entityManager, collision, previousScene, font); break;
		case SceneType::WC: next = new Wc(win, input, render, tex, entityManager, collision, previousScene, font); break;
		case SceneType::EXTERIOR: next = new Exterior(win, input, render, tex, entityManager, collision, previousScene, font); break;
		case SceneType::BATTLE: next = new Battle(win, input, render, tex, entityManager, font); break;
		default: break;
		}

		current->transitionRequired = false;
	}

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