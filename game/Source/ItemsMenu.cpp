#include "ItemsMenu.h"

#include "SceneManager.h"

// Constructor
ItemsMenu::ItemsMenu(SceneManager* sceneManager)
{
    this->sceneManager = sceneManager;
}
// Destructor
ItemsMenu::~ItemsMenu()
{
}



bool ItemsMenu::Load()
{

    f = 0;

    return true;
}

bool ItemsMenu::Update(float dt)
{
    GamePad& pad = sceneManager->input->pads[0];

    return true;
}

bool ItemsMenu::Draw()
{

    return true;
}

bool ItemsMenu::Unload()
{
    sceneManager->tex->UnLoad(itemsText);

    return true;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool ItemsMenu::OnGuiMouseClickEvent(GuiControl* control)
{
    GamePad& pad = sceneManager->input->pads[0];

    switch (control->id)
    {
    case 1:
        sceneManager->win->ToggleFullscreen(sceneManager->win->window);
        break;
    default: break;
    }

    return true;
}