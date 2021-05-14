#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "GuiButton.h"

#define MAX_ZOOM 3.0f
#define MIN_ZOOM 0.3f

class SceneManager;
class SDL_Texture;

class Title : public Scene
{
public:

    // Constructor
    Title(SceneManager* sceneManager);
    // Destructor
    virtual ~Title();


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
    
    SceneManager* sceneManager;

    SDL_Texture* bgTitle;
    SDL_Texture* titleName;

    struct Buttons
    {
        GuiButton* buttonPlay;
        GuiButton* buttonContinue;
        GuiButton* buttonSettings;
        GuiButton* buttonExit;
    }buttons;

    int c;
    int controllerMenu[4] = { 1, 2, 3, 4 };

    bool oneTime = true;
    bool openOptions = false;
    int temporalAppearTitle = 0;

    int pos1 = 12;

    //float titlePosX = 1280 + 718;
    float initPosY = -350;
    float titlePosY = initPosY;
    float currentTime = 0.0f;
};

#endif // __SCENETITLE_H__