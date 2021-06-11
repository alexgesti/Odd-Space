#ifndef __NAMESELCTOR_H__
#define __NAMESELCTOR_H__

#include "Scene.h"
#include "GuiButton.h"

class SceneManager;
class SDL_Texture;

class NameSelector : public Scene
{
public:

    // Constructor
    NameSelector(SceneManager* sceneManager);

    // Destructor
    virtual ~NameSelector();

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

    SceneManager* sceneManager;

    SDL_Texture* bg;

    struct Buttons
    {
        GuiButton* buttonA;
        GuiButton* buttonB;
        GuiButton* buttonC;
        GuiButton* buttonD;
        GuiButton* buttonE;
        GuiButton* buttonF;
        GuiButton* buttonG;
        GuiButton* buttonH;
        GuiButton* buttonI;
        GuiButton* buttonJ;
        GuiButton* buttonK;
        GuiButton* buttonL;
        GuiButton* buttonM;
        GuiButton* buttonN;
        GuiButton* buttonO;
        GuiButton* buttonP;
        GuiButton* buttonQ;
        GuiButton* buttonR;
        GuiButton* buttonS;
        GuiButton* buttonT;
        GuiButton* buttonU;
        GuiButton* buttonV;
        GuiButton* buttonW;
        GuiButton* buttonX;
        GuiButton* buttonY;
        GuiButton* buttonZ;
        GuiButton* buttonBack;
        GuiButton* buttonDone;
    }buttons;

    int f = 0;
    int c = 0;
    int controllerMenu[3][10] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }, { 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } };

    std::string name;
};

#endif // __NAMESELCTOR_H__