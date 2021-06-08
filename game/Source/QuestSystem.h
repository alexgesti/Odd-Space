#ifndef __QUESTSYSTEM_H__
#define __QUESTSYSTEM_H__

#include "SString.h"
#include "List.h"
#include "Render.h"

class SceneManager;

enum class QuestType
{
	COLLECT,
	KILL,
	INTERACT
};

class Quest
{
public:
	QuestType type;
	int amount = 0; // Amount of enemies/items to kill/collect
	SString interactionName = '/0'; // Interaction name for Interact quests
	SString text;
	bool operator!=(Quest quest)
	{
		return (type != quest.type || amount != quest.amount || interactionName.operator!=(quest.interactionName) || text.operator!=(quest.text));
	}
};

class QuestSystem
{
public:
	QuestSystem(SceneManager* sceneManager) 
	{
		this->sceneManager = sceneManager;
	};
	~QuestSystem() {};

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

	//bool CheckMainQuest(); // Checkea si se ha completado la main quest

	//MAYBE ESTARIA BIEN HACER UNA FUNCION DIFERENTE PARA CHECKEAR SI SE HAN COMPLETADO, TIPO CheckCollectSideQuest/CheckKillSideQuest/CheckInteractSideQuest Y QUIZA LO MISMO CON EL mainQuest

public:
	Quest mainQuest;
	List<Quest> sideQuests;
	SceneManager* sceneManager;

private:
	int maxSideQuests = 3;
};

#endif //__QUESTSYSTEM_H__