#include "QuestSystem.h"
#include "SceneManager.h"

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
	}*/
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
	renderer->DrawText(font, "Main quest:", 0, 14, 25, 5, {255, 255, 255, 255});
	renderer->DrawText(font, mainQuest.text.GetString(), 10, 44, 20, 5, { 255, 255, 255, 255 });
	renderer->DrawText(font, "Side quests:", 0, 74, 25, 5, { 255, 255, 255, 255 });
	for (int i = 0; i < sideQuests.Count(); i++)
	{
		renderer->DrawText(font, sideQuests.At(i)->data.text.GetString(), 10, 104 + (30 * i), 20, 5, { 255, 255, 255, 255 });
	}
}