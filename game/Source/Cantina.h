#ifndef __CANTINA_H__
#define __CANTINA_H__

#include "Scene.h"

class Map;

class Window;
class Input;
class Render;
class Textures;
class EntityManager;

class Cantina : public Scene
{
public:

    // Constructor
    Cantina(Window* win, Input* input, Render* render, Textures* tex, EntityManager* entityManager);
    // Destructor
    virtual ~Cantina();


    // Load this scene
    bool Load();

    // Update this scene
    bool Update(float dt);

    // Draw this scene
    bool Draw();

    // Unload this scene
    bool Unload();

private:
    Map* map;

    Window* win;
    Input* input;
    Render* render;
    Textures* tex;
    EntityManager* entityManager;
};

#endif // __CANTINA_H__