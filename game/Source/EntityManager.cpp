#include "EntityManager.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "SceneManager.h"

//Characters
#include "Player.h"
#include "OldCaptain.h"
//Enemies
#include "MutantRat.h"
#include "GiantBat.h"
#include "DrunkCustomer.h"
#include "StandardPirate.h"
//Items
#include "CookedPlate.h"
#include "StrongRon.h"
#include "RawMeat.h"
#include "Pint.h"
#include "LargeRawMeat.h"
#include "Jug.h"
#include "ElaboratedPlate.h"

#include "Defs.h"
#include "Log.h"
#include <time.h>



// Constructor
EntityManager::EntityManager(Input* input, Render* render, Textures* tex) : Module()
{
	this->input = input;
	this->render = render;
	this->tex = tex;

	name.Create("entitymanager");
}
// Destructor
EntityManager::~EntityManager()
{}


// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	srand(time(NULL));

	return ret;
}


// Called each loop iteration
bool EntityManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}


// Called before quitting
bool EntityManager::CleanUp()
{
	if (!active) return true;

	return true;
}


Entity* EntityManager::CreateEntity(EntityType type)
{
	Entity* ret = nullptr;

	switch (type)
	{
		// L13: Create the corresponding type entity
	case EntityType::HERO:
		ret = Player::GetInstance(input, render, tex);

		// Created entities are added to the list
		if (ret != nullptr && (Player*)entities[0].start == nullptr)
		{
			Player::SetCollision(&collision, (Player*)ret);
			entities[0].Add(ret);
		}
		break;

	case EntityType::CAPTAIN:
		ret = Captain::GetInstance(render, tex);

		// Created entities are added to the list
		if (ret != nullptr && (Captain*)entities[0].At(1) == nullptr) entities[0].Add(ret);
		break;

	case EntityType::ENEMY:
		switch (*previousScene)
		{
		case SceneType::CANTINA:
			ret = DrunkCustomer::GetInstance(render, tex);
			break;

		case SceneType::WC:
		case SceneType::EXTERIOR:
			ret = MutantRat::GetInstance(render, tex);
			break;

		case SceneType::DUNGEON_EXT:
		case SceneType::DUNGEON_F1:
		case SceneType::DUNGEON_F2:
			switch (rand() % 2)
			{
			case 0:
				ret = MutantRat::GetInstance(render, tex);
				break;
			case 1:
				ret = GiantBat::GetInstance(render, tex);
				break;
			}
			break;

		default:
			ret = StandardPirates::GetInstance(render, tex);
			break;
		}

		// Created entities are added to the list
		if (ret != nullptr) entities[1].Add(ret);
		break;

	case EntityType::RANDITEM:
	{
		int drop = rand() % 3;
		for (int d = 0; d < drop; d++)
		{
			switch (rand() % 15)
			{
				//20%
			case 0:
			case 1:
			case 2:
				quantity[0]++;
				ret = RawMeat::GetInstance(render, tex);
				break;

				//20%
			case 3:
			case 4:
			case 5:
				quantity[4]++;
				ret = Pint::GetInstance(render, tex);
				break;

				//13%
			case 6:
			case 7:
				quantity[1]++;
				ret = LargeRawMeat::GetInstance(render, tex);
				break;

				//13%
			case 8:
			case 9:
				quantity[5]++;
				ret = Jug::GetInstance(render, tex);
				break;

				//13%
			case 10:
			case 11:
				quantity[2]++;
				ret = CookedPlate::GetInstance(render, tex);
				break;

				//13%
			case 12:
			case 13:
				quantity[6]++;
				ret = StrongRon::GetInstance(render, tex);
				break;

				//7%
			case 14:
				quantity[3]++;
				ret = ElaboratedPlate::GetInstance(render, tex);
				break;

			default: break;
			}
		}
		break;
	}
	default: break;
	}

	return ret;
}

Entity* EntityManager::GenerateListItems()
{
	Entity* ret = nullptr;

	ret = RawMeat::GetInstance(render, tex);
	if (ret != nullptr) entities[2].Add(ret);

	ret = LargeRawMeat::GetInstance(render, tex);
	if (ret != nullptr) entities[2].Add(ret);

	ret = CookedPlate::GetInstance(render, tex);
	if (ret != nullptr) entities[2].Add(ret);

	ret = ElaboratedPlate::GetInstance(render, tex);
	if (ret != nullptr) entities[2].Add(ret);

	ret = Pint::GetInstance(render, tex);
	if (ret != nullptr) entities[2].Add(ret);

	ret = Jug::GetInstance(render, tex);
	if (ret != nullptr) entities[2].Add(ret);

	ret = StrongRon::GetInstance(render, tex);
	if (ret != nullptr) entities[2].Add(ret);

	return ret;
}


bool EntityManager::UpdateAll(float dt, bool doLogic)
{
	if (doLogic)
	{
		//Same lenght as entities
		for (int i = 0; i < 3; i++)
		{
			// TODO: Update all entities 
			ListItem<Entity*>* list = NULL;
			list = entities[i].start;

			while (list != NULL)
			{
				list->data->Update(dt);
				if (list->data->infoEntities.info.HP <= 0 && !list->data->deadAdded)
				{
					enemyKills++;
					list->data->deadAdded = true;
				}
				list = list->next;
			}
		}
	}

	return true;
}

bool EntityManager::Draw()
{
	//Same lenght as entities
	for (int i = 0; i < 3; i++)
	{
		ListItem<Entity*>* list = NULL;
		list = entities[i].start;

		while (list != NULL)
		{
			list->data->Draw();
			list = list->next;
		}
	}

	return true;
}

// Destroy an existing Entity
bool EntityManager::DestroyEntity(int i)
{
	ListItem<Entity*>* list = NULL;
	list = entities[i].start;

	while (list != NULL)
	{
		list->data->UnLoad();
		RELEASE(list->data);
		list = list->next;
	}

	return true;
}
