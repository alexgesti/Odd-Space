#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Module.h"
#include "Scene.h"

class GuiButton;

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Window.h"
#include "EntityManager.h"
#include "DialogSystem.h"
#include "Audio.h"
#include "Collision.h"
#include "Speak.h"

class Font;

class SceneManager : public Module
{
public:

	// Constructor
	SceneManager(Input* input, Render* render, Textures* tex, Window* win, EntityManager* entityManager, Audio* audio, DialogueSystem* dialogueSystem);
	// Destructor
	virtual ~SceneManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:

	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	EntityManager* entityManager;
	DialogueSystem* dialogueSystem;
	Audio* audio;

	Collision* collision;
	Speak* speak;

	SceneType* previousScene;
	SceneType currentscenetype;
	Scene* current;
	Scene* pause;
	Scene* next;

	Font* font;

	bool toDrawX = false;
	bool isPause = false;
	bool pauseMusicFaded = false;

	bool gameIsWorking = true;

	bool initialTextSaid = false;

	bool newgamerequested = false;
	bool currentgamerequested = false;
	bool saverequested = false;
	bool loadrequested = false;

	bool exitGame = false;

	bool wasBattle = false;

	// DUNGEON KEY
	//bool dungeonKey = false;

	bool crazyManActive = true;
	bool crazyManDrawable = true;

private:
	// Required variables to manage screen transitions (fade-in, fade-out)
	bool onTransition;
	bool fadeOutCompleted;
	float transitionAlpha;

	SDL_Texture* xMark;
};

#endif // __SCENEMANAGER_H__