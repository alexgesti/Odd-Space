#include "DialogSystem.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Font.h"
#include "Speak.h"

#include "SDL/include/SDL.h"


DialogueSystem::DialogueSystem() {}

DialogueSystem::~DialogueSystem() {}

bool DialogueSystem::Start()
{
	LoadDialogue("dialogues.xml");
	currentNode = dialogueTrees[id]->dialogueNodes[0];
	//PerformDialogue(Id);
	font = new Font("assets/typo/Adore64.xml", tex);
	optionsTex = tex->Load("assets/sprites/UI/UI_Text.png");
	//nameTex = optionsTex;
	nameTex = tex->Load("assets/sprites/UI/UI_Text.png");
	return true;
}

bool DialogueSystem::Update(float dt)
{
	if (inConversation)
	{
		if (input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && !currentNode->lastSentence && currentNode->hasOptions)
		{
			playerInput = 0;
			if (currentNode->dialogueOptions.at(playerInput)->returnCode == 1) triggerEvent = true;
			PerformDialogue(id);

			nextSentence = true;
		}

		if (input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && !currentNode->lastSentence && currentNode->hasOptions)
		{
			playerInput = 1;
			if (currentNode->dialogueOptions.at(playerInput)->returnCode == 1) triggerEvent = true;
			PerformDialogue(id);

			nextSentence = true;
		}

		if (input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && !currentNode->lastSentence && currentNode->hasOptions)
		{
			playerInput = 2;
			if (currentNode->dialogueOptions.at(playerInput)->returnCode == 1) triggerEvent = true;
			PerformDialogue(id);

			nextSentence = true;
		}

		// Restart conversation
		if (input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		{
			id = 0;
			currentNode = dialogueTrees[id]->dialogueNodes[0];
			playerInput = 9;
			PerformDialogue(id);

			nextSentence = true;
		}

		if (input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
		{
			// Finish speaking sentence
			if (speak->speaking) speak->Finish();

			// If it's last sentence disable dialogueSystem
			else if (currentNode->lastSentence)
			{
				if (currentNode->dialogueOptions.at(0)->returnCode == 1) triggerEvent = true;
				inConversation = false;
			}

			// If the sentence has no options continue with the next line of dialogue
			else if(!currentNode->hasOptions)
			{
				if (currentNode->dialogueOptions.at(0)->returnCode == 1) triggerEvent = true;
				playerInput = 0;
				PerformDialogue(id);
				nextSentence = true;
			}

			showOptions = true;
		}
	}

	return true;
}

bool DialogueSystem::Draw()
{
	char NPCdialogue[300] = { 0 };
	sprintf_s(NPCdialogue, 300, currentNode->text.c_str(), 56);

	if (!speak->speaking && nextSentence)
	{
 		speak->SayText(NPCdialogue, true);
		LOG("%s", NPCdialogue);
		showOptions = false;
		nextSentence = false;
	}

	else if (speak->textSaid && !showOptions)
		showOptions = true;

	if (speak->speaking || showOptions)
	{
		SDL_Rect section = {0, 479, 225, 65};
		render->DrawTexture(nameTex, -render->camera.x, -render->camera.y + 481, &section);
		render->DrawText(font, currentNode->name.c_str(), 15, 508, 16, 0, { 255, 255, 255, 255 });
	}

	/*if (!speak->speaking && showOptions)
	{
		char response[64] = { 0 };
		for (int i = 0; i < currentNode->answersList.Count(); i++)
		{
			sprintf_s(response, 64, currentNode->answersList.At(i)->data.c_str(), 56);
			speak->SayText(response, false);
			speak->Finish();
			//render->DrawText(font, response, 10, 200 + (60 * (i + 1)), 80, 0, { 0, 255, 255, 255 });
		}
		showOptions = false;
	}*/

	if (showOptions)
	{
		if (currentNode->hasOptions)
		{
			SDL_Rect rect = { 500, 550, 780, 170 };
			render->DrawTexture(optionsTex, -render->camera.x + 500, -render->camera.y + 376, &rect);
		}

		char response[300] = { 0 };
		for (int i = 0; i < currentNode->answersList.Count(); i++)
		{
			sprintf_s(response, 300, currentNode->answersList.At(i)->data.c_str(), 56);

			// Draw the "X" option more on the left bottom
			if (!currentNode->hasOptions || currentNode->lastSentence)
			{
				render->DrawText(font, response, 1200, 670, 17, 0, { 255, 255, 255, 255 });
			}

			else render->DrawText(font, response, 520, 360 + (60 * (i + 1)), 17, 0, { 255, 255, 255, 255 });
		}

		// If it's the last sentence print an X as well
		if (currentNode->answersList.Count() == 0) render->DrawText(font, "X", 1200, 670, 21, 0, { 255, 255, 255, 255 });
	}

	return true;
}

bool DialogueSystem::CleanUp()
{
	for (int i = 0; i < dialogueTrees.size(); i++)
	{
		for (int j = 0; j < dialogueTrees[i]->dialogueNodes.size(); j++) delete dialogueTrees[i]->dialogueNodes[j];

		dialogueTrees[i]->dialogueNodes.clear();
		delete dialogueTrees[i];
	}
	dialogueTrees.clear();

	return true;
}

void DialogueSystem::PerformDialogue(int treeId)
{
	if (playerInput >= 0 && playerInput < currentNode->dialogueOptions.size())
	{
		for (int i = 0; i < dialogueTrees[treeId]->dialogueNodes.size(); i++)
		{
			// If a dialogue with options is the last dialogue
			if (currentNode->dialogueOptions[playerInput]->nextNode == -1)
			{
				// trigger event if needed and stop conversation
				if (currentNode->dialogueOptions[playerInput]->returnCode == 1) triggerEvent = true;
				inConversation = false;
				break;
			}

			if (currentNode->dialogueOptions[playerInput]->nextNode == dialogueTrees[treeId]->dialogueNodes[i]->nodeId)
			{
				currentNode = dialogueTrees[treeId]->dialogueNodes[i];
				break;
			}
		}
	}

	//BlitDialog();
}

bool DialogueSystem::LoadDialogue(const char* file)
{
	pugi::xml_parse_result result = dialogues.load_file(file);

	bool ret = true;

	if (result == NULL)
	{
		LOG("Could not load dialogue xml file %s. pugi error: %s", file, result.description());
		ret = false;
	}
	else
	{
		pugi::xml_node n = dialogues.first_child().child("dialogue");

		for (n; n != NULL; n = n.next_sibling("dialogue"))
		{
			DialogueTree* tree = new DialogueTree;
			tree->treeId = n.attribute("Id").as_int();
			LoadNodes(n, tree);
			dialogueTrees.push_back(tree);
		}
	}
	return true;
}

bool DialogueSystem::LoadNodes(pugi::xml_node& trees, DialogueTree* example)
{
	for (pugi::xml_node n = trees.child("node"); n != NULL; n = n.next_sibling("node"))
	{
		DialogueNode* node = new DialogueNode;
		node->text.assign(n.attribute("text").as_string());
		node->nodeId = n.attribute("id").as_int();
		node->hasOptions = n.attribute("hasOptions").as_bool(true);
		node->lastSentence = n.attribute("lastSentence").as_bool(false);
		node->name = n.attribute("name").as_string();
		LoadOptions(n, node);
		example->dialogueNodes.push_back(node);
	}

	return true;
}

bool DialogueSystem::LoadOptions(pugi::xml_node& response, DialogueNode* answers)
{
	for (pugi::xml_node option = response.child("dialogue"); option != NULL; option = option.next_sibling("dialogue"))
	{
		DialogueOption* selection = new DialogueOption;
		selection->text.assign(option.attribute("option").as_string());
		selection->nextNode = option.attribute("nextNode").as_int();
		selection->returnCode = option.attribute("returnCode").as_int();
		answers->dialogueOptions.push_back(selection);
		answers->answersList.Add((option.attribute("option").as_string()));
	}

	return true;
}

void DialogueSystem::SetConversation(int id)
{
	this->id = id;
	currentNode = dialogueTrees[this->id]->dialogueNodes[0];
	speak->Finish();
	nextSentence = true;
}