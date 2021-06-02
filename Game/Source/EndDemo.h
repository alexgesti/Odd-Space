#ifndef __ENDDEMO_H__
#define __ENDDEMO_H__

#include "Scene.h"
#include "GuiButton.h"

#define MAX_ZOOM 3.0f
#define MIN_ZOOM 0.3f

class SceneManager;
class SDL_Texture;

class EndDemo : public Scene
{
public:

    // Constructor
    EndDemo(SceneManager* sceneManager);
    // Destructor
    virtual ~EndDemo();


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
        GuiButton* buttonExit;
    }buttons;

    int c;
    int controllerMenu[2] = { 1, 2 };

    bool dead = false;

    int pos1 = 12;
};

#endif // __SCENETITLE_H__
