#include "Scene.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"

#include "Defs.h"
#include "Log.h"



// Constructor
Scene::Scene(Window* win, Input* input, Render* render, Textures* tex, Audio* audio) : Module()
{
	name.Create("scene");

	this->win = win;
	this->input = input;
	this->render = render;
	this->tex = tex;
	this->audio = audio;
}
// Destructor
Scene::~Scene()
{}


// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}
// Called before the first frame
bool Scene::Start()
{
	img = tex->Load("Assets/Textures/test.png");
	audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");
	return true;
}


// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if(input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		render->camera.y -= 1;

	if(input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		render->camera.y += 1;

	if(input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		render->camera.x -= 1;

	if(input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		render->camera.x += 1;

	if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		ToggleFullscreen(win->window);

	render->DrawTexture(img, 380, 100);

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::ToggleFullscreen(SDL_Window* Window)
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
}