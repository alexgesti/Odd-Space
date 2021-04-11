#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "Collision.h"

#include "List.h"

class Input;
class Render;
class Player;
enum class SceneType;

class EntityManager : public Module
{
public:

	// Constructor
	EntityManager(Input* input, Render* render);
	// Destructor
	virtual ~EntityManager();


	// Called before render is available
	bool Awake(pugi::xml_node&);


	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Additional methods
	Entity* CreateEntity(EntityType type);
	void DestroyEntity(Entity* entity);

	void AddEntity(Entity* entity);

	bool UpdateAll(float dt, bool doLogic);

	bool Draw();

public:

	List<Entity*> entities[4];

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	Collision collision;

private:

	Input* input;
	Render* render;

	//Number of list created
	int numList = 4;

public:
	SceneType* previousScene;
};

#endif // __ENTITYMANAGER_H__
