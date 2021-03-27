#include "EntityManager.h"

#include "Player.h"
//#include "Enemy.h"
//#include "Item.h"

#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager(Input* input) : Module()
{
	this->input = input;
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
	case EntityType::PLAYER: ret = Player::GetInstance(input);  break;
		//case EntityType::ENEMY: ret = new Enemy();  break;
		//case EntityType::ITEM: ret = new Item();  break;
		default: break;
	}

	// Created entities are added to the list
	if (ret != nullptr) entities.Add(ret);

	return ret;
}

bool EntityManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(input, dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}

bool EntityManager::UpdateAll(Input* input, float dt, bool doLogic)
{
	if (doLogic)
	{
		// TODO: Update all entities 
		ListItem<Entity*>* list;
		list = entities.start;

		while (list != NULL)
		{
			list->data->Update(dt);
			list = list->next;
		}
	}

	return true;
}

bool EntityManager::Draw(Render* render)
{
	ListItem<Entity*>* list;
	list = entities.start;

	while (list != NULL)
	{
		list->data->Draw(render);
		list = list->next;
	}
	return true;
}