#include "QuestSystem.h"
#include "SceneManager.h"
#include <fstream>

QuestSystem::QuestSystem(SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;

	//Load main quests

	ifstream ip("main_quests.csv");

	if (!ip.is_open()) LOG("ERROR: File Open");

	string diferenciator;
	string id;
	string type;
	string Main_name;
	string Main_description;
	string Step_name;
	string Step_value;
	int Step_quantity  = 0;

	bool isStep = false; //Checks if we are on a step or in a main quest
	int stepAmount = 0;
	MainQuest temp;

	List<Quest> steps;

	while (ip.good())
	{
		getline(ip, diferenciator, ',');

		if (diferenciator == "M") isStep = false;
		else if (diferenciator == "S") isStep = true;

		if (!isStep && stepAmount != 0) // Add main quest
		{
			temp.name.operator=(Main_name.c_str());
			temp.ID = stoi(id);
			temp.value.operator=(Main_description.c_str());
			temp.stepAmount = stepAmount;
			temp.type = QuestType::MAIN;

			mainQuests.Add(temp);
			for (int i = 0; i < steps.Count(); i++)
			{
				mainQuests.At(temp.ID)->data.steps.Add(steps.At(i)->data);
			}
			steps.Clear();

			stepAmount = 0;
		}

		if (!isStep) //Leer parametros de main quest
		{
			getline(ip, id, ',');

			string temporal;
			getline(ip, temporal, ',');

			// Evita que si en algun nombre/descripción hay comas se salte lo que hay despues
			if (temporal.at(0) == '\"')
			{
				do
				{
					Main_name += temporal;
					getline(ip, temporal, ',');
					temporal = ", " + temporal;
				} while (temporal.find_last_of('\"') == string::npos);

				Main_name += temporal;

				Main_name = Main_name.substr(1, Main_name.size() - 2); //Deletes the " characters that are at the beggining and end of the string
			}

			else Main_name = temporal;

			getline(ip, Main_description, '\n');
			if (Main_description.at(0) != '\"')
			{
				Main_description.insert(0, "\"");
				Main_description.push_back('\"');
			}
		}

		else //Leer parametros de step y la añadimos a la lista
		{
			getline(ip, type, ',');

			string temporal;
			getline(ip, temporal, ',');

			// Evita que si en algun nombre/descripción hay comas se salte lo que hay despues
			if (temporal.at(0) == '\"')
			{
				do
				{
					Step_name += temporal;
					getline(ip, temporal, ',');
					temporal = ", " + temporal;
				} while (temporal.find_last_of('\"') == string::npos);

				Step_name += temporal;

				Step_name = Step_name.substr(1, Step_name.size() - 2); //Deletes the " characters that are at the beggining and end of the string
			}

			else Step_name = temporal;

			getline(ip, Step_value, '\n');

			QuestType questType = QuestType::INTERACT; //Hay que inicializarla para que no de problemas
			if (type == "INTERACT") questType = QuestType::INTERACT;
			else if (type == "TRAVEL") questType = QuestType::TRAVEL;
			else if (type == "KILL" || type == "COLLECT")
			{
				if(type == "KILL") questType = QuestType::KILL;
				else questType = QuestType::COLLECT;
				int i = Step_value.find_first_of(" "); // Find separator between amount and enemy name
				Step_quantity = stoi(Step_value.substr(0, i)); // Get amount
				Step_value = Step_value.substr(i + 1, Step_value.length()); // Get name
			}

			Quest step;
			step.name.operator=(Step_name.c_str());
			step.type = questType;
			step.value.operator=(Step_value.c_str());
			step.quantity = Step_quantity;

			//temp.steps.Add(step);
			steps.Add(step);

			Step_name.clear();
			Step_quantity = 0;

			stepAmount++;
		}
	}

	ip.close();

	if (stepAmount != 0) // Add last main quest on the file
	{
		temp.name.operator=(Main_name.c_str());
		temp.ID = stoi(id);
		temp.value.operator=(Main_description.c_str());
		temp.stepAmount = stepAmount;
		temp.type = QuestType::MAIN;

		mainQuests.Add(temp);

		for (int i = 0; i < steps.Count(); i++)
		{
			mainQuests.At(temp.ID)->data.steps.Add(steps.At(i)->data);
		}

		steps.Clear();

		Main_name.clear();

		stepAmount = 0;
	}

	currentStepType = mainQuests.start->data.steps.start->data.type; // ESTO HABRÁ QUE CAMBIARLO LUEGO Y HACERLE UN LOAD AL QUEST SYSTEM PARA ESTO
};

