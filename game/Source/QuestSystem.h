#ifndef __QUESTSYSTEM_H__
#define __QUESTSYSTEM_H__

#define MAXDESCLENGTH 45 // Maximum amount of characters for a line on main quest description
#define MAXSTEPLENGTH 35 // Maximum amount of characters for a line on main quest description

#include "SString.h"
#include "List.h"
#include "Render.h"

class SceneManager;

enum class QuestType
{
	COLLECT,
	KILL,
	INTERACT,
	TRAVEL,
	MAIN
};

class Quest
{
public:
	SString name = '/0';
	SString value = '/0';
	QuestType type;
	int quantity; // Amount of items or enemies to collect or kill
	int counter; // Amount of items or enemies already collected or killed

	/*QuestType type;
	int amount = 0; // Amount of enemies/items to kill/collect
	SString interactionName = '/0'; // Interaction name for Interact quests
	SString text;
	bool operator!=(Quest quest)
	{
		return (type != quest.type || amount != quest.amount || interactionName.operator!=(quest.interactionName) || text.operator!=(quest.text));
	}*/
};

/*class CollectQuest : public Quest
{
	//Collect x item

};

class KillQuest : public Quest
{
	//Kill x enemy
};

class InteractQuest : public Quest
{
	//Do x interaction
	SString interactionName = '/0';
};

class TravelQuest : public Quest
{
	//Travel to x scene
	SString sceneName = '/0';
};*/

class MainQuest: public Quest
{
public:
	//Main quest template
	int ID = 0;
	List<Quest> steps;
	int currentStep = 0;
	int stepAmount = 0;
	//string description = "/0";
};

class QuestSystem
{
public:
	QuestSystem(SceneManager* sceneManager);
	~QuestSystem() {};

	void UpdateMain(SString value);

	bool CheckInteract(SString value, SString questValue);
	bool CheckTravel(SString value, SString questValue);
	bool CheckKillCollect(SString value, SString questValue);
	bool CheckCollect(SString value, SString questValue);

	void Draw(Render* renderer, Font* font);

	/*
	void AddSideQuest(Quest);
	void ChangeMainQuest(Quest);
	void CompleteSideQuest(Quest);
	//void CheckSideQuests(); // Checkea si se ha completado alguna de las side quests
	//void CheckSideQuestCollect(Quest quest, Quest listQuest);
	//void CheckSideQuestKill(Quest quest, Quest listQuest);
	void CheckSideQuests(Quest quest, int amount);
	bool CheckMainQuestCollect(int amount);
	bool CheckMainQuestKill(int amount);
	void ClearQuests();
	void Draw(Render* renderer, Font* font);
	*/

	//bool CheckMainQuest(); // Checkea si se ha completado la main quest

	//MAYBE ESTARIA BIEN HACER UNA FUNCION DIFERENTE PARA CHECKEAR SI SE HAN COMPLETADO, TIPO CheckCollectSideQuest/CheckKillSideQuest/CheckInteractSideQuest Y QUIZA LO MISMO CON EL mainQuest

public:
	List<MainQuest> mainQuests;
	//Quest currentMainQuest;
	int currentMainQuestID = 0;
	List<Quest> sideQuests;
	SceneManager* sceneManager;
	QuestType currentStepType;

private:
	int maxSideQuests = 3;
};

#endif //__QUESTSYSTEM_H__