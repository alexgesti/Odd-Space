#include "EntityManager.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "SceneManager.h"

#include "Player.h"
#include "OldCaptain.h"
#include "Enemy.h"
#include "MutantRat.h"
#include "GiantBat.h"
#include "DrunkCustomer.h"
#include "StandardPirates.h"
//#include "Item.h"

#include "Defs.h"
#include "Log.h"



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
		ret = Captain::GetInstance(input, render);

		// Created entities are added to the list
		if (ret != nullptr && (Captain*)entities[0].At(1) == nullptr) entities[0].Add(ret);
		break;

	case EntityType::ENEMY:
		switch (*previousScene)
		{
		case SceneType::CANTINA: 
			ret = DrunkCustomer::GetInstance(input, render);
			break;
		case SceneType::WC: 
			ret = MutantRat::GetInstance(input, render);
			break;
		case SceneType::EXTERIOR: 
			ret = GiantBat::GetInstance(input, render);
			break;
		default: 
			ret = StandardPirates::GetInstance(input, render);
			break;
		}

		// Created entities are added to the list
		if (ret != nullptr) entities[1].Add(ret);
		break;

	//case EntityType::ITEM: ret = new Item();  break;
	default: break;
	}

	return ret;
}


bool EntityManager::UpdateAll(float dt, bool doLogic)
{
	if (doLogic)
	{
		//Same lenght as entities
		for (int i = 0; i < 4; i++)
		{
			// TODO: Update all entities 
			ListItem<Entity*>* list = NULL;
		list = entities[i].start;

		while (list != NULL)
		{
			list->data->Update(dt);
			list = list->next;
		}
	}
	}

	return true;
}

bool EntityManager::Draw()
{
	//Same lenght as entities
	for (int i = 0; i < 4; i++)
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