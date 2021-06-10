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

    sceneManager->entityManager->GenerateListItems();

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

    itemsButtons[6] = new GuiButton(6, { 344, (6 * 79) + 110, 830, 79 }, "Strong Ron", sceneManager->audio, false);
    buttonItems[6] = 6;
    itemsButtons[6]->SetObserver(this);

    stepedAnimation = new StepedAnimation();
    stepedAnimation->speed = 80.0f;

    if (sceneManager->currentscenetype == SceneType::BATTLE)
    {
        stepedAnimation->Pushback(341, 1176, 105, 105, 1083, 5);
        stepedAnimation->Pushback(1176, 1176, 105, 661, 5, 572);
        stepedAnimation->Pushback(1181, 341, 661, 661, 1103 - 253, 5);
        stepedAnimation->Pushback(341, 341, 661, 105, 5, 665 - 100);
    }

    else
    {
        stepedAnimation->Pushback(83, 1177, 100, 100, 1083, 5);
        stepedAnimation->Pushback(1177, 1177, 100, 665, 5, 572);
        stepedAnimation->Pushback(1182, 334, 665, 665, 1103 - 253, 5);
        stepedAnimation->Pushback(334, 334, 668, 194, 5, 622 - 144);
        stepedAnimation->Pushback(334, 83, 194, 194, 233, 5);
        stepedAnimation->Pushback(83, 83, 194, 100, 5, 94);
    }

    c = 0;
    f = 0;

    UI = sceneManager->tex->Load("sprites/ui/ui_menupause.png");

    hpRecoverFx = sceneManager->audio->LoadFx("audio/fx/battle_hp_recover.wav");
    reviveFx = sceneManager->audio->LoadFx("audio/fx/battle_revive.wav");
    spRecoverFx = sceneManager->audio->LoadFx("audio/fx/battle_sp_recover.wav");

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

        if (c > 6) c = 0;
        if (c < 0) c = 6;

        for (int i = 0; i < 7; i++)
        {
            if(itemsButtons[i]->state != GuiControlState::PRESSED) itemsButtons[i]->Update(sceneManager->input, buttonItems[c], dt);
            else itemsButtons[i]->Update(sceneManager->input, buttonItems[c], 0.016f);
            if(sceneManager->entityManager->quantity[i] == 0) itemsButtons[i]->disabled = true;
            else itemsButtons[i]->disabled = false;
        }
    }

    return true;
}

bool ItemsMenu::Draw()
{
    SDL_Rect rect = { 1106, 0, 1105, 624 };

    SDL_Rect rect2;

    if (sceneManager->isPause) rect2 = { 1068, 0, 36, 569 }; // Pause Menu
    else // Battle
    {
        rect2 = { 2224, 0, 852, 624 };
        sceneManager->render->DrawTexture(UI, -sceneManager->render->camera.x + 335, -sceneManager->render->camera.y + 50, &rect2);

        rect2 = { 1024, 0, 36, 569 };
    }

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
    for (int i = 0; i < 7; i++)
    {
        itemsButtons[i]->Draw(sceneManager->render, sceneManager->font);
        std::string object = std::to_string(sceneManager->entityManager->quantity[i]);
        sceneManager->render->DrawText(sceneManager->font, ("x " + object).c_str(), 700, (i * 79) + 137, 25, 0, { 255, 255, 255, 255 });
    
        switch (c)
        {
        case 0:
            sceneManager->render->DrawText(sceneManager->font, "A small piece of raw meat. +25% HP.", 348, 67, 25, 0, { 255, 255, 255, 255 });
            break;
        case 1:
            sceneManager->render->DrawText(sceneManager->font, "A large piece of raw meat. +50% HP.", 348, 67, 25, 0, { 255, 255, 255, 255 });
            break;
        case 2:
            sceneManager->render->DrawText(sceneManager->font, "Cooked buffalo meat. +25% HP all team.", 348, 67, 25, 0, { 255, 255, 255, 255 });
            break;
        case 3:
            sceneManager->render->DrawText(sceneManager->font, "Cooked plate with cheese. +50% HP all team.", 348, 67, 25, 0, { 255, 255, 255, 255 });
            break;
        case 4:
            sceneManager->render->DrawText(sceneManager->font, "A nice glass of standard beer. +25% SP.", 348, 67, 25, 0, { 255, 255, 255, 255 });
            break;
        case 5:
            sceneManager->render->DrawText(sceneManager->font, "A nice jug of standard beer. +50% SP.", 348, 67, 25, 0, { 255, 255, 255, 255 });
            break;
        case 6:
            sceneManager->render->DrawText(sceneManager->font, "The STRONGEST ron. Revives a fallen ally.", 348, 67, 25, 0, { 255, 255, 255, 255 });
            break;
        default:
            break;
        }
    }

    int amountDisapeared = 0;

    for (int i = 0; i < stepedAnimation->currentStep; i++)
    {
        SDL_Rect temp = stepedAnimation->GetStep(i);
        sceneManager->render->DrawRectangle(temp, 255, 255, 255, stepedAnimation->steps[i].alpha, true, false);
        if (stepedAnimation->steps[i].disapear) stepedAnimation->steps[i].alpha -= 3;
        if (stepedAnimation->steps[i].alpha <= 0)
        {
            stepedAnimation->steps[i].alpha = 0;
            stepedAnimation->steps[i].disapear = false;
        }

        if (!stepedAnimation->steps[i].disapear) amountDisapeared++;
    }

    if (!stepedAnimation->animationCompleted)
    {
        SDL_Rect temp = stepedAnimation->Update();
        sceneManager->render->DrawRectangle(temp, 255, 255, 255, 255, true, false);
    }

    else if (amountDisapeared >= stepedAnimation->stepAmount)
    {
        stepedAnimation->Reset();
        
        if (sceneManager->currentscenetype == SceneType::BATTLE)
        {
            stepedAnimation->Pushback(341, 1176, 105, 105, 1083, 5);
            stepedAnimation->Pushback(1176, 1176, 105, 661, 5, 572);
            stepedAnimation->Pushback(1181, 341, 661, 661, 1103 - 253, 5);
            stepedAnimation->Pushback(341, 341, 661, 105, 5, 665 - 100);
        }

        else
        {
            stepedAnimation->Pushback(83, 1177, 100, 100, 1083, 5);
            stepedAnimation->Pushback(1177, 1177, 100, 665, 5, 572);
            stepedAnimation->Pushback(1182, 334, 665, 665, 1103 - 253, 5);
            stepedAnimation->Pushback(334, 334, 668, 194, 5, 622 - 144);
            stepedAnimation->Pushback(334, 83, 194, 194, 233, 5);
            stepedAnimation->Pushback(83, 83, 194, 100, 5, 94);
        }
    }

    return true;
}

bool ItemsMenu::Unload()
{
    sceneManager->tex->UnLoad(itemsText);
    sceneManager->tex->UnLoad(UI);

    sceneManager->audio->UnloadFx(hpRecoverFx);
    sceneManager->audio->UnloadFx(spRecoverFx);
    sceneManager->audio->UnloadFx(reviveFx);

    sceneManager->openItems = false;

    chooseMenu = 0;

    for (int i = 0; i < 2; i++)
    {
        charButtons[i];
        RELEASE(charButtons[i]);
    }

    for (int i = 0; i < 7; i++)
    {
        itemsButtons[i]->UnLoad();
        RELEASE(itemsButtons[i]);
    }

    RELEASE(stepedAnimation);

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
        for (int i = 0; i < 7; i++)
        {
            if (control->id == i)
            {
                if (i == 2 || i == 3)
                {
                    for (int g = 0; g < 2; g++)
                    {
                        sceneManager->entityManager->entities[2].At(g)->data->ItemFunction(
                            &sceneManager->entityManager->entities[0].At(g)->data->infoEntities.info.HP,
                            &sceneManager->entityManager->entities[0].At(g)->data->infoEntities.info.SP,
                            sceneManager->entityManager->entities[0].At(g)->data->infoEntities.info.maxHP,
                            sceneManager->entityManager->entities[0].At(g)->data->infoEntities.info.maxSP);
                    }

                    if (sceneManager->entityManager->quantity[i] != 0) sceneManager->entityManager->quantity[i] -= 1;

                    sceneManager->audio->PlayFx(hpRecoverFx);
                }
                else
                {
                    chooseMenu = 1;
                    choosedItem = i;
                }
            }
        }
        break;
    case 1:

        switch (choosedItem) 
        {
        case 0:
        case 1:
            sceneManager->audio->PlayFx(hpRecoverFx);
            break;

        case 4:
        case 5:
            sceneManager->audio->PlayFx(spRecoverFx);
            break;

        case 6:
            sceneManager->audio->PlayFx(reviveFx);
            break;
        }

        sceneManager->entityManager->entities[2].At(choosedItem)->data->ItemFunction(
            &sceneManager->entityManager->entities[0].At(control->id)->data->infoEntities.info.HP,
            &sceneManager->entityManager->entities[0].At(control->id)->data->infoEntities.info.SP,
            sceneManager->entityManager->entities[0].At(control->id)->data->infoEntities.info.maxHP,
            sceneManager->entityManager->entities[0].At(control->id)->data->infoEntities.info.maxSP);

        if (sceneManager->entityManager->quantity[choosedItem] != 0) sceneManager->entityManager->quantity[choosedItem] -= 1;

        chooseMenu = 0;

        f = -1;

        for (int i = 0; i < 2; i++)
            charButtons[i]->Update(sceneManager->input, buttonChars[f], 0.016f);

        f = 0;

        break;
    default:
        break;
    }

    return true;
}