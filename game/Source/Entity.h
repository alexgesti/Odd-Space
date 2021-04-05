#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"


struct Stat
{
    int HP;
    int SP;
    int ATK;
    int DEF;
    int SPL;
    int SPD;
    int AGL;
    int LCK;
};
struct Stat stats[];

struct Skill
{
    int skill1;
    int skill2;
    int skill3;
    int skill4;
    int skill5;
};
struct Skill skills [];

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
    bool renderable = false;
    //SDL_Texture* texture;
};

#endif // __ENTITY_H__