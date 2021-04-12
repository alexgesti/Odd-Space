#ifndef __EXTERIOR_H__
#define __EXTERIOR_H__

#define BOTTOM_CAMERA_LIMIT -48
#define TOP_CAMERA_LIMIT 0

#include "Scene.h"
#include "Font.h"

class Map;

class Window;
class Input;
class Render;
class Textures;
class EntityManager;

class Collision;
class Speak;

class Exterior : public Scene
{
public:

    // Constructor
    Exterior(Window* win, Input* input, Render* render, Textures* tex, EntityManager* entityManager, Collision* collision, SceneType* previousScene, Font* font, Speak* speak);
    // Destructor
    virtual ~Exterior();


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
    Speak* speak;

    SceneType* previousScene;

    Font* font;
};

#endif // __EXTERIOR_H__