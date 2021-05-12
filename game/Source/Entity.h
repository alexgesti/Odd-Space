#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"
#include "Animation.h"

#include "SDL/include/SDL.h"


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

    Entity(EntityType type) : type(type), active(true) 
    {
        hurtAnim->loop = false;
        hurtAnim->speed = 0.15f;
        for (int i = -1; i < 8; ++i)
            hurtAnim->PushBack({ 64 * i, 0, 64, 96 });

        deathAnim->loop = true;
        deathAnim->speed = 0.15f;
        for (int i = 0; i < 4; i++) deathAnim->PushBack({ 128 * i, 0, 128, 96 });
        deathAnim->PushBack({ 256, 0, 128, 96 });
        deathAnim->PushBack({ 128, 0, 128, 96 });
    }

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
    SDL_Texture* hurtTexture;
    SDL_Texture* shieldTexture;
    SDL_Texture* deathTexture;
    //Animation* currentGeneralAnimation;
    Animation* hurtAnim = new Animation();
    Animation* deathAnim = new Animation();
    bool active = true;

    // Possible properties, it depends on how generic we
    // want our Entity class, maybe it's not renderable...
    iPoint temPos;
    iPoint position;        // Use a float instead?
    iPoint prevPos;
    bool transitioning = false;
    bool isPause = false;
    bool renderable = false;
    bool interacting = false;
    bool inBattle = false;
    bool inConversation = false;
    bool noClip = false;

    bool loadedPos = false;
};

#endif // __ENTITY_H__