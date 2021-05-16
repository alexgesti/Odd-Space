#ifndef __DIALOGSYSTEM_H__
#define __DIALOGSYSTEM_H__

#include "Log.h"
#include <string>
#include <iostream>
#include <vector>

#include "Render.h"
#include "Textures.h"
#include "Module.h"
#include "Input.h"
#include "Audio.h"
#include "GuiButton.h"
#include "DynArray.h"

#include "SDL/include/SDL.h"

using namespace std;

class DialogueNode;
class Speak;
class GuiButton;
struct SDL_Texture;

class DialogueOption
{
public:
	DialogueOption() {};
	~DialogueOption() {};

	DialogueOption(string Text, int ReturnCode, int NextNode);
	string text;
	int returnCode;
	int nextNode;
	int notRepeat;
};

class DialogueNode
{
public:
	DialogueNode() {};
	~DialogueNode() {};

	DialogueNode(string Text);
	string text;
	vector <DialogueOption*> dialogueOptions;
	List <string> answersList;
	int nodeId;
	bool hasOptions;
	bool lastSentence;
	string quest;
	string name;
};

class DialogueTree
{
public:
	DialogueTree() {};
	~DialogueTree() {};


public:
	int treeId;
	vector <DialogueNode*> dialogueNodes;
};

class DialogueSystem : public Module
{
public:
	DialogueSystem();
	DialogueSystem(Input* input, Render* render, Textures* tex, Audio* audio)
	{
		this->input = input;
		this->render = render;
		this->tex = tex;
		this->audio = audio;
	}
	~DialogueSystem();

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	void PerformDialogue(int treeId);
	bool LoadDialogue(const char*);
	bool LoadNodes(pugi::xml_node& trees, DialogueTree* oak);
	bool LoadOptions(pugi::xml_node& text_node, DialogueNode* npc);
	bool Draw();

	void SetConversation(int id);

	void GetObserver(Scene* scene);

	// Declare on mouse click event
	bool OnGuiMouseClickEvent(GuiControl* control);

public:

	Speak* speak;
	Font* font;

	bool inConversation = false;
	bool triggerEvent = false;

	DialogueNode* currentNode;

	//DynArray<int> completedDialoguesId;
	List<int> completedDialoguesId;

	bool createKillQuest = false;
	bool createCollectQuest = false;
	
private:

	int playerInput = -1;
	int id = 0;
	std::vector <DialogueTree*> dialogueTrees;
	pugi::xml_document	dialogues;

	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;

	bool showOptions;
	bool nextSentence = true;

	// Options quad texture
	SDL_Texture* optionsTex;

	GuiButton* buttonOpt1;
	GuiButton* buttonOpt2;
	GuiButton* buttonOpt3;
	int controllerMenu[3] = { 1, 2, 3 };
	int c = 0;
};
#endif // __DIALOGSYSTEM_H__
