#ifndef __CANTINA_H__
#define __CANTINA_H__

#define BOTTOM_CAMERA_LIMIT -110
#define TOP_CAMERA_LIMIT 0

#define UPPER_DOOR 200

//Quiza no hace falta un LOWER_DOOR, si no es el UPPER_DOOR hacemos un else y ya
#define LOWER_DOOR 760

#include "Scene.h"
#include "Font.h"
#include "Animation.h"

class Map;

class SceneManager;

class Cantina : public Scene
{
public:

    // Constructor
    Cantina(SceneManager* sceneManager);
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

    SceneManager* sceneManager;

    SDL_Texture* texBarman;
    Animation* animBarmanIdle = new Animation();
};

#endif // __CANTINA_H__