void QuestSystem::UpdateMain(SString value)
{
	//MainQuest mainQuest = mainQuests.At(currentMainQuestID)->data;
	bool completed = false;
	bool lastQuest = currentMainQuestID == mainQuests.Count() - 1; // Si estamos en la ultima quest esta se reseteará cada vez que la completemos
	//We check if currentStep has been completed
	switch (currentStepType)
	{
	case QuestType::INTERACT:
		completed = CheckInteract(value, mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.value);
		break;

	case QuestType::COLLECT:
	case QuestType::KILL:
		completed = CheckKillCollect(value, mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.value);
		break;
	case QuestType::TRAVEL:
		completed = CheckTravel(value, mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.value);
		break;
	default:
		break;
	}

	if (completed)
	{
		mainQuests.At(currentMainQuestID)->data.currentStep++;

		//Pasar a la siguiente mainQuest
		if (mainQuests.At(currentMainQuestID)->data.currentStep >= mainQuests.At(currentMainQuestID)->data.stepAmount)
		{
			if (!lastQuest) //Pasar a la siguiente quest solo si no es la ultima
			{
				currentMainQuestID++;
				currentStepType = mainQuests.At(currentMainQuestID)->data.steps.start->data.type;
			}

			else
			{
				mainQuests.At(currentMainQuestID)->data.currentStep = 0;
				currentStepType = mainQuests.At(currentMainQuestID)->data.steps.start->data.type;
			}
		}

		//Updatear el currentQuestType al tipo del paso en el que estamos
		else currentStepType = mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.type;
	}
}

bool QuestSystem::CheckInteract(SString value, SString questValue)
{
	if (value.operator==(questValue)) return true;
	else return false;
}

bool QuestSystem::CheckTravel(SString value, SString questValue)
{
	if (value.operator==(questValue)) return true;
	else return false;
}

bool QuestSystem::CheckKillCollect(SString value, SString questValue)
{
	if (value.operator==(questValue)) mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.counter++;

	if (mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.counter >= mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.quantity) return true;
	else return false;
}

void QuestSystem::Draw(Render* renderer, Font* font)
{
	int Yaxis = 0;

	//Main quest name
	renderer->DrawText(font, ("Main quest: " + (string)mainQuests.At(currentMainQuestID)->data.name.GetString()).c_str(), 354, Yaxis * 39 + 120, 23, 5, { 255, 255, 255, 255 });
	Yaxis = 50 + 120;

	//Main quest description
	string description = mainQuests.At(currentMainQuestID)->data.value.GetString();

	//Divide description in varipus lines so it doesn't overflow on the screen
	if (description.length() > MAXDESCLENGTH)
	{
		int startAt = 0; //Start point for next line
		int len = MAXDESCLENGTH; //length of the substring;

		//This for loop divides the description until it ends
		for (int i = MAXDESCLENGTH; i < description.length(); i++, len++)
		{
			// 32 is ASCII for space so a word doesn't get cut in the middle
			if (description.at(i) == 32)
			{
				//Get the sibstring that we need and draw it
				string temp = description.substr(startAt, len);
				if (temp.at(0) == 32) temp.erase(0, 1); // Deletes first character of the new line if its a space
				renderer->DrawText(font, temp.c_str(), 354, Yaxis, 15, 5, { 255, 255, 255, 255 });

				// New starting point at the description string for next line
				startAt = i + 1;
				Yaxis += 30;

				// Jump to next max lenght position
				i += MAXDESCLENGTH;

				// Reset len var for substring lenght
				len = MAXDESCLENGTH;
			}
		}

		// Last line doesn't get drawn on loop
		string temp = description.substr(startAt, len);
		if (temp.at(0) == 32) temp.erase(0, 1);
		renderer->DrawText(font, temp.c_str(), 354, Yaxis, 15, 5, { 255, 255, 255, 255 });
		Yaxis += 50;
	}

	else
	{
		renderer->DrawText(font, mainQuests.At(currentMainQuestID)->data.value.GetString(), 354, Yaxis * 39 + 120, 23, 5, { 255, 255, 255, 255 });
		Yaxis += 50;
	}

	//Main quest description
	string step = ("Step(" + to_string(mainQuests.At(currentMainQuestID)->data.currentStep + 1) + "/" + to_string(mainQuests.At(currentMainQuestID)->data.stepAmount) + "): " + (string)mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.name.GetString()).c_str();

	//Divide description in varipus lines so it doesn't overflow on the screen
	if (step.length() > MAXSTEPLENGTH)
	{
		int startAt = 0; //Start point for next line
		int len = MAXSTEPLENGTH; //length of the substring;

		//This for loop divides the description until it ends
		for (int i = MAXSTEPLENGTH; i < step.length(); i++, len++)
		{
			// 32 is ASCII for space so a word doesn't get cut in the middle
			if (step.at(i) == 32)
			{
				//Get the sibstring that we need and draw it
				string temp = step.substr(startAt, len);
				if (temp.at(0) == 32) temp.erase(0, 1);
				renderer->DrawText(font, temp.c_str(), 390, Yaxis, 19, 5, { 255, 255, 255, 255 });

				// New starting point at the description string for next line
				startAt = i + 1;
				Yaxis += 30;

				// Jump to next max lenght position
				i += MAXSTEPLENGTH;

				// Reset len var for substring lenght
				len = MAXSTEPLENGTH;
			}
		}

		// Last line doesn't get drawn on loop
		string temp = step.substr(startAt, len);
		if (temp.at(0) == 32) temp.erase(0, 1);
		renderer->DrawText(font, temp.c_str(), 390, Yaxis, 19, 5, { 255, 255, 255, 255 });
	}
	
	//Step data
	else
	{
		renderer->DrawText(font, ("Step(" + to_string(mainQuests.At(currentMainQuestID)->data.currentStep + 1) + "/" + to_string(mainQuests.At(currentMainQuestID)->data.stepAmount) + "): " + (string)mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.name.GetString()).c_str(), 390, Yaxis, 19, 5, { 255, 255, 255, 255 });
	}

	Yaxis += 30;

	// Print how many items or enemies we have collected or killed and how many we need
	if (currentStepType == QuestType::KILL || currentStepType == QuestType::COLLECT)
	{
		renderer->DrawText(font, ((string)mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.value.GetString() + ": " + to_string(mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.counter) + "/" + to_string(mainQuests.At(currentMainQuestID)->data.steps.At(mainQuests.At(currentMainQuestID)->data.currentStep)->data.quantity)).c_str(), 390, Yaxis, 14, 5, { 255, 255, 255, 255 });
		Yaxis += 50;
	}

	else Yaxis += 20;

	renderer->DrawText(font, "Side quests:", 354, Yaxis, 23, 5, { 255, 255, 255, 255 });
	Yaxis += 50;

	for (int i = 0; i < 3; i++)
	{
		renderer->DrawText(font, ("Quest number" + to_string(i+1)).c_str(), 390, Yaxis, 19, 5, { 255, 255, 255, 255 });
		Yaxis += 40;
	}
}

