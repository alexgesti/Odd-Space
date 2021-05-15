#include "DialogSystem.h"

#include "Font.h"
#include "Speak.h"


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

	// Buttons Dialog
	buttonOpt1 = new GuiButton(1, { 511, 384, 757, 50 }, "Option 1", audio, false);
	buttonOpt2 = new GuiButton(2, { 511, 434, 757, 50 }, "Option 2", audio, false);
	buttonOpt3 = new GuiButton(3, { 511, 484, 757, 50 }, "Option 3", audio, false);

	return true;
}

bool DialogueSystem::Update(float dt)
{	
	GamePad& pad = input->pads[0];

	if (inConversation)
	{
		if (!currentNode->lastSentence && currentNode->hasOptions)
		{
			if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
				controllerMenu[c++];

			if (input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
				controllerMenu[c--];

			if (c > 2) c = 0;
			if (c < 0) c = 2;

			buttonOpt1->Update(input, controllerMenu[c], dt);
			buttonOpt2->Update(input, controllerMenu[c], dt);
			buttonOpt3->Update(input, controllerMenu[c], dt);
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

		if (input->GetKey(SDL_SCANCODE_X) == KEY_UP || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_UP)
		{
			// Finish speaking sentence
			if (speak->speaking) speak->Finish();

			// If it's last sentence disable dialogueSystem
			else if (currentNode->lastSentence)
			{
				if (currentNode->dialogueOptions.at(0)->returnCode == 1) triggerEvent = true;
				// Añadimos la opción 0 porque es la única que hay
				if (currentNode->dialogueOptions.at(0)->notRepeat == true)
					completedDialoguesId.Add(id);
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
		render->DrawText(font, currentNode->name.c_str(), 15, 508, 20, 0, { 255, 255, 255, 255 });
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
		//Render rectangle UI
		if (currentNode->hasOptions)
		{
			SDL_Rect rect = { 500, 550, 780, 170 };
			render->DrawTexture(optionsTex, -render->camera.x + 500, -render->camera.y + 375, &rect);
		}

		//Check all the posible answers
		char response[300] = { 0 };
		for (int i = 0; i < currentNode->answersList.Count(); i++)
		{
			sprintf_s(response, 300, currentNode->answersList.At(i)->data.c_str(), 56);

			// Draw the "X" option more on the left bottom
			if (!currentNode->hasOptions || currentNode->lastSentence)
			{
				render->DrawText(font, response, 1200, 670, 17, 0, { 255, 255, 255, 255 });
			}

			//Render options in the buttons
			else
			{
				switch (i)
				{
				case 0:
					buttonOpt1->text = response;
					buttonOpt1->Draw(render, font);
					break;
				case 1:
					buttonOpt2->text = response;
					buttonOpt2->Draw(render, font);
					break;
				case 2:
					buttonOpt3->text = response;
					buttonOpt3->Draw(render, font);
					break;
				default: break;
				}
			}
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

	delete buttonOpt1;
	buttonOpt1 = nullptr;
	delete buttonOpt2;
	buttonOpt2 = nullptr;
	delete buttonOpt3;
	buttonOpt3 = nullptr;

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
				if (currentNode->dialogueOptions.at(playerInput)->notRepeat == true) completedDialoguesId.Add(id);
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
		selection->notRepeat = option.attribute("notRepeat").as_int();
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

void DialogueSystem::GetObserver(Scene* scene)
{
	buttonOpt1->SetObserver(scene);
	buttonOpt2->SetObserver(scene);
	buttonOpt3->SetObserver(scene);
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool DialogueSystem::OnGuiMouseClickEvent(GuiControl* control)
{
	if (!currentNode->lastSentence && currentNode->hasOptions && !speak->speaking)
	{
		switch (control->id)
		{
		case 1:
			playerInput = 0;
			if (currentNode->dialogueOptions.at(playerInput)->returnCode == 1) triggerEvent = true;
			if (currentNode->dialogueOptions.at(playerInput)->notRepeat == true) completedDialoguesId.Add(id);
			PerformDialogue(id);

			nextSentence = true;
			break;
		case 2:
			playerInput = 1;
			if (currentNode->dialogueOptions.at(playerInput)->returnCode == 1) triggerEvent = true;
			if (currentNode->dialogueOptions.at(playerInput)->notRepeat == true) completedDialoguesId.Add(id);
			PerformDialogue(id);

			nextSentence = true;
			break;
		case 3:
			playerInput = 2;
			if (currentNode->dialogueOptions.at(playerInput)->returnCode == 1) triggerEvent = true;
			if (currentNode->dialogueOptions.at(playerInput)->notRepeat == true) completedDialoguesId.Add(id);
			PerformDialogue(id);

			nextSentence = true;
			break;
		default: break;
		}
	}

	return true;
}