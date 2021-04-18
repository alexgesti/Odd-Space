#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"


struct Info
{
    SString name;
    int HP;
    int SP;
    int maxHP;
    int maxSP;
    int LVL;
};

struct Stat
{
    int ATK;
    int DEF;
    int SPD;
    int LCK;
};

struct Skill
{
    SString name;
    SString description;
    int cost;
    bool picked = false;
};

struct Entities
{
    Info info;
    Stat stats;
    Skill skills[5];
    bool defense;
    bool attack;
};

enum class EntityType
{
    HERO,
    CAPTAIN,
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

    virtual bool UnLoad()
    {
        return true;
    }

public:

    EntityType type;
    Entities infoEntities;
    bool active = true;
    //SString name;         // Entity name identifier?
    //uint32 id;            // Entity identifier?

    // Possible properties, it depends on how generic we
    // want our Entity class, maybe it's not renderable...
    iPoint temPos;
    iPoint position;        // Use a float instead?
    bool transitioning = false;
    bool isPause = false;
    bool renderable = false;
    bool interacting = false;
    bool inBattle = false;
    bool inConversation = false;

    bool loadedPos = false;
};

#endif // __ENTITY_H__