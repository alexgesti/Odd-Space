#ifndef __WC_H__
#define __WC_H__

#define BOTTOM_CAMERA_LIMIT -1100
#define TOP_CAMERA_LIMIT 1000

#include "Scene.h"

class Map;

class Window;
class Input;
class Render;
class Textures;
class EntityManager;

class Collision;

class Wc : public Scene
{
public:

    // Constructor
    Wc(Window* win, Input* input, Render* render, Textures* tex, EntityManager* entityManager, Collision* collision, SceneType* previousScene);
    // Destructor
    virtual ~Wc();


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

#endif // __WC_H__