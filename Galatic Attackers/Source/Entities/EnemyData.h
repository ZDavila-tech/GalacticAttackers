// This class creates all types of enemy prefabs
#ifndef ENEMYDATA_H
#define ENEMYDATA_H

// Contains our global game settings
#include "../GameConfig.h"

// example space game (avoid name collisions)
namespace GA
{
	class EnemyData
	{
	public:
		// Load required entities and/or prefabs into the ECS 
		bool Load(	std::shared_ptr<flecs::world> _game,
					std::weak_ptr<const GameConfig> _gameConfig,
					GW::AUDIO::GAudio _audioEngine,
					std::shared_ptr<Level_Data> _levelData);
		// Unload the entities/prefabs from the ECS
		bool Unload(std::shared_ptr<flecs::world> _game);

	

	};

};

#endif