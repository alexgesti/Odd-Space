#ifndef __ITEMSMENU_H__
#define __ITEMSMENU_H__

#include "Scene.h"
#include "GuiButton.h"
#include "Animation.h"

class SceneManager;

class ItemsMenu : public Scene
{
public:

    // Constructor
    ItemsMenu(SceneManager* sceneManager);

    // Destructor
    virtual ~ItemsMenu();

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
    int buttonItems[7];
    int choosedItem;

    int f;
    int buttonChars[2];

    bool chooseMenu = 0;

    GuiButton* itemsButtons[7];
    GuiButton* charButtons[2];

    SDL_Texture* itemsText;
    SDL_Texture* UI;

    StepedAnimation* stepedAnimation;
};

#endif // __ITEMSMENU_H__