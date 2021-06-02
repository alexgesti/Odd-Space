#ifndef __SAVEFILEMANAGER_H_
#define __SAVEFILEMANAGER_H_

#include "App.h"
#include "Log.h"
#include "SDL/include/SDL.h"

#include "Encrypt.h"

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
	void LoadSaveState();

	bool SaveDialogueFile() const;
	bool LoadDialogueFile();

private:

	SceneManager* sceneManager;

	Encrypt* encrypt;

public:

	SString loadedgame;
	mutable SString savedgame;
	SString fileName = "save_game.xml";

};
#endif // __SAVEFILEMANAGER_H__
