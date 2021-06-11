#include "NameSelector.h"

#include "SceneManager.h"


// Constructor
NameSelector::NameSelector(SceneManager* sceneManager) : Scene()
{
    this->sceneManager = sceneManager;
}
// Destructor
NameSelector::~NameSelector()
{
    Unload();
}



bool NameSelector::Load()
{
    bg = sceneManager->tex->Load("sprites/ui/name_selector.png");

    sceneManager->audio->PlayMusic("audio/music/menu_music.ogg", 2);

    // Buttons
    buttons.buttonA = new GuiButton(1, { 75, 333, 448, 128 }, "A", sceneManager->audio);
    buttons.buttonA->SetObserver(this);
    buttons.buttonB = new GuiButton(2, { 145, 333, 448, 128 }, "B", sceneManager->audio);
    buttons.buttonB->SetObserver(this);            
    buttons.buttonC = new GuiButton(3, { 215, 333, 448, 128 }, "C", sceneManager->audio);
    buttons.buttonC->SetObserver(this);            
    buttons.buttonD = new GuiButton(4, { 285, 333, 448, 128 }, "D", sceneManager->audio);
    buttons.buttonD->SetObserver(this);            
    buttons.buttonE = new GuiButton(5, { 355, 333, 448, 128 }, "E", sceneManager->audio);
    buttons.buttonE->SetObserver(this);            
    buttons.buttonF = new GuiButton(6, { 425, 333, 448, 128 }, "F", sceneManager->audio);
    buttons.buttonF->SetObserver(this);            
    buttons.buttonG = new GuiButton(7, { 495, 333, 448, 128 }, "G", sceneManager->audio);
    buttons.buttonG->SetObserver(this);            
    buttons.buttonH = new GuiButton(8, { 565, 333, 448, 128 }, "H", sceneManager->audio);
    buttons.buttonH->SetObserver(this);            
    buttons.buttonI = new GuiButton(9, { 635, 333, 448, 128 }, "I", sceneManager->audio);
    buttons.buttonI->SetObserver(this);
    buttons.buttonJ = new GuiButton(10, { 705, 333, 448, 128 }, "J", sceneManager->audio);
    buttons.buttonJ->SetObserver(this);
    buttons.buttonK = new GuiButton(11, { 75, 433, 448, 128 }, "K", sceneManager->audio);
    buttons.buttonK->SetObserver(this);
    buttons.buttonL = new GuiButton(12, { 145, 433, 448, 128 }, "L", sceneManager->audio);
    buttons.buttonL->SetObserver(this);
    buttons.buttonM = new GuiButton(13, { 215, 433, 448, 128 }, "M", sceneManager->audio);
    buttons.buttonM->SetObserver(this);
    buttons.buttonN = new GuiButton(14, { 285, 433, 448, 128 }, "N", sceneManager->audio);
    buttons.buttonN->SetObserver(this);
    buttons.buttonO = new GuiButton(15, { 355, 433, 448, 128 }, "O", sceneManager->audio);
    buttons.buttonO->SetObserver(this);
    buttons.buttonP = new GuiButton(16, { 425, 433, 448, 128 }, "P", sceneManager->audio);
    buttons.buttonP->SetObserver(this);
    buttons.buttonQ = new GuiButton(17, { 495, 433, 448, 128 }, "Q", sceneManager->audio);
    buttons.buttonQ->SetObserver(this);
    buttons.buttonR = new GuiButton(18, { 565, 433, 448, 128 }, "R", sceneManager->audio);
    buttons.buttonR->SetObserver(this);
    buttons.buttonS = new GuiButton(19, { 635, 433, 448, 128 }, "S", sceneManager->audio);
    buttons.buttonS->SetObserver(this);
    buttons.buttonT = new GuiButton(20, { 705, 433, 448, 128 }, "T", sceneManager->audio);
    buttons.buttonT->SetObserver(this);
    buttons.buttonU = new GuiButton(21, { 75, 533, 448, 128 }, "U", sceneManager->audio);
    buttons.buttonU->SetObserver(this);
    buttons.buttonV = new GuiButton(22, { 145, 533, 448, 128 }, "V", sceneManager->audio);
    buttons.buttonV->SetObserver(this);
    buttons.buttonW = new GuiButton(23, { 215, 533, 448, 128 }, "W", sceneManager->audio);
    buttons.buttonW->SetObserver(this);
    buttons.buttonX = new GuiButton(24, { 285, 533, 448, 128 }, "X", sceneManager->audio);
    buttons.buttonX->SetObserver(this);
    buttons.buttonY = new GuiButton(25, { 355, 533, 448, 128 }, "Y", sceneManager->audio);
    buttons.buttonY->SetObserver(this);
    buttons.buttonZ = new GuiButton(26, { 425, 533, 448, 128 }, "Z", sceneManager->audio);
    buttons.buttonZ->SetObserver(this);
    buttons.buttonBack = new GuiButton(27, { 530, 547, 448, 100 }, "BACK", sceneManager->audio);
    buttons.buttonBack->SetObserver(this);
    buttons.buttonDone = new GuiButton(28, { 670, 547, 448, 100 }, "DONE", sceneManager->audio);
    buttons.buttonDone->SetObserver(this);
    return false;
}

