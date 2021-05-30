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
    // Character select
    charButtons[0] = new GuiButton(0, { 344, (0 * 79) + 110, 830, 79 }, "Hero", sceneManager->audio, false);
    buttonChars[0] = 0;
    charButtons[0]->SetObserver(this);

    charButtons[1] = new GuiButton(1, { 344, (1 * 79) + 110, 830, 79 }, "Captain", sceneManager->audio, false);
    buttonChars[1] = 1;
    charButtons[1]->SetObserver(this);

    charButtons[2] = new GuiButton(2, { 344, (2 * 79) + 110, 830, 79 }, "Back", sceneManager->audio, false);
    buttonChars[2] = 2;
    charButtons[2]->SetObserver(this);
    
    // Items select
    for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
    {
        if (i == sceneManager->entityManager->entities[2].Count())
        {
            itemsButtons[i] = new GuiButton(i, { 344, (i * 79) + 110, 830, 79 }, "NULL", sceneManager->audio, false);
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
    f = 0;

    return true;
}

bool ItemsMenu::Update(float dt)
{
    GamePad& pad = sceneManager->input->pads[0];

    // Character select
    if (chooseMenu == 1)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            buttonChars[f++];

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            buttonChars[f--];

        if (f > 2) f = 0;
        if (f < 0) f = 2;

        for (int i = 0; i < 3; i++)
            charButtons[i]->Update(sceneManager->input, buttonChars[f], dt);
    }
    // Items select
    else if (chooseMenu == 0)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            buttonItems[c++];

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            buttonItems[c--];

        if (c > sceneManager->entityManager->entities[2].Count() - 1) c = 0;
        if (c < 0) c = sceneManager->entityManager->entities[2].Count();

        for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
            if (i != sceneManager->entityManager->entities[2].Count()) itemsButtons[i]->Update(sceneManager->input, buttonItems[c], dt);
    }

    return true;
}

bool ItemsMenu::Draw()
{
    // Character select
    if (chooseMenu == 1)
    {
        for (int i = 0; i < 3; i++)
            charButtons[i]->Draw(sceneManager->render, sceneManager->font);
    }
    // Items select
    else if (chooseMenu == 0)
    {
        for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
            if (i != sceneManager->entityManager->entities[2].Count()) itemsButtons[i]->Draw(sceneManager->render, sceneManager->font);
    }

    return true;
}

bool ItemsMenu::Unload()
{
    sceneManager->tex->UnLoad(itemsText);

    sceneManager->openItems = false;

    chooseMenu = 0;

    for (int i = 0; i < 3; i++)
    {
        charButtons[i];
        RELEASE(charButtons[i]);
    }

    for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
    {
        itemsButtons[i]->UnLoad();
        RELEASE(itemsButtons[i]);
    }

    return true;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool ItemsMenu::OnGuiMouseClickEvent(GuiControl* control)
{
    GamePad& pad = sceneManager->input->pads[0];

    switch (chooseMenu)
    {
    case 0:
        for (int i = 0; i < sceneManager->entityManager->entities[2].Count() + 1; i++)
        {
            if (control->id == i && i != sceneManager->entityManager->entities[2].Count())
            {
                chooseMenu = 1;
                choosedItem = i;
            } //sceneManager->entityManager->entities[2].At(i)->data->ItemFunction(); //Acceder a item para que haga la funcion.
        }
        break;
    case 1:
        switch (control->id)
        {
        case 0:
            sceneManager->entityManager->entities[2].At(choosedItem)->data->ItemFunction(&sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP, 
                &sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.SP,
                sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.maxHP,
                sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.maxSP);
            break;
        case 1:
            sceneManager->entityManager->entities[2].At(choosedItem)->data->ItemFunction(&sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP,
                &sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.SP,
                sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxHP,
                sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxSP);
            break;
        case 2:
            chooseMenu = 0;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return true;
}