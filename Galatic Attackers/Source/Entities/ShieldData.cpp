#include "ShieldData.h"
#include "../Components/Identification.h"
#include "../Components/Visuals.h"
#include "../Components/Physics.h"
#include "Prefabs.h"
#include "../Components/Gameplay.h"

bool GA::ShieldData::Load(std::shared_ptr<flecs::world> _game,
	std::weak_ptr<const GameConfig> _gameConfig,
	GW::AUDIO::GAudio _audioEngine)
{
	// Grab init settings for players
	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();

	// Create prefab for lazer weapon
	// color
	float red = (*readCfg).at("Shield").at("red").as<float>();
	float green = (*readCfg).at("Shield").at("green").as<float>();
	float blue = (*readCfg).at("Shield").at("blue").as<float>();
	// other attributes
	float speed = (*readCfg).at("Shield").at("speed").as<float>();
	float xscale = (*readCfg).at("Shield").at("xscale").as<float>();
	float yscale = (*readCfg).at("Shield").at("yscale").as<float>();
	int dmg = (*readCfg).at("Shield").at("damage").as<int>();
	int pcount = (*readCfg).at("Shield").at("projectiles").as<int>();
	float frate = (*readCfg).at("Shield").at("firerate").as<float>();
	std::string fireFX = (*readCfg).at("Shield").at("fireFX").as<std::string>();
	// default projectile scale
	GW::MATH2D::GMATRIX2F world;
	GW::MATH2D::GMatrix2D::Scale2F(GW::MATH2D::GIdentityMatrix2F,
		GW::MATH2D::GVECTOR2F{ xscale, yscale }, world);
	// Load sound effect used by this bullet prefab
	GW::AUDIO::GSound shoot;
	shoot.Create(fireFX.c_str(), _audioEngine, 0.15f); // we need a global music & sfx volumes
	// add prefab to ECS
	auto shieldPrefab = _game->prefab("Crystal1")
		// .set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		.set<Acceleration>({ 0, 0 })
		.set<Velocity>({ 0, speed })
		.set<GW::AUDIO::GSound>(shoot.Relinquish())
		// .override<> ensures a component is unique to each entity created from a prefab 
		.set_override<Damage>({ dmg })
		.override<Position>()
		.override<Shield>(); // Tag this prefab as a bullet (for queries/systems)

	// register this prefab by name so other systems can use it
	RegisterPrefab("Shield", shieldPrefab);

	return true;
}

bool GA::ShieldData::Unload(std::shared_ptr<flecs::world> _game)
{
	// remove all bullets and their prefabs
	_game->defer_begin(); // required when removing while iterating!
	_game->each([](flecs::entity e, Shield&) {
		e.destruct(); // destroy this entitiy (happens at frame end)
		});
	_game->defer_end(); // required when removing while iterating!

	// unregister this prefab by name
	UnregisterPrefab("Shield");

	return true;
}