#include "App.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "EntityManager.h"
#include "SceneManager.h"
#include "DialogSystem.h"
#include "SaveFileManager.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>



// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(ptimer);
	frames = 0;

	win = new Window();
	input = new Input(win);
	render = new Render(win);
	tex = new Textures(render);
	audio = new Audio();
	entityManager = new EntityManager(input, render, tex);
	dialogueSystem = new DialogueSystem(input, render, tex);
	sceneManager = new SceneManager(input, render, tex, win, entityManager, audio, dialogueSystem);

	// Not modules
	saveFileManager = new SaveFileManager(sceneManager);

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(audio);
	AddModule(entityManager);
	AddModule(dialogueSystem);
	AddModule(sceneManager);

	// Render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.Clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.Add(module);
}

// Called before render is available
bool App::Awake()
{
	// TODO 3: Load config from XML
	bool ret = LoadConfig();

	if(ret == true)
	{
		// TODO 4: Read the title from the config file
		title.Create(configApp.child("title").child_value());
		win->SetTitle(title.GetString());

		cappedms = configApp.attribute("framerate_cap").as_uint();

		ListItem<Module*>* item;
		item = modules.start;

		while(item != NULL && ret == true)
		{
			// TODO 5: Add a new argument to the Awake method to receive a pointer to an xml node.
			// If the section with the module name exists in config.xml, fill the pointer with the valid xml_node
			// that can be used to read all variables for that module.
			// Send nullptr if the node does not exist in config.xml
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	return ret;
}

// Called before the first frame
bool App::Start()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// Load config from XML file
bool App::LoadConfig()
{
	bool ret = true;

	// TODO 3: Load config.xml file using load_file() method from the xml_document class
	pugi::xml_parse_result result = configFile.load_file("config.xml");

	// TODO 3: Check result for loading errors
	if(result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		config = configFile.child("config");
		configApp = config.child("app");
	}

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	framecount++;
	lastsecframecount++;

	// L08: DONE 4: Calculate the dt: differential time since last frame
	dt = frametime.ReadSec();
	frametime.Start();
	delayTimer.Start();
}

// ---------------------------------------------
void App::FinishUpdate()
{
	// This is a good place to call Load / Save functions
	if (sceneManager->loadrequested)
	{
		saveFileManager->LoadGame();
		sceneManager->loadrequested = false;
	}
	if (sceneManager->saverequested)
	{
		saveFileManager->SaveGame();
		sceneManager->saverequested = false;
		//sceneManager->newgamerequested = false;
		//sceneManager->currentgamerequested = false;
	}

	FramerateLogic();

	static char title[256];
	sprintf_s(title, 256, "Odd Space (FPS: %i / Av.FPS: %.2f / Last Frame Ms: %02u ms / Last dt: %.3f / Play Time: %.3f / Frame Count: %I64u",
		prevlastsecframecount, averagefps, lastframems, dt, secondssincestartup, framecount);

	win->SetTitle(title);
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) 
		{
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) 
		{
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) 
		{ 
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc) return args[index];
	else return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
/*void App::LoadGameRequest(const char* fileName)
{
	loadgamerequested = true;
	loadedgame.Create(fileName);
}

// ---------------------------------------
void App::SaveGameRequest(const char* fileName) const
{
	savegamerequested = true;
	savedgame.Create(fileName);
}*/

void App::FramerateLogic()
{
	if (lastsecframetime.Read() > 1000)
	{
		lastsecframetime.Start();
		prevlastsecframecount = lastsecframecount;
		lastsecframecount = 0;
	}

	averagefps = float(framecount) / startuptime.ReadSec();
	secondssincestartup = startuptime.ReadSec();
	lastframems = frametime.Read();

	int delayTime = (1000 / cappedms) - lastframems;
	if (delayTime > 0)
	{
		SDL_Delay((Uint32)delayTime);
	}
}