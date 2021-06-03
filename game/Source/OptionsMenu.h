#ifndef __OPTIONSMENU_H__
#define __OPTIONSMENU_H__

#include "Scene.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "Animation.h"

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

    int c;
    int fmax;
    int buttonOption[5] = { 1, 2, 3, 4, 5 };

    SDL_Texture* texture;
    /*SDL_Texture* explosion;
    Animation* explosionAnim = new Animation();
    bool playingExplosionVsync = false;
    bool playingExplosionfullScreen = false;*/
    StepedAnimation* stepedAnimation;

    GuiCheckBox* fullScreen;
    GuiCheckBox* VSync;
    GuiSlider* music;
    GuiSlider* fx;
    GuiButton* exit;
};

#endif // __OPTIONSMENU_H__