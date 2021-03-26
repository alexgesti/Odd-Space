#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"



class Window;
class Input;
class Render;
class Textures;
class Audio;

struct SDL_Texture;
struct SDL_Window;

class Scene : public Module
{
public:

	// Constructor
	Scene(Window* win, Input* input, Render* render, Textures* tex, Audio* audio);
	// Destructor
	virtual ~Scene();


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

	// Fullscreen
	void ToggleFullscreen(SDL_Window* Window);

private:

	SDL_Texture* img;

private:

	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;

	bool fullscreen = false;
};

#endif // __SCENE_H__