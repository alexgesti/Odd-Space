#ifndef __OPTIONSMENU_H__
#define __OPTIONSMENU_H__

#include "Scene.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"

#include "SDL_mixer/include/SDL_mixer.h"

class SceneManager;

class OptionsMenu : public Scene
{
public:

    // Constructor
    OptionsMenu(SceneManager* sceneManager);

    // Destructor
    virtual ~OptionsMenu();

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

private:

    SceneManager* sceneManager;

    int f;
    int buttonOption[4] = { 1, 2, 3, 4 };

    SDL_Texture* optionsText;
    GuiCheckBox* fullScreen;
    GuiCheckBox* VSync;
    GuiSlider* music;
    GuiSlider* fx;
};

#endif // __OPTIONSMENU_H__