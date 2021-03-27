#ifndef __CANTINA_H__
#define __CANTINA_H__

#include "Scene.h"

//#include "Map.h"
//#include "Player.h"

class Cantina : public Scene
{
public:

    Cantina(Window* win, EntityManager* entityManager);
    virtual ~Cantina();

    bool Load(Textures* tex);

    bool Update(Input* input, float dt);

    bool Draw(Render* render);

    bool Unload(Textures* tex);

private:

    Window* win;
    EntityManager* entityManager;
    //Map* map;
};

#endif // __CANTINA_H__