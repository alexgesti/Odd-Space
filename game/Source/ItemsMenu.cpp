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
            itemsButtons[i] = new GuiButton(2, { 344, (i * 79) + 110, 830, 79 }, "Back", sceneManager->audio);
            buttonItems[i] = 2;
            itemsButtons[i]->SetObserver(this);
        }
        else
        {
            itemsButtons[i] = new GuiButton(1, { 344, (i * 79) + 110, 830, 79 }, "Item", sceneManager->audio);
            buttonItems[i] = 1;
            itemsButtons[i]->SetObserver(this);
            itemsButtons[i]->text = sceneManager->entityManager->entities[2].At(i)->data->infoEntities.info.name;
        }
    }

    f = 0;

    return true;
}

bool ItemsMenu::Update(float dt)
{
    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
        buttonItems[f++];

    if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        buttonItems[f--];

    if (f > sceneManager->entityManager->entities[2].Count()) f = 0;
    if (f < 0) f = sceneManager->entityManager->entities[2].Count();

    for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
        itemsButtons[i]->Update(sceneManager->input, buttonItems[f], dt);

    return true;
}

bool ItemsMenu::Draw()
{
    SDL_Rect options = { -sceneManager->render->camera.x + 344, -sceneManager->render->camera.y + 110, 830, 553 };
    sceneManager->render->DrawRectangle(options, 0, 0, 255, 255);

    for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
        itemsButtons[i]->Draw(sceneManager->render, sceneManager->font);
        

    return true;
}

bool ItemsMenu::Unload()
{
    sceneManager->tex->UnLoad(itemsText);

    sceneManager->openItems = false;

    for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
    {
        delete itemsButtons[i];
        itemsButtons[i] = nullptr;
    }

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