#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "PerfTimer.h"
#include "Timer.h"

#include "PugiXml/src/pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);
	// Destructor
	virtual ~App();


	// Called before render is available
	bool Awake();
	// Called before the first frame
	bool Start();


	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();



	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

private:

	// Load config file
	bool LoadConfig();

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	void FramerateLogic();

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Scene* scene;

	uint64 framecount = 0;
	uint32 cappedms = 60;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	uint frames;

	PerfTimer ptimer;
	PerfTimer delayTimer;

	float averagefps = 0.0f;
	float secondssincestartup = 0.0f;
	uint32 lastframems = 0;
	uint32 framesonlastupdate = 0;
	uint32 delaytime = 0;

	Timer startuptime;
	Timer frametime;
	Timer lastsecframetime;
	uint32 lastsecframecount = 0;
	uint32 prevlastsecframecount = 0;
	float dt = 0.0f;

	// TODO 2: Create new variables from pugui namespace:
	// a xml_document to store the config file and
	// two xml_node to read specific branches of the xml
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;
};

#endif	// __APP_H__