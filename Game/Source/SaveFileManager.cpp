#include "SaveFileManager.h"

#include "SceneManager.h"
#include "EntityManager.h"

#include "SDL/include/SDL.h"


SaveFileManager::SaveFileManager(SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
}

SaveFileManager::~SaveFileManager() {}

// Load / Save
void SaveFileManager::LoadGameRequest(const char* fileName)
{
	loadedgame.Create(fileName);
}

// ---------------------------------------
void SaveFileManager::SaveGameRequest(const char* fileName) const
{
	savedgame.Create(fileName);
}

/*bool SaveFileManager::StartFile(pugi::xml_node& data) const
{
	pugi::xml_node camerasave = data.append_child("Camera");
	pugi::xml_node playersave = data.append_child("Player");
	pugi::xml_node scenesave = data.append_child("Scene");

	camerasave.append_attribute("y") = -1000;

	return true;
}

bool SaveFileManager::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node camerasave = data.append_child("Camera");
	pugi::xml_node playersave = data.append_child("Player");
	pugi::xml_node scenesave = data.append_child("Scene");

	camerasave.append_attribute("y") = sceneManager->render->camera.y;

	return true;
}*/

/*bool SaveFileManager::LoadState(pugi::xml_node& data)
{
	sceneManager->render->camera.x = data.child("Camera").attribute("x").as_int();
	sceneManager->render->camera.y = data.child("Camera").attribute("y").as_int();

	return true;
}*/

// ---------------------------------------
// Create a method to actually load an xml file
// then call all the modules to load themselves
bool SaveFileManager::LoadGame()
{
	bool ret = false;

	pugi::xml_document file;
	pugi::xml_parse_result result = file.load_file("save_game.xml");

	if (result != NULL)
	{
		LOG("Loading new Game State from save_game.xml...");
		ret = true;

		pugi::xml_node node = file.child("save_state");

		sceneManager->render->camera.y = node.child("Camera").attribute("y").as_int();

		SceneType aux;
		aux = (SceneType)node.child("Scene").attribute("scene").as_int();
		if (sceneManager->currentscenetype != aux)
		{
			sceneManager->current->TransitionToScene(aux);
		}

		if (ret == true)
		{
			LOG("...finished loading");
		}
	}
	else LOG("Could not load game state xml file savegame.xml. pugi error: %s", result.description());

	return ret;
}

// Implement the xml save method for current state
bool SaveFileManager::SaveGame() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", savedgame.GetString());

	pugi::xml_document file;
	pugi::xml_node base = file.append_child("save_state");

	pugi::xml_node node = base.append_child(sceneManager->name.GetString());
	
	// Things to save
	pugi::xml_node camerasave = node.append_child("Camera");
	pugi::xml_node scenesave = node.append_child("Scene");

	camerasave.append_attribute("y") = sceneManager->render->camera.y;

	scenesave.append_attribute("scene") = (int)sceneManager->currentscenetype;

	bool succ = file.save_file("save_game.xml");
	if (succ != true)
	{
		LOG("File save error. pugi error: %d", pugi::status_internal_error);
	}
	else LOG("... finished saving");

	return ret;
}