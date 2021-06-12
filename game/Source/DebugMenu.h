#ifndef __DEBUGMENU_H__
#define __DEBUGMENU_H__

#include "Scene.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"

class SceneManager;

class Debug : public Scene
{
public:

    // Constructor
    Debug(SceneManager* sceneManager);
    // Destructor
    virtual ~Debug();


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

    SDL_Texture* texture;

    SceneManager* sceneManager;

    struct DebugButtons
    {
        GuiCheckBox* noClip;
        GuiCheckBox* godMode;
        GuiCheckBox* dialogue;
        GuiCheckBox* colliders;
        GuiButton* battle;
        GuiButton* item;
        GuiButton* scene;
        GuiButton* particle;
    }debug;

    struct SceneButtons
    {
        GuiButton* exterior;
        GuiButton* cantina;
        GuiButton* wc;
        GuiButton* dungeonExt;
        GuiButton* dungeonF1;
        GuiButton* dungeonF2;
    }scene;

    struct ParticleButtons
    {
        GuiButton* smoke;
        GuiButton* heal;
        GuiButton* bless;
    }particle;

    int c, f;
    int controllerMenu[4][2];
    int controllerScene[6];
    int controllerParticle[3];

    bool debugscene = false;
    bool debugparticle = false;
};

#endif // __DEBUGMENU_H__
