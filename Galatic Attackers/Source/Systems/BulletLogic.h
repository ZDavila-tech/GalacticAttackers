// The Bullet system is responsible for inflicting damage and cleaning up bullets
#ifndef BULLETLOGIC_H
#define BULLETLOGIC_H

// Contains our global game settings
#include "../GameConfig.h"
#include "../Entities/BulletData.h"

// example space game (avoid name collisions)
namespace GA
{
	class BulletLogic
	{
		// shared connection to the main ECS engine
		std::shared_ptr<flecs::world> game;
		// non-ownership handle to configuration settings
		std::weak_ptr<const GameConfig> gameConfig;
		std::shared_ptr<Level_Data> levelData;
	public:
		// attach the required logic to the ECS 
		bool Init(std::shared_ptr<flecs::world> _game,
			std::weak_ptr<const GameConfig> _gameConfig,
			std::shared_ptr<Level_Data> _levelData);
		// control if the system is actively running
		bool Activate(bool runSystem);
		// release any resources allocated by the system
		bool Shutdown();
	};

};

#endif