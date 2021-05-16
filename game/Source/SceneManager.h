#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Module.h"
#include "Scene.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Window.h"
#include "EntityManager.h"
#include "DialogSystem.h"
#include "Audio.h"
#include "Collision.h"
#include "Speak.h"

#include <vector>

using namespace std;

class Font;
class GuiButton;

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
	Scene* next;
	Scene* pause;
	Scene* options;
	Scene* items;

	Font* font;

	bool toDrawX = false;
	bool isPause = false;
	bool pauseMusicFaded = false;

	bool gameIsWorking = true;

	bool newgamerequested = false;
	bool currentgamerequested = false;
	bool saverequested = false;
	bool loadrequested = false;

	bool exitGame = false;
	bool capped = true;

	bool wasBattle = false;

	bool openOptions = false;
	bool openItems = false;

	// DUNGEON 
	bool leverTri = false;
	bool leverCir = false;
	bool leverCro = false;

	vector <int> levers;
	vector <int> door1Sol{ 1,2,3 };

	bool door1Open = false;
	bool door2Open = false;


	bool resetDungeon = true;

	bool crazyManActive = true;
	bool crazyManDrawable = true;

	//sounds
	int doorClose;
	int doorOpen;
	
	int volumeMusic;
	int volumeFx;
	bool fullscreenCheck = false;
	bool VSyncCheck = true;

	// --- SCENE-SPECIFIC VARIABLES --- //
	bool initialExtTextSaid = false;

private:
	// Required variables to manage screen transitions (fade-in, fade-out)
	bool onTransition;
	bool fadeOutCompleted;
	float transitionAlpha;

	SDL_Texture* xMark;
};

#endif // __SCENEMANAGER_H__