/*
void QuestSystem::AddSideQuest(Quest quest)
{
	if(sideQuests.Count() < maxSideQuests) sideQuests.Add(quest);
}

void QuestSystem::ChangeMainQuest(Quest quest)
{
	mainQuest = quest;
}

void QuestSystem::CompleteSideQuest(Quest quest)
{
	ListItem<Quest>* temp = sideQuests.start;
	while (temp->data != quest && temp != NULL)
	{
		temp = temp->next;
	}

	if (temp != NULL) sideQuests.Del(temp);
}

/*void QuestSystem::CheckSideQuests()
{
	ListItem<Quest>* temp = sideQuests.start;
	while (temp != NULL)
	{
		switch (temp->data.type)
		{
		case QuestType::COLLECT:
			break;
		case QuestType::KILL:
			break;
		case QuestType::INTERACT:
			break;
		}

		temp = temp->next;
	}
	//CompleteSideQuest()
}

bool QuestSystem::CheckMainQuest()
{
	switch (mainQuest.type)
	{
		case QuestType::COLLECT:
			break;
		case QuestType::KILL:
			break;
		case QuestType::INTERACT:
			break;
	}
}*/
/*void QuestSystem::CheckSideQuestCollect(Quest quest, Quest listQuest)
{
	if (quest.amount >= listQuest.amount) CompleteSideQuest(listQuest);
}

void QuestSystem::CheckSideQuestKill(Quest quest, Quest listQuest)
{
	if (quest.amount >= listQuest.amount) CompleteSideQuest(listQuest);
}*/

/*
void QuestSystem::CheckSideQuests(Quest quest, int amount)
{
	/*ListItem<Quest>* temp = sideQuests.start;
	while (temp != NULL)
	{
		switch (temp->data.type)
		{
		case QuestType::COLLECT:
			CheckSideQuestCollect(quest, temp->data);
			break;
		case QuestType::KILL:
			CheckSideQuestKill(quest, temp->data);
			break;
		}
	}
	if (amount >= quest.amount) CompleteSideQuest(quest);
}

bool QuestSystem::CheckMainQuestCollect(int amount)
{
	if (amount >= mainQuest.amount) return true;
	else return false;
}

void QuestSystem::ClearQuests()
{
	ListItem<Quest>* temp = sideQuests.start;
	while (temp != NULL)
	{
		sideQuests.Del(temp);

		temp = temp->next;
	}
}

void QuestSystem::Draw(Render* renderer, Font* font)
{
	renderer->DrawText(font, "Main quest:", 354, 0 * 39 + 120, 25, 5, {255, 255, 255, 255});
	renderer->DrawText(font, mainQuest.text.GetString(), 374, 1 * 39 + 120, 20, 5, { 255, 255, 255, 255 });
	renderer->DrawText(font, "Side quests:", 354, 2 * 39 + 120, 25, 5, { 255, 255, 255, 255 });
	for (int i = 0; i < sideQuests.Count(); i++)
	{
		renderer->DrawText(font, sideQuests.At(i)->data.text.GetString(), 374, (i + 3) * 39 + 120, 20, 5, { 255, 255, 255, 255 });
	}
}
*/