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
    for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
    {
        if (i == sceneManager->entityManager->entities[2].Count())
        {
            itemsButtons[i] = new GuiButton(i, { 344, (i * 79) + 110, 830, 79 }, "Back", sceneManager->audio, false);
            buttonItems[i] = i;
            itemsButtons[i]->SetObserver(this);
        }
        else
        {
            itemsButtons[i] = new GuiButton(i, { 344, (i * 79) + 110, 830, 79 }, "Item", sceneManager->audio, false);
            buttonItems[i] = i;
            itemsButtons[i]->SetObserver(this);
            itemsButtons[i]->text = sceneManager->entityManager->entities[2].At(i)->data->infoEntities.info.name;
        }
    }

    c = 0;

    return true;
}

bool ItemsMenu::Update(float dt)
{
    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
        buttonItems[c++];

    if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        buttonItems[c--];

    if (c > sceneManager->entityManager->entities[2].Count()) c = 0;
    if (c < 0) c = sceneManager->entityManager->entities[2].Count();

    for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
        itemsButtons[i]->Update(sceneManager->input, buttonItems[c], dt);

    return true;
}

bool ItemsMenu::Draw()
{
    SDL_Rect options = { -sceneManager->render->camera.x + 344, -sceneManager->render->camera.y + 110, 830, 553 };
    //sceneManager->render->DrawRectangle(options, 100, 100, 100, 255);

    for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
        itemsButtons[i]->Draw(sceneManager->render, sceneManager->font);
        

    return true;
}

bool ItemsMenu::Unload()
{
    sceneManager->tex->UnLoad(itemsText);

    sceneManager->openItems = false;

    for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
        RELEASE(itemsButtons[i]);

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
        break;
    default: break;
    }

    return true;
}