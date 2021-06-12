#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Module.h"
#include "Scene.h"
#include "Animation.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Window.h"
#include "EntityManager.h"
#include "DialogSystem.h"
#include "Audio.h"
#include "Collision.h"
#include "Speak.h"
#include "QuestSystem.h"
#include "ParticleSystem.h"

#include <vector>

using namespace std;

class Font;
class GuiButton;

class SceneManager : public Module
{
public:

	// Constructor
	SceneManager(Input* input, Render* render, Textures* tex, Window* win, EntityManager* entityManager, Audio* audio, DialogueSystem* dialogueSystem, ParticleSystem* pSystem);
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


	void ResetGame();

public:

	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	EntityManager* entityManager;
	DialogueSystem* dialogueSystem;
	Audio* audio;
	ParticleSystem* particleSystem;

	Collision* collision;
	Speak* speak;
	QuestSystem* questSystem;

	SceneType* previousScene;
	SceneType currentscenetype;
	Scene* current;
	Scene* next;
	Scene* pause;
	Scene* options;
	Scene* items;
	Scene* debug;

	Font* font;

	bool toDrawX = false;
	bool xMarkFXFlag = true;
	bool isPause = false;
	bool isDebug = false;
	bool pauseMusicFaded = false;
	bool gameIsWorking = true;

	bool newgamerequested = false;
	bool currentgamerequested = false;
	bool saverequested = false;
	bool loadrequested = false;

	bool exitToMainMenu = false;
	bool exitGame = false;
	bool capped = true;

	bool wasBattle = false;

	bool openOptions = false;
	bool openItems = false;

	// DUNGEON 

	// F1
	bool leverTri = false;
	bool leverCir = false;
	bool leverCro = false;

	bool doorOpening = false;
	bool door2Opening = false;

	vector <int> levers;
	vector <int> door1Sol{ 1,2,3 };

	bool door1Open = false;
	bool door2Open = false;

	bool savedataexist = false;

	// F2
	bool p1 = false;
	bool p2 = false;
	bool p3 = false;
	bool p4 = false;
	bool p5 = false;
	bool p6 = false;
	bool p7 = false;
	bool p8 = false;
	bool chestopen = false;

	bool seq1 = false;
	bool seq2 = false;
	bool seq3 = false;
	bool seqESP = false;

	bool crazyManActive = true;
	bool crazyManDrawable = true;

	//Sounds
	int doorClose;
	int doorOpen;
	int stairsFx;
	int xMarkFX;
	int unPauseFx;

	int battleEncounter;
	bool oneTimeBattleMusic;
	
	//Options
	int volumeMusic;
	int volumeFx;
	bool fullscreenCheck = false;

	bool drawColliders = false;
	bool beGod = false;

	//Title
	SDL_Texture* bgTitle;

	bool once = false;
	int temporalAppearTitle = 0;
	int pos1 = 12;

	// --- SCENE-SPECIFIC VARIABLES --- //
	bool initialTextTextSaid = false;
	float alphaP;

private:
	// Required variables to manage screen transitions (fade-in, fade-out)
	bool onTransition;
	bool fadeOutCompleted;
	float transitionAlpha;

	// Required variables to manage battle transitions (fade-in, fade-out)
	//bool oneTime;
	//int counterTimeDoit;
	float transitionScreen;
	int altura;

	SDL_Texture* xMark;
	Animation* animXMark = new Animation();
};

#endif // __SCENEMANAGER_H__