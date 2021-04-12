#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"


struct Stat
{
    int HP;
    int SP;
    int LVL;
    int ATK;
    int DEF;
    int SPL;
    int SPD;
    int AGL;
    int LCK;
};

struct Skill
{
    SString name;
    SString description;
    int cost;
};

struct Entities
{
    SString name;
    Stat stats;
    Skill skills[5];
};

enum class EntityType
{
    PLAYER,
    ENEMY,
    ITEM,
    MAP,
    UNKNOWN
};

class Entity
{
public:

    Entity(EntityType type) : type(type), active(true) {}

    virtual bool Update(float dt)
    {
        return true;
    }

    virtual bool Draw()
    {
        return true;
    }

public:

    EntityType type;
    bool active = true;
    //SString name;         // Entity name identifier?
    //uint32 id;            // Entity identifier?

    // Possible properties, it depends on how generic we
    // want our Entity class, maybe it's not renderable...
    iPoint position;        // Use a float instead?
    bool transitioning = false;
    bool renderable = false;
    bool interacting = false;
    //SDL_Texture* texture;
};

#endif // __ENTITY_H__