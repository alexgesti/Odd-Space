#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Module.h"
#include "Scene.h"

class GuiButton;

class Window;
class Input;
class Render;
class Textures;
class EntityManager;
class DialogueSystem;
class Collision;
class Audio;
class Speak;

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

private:

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
	Scene* current;
	Scene* next;

	Font* font;

	// Required variables to manage screen transitions (fade-in, fade-out)
	bool onTransition;
	bool fadeOutCompleted;
	float transitionAlpha;
};

#endif // __SCENEMANAGER_H__