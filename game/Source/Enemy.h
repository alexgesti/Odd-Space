#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"


enum class EnemyType
{
    STANDARTPIRATE,
    MUTANTRAT,
    GIANTBAT,
    DRUNKCUSTOMER,
    CAPTAINRATEYE
};

class Enemy : public Entity
{
public:

    Enemy(EnemyType type) : Entity(EntityType::ENEMY), type(type), active(true) {}

    virtual bool Update(float dt)
    {
        return true;
    }

    virtual bool Draw()
    {
        return true;
    }

public:

    EnemyType type;
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