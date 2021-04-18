#ifndef __SAVEFILEMANAGER_H_
#define __SAVEFILEMANAGER_H_

#include "App.h"
#include "Log.h"
#include "SDL/include/SDL.h"

class SaveFileManager
{
public:

	SaveFileManager(SceneManager* sceneManager);
	~SaveFileManager();

	// Create methods to request Load / Save
	void LoadGameRequest(const char* fileName);
	void SaveGameRequest(const char* fileName) const;

	//bool StartFile(pugi::xml_node& data) const;

	//bool SaveState(pugi::xml_node& data) const;

	//bool LoadState(pugi::xml_node& data);

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

private:

	SceneManager* sceneManager;

public:

	SString loadedgame;
	mutable SString savedgame;
	bool savedataexist;

};
#endif // __SAVEFILEMANAGER_H__