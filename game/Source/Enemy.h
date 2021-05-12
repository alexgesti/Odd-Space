#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"


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

    Enemy(EnemyType type) : Entity(EntityType::ENEMY), enemyType(type) {}

public:

    EnemyType enemyType;
};

#endif // __ENTITY_H__