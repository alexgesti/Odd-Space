#include "SceneManager.h"

#include "Logo.h"
#include "Title.h"
#include "NameSelector.h"
#include "Cantina.h"
#include "Wc.h"
#include "Battle.h"
#include "Exterior.h"
#include "PauseMenu.h"
#include "OptionsMenu.h"
#include "ItemsMenu.h"
#include "DebugMenu.h"
#include "DungeonExt.h"
#include "DungeonF1.h"
#include "DungeonF2.h"
#include "EndDemo.h"

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL.h"

#define FADEOUT_TRANSITION_SPEED	2.0f
#define FADEIN_TRANSITION_SPEED		2.0f

SceneManager::SceneManager(Input* input, Render* render, Textures* tex, Window* win, EntityManager* entityManager, Audio* audio, DialogueSystem* dialogueSystem, ParticleSystem* pSystem) : Module()
{
	name.Create("scenemanager");

	onTransition = false;
	fadeOutCompleted = false;
	transitionAlpha = 0.0f;
	volumeMusic = 128;
	volumeFx = 128;

	this->input = input;
	this->render = render;
	this->tex = tex;
	this->win = win;
	this->entityManager = entityManager;
	this->dialogueSystem = dialogueSystem;
	this->audio = audio;
	this->particleSystem = pSystem;

	this->collision = &entityManager->collision;
}

// Destructor
SceneManager::~SceneManager()
{}

