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
    charButtons[0] = new GuiButton(0, { 927, 107, 900, 90 }, "Hero", sceneManager->audio, false);
    buttonChars[0] = 0;
    charButtons[0]->SetObserver(this);

    charButtons[1] = new GuiButton(1, { 927, 385, 900, 90 }, "Captain", sceneManager->audio, false);
    buttonChars[1] = 1;
    charButtons[1]->SetObserver(this);
    
    // Items select
    itemsButtons[0] = new GuiButton(0, { 344, (0 * 79) + 110, 830, 79 }, "Raw meat", sceneManager->audio, false);
    buttonItems[0] = 0;
    itemsButtons[0]->SetObserver(this);

    itemsButtons[1] = new GuiButton(1, { 344, (1 * 79) + 110, 830, 79 }, "Large raw meat", sceneManager->audio, false);
    buttonItems[1] = 1;
    itemsButtons[1]->SetObserver(this);

    itemsButtons[2] = new GuiButton(2, { 344, (2 * 79) + 110, 830, 79 }, "Cooked plate", sceneManager->audio, false);
    buttonItems[2] = 2;
    itemsButtons[2]->SetObserver(this);

    itemsButtons[3] = new GuiButton(3, { 344, (3 * 79) + 110, 830, 79 }, "Elaborated plate", sceneManager->audio, false);
    buttonItems[3] = 3;
    itemsButtons[3]->SetObserver(this);

    itemsButtons[4] = new GuiButton(4, { 344, (4 * 79) + 110, 830, 79 }, "Pint", sceneManager->audio, false);
    buttonItems[4] = 4;
    itemsButtons[4]->SetObserver(this);

    itemsButtons[5] = new GuiButton(5, { 344, (5 * 79) + 110, 830, 79 }, "Jug", sceneManager->audio, false);
    buttonItems[5] = 5;
    itemsButtons[5]->SetObserver(this);

    itemsButtons[6] = new GuiButton(6, { 344, (6 * 79) + 110, 830, 79 }, "Strong ron", sceneManager->audio, false);
    buttonItems[6] = 6;
    itemsButtons[6]->SetObserver(this);

    c = 0;
    f = 0;

    UI = sceneManager->tex->Load("sprites/ui/ui_menupause.png");

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

        if (f > 1) f = 0;
        if (f < 0) f = 1;

        for (int i = 0; i < 2; i++)
            charButtons[i]->Update(sceneManager->input, buttonChars[f], dt);
    }
    // Items select
    else if (chooseMenu == 0)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            buttonItems[c++];

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            buttonItems[c--];

        if (c > 5) c = 0;
        if (c < 0) c = 5;

        for (int i = 0; i < 6; i++)
        {
            itemsButtons[i]->Update(sceneManager->input, buttonItems[c], dt);
            if(sceneManager->entityManager->quantity[i] == 0) itemsButtons[i]->disabled = true;
            else itemsButtons[i]->disabled = false;
        }
    }

    return true;
}

bool ItemsMenu::Draw()
{
    SDL_Rect rect = { 1106, 0, 1105, 624 };

    SDL_Rect rect2 = { 1048, 0, 36, 569 };
    sceneManager->render->DrawTexture(UI, -sceneManager->render->camera.x + 870, -sceneManager->render->camera.y + 102, &rect2);

    // Character select
    for (int i = 0; i < 2; i++)
        charButtons[i]->Draw(sceneManager->render, sceneManager->font);

    //Player
    std::string HP = std::to_string(sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP);
    std::string maxHP = std::to_string(sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.maxHP);
    sceneManager->render->DrawText(sceneManager->font, ("HP " + HP + " / " + maxHP).c_str(), 47 + (rect.w / 1.25f), 48 + rect.h / 3.75f, 25, 0, { 255, 255, 255, 255 });

    std::string SP = std::to_string(sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.SP);
    std::string maxSP = std::to_string(sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.maxSP);
    sceneManager->render->DrawText(sceneManager->font, ("SP " + SP + " / " + maxSP).c_str(), 47 + (rect.w / 1.25f), 48 + rect.h / 2.5f, 25, 0, { 255, 255, 255, 255 });

    //Captain
    HP = std::to_string(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP);
    maxHP = std::to_string(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxHP);
    sceneManager->render->DrawText(sceneManager->font, ("HP " + HP + " / " + maxHP).c_str(), 47 + (rect.w / 1.25f), 48 + rect.h / 1.4f, 25, 0, { 255, 255, 255, 255 });

    SP = std::to_string(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.SP);
    maxSP = std::to_string(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxSP);
    sceneManager->render->DrawText(sceneManager->font, ("SP " + SP + " / " + maxSP).c_str(), 47 + (rect.w / 1.25f), 48 + rect.h / 1.2f, 25, 0, { 255, 255, 255, 255 });

    // Items select
    for (int i = 0; i < 6; i++)
    {
        itemsButtons[i]->Draw(sceneManager->render, sceneManager->font);
        //sceneManager->render->DrawText(sceneManager->font, "x 0", 700, (i * 79) + 137, 25, 0, { 255, 255, 255, 255 });
        std::string object = std::to_string(sceneManager->entityManager->quantity[i]);
        sceneManager->render->DrawText(sceneManager->font, ("x " + object).c_str(), 700, (i * 79) + 137, 25, 0, { 255, 255, 255, 255 });
    }

    return true;
}

bool ItemsMenu::Unload()
{
    sceneManager->tex->UnLoad(itemsText);
    sceneManager->tex->UnLoad(UI);

    sceneManager->openItems = false;

    chooseMenu = 0;

    for (int i = 0; i < 2; i++)
    {
        charButtons[i];
        RELEASE(charButtons[i]);
    }

    for (int i = 0; i < 6; i++)
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
        for (int i = 0; i < 6; i++)
        {
            if (control->id == i)
            {
                chooseMenu = 1;
                choosedItem = i;
            }
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
            if(sceneManager->entityManager->quantity[choosedItem] != 0) sceneManager->entityManager->quantity[choosedItem] -= 1;
            chooseMenu = 0;
            break;
        case 1:
            sceneManager->entityManager->entities[2].At(choosedItem)->data->ItemFunction(&sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP,
                &sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.SP,
                sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxHP,
                sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxSP);
            if (sceneManager->entityManager->quantity[choosedItem] != 0) sceneManager->entityManager->quantity[choosedItem] -= 1;
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