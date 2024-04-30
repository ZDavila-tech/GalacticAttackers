#include "PlayerLogic.h"
#include "../Components/Identification.h"
#include "../Components/Physics.h"
#include "../Components/Visuals.h"
#include "../Components/Gameplay.h"
#include "../Components/Components.h"
#include "../Entities/Prefabs.h"
#include "../Events/Playevents.h"

using namespace GW;
using namespace GA; // Example Space Game
using namespace GW::INPUT; // input libs
using namespace GW::AUDIO; // audio libs

// Connects logic to traverse any players and allow a controller to manipulate them
bool GA::PlayerLogic::Init(std::shared_ptr<flecs::world> _game,
	std::weak_ptr<const GameConfig> _gameConfig,
	GW::INPUT::GInput _immediateInput,
	GW::INPUT::GBufferedInput _bufferedInput,
	GW::INPUT::GController _controllerInput,
	GW::AUDIO::GAudio _audioEngine,
	GW::CORE::GEventGenerator _eventPusher,
	std::shared_ptr<Level_Data> _levelData, std::shared_ptr<int> _currentLevel,
	std::shared_ptr<bool> _levelChange, std::shared_ptr<bool> _youWin, std::shared_ptr<bool> _youLose, std::shared_ptr<bool> _pause,
	std::shared_ptr<int> _enemyCount)
{
	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;
	immediateInput = _immediateInput;
	bufferedInput = _bufferedInput;
	controllerInput = _controllerInput;
	audioEngine = _audioEngine;
	levelData = _levelData;
	currentLevel = _currentLevel;
	levelChange = _levelChange;
	youWin = _youWin;
	youLose = _youLose;
	pause = _pause;
	enemyCount = _enemyCount;

	// Init any helper systems required for this task
	std::shared_ptr<const GameConfig> readCfg = gameConfig.lock();
	int width = (*readCfg).at("Window").at("width").as<int>();
	float speed = (*readCfg).at("Player").at("speed").as<float>();
	chargeTime = (*readCfg).at("Player").at("chargeTime").as<float>();

	// add logic for updating players
	playerSystem = game->system<Player, Position, ControllerID>("Player System")
		.iter([this, speed](flecs::iter it, Player*, Position* p, ControllerID* c) {
		if (!(*pause))
		{
			for (auto i : it)
			{
				// left-right movement
				float xaxis = 0, input = 0;

				// Use the controller/keyboard to move the player around the screen			
				if (c[i].index == 0) { // enable keyboard controls for player 1
					immediateInput.GetState(G_KEY_LEFT, input); xaxis -= input;
					immediateInput.GetState(G_KEY_RIGHT, input); xaxis += input;
				}

				// grab left-thumb stick
				controllerInput.GetState(c[i].index, G_LX_AXIS, input); xaxis += input;
				controllerInput.GetState(c[i].index, G_DPAD_LEFT_BTN, input); xaxis -= input;
				controllerInput.GetState(c[i].index, G_DPAD_RIGHT_BTN, input); xaxis += input;
				xaxis = G_LARGER(xaxis, -1);// cap right motion
				xaxis = G_SMALLER(xaxis, 1);// cap left motion

				// apply movement
				if (xaxis != 0)
				{
					p[i].value.x += xaxis * it.delta_time() * speed;

					// limit the player to stay within -1 to +1 NDC
					p[i].value.x = G_LARGER(p[i].value.x, -1.f);
					p[i].value.x = G_SMALLER(p[i].value.x, 1.f);

					ModelTransform* edit = it.entity(i).get_mut<ModelTransform>();

					if (edit->matrix.row4.x > -42 && edit->matrix.row4.x < +42)
					{
						GW::MATH::GMatrix::TranslateLocalF(edit->matrix, GW::MATH::GVECTORF{ -p[i].value.x, p[i].value.y, 0, 1 }, edit->matrix);
						if (edit->matrix.row4.x < -40)
							edit->matrix.row4.x = -40;
						else if (edit->matrix.row4.x > 40)
							edit->matrix.row4.x = 40;

						levelData->levelTransforms[edit->rendererIndex] = edit->matrix;
					}
				}

				//	// fire weapon if they are in a firing state
				if (it.entity(i).has<Firing>())
				{
					ModelTransform* edit = it.entity(i).get_mut<ModelTransform>();
					FireLasers(it.entity(i).world(), edit->matrix.row4);
					it.entity(i).remove<Firing>();
				}

				if ((*enemyCount) <= 0)
				{
					(*youWin) = true;
				}
			}
			// process any cached button events after the loop (happens multiple times per frame)
			ProcessInputEvents(it.world());
		}
			});

	// Create an event cache for when the spacebar/'A' button is pressed
	pressEvents.Create(Max_Frame_Events); // even 32 is probably overkill for one frame

	// register for keyboard and controller events
	bufferedInput.Register(pressEvents);
	controllerInput.Register(pressEvents);

	// create the on explode handler
	onExplode.Create([this](const GW::GEvent& e) {
		GA::PLAY_EVENT event; GA::PLAY_EVENT_DATA eventData;
		if (+e.Read(event, eventData) && event == GA::PLAY_EVENT::ENEMY_DESTROYED) {
			// only in here if event matches
		}
		});


	nextLevel.Create([this](const GW::GEvent& e) {
		GA::PLAY_EVENT event; GA::PLAY_EVENT_DATA eventData;
		if (+e.Read(event, eventData) && event == GA::PLAY_EVENT::NEXT_LEVEL) {
			// only in here if event matches
			GW::SYSTEM::GLog log;
			++(*currentLevel);
			(*levelChange) = true;
		}
		});

	/*resetLevel.Create([this](const GW::GEvent& e) {
		GA::PLAY_EVENT event; GA::PLAY_EVENT_DATA eventData;
		if (+e.Read(event, eventData) && event == GA::PLAY_EVENT::RESET_LEVEL) {
			// only in here if event matches
			GW::SYSTEM::GLog log;
			(*currentLevel) = 1;
			(*levelChange) == true;
			levelData->LoadLevel("../GameLevel_1.txt", "../Models", log);
		}
		});*/

	youWon.Create([this](const GW::GEvent& e) {
		GA::PLAY_EVENT event; GA::PLAY_EVENT_DATA eventData;
		if (+e.Read(event, eventData) && event == GA::PLAY_EVENT::WIN) {
			// only in here if event matches
			*youWin = true;
		}
		});

	youLost.Create([this](const GW::GEvent& e) {
		GA::PLAY_EVENT event; GA::PLAY_EVENT_DATA eventData;
		if (+e.Read(event, eventData) && event == GA::PLAY_EVENT::LOSE) {
			// only in here if event matches
			*youLose = true;
		}
		});

	_eventPusher.Register(onExplode);
	_eventPusher.Register(nextLevel);
	_eventPusher.Register(resetLevel);
	_eventPusher.Register(youWon);
	_eventPusher.Register(youLost);
	return true;
}

// Free any resources used to run this system
bool GA::PlayerLogic::Shutdown()
{
	playerSystem.destruct();
	game.reset();
	gameConfig.reset();

	return true;
}

// Toggle if a system's Logic is actively running
bool GA::PlayerLogic::Activate(bool runSystem)
{
	if (playerSystem.is_alive()) {
		(runSystem) ?
			playerSystem.enable()
			: playerSystem.disable();
		return true;
	}
	return false;
}

bool GA::PlayerLogic::ProcessInputEvents(flecs::world& stage)
{
	// pull any waiting events from the event cache and process them
	GW::GEvent event;
	while (+pressEvents.Pop(event)) {
		bool fire = false;
		GController::Events controller;
		GController::EVENT_DATA c_data;
		GBufferedInput::Events keyboard;
		GBufferedInput::EVENT_DATA k_data;
		// these will only happen when needed
		if (+event.Read(keyboard, k_data)) {
			if (keyboard == GBufferedInput::Events::KEYPRESSED) {
				if (k_data.data == G_KEY_SPACE) {
					fire = true;
					flecs::entity bullet;
					RetreivePrefab("Lazer Bullet", bullet);
					GW::AUDIO::GSound shoot = *bullet.get<GW::AUDIO::GSound>();
					shoot.Play();
				}
			}
		}
		else if (+event.Read(controller, c_data)) {
			if (controller == GController::Events::CONTROLLERBUTTONVALUECHANGED) {
				if (c_data.inputValue > 0 && c_data.inputCode == G_SOUTH_BTN)
					fire = true;
			}
		}
		if (fire) {
			// grab player one and set them to a firing state
			stage.entity("Player").add<Firing>();
		}
	}
	return true;
}

// play sound and launch two laser rounds
bool GA::PlayerLogic::FireLasers(flecs::world& stage, GW::MATH::GVECTORF& origin)
{
	// Grab the prefab for a laser round
	flecs::entity bullet;
	RetreivePrefab("Lazer Bullet", bullet);

	auto laserLeft = stage.entity().is_a(bullet)
		.set<Position>({ origin.x, origin.y });

	ModelTransform* bulletT = bullet.get_mut<ModelTransform>();
	bulletT->matrix.row4.x = origin.x;

	return true;
}