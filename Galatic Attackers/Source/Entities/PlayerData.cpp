#include "PlayerData.h"
#include "../Components/Identification.h"
#include "../Components/Visuals.h"
#include "../Components/Physics.h"
#include "../Components/Components.h"
#include "Prefabs.h"

bool GA::PlayerData::Load(  std::shared_ptr<flecs::world> _game, 
                            std::weak_ptr<const GameConfig> _gameConfig)
{
	// Grab init settings for players
	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();
	// color
	float red = (*readCfg).at("Player").at("red").as<float>();
	float green = (*readCfg).at("Player").at("green").as<float>();
	float blue = (*readCfg).at("Player").at("blue").as<float>();

	float red1 = (*readCfg).at("Shield").at("red").as<float>();
	float green1 = (*readCfg).at("Shield").at("green").as<float>();
	float blue1 = (*readCfg).at("Shield").at("blue").as<float>();
	// start position
	float xstart = (*readCfg).at("Player").at("xstart").as<float>();
	float ystart = (*readCfg).at("Player").at("ystart").as<float>();
	float scale = (*readCfg).at("Player").at("scale").as<float>();

	auto e = _game->lookup("Player");
	// if the entity is valid
	if (e.is_valid()) {
		e.add<Player>();
		e.add<Collidable>();
		e.set<Material>({ red, green, blue });
		e.set<Position>({ xstart, ystart });
		e.set<ControllerID>({ 0 });
	}
	auto a = _game->lookup("shield");
	if (a.is_valid()) {
		a.set<Material>({ red1, green1, blue1 });
	}
	return true;
}

bool GA::PlayerData::Unload(std::shared_ptr<flecs::world> _game)
{
	// remove all players
	_game->defer_begin(); // required when removing while iterating!
		_game->each([](flecs::entity e, Player&) {
			e.destruct(); // destroy this entitiy (happens at frame end)
		});
	_game->defer_end(); // required when removing while iterating!

    return true;
}