bool NameSelector::Update(float dt)
{
    bool ret = false;

    if (name.length() == 1)
    {
        char letter = name.at(0);
        letter = toupper(letter);
        name.clear();
        name.push_back(letter);
    }

    /*if (titlePosX > 500.0f)
    {
        titlePosX = EaseBounceOut(currentTime, (float)(1280 + 718), 500.0f - (float)(1280 + 718), 3);
        currentTime += dt;
    }*/

    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
        controllerMenu[f][c++];

    if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
        controllerMenu[f][c--];

    if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
    {
        controllerMenu[f++][c];
        // If going from 1st to 3rd or 2nd to 3rd row
        if (f == 2 && c > 7) c = 7;
    }

    if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        controllerMenu[f--][c];

    //Establecer limites fila/columna botones
    if (f == 2 && c > 7) c = 0;
    if (f == 2 && c < 0) c = 7;
    if (f > 2) f = 0;
    if (f < 0) f = 2;
    if (c > 9) c = 0;
    if (c < 0) c = 9;

    buttons.buttonA->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonB->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonC->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonD->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonE->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonF->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonG->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonH->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonI->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonJ->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonK->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonL->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonM->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonN->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonO->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonP->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonQ->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonR->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonS->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonT->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonU->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonV->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonW->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonX->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonY->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonZ->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonBack->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonDone->Update(sceneManager->input, controllerMenu[f][c], dt);

    return ret;
}

bool NameSelector::Draw()
{
    sceneManager->render->DrawTexture(bg, 0, 100, NULL);

    for (int i = 0; i < name.length(); i++)
    {
        string letter;
        letter.push_back(name.at(i));
        sceneManager->render->DrawText(sceneManager->font, letter.c_str(), 100 + (i * 128), 205, 70, 0, {255, 255, 255, 255});
    }

    buttons.buttonA->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonB->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonC->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonD->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonE->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonF->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonG->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonH->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonI->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonJ->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonK->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonL->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonM->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonN->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonO->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonP->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonQ->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonR->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonS->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonT->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonU->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonV->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonW->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonX->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonY->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonZ->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonBack->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonDone->Draw(sceneManager->render, sceneManager->font);

    return false;
}

bool NameSelector::Unload()
{
    // Delete buttons and textures
    sceneManager->tex->UnLoad(bg);

    if (sceneManager->openOptions) sceneManager->options->Unload();

    buttons.buttonA->UnLoad();
    RELEASE(buttons.buttonA);
    buttons.buttonB->UnLoad();
    RELEASE(buttons.buttonB);
    buttons.buttonC->UnLoad();
    RELEASE(buttons.buttonC);
    buttons.buttonD->UnLoad();
    RELEASE(buttons.buttonD);
    buttons.buttonE->UnLoad();
    RELEASE(buttons.buttonE);
    buttons.buttonF->UnLoad();
    RELEASE(buttons.buttonF);
    buttons.buttonG->UnLoad();
    RELEASE(buttons.buttonG);
    buttons.buttonH->UnLoad();
    RELEASE(buttons.buttonH);
    buttons.buttonI->UnLoad();
    RELEASE(buttons.buttonI);
    buttons.buttonJ->UnLoad();
    RELEASE(buttons.buttonJ);
    buttons.buttonK->UnLoad();
    RELEASE(buttons.buttonK);
    buttons.buttonL->UnLoad();
    RELEASE(buttons.buttonL);
    buttons.buttonM->UnLoad();
    RELEASE(buttons.buttonM);
    buttons.buttonN->UnLoad();
    RELEASE(buttons.buttonN);
    buttons.buttonO->UnLoad();
    RELEASE(buttons.buttonO);
    buttons.buttonP->UnLoad();
    RELEASE(buttons.buttonP);
    buttons.buttonQ->UnLoad();
    RELEASE(buttons.buttonQ);
    buttons.buttonR->UnLoad();
    RELEASE(buttons.buttonR);
    buttons.buttonS->UnLoad();
    RELEASE(buttons.buttonS);
    buttons.buttonT->UnLoad();
    RELEASE(buttons.buttonT);
    buttons.buttonU->UnLoad();
    RELEASE(buttons.buttonU);
    buttons.buttonV->UnLoad();
    RELEASE(buttons.buttonV);
    buttons.buttonW->UnLoad();
    RELEASE(buttons.buttonW);
    buttons.buttonX->UnLoad();
    RELEASE(buttons.buttonX);
    buttons.buttonY->UnLoad();
    RELEASE(buttons.buttonY);
    buttons.buttonZ->UnLoad();
    RELEASE(buttons.buttonZ);
    buttons.buttonBack->UnLoad();
    RELEASE(buttons.buttonBack);
    buttons.buttonDone->UnLoad();
    RELEASE(buttons.buttonDone);

    return false;
}



//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool NameSelector::OnGuiMouseClickEvent(GuiControl* control)
{
    switch (control->id)
    {
    case 1:
        if (name.length() < 9)
            name.push_back('a');
        break;
    case 2:
        if (name.length() < 9)
            name.push_back('b');
        break;
    case 3:
        if (name.length() < 9)
            name.push_back('c');
        break;
    case 4:
        if (name.length() < 9)
            name.push_back('d');
        break;
    case 5:
        if (name.length() < 9)
            name.push_back('e');
        break;
    case 6:
        if (name.length() < 9)
            name.push_back('f');
        break;
    case 7:
        if (name.length() < 9)
            name.push_back('g');
        break;
    case 8:
        if (name.length() < 9)
            name.push_back('h');
        break;
    case 9:
        if (name.length() < 9)
            name.push_back('i');
        break;
    case 10:
        if (name.length() < 9)
            name.push_back('j');
        break;
    case 11:
        if (name.length() < 9)
            name.push_back('k');
        break;
    case 12:
        if (name.length() < 9)
            name.push_back('l');
        break;
    case 13:
        if (name.length() < 9)
            name.push_back('m');
        break;
    case 14:
        if (name.length() < 9)
            name.push_back('n');
        break;
    case 15:
        if (name.length() < 9)
            name.push_back('o');
        break;
    case 16:
        if (name.length() < 9)
            name.push_back('p');
        break;
    case 17:
        if (name.length() < 9)
            name.push_back('q');
        break;
    case 18:
        if (name.length() < 9)
            name.push_back('r');
        break;
    case 19:
        if (name.length() < 9)
            name.push_back('s');
        break;
    case 20:
        if (name.length() < 9)
            name.push_back('t');
        break;
    case 21:
        if (name.length() < 9)
            name.push_back('u');
        break;
    case 22:
        if (name.length() < 9)
            name.push_back('v');
        break;
    case 23:
        if (name.length() < 9)
            name.push_back('w');
        break;
    case 24:
        if (name.length() < 9)
            name.push_back('x');
        break;
    case 25:
        if (name.length() < 9)
            name.push_back('y');
        break;
    case 26:
        if (name.length() < 9)
            name.push_back('z');
        break;
    case 27:
        if (name.length() > 0)
            name.pop_back();
        break;
    case 28:
        sceneManager->dialogueSystem->playerName = name;
        sceneManager->dialogueSystem->LoadDialogue("dialogues.xml");
        sceneManager->dialogueSystem->currentNode = sceneManager->dialogueSystem->dialogueTrees[sceneManager->dialogueSystem->id]->dialogueNodes[0];
        TransitionToScene(SceneType::EXTERIOR);
        break;
    default: break;
    }
    return true;
}