#ifndef __DUNGEONEXT_H__
#define __DUNGEONEXT_H__

#define BOTTOM_CAMERA_LIMIT -16
#define TOP_CAMERA_LIMIT 0
#define UPPER_DOOR 512

#include "Scene.h"
#include "Font.h"
#include "Animation.h"

class Map;

class SceneManager;

class DungeonExt : public Scene
{
public:

    // Constructor
    DungeonExt(SceneManager* sceneManager);
    // Destructor
    virtual ~DungeonExt();


    // Load this scene
    bool Load();

    // Update this scene
    bool Update(float dt);

    // Draw this scene
    bool Draw();

    // Unload this scene
    bool Unload();

    // Declare on mouse click event
    bool OnGuiMouseClickEvent(GuiControl* control);

private:

    Map* map;

    SceneManager* sceneManager;

    int stairsFx;
};


#endif // !__DUNGEONEXT_H__


