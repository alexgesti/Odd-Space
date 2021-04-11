#ifndef __SCENEBATTLE_H__
#define __SCENEBATTLE_H__

#include "Scene.h"

//#define MAX_ZOOM 3.0f
//#define MIN_ZOOM 0.3f



class Window;
class Input;
class Render;
class Textures;
class EntityManager;
class SDL_Texture;
class GuiButton;

class Battle : public Scene
{
public:

    // Constructor
    Battle(Window* win, Input* input, Render* render, Textures* tex, EntityManager* entityManager);
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
    void PlayerTurn(float dt);


    // Declare on mouse click event
    bool OnGuiMouseClickEvent(GuiControl* control);

private:

    Window* win;
    Input* input;
    Render* render;
    Textures* tex;
    EntityManager* entityManager;

    struct ButtonsMenu
    {
        GuiButton* buttonAttack;
        GuiButton* buttonGuard;
        GuiButton* buttonSkills;
        GuiButton* buttonRun;
        GuiButton* buttonItem;
        GuiButton* buttonBack;
    } buttonsMenu;

    struct ButtonsSkills
    {
        GuiButton* buttonSkill1;
        GuiButton* buttonSkill2;
        GuiButton* buttonSkill3;
        GuiButton* buttonSkill4;
        GuiButton* buttonSkill5;
        GuiButton* buttonBack;
    } buttonsSkills;

    struct ButtonsEnemy
    {
        GuiButton* buttonEnemy1;
        GuiButton* buttonEnemy2;
        GuiButton* buttonEnemy3;
        GuiButton* buttonEnemy4;
        GuiButton* buttonEnemy5;
        GuiButton* buttonBack;
    } buttonsEnemies;

    bool playerTurn;
    bool chooseAction = true;
    bool chooseEnemy = false;
    bool chooseSkill = false;

    int random;

    int f = 0;
    int c = 0;
    int controllerMenu[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int controllerSkill[2][3] = { {7, 8, 9}, {10, 11, 12} };
    int controllerEnemy[];

};

#endif // __SCENEBATTLE_H__