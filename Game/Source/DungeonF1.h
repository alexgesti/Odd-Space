#ifndef __DUNGEONF1_H__
#define __DUNGEONF1_H__

#define BOTTOM_CAMERA_LIMIT -1520
#define TOP_CAMERA_LIMIT -257
#define RIGHT_CAMERA_LIMIT -1664
#define LEFT_CAMERA_LIMIT 0
#define HORIZONTAL_DOOR 1536
#define END_DOOR 960

#include "Scene.h"
#include "Font.h"
#include "Animation.h"

class Map;

class SceneManager;

class DungeonF1 : public Scene
{
public:

    // Constructor
    DungeonF1(SceneManager* sceneManager);
    // Destructor
    virtual ~DungeonF1();


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

    int stairsFx;

private:

    Map* map;

    SceneManager* sceneManager;

};


#endif // !__DUNGEONF1_H__
