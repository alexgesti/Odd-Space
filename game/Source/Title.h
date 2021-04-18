#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "GuiButton.h"
#include "Audio.h"

#define MAX_ZOOM 3.0f
#define MIN_ZOOM 0.3f

class SceneManager;
class SDL_Texture;

class Title : public Scene
{
public:

    // Constructor
    Title(SceneManager* sceneManager, Audio* audio);
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
    
    Audio* audio;
    SceneManager* sceneManager;

    SDL_Texture* bgTitle;

    struct Buttons
    {
        GuiButton* buttonPlay;
        GuiButton* buttonContinue;
        GuiButton* buttonSettings;
        GuiButton* buttonExit;
    }buttons;

    int f;
    int c;
    int controllerMenu[2][2] = { {1, 2}, {3, 4} };

    bool oneTime = true;
    int temporalAppearTitle = 0;
    int selected = 0;
};

#endif // __SCENETITLE_H__