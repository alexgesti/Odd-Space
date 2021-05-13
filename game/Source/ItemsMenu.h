#ifndef __ITEMSMENU_H__
#define __ITEMSMENU_H__

#include "Scene.h"
#include "GuiButton.h"

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

    int f;
    int buttonItems[4] = { 1, 2, 3, 4 };

    SDL_Texture* itemsText;
};

#endif // __ITEMSMENU_H__