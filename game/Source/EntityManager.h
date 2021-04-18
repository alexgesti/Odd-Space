#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "Collision.h"

#include "List.h"

class Input;
class Render;
class Player;
class Textures;

enum class SceneType;

class EntityManager : public Module
{
public:

	// Constructor
	EntityManager(Input* input, Render* render, Textures* tex);
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

	void AddEntity(Entity* entity);

	bool UpdateAll(float dt, bool doLogic);

	bool Draw();

	bool DestroyEntity(int i);

public:

	List<Entity*> entities[4];

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	Collision collision;

	SceneType* previousScene;

private:

	Input* input;
	Render* render;
	Textures* tex;
};

#endif // __ENTITYMANAGER_H__
