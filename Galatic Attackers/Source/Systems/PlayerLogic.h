// The player system is responsible for allowing control over the main ship(s)
#ifndef PLAYERLOGIC_H
#define PLAYERLOGIC_H

// Contains our global game settings
#include "../GameConfig.h"
#include "../Components/Physics.h"

// example space game (avoid name collisions)
namespace GA 
{
	class PlayerLogic 
	{
		// shared connection to the main ECS engine
		std::shared_ptr<flecs::world> game;
		// non-ownership handle to configuration settings
		std::weak_ptr<const GameConfig> gameConfig;
		// handle to our running ECS system
		flecs::system playerSystem;
		// permananent handles input systems
		GW::INPUT::GInput immediateInput;
		GW::INPUT::GBufferedInput bufferedInput;
		GW::INPUT::GController controllerInput;
		// permananent handle to audio system
		GW::AUDIO::GAudio audioEngine;
		// key press event cache (saves input events)
		// we choose cache over responder here for better ECS compatibility
		GW::CORE::GEventCache pressEvents;
		// varibables used for charged shot timing
		float chargeStart = 0, chargeEnd = 0, chargeTime;
		// event responder
		GW::CORE::GEventResponder onExplode;
		GW::CORE::GEventResponder lostLife;
		GW::CORE::GEventResponder nextLevel;
		GW::CORE::GEventResponder resetLevel;
		GW::CORE::GEventResponder youWon;
		GW::CORE::GEventResponder youLost;
		std::shared_ptr<Level_Data> levelData;
		std::shared_ptr<int> currentLevel;
		std::shared_ptr<bool> levelChange;
		std::shared_ptr<bool> youWin;
		std::shared_ptr<bool> youLose;
		std::shared_ptr<bool> pause;
		std::shared_ptr<int> enemyCount;
	public:
		// attach the required logic to the ECS 
		bool Init(	std::shared_ptr<flecs::world> _game,
					std::weak_ptr<const GameConfig> _gameConfig,
					GW::INPUT::GInput _immediateInput,
					GW::INPUT::GBufferedInput _bufferedInput,
					GW::INPUT::GController _controllerInput,
					GW::AUDIO::GAudio _audioEngine,
					GW::CORE::GEventGenerator _eventPusher,
					std::shared_ptr<Level_Data> _levelData,
					std::shared_ptr<int> _currentLevel,
					std::shared_ptr<bool> _levelChange, std::shared_ptr<bool> _youWin, std::shared_ptr<bool> _youLose, std::shared_ptr<bool> _pause,
					std::shared_ptr<int> _enemyCount);
		// control if the system is actively running
		bool Activate(bool runSystem);
		// release any resources allocated by the system
		bool Shutdown(); 
	private:
		// how big the input cache can be each frame
		static constexpr unsigned int Max_Frame_Events = 32;
		// helper routines
		bool ProcessInputEvents(flecs::world& stage);
		//bool FireLasers(flecs::world& stage, GA::Position& origin);
		bool FireLasers(flecs::world& stage, GW::MATH::GVECTORF& origin);
	};

};

#endif