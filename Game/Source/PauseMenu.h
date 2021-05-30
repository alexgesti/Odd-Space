#ifndef __PAUSEMENU_H__
#define __PAUSEMENU_H__

#include "Scene.h"
#include "GuiButton.h"

#include "SDL/include/SDL.h"

class SceneManager;

class PauseMenu : public Scene
{
public:

    // Constructor
    PauseMenu(SceneManager* sceneManager);

    // Destructor
    virtual ~PauseMenu();

    // Load this scene
    bool Load();

    // Update this scene
    bool Update(float dt);

    // Draw this scene
    bool Draw();

    // Unload this scene
    bool Unload();

    // Manage GUI events for this screen
    bool OnGuiMouseClickEvent(GuiControl* control);

    int pauseFx = 0;
    int unPauseFx = 0;

private:

    SceneManager* sceneManager;

    int f;
    int buttonMenuMax[6] = { 1, 2, 3, 4, 5, 6 };

    SDL_Texture* pause = nullptr;

    GuiButton* buttonItems;
    GuiButton* buttonSkills;
    GuiButton* buttonEquip;
    GuiButton* buttonSettings;
    GuiButton* buttonSave;
    GuiButton* buttonLoad;
};

#endif // __PAUSEMENU_H__