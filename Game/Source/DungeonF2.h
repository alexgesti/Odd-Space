#ifndef __DUNGEONF2_H__
#define __DUNGEONF2_H__

#define BOTTOM_CAMERA_LIMIT -1104
#define TOP_CAMERA_LIMIT 0
#define UPPER_DOOR 512

#include "Scene.h"
#include "Font.h"
#include "Animation.h"

class Map;

class SceneManager;

class DungeonF2 : public Scene
{
public:

    // Constructor
    DungeonF2(SceneManager* sceneManager);
    // Destructor
    virtual ~DungeonF2();


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

    int leverFx;
    int winFx;
    int bigdoor;
    int itempick;

    SDL_Texture* leverTex;
    SDL_Texture* fakeWall;
};


#endif // !__DUNGEONF2_H__
