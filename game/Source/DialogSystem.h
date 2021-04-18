#ifndef __DIALOGSYSTEM_H__
#define __DIALOGSYSTEM_H__

#include "App.h"
#include "Log.h"
#include <string>
#include <iostream>
#include <vector>
#include "Render.h"
#include "Textures.h"
#include "Module.h"
#include "Input.h"
#include "SDL/include/SDL.h"

using namespace std;

class DialogueNode;
class Speak;
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
	DialogueSystem(Input* input, Render* render, Textures* tex)
	{
		this->input = input;
		this->render = render;
		this->tex = tex;
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

public:

	Speak* speak;
	Font* font;

	bool inConversation = false;
	bool triggerEvent = false;

	DialogueNode* currentNode;
	
private:

	int playerInput = 7;
	int id = 0;
	std::vector <DialogueTree*> dialogueTrees;
	pugi::xml_document	dialogues;

	Input* input;
	Render* render;
	Textures* tex;

	bool showOptions;
	bool nextSentence = true;

	//Options quad texture
	SDL_Texture* optionsTex;
};
#endif // __DIALOGSYSTEM_H__