// Called before render is available
bool SceneManager::Awake()
{
	LOG("Loading Scene manager");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneManager::Start()
{
	font = new Font("typo/Adore64.xml", tex);
	speak = new Speak(audio, render, font, input, tex);
	dialogueSystem->speak = speak;
	xMark = tex->Load("sprites/ui/ui_xmarkanim.png");

	animXMark->loop = false;
	animXMark->speed = 0.45f;
	for (int i = 0; i < 5; ++i)
		animXMark->PushBack({ 20 * i, 0, 20, 20 });

	doorClose = audio->LoadFx("audio/fx/world_door_close.wav");
	doorOpen = audio->LoadFx("audio/fx/world_door_open.wav");
	battleEncounter = audio->LoadFx("audio/fx/battle_sp_recover.wav");
	stairsFx = audio->LoadFx("audio/fx/world_stairs.wav");
	xMarkFX = audio->LoadFx("audio/fx/xmark_fx.wav");
	unPauseFx = audio->LoadFx("audio/fx/unpause_ui.wav");

	previousScene = new SceneType;
	entityManager->previousScene = previousScene;
	//current = new Logo(this);
	current = new Title(this);
	//current = new Battle(win, input, render, tex, entityManager, font, speak);
	//current = new Cantina(this);
	//current = new Wc(this);
	//current = new Exterior(this);
	//current = new DungeonF1(this);
	//current = new DungeonF2(this);
	//current = new EndDemo(this);
	currentscenetype = SceneType::TITLE;

	current->Load();

	debug = new Debug(this);
	debug->Load();
	options = new OptionsMenu(this);
	items = new ItemsMenu(this);
	pause = new PauseMenu(this);
	pause->Load();

	dialogueSystem->speak = speak;
	dialogueSystem->GetObserver(current);
	next = nullptr;

	questSystem = new QuestSystem(this);
	Quest quest;
	quest.interactionName = "captain";
	quest.text = "Talk with the captain";
	questSystem->ChangeMainQuest(quest);

	return true;
}

// Called each loop iteration
bool SceneManager::PreUpdate()
{
	/*
	// L12b: Debug pathfing
	static iPoint origin;
	static bool originSelected = false;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);

	if(app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(originSelected == true)
		{
			app->pathFinding->CreatePath(origin, p);
			originSelected = false;
		}
		else
		{
			origin = p;
			originSelected = true;
		}
	}
	*/

	return true;
}

// Called each loop iteration
bool SceneManager::Update(float dt)
{
	GamePad& pad = input->pads[0];

	if (!onTransition)
	{
		if (beGod)
		{
			entityManager->CreateEntity(EntityType::HERO)->infoEntities.info.HP = entityManager->CreateEntity(EntityType::HERO)->infoEntities.info.maxHP;
			entityManager->CreateEntity(EntityType::CAPTAIN)->infoEntities.info.HP = entityManager->CreateEntity(EntityType::CAPTAIN)->infoEntities.info.maxHP;
		}

		if ((input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_GUIDE) == KEY_DOWN) &&
			(currentscenetype != SceneType::LOGO && currentscenetype != SceneType::TITLE))
		{
			isDebug = !isDebug;
			if(isDebug) entityManager->CreateEntity(EntityType::HERO)->transitioning = true;
			else entityManager->CreateEntity(EntityType::HERO)->transitioning = false;
		}

		if ((input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN) &&
			(currentscenetype != SceneType::BATTLE && currentscenetype != SceneType::LOGO && currentscenetype != SceneType::TITLE && !isDebug))
		{
			isPause = !isPause;
			if (!isPause)
			{
				if (openItems) items->Unload();
				if (openOptions) options->Unload();
				entityManager->CreateEntity(EntityType::HERO)->transitioning = false;
				audio->PlayFx(unPauseFx);
				alphaP = 1.0f;
			}
			else entityManager->CreateEntity(EntityType::HERO)->transitioning = true;
			
		}

		if (isDebug) debug->Update(dt);
		else if (isPause) pause->Update(dt);
		else
		{
			if (pauseMusicFaded && exitToMainMenu == false)
			{
				audio->FadeInMusic(0.5f, "audio/music/exterior_music.ogg");
				pauseMusicFaded = false;
			}

			current->Update(dt);
		}

		//Create quests
		if(dialogueSystem->createKillQuest)
		{
			Quest quest;
			quest.type = QuestType::KILL;
			quest.amount = entityManager->enemyKills + (rand() %3) + 1;
			std::string amount = std::to_string(quest.amount);
			quest.text.Create(("Kill " + amount + " enemies").c_str());
			questSystem->AddSideQuest(quest);
			dialogueSystem->createKillQuest = false;
		}

		if (dialogueSystem->createCollectQuest)
		{
			Quest quest;
			quest.type = QuestType::COLLECT;
			quest.amount = 3;
			std::string amount = std::to_string(quest.amount);
			quest.text.Create(("Collect " + amount + " items").c_str());
			questSystem->AddSideQuest(quest);
			dialogueSystem->createCollectQuest = false;
		}
	}

	else
	{
		if (!fadeOutCompleted)
		{
			if (current->nextScene == SceneType::BATTLE)
			{
				if (!oneTimeBattleMusic)
				{
					altura = -720;
					transitionAlpha = 1;
					audio->PlayFx(battleEncounter);
					audio->FadeOutMusic(0.1f, "audio/music/exterior_music.ogg");
					oneTimeBattleMusic = !oneTimeBattleMusic;
				}
	
				altura += 700 * dt;
				
				if (altura >= 0)
				{
					altura = 0;
				}
			}
			else if (current->nextScene != SceneType::BATTLE) transitionAlpha += (FADEOUT_TRANSITION_SPEED * dt);

			// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
			// For that reason we compare against 1.01f, to avoid last frame loading stop
			if (transitionAlpha > 1.01f || altura >= 0)
			{
				transitionAlpha = 1.0f;

				currentscenetype = current->nextScene;
				current->Unload();	// Unload current screen
				next->Load();	// Load next screen

				RELEASE(current);	// Free current pointer
				current = next;		// Assign next pointer
				next = nullptr;

				dialogueSystem->GetObserver(current);

				// Activate fade out effect to next loaded screen
				fadeOutCompleted = true;
			}
		}

		else // Transition fade out logic
		{
			transitionAlpha -= (FADEIN_TRANSITION_SPEED * dt);

			if (transitionAlpha < -0.01f)
			{
				transitionAlpha = 0.0f;
				fadeOutCompleted = false;
				onTransition = false;
				//oneTime = false;
				oneTimeBattleMusic = false;
				//counterTimeDoit = 0;
				transitionScreen = 0;
				if(!isDebug) entityManager->CreateEntity(EntityType::HERO)->transitioning = false;
			}
		}
	}

	// Draw current scene
	current->Draw();
	if (toDrawX)
	{
		if (xMarkFXFlag)
		{
			audio->PlayFx(xMarkFX);
			xMarkFXFlag = false;
			animXMark->Reset();
		}
		animXMark->Update();
		SDL_Rect rect = animXMark->GetCurrentFrame();
		render->DrawTexture(xMark, entityManager->CreateEntity(EntityType::HERO)->position.x + 6, entityManager->CreateEntity(EntityType::HERO)->position.y - 85, &rect);
	}
	else
	{
		xMarkFXFlag = true;
	}

	if (dialogueSystem->inConversation)
	{
		if (!entityManager->CreateEntity(EntityType::HERO)->inConversation) entityManager->CreateEntity(EntityType::HERO)->inConversation = true;
		speak->Update(dt);
		dialogueSystem->Draw();
	}
	else if(entityManager->CreateEntity(EntityType::HERO)->inConversation) entityManager->CreateEntity(EntityType::HERO)->inConversation = false;

	// Draw full screen rectangle in front of everything
	if (onTransition) render->DrawRectangle({ -render->camera.x, -render->camera.y + altura, 1280, 720 }, 0, 0, 0, (unsigned char)(255.0f * transitionAlpha));

	if (isPause) pause->Draw();

	if (isDebug) debug->Draw();

	// L12b: Debug pathfinding
	/*
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	const 
	<iPoint>* path = app->pathFinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		app->render->DrawTexture(debugTex, pos.x, pos.y);
	}
	*/

	if (isDebug && debug->transitionRequired)
	{
		current->transitionRequired = true;
		current->nextScene = debug->nextScene;

		debug->transitionRequired = false;
	}
	if (current->transitionRequired)
	{
		entityManager->CreateEntity(EntityType::HERO)->transitioning = true;
		onTransition = true;
		fadeOutCompleted = false;
		transitionAlpha = 0.0f;

		ListItem<Quest>* temp = questSystem->sideQuests.start;

		switch (current->nextScene)
		{
		case SceneType::LOGO: next = new Logo(this); break;
		case SceneType::TITLE: next = new Title(this); break;
		case SceneType::NAME_SELECTOR: next = new NameSelector(this); break;
		case SceneType::CANTINA: next = new Cantina(this); break;
		case SceneType::WC: next = new Wc(this); break;
		case SceneType::EXTERIOR: next = new Exterior(this); break;
		case SceneType::BATTLE:
			next = new Battle(this);
			while (temp != NULL)
			{
				if(temp->data.type == QuestType::COLLECT)
					questSystem->CheckSideQuests(temp->data, 3);
				else if (temp->data.type == QuestType::COLLECT)
					questSystem->CheckSideQuests(temp->data, entityManager->enemyKills);
				temp = temp->next;
			}
			break;
		case SceneType::DUNGEON_EXT: next = new DungeonExt(this); break;
		case SceneType::DUNGEON_F1: next = new DungeonF1(this); break;
		case SceneType::DUNGEON_F2: next = new DungeonF2(this); break;
		case SceneType::ENDDEMO: next = new EndDemo(this); break;
		default: break;
		}
		current->transitionRequired = false;
	}

	return true;
}

// Called each loop iteration
bool SceneManager::PostUpdate()
{
	return gameIsWorking;
}

// Called before quitting
bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	if (current != nullptr) current->Unload();

	if (openOptions) options->Unload();
	if (openOptions) items->Unload();
	pause->Unload();
	RELEASE(pause);
	debug->Unload();
	RELEASE(debug);

	audio->UnloadFx(doorClose);
	audio->UnloadFx(doorOpen);
	audio->UnloadFx(battleEncounter);
	audio->UnloadFx(stairsFx);
	audio->UnloadFx(xMarkFX);
	audio->UnloadFx(unPauseFx);

	tex->UnLoad(xMark);

	return true;
}


void SceneManager::ResetGame()
{
	int id = entityManager->entities->Find(entityManager->player);
	entityManager->DestroyPlayer();
	entityManager->CreateEntity(EntityType::HERO);
	entityManager->CreateEntity(EntityType::CAPTAIN);
	string dialogFile = "save_completed_dialogues.xml";
	remove(dialogFile.c_str());
	initialTextTextSaid = false;
	dialogueSystem->completedDialoguesId.Clear();
	dialogueSystem->playerName.clear();
}