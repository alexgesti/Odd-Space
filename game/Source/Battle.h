#ifndef __SCENEBATTLE_H__
#define __SCENEBATTLE_H__

#include "Scene.h"

//#define MAX_ZOOM 3.0f
//#define MIN_ZOOM 0.3f



class Window;
class Input;
class Render;
class Textures;
class SDL_Texture;
class GuiButton;

class Battle : public Scene
{
public:

    // Constructor
    Battle(Window* win, Input* input, Render* render, Textures* tex);
    // Destructor
    virtual ~Battle();


    // Load this scene
    bool Load();

    // Update this scene
    bool Update(float dt);

    // Draw this scene
    bool Draw();

    // Unload this scene
    bool Unload();


    //Damage Calculator
    int DamageCalculator();


    // Declare on mouse click event
    bool OnGuiMouseClickEvent(GuiControl* control);

private:

    Window* win;
    Input* input;
    Render* render;
    Textures* tex;

    GuiButton* buttonAttack;
    GuiButton* buttonGuard;
    GuiButton* buttonSkills;
    GuiButton* buttonRun;
    GuiButton* buttonItem;
    GuiButton* buttonBack1;

    SDL_Texture* cantinaBattle;

    bool playerTurn;
    bool chooseEnemy;
    bool chooseSkill;
    int f = 0;
    int c = 0;
    int controllerMenuSupport[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int controllerSkillSupport[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int controllerEnemySupport[2][3] = { {1, 2, 3}, {4, 5, 6} };

};

#endif // __SCENEBATTLE_H__