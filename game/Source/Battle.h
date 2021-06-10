#ifndef __SCENEBATTLE_H__
#define __SCENEBATTLE_H__

#include "Scene.h"
#include "Font.h"
#include "Animation.h"
#include "ParticleSystem.h"

//#define MAX_ZOOM 3.0f
//#define MIN_ZOOM 0.3f

class Map;

class SceneManager;

class GuiButton;

class Emitter;

class Battle : public Scene
{
public:

    // Constructor
    Battle(SceneManager* sceneManager);
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

    //Menu
    void PlayerMenu(float dt);

    // Damage dealt by Player
    void DamagePlayer(int player);

    //Run
    void BattleEscaped();

    //Player Turns
    void ChangeTurns();

    //Damage dealt by enemy
    void DamageEnemy(int enemy);

    // Declare on mouse click event
    bool OnGuiMouseClickEvent(GuiControl* control);

private:

    Map* map;

    SceneManager* sceneManager;

    List<Emitter*> smokes;
    List<Emitter*> heals;
    List<Emitter*> blesses;

    SDL_Texture* UI;
    SDL_Texture* VorL;

    struct Buttons
    {
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
            GuiButton* buttonSkill[5];
            GuiButton* buttonBack;
        } buttonsSkills;

        struct ButtonsEnemy
        {
            GuiButton* buttonEnemy[5];
            GuiButton* buttonBack;
        } buttonsEnemies;
    } buttons;

    struct Fx
    {
        int loseFx = 0;
        int winFx = 0;
        int strikeFx = 0;
        int hurtFx = 0;
        int deathFx = 0;
        int runFx = 0;
        int guardFx = 0;
        int debuffFx = 0;
        bool playOnce = false;
    }fx;

    int totalEnemies;
    int selectedEnemies[2];
    int selectedCharacters[5];
    int characterTurn;

    float preparetochange = 0;
    int timerequired;
    bool win = false;
    bool lose = false;

    bool playerMenu = true;
    bool animation = false;
    int actualCharacterAnim;
    int actualEnemyAnim;

    //UI Controller
    int chooseMenu;
    int f;
    int c;
    int controllerMenu[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int controllerSkill[2][3] = { {7, 8, 9}, {10, 11, 12} };
    int controllerEnemy[6];
};

#endif // __SCENEBATTLE_H__