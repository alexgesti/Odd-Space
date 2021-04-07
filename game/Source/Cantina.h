#ifndef __CANTINA_H__
#define __CANTINA_H__

#define BOTTOM_CAMERA_LIMIT -110
#define TOP_CAMERA_LIMIT 0

#define UPPER_DOOR 200
#define LOWER_DOOR 760

#include "Scene.h"

class Map;

class Window;
class Input;
class Render;
class Textures;
class EntityManager;

class Collision;

class Cantina : public Scene
{
public:

    // Constructor
    Cantina(Window* win, Input* input, Render* render, Textures* tex, EntityManager* entityManager, Collision* collision, SceneType* previousScene);
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

    Collision* collision;

    SceneType* previousScene;
};

#endif // __CANTINA_H__