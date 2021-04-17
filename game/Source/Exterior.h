#ifndef __EXTERIOR_H__
#define __EXTERIOR_H__

#define BOTTOM_CAMERA_LIMIT -48
#define TOP_CAMERA_LIMIT 0

#include "Scene.h"
#include "Font.h"

class Map;

class SceneManager;

class Exterior : public Scene
{
public:

    // Constructor
    Exterior(SceneManager* sceneManager);
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

    SceneManager* sceneManager;
};

#endif // __EXTERIOR_H__