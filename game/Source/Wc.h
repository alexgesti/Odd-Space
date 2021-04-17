#ifndef __WC_H__
#define __WC_H__

#define BOTTOM_CAMERA_LIMIT -1100
#define TOP_CAMERA_LIMIT 1000

#include "Scene.h"
#include "Font.h"
#include "Point.h"

class Map;

class SceneManager;

class Wc : public Scene
{
public:

    // Constructor
    Wc(SceneManager* sceneManager);
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

    SceneManager* sceneManager;

    int wcFx;
};

#endif // __WC_H__