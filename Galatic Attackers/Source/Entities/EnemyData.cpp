#include "EnemyData.h"
#include "../Components/Identification.h"
#include "../Components/visuals.h"
#include "../Components/Physics.h"
#include "../Entities/Prefabs.h"
#include "../Components/Gameplay.h"
#include "../Components/Components.h"

bool GA::EnemyData::Load(std::shared_ptr<flecs::world> _game,
	std::weak_ptr<const GameConfig> _gameConfig,
	GW::AUDIO::GAudio _audioEngine,
	std::shared_ptr<Level_Data> _levelData)
{
	// Grab init settings for players
	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();

	// Create prefab for lazer weapon
	// color
	float red = (*readCfg).at("Enemy1").at("red").as<float>();
	float green = (*readCfg).at("Enemy1").at("green").as<float>();
	float blue = (*readCfg).at("Enemy1").at("blue").as<float>();
	// other attributes
	float xscale = (*readCfg).at("Enemy1").at("xscale").as<float>();
	float yscale = (*readCfg).at("Enemy1").at("yscale").as<float>();
	float angle = (*readCfg).at("Enemy1").at("angle").as<float>();
	int health = (*readCfg).at("Enemy1").at("health").as<int>();

	// default projectile orientation & scale
	GW::MATH2D::GMATRIX2F world;
	GW::MATH2D::GMatrix2D::Rotate2F(GW::MATH2D::GIdentityMatrix2F,
		G_DEGREE_TO_RADIAN_F(angle), world);
	GW::MATH2D::GMatrix2D::Scale2F(world,
		GW::MATH2D::GVECTOR2F{ xscale, yscale }, world);

	// add prefab to ECS
	auto enemyPrefab = _game->prefab("Spaceship5")
		 //.set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		.set<ModelBoundary*>(_game->prefab("Spaceship5").get_mut<ModelBoundary>())
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with

	auto enemyPrefab1 = _game->prefab("Spaceship5.001")
		// .set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		//.override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with
	auto enemyPrefab2 = _game->prefab("Spaceship5.002")
		// .set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with

	auto enemyPrefab3 = _game->prefab("Spaceship5.003")
		// .set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with

	auto enemyPrefab4 = _game->prefab("Spaceship5.004")
		// .set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with

	auto enemyPrefab5 = _game->prefab("Spaceship5.005")
		// .set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with

	auto enemyPrefab6 = _game->prefab("Spaceship5.006")
		// .set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with

	auto enemyPrefab7 = _game->prefab("Spaceship5.007")
		// .set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with

	auto enemyPrefab8 = _game->prefab("Spaceship5.008")
		//.set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		//.override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with
	auto enemyPrefab9 = _game->prefab("Spaceship5.009")
		//.set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		//.override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with
	auto enemyPrefab10 = _game->prefab("Spaceship5.010")
		//.set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		//.override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with
	auto enemyPrefab11 = _game->prefab("Spaceship5.011")
		//.set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		//.override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with
	auto enemyPrefab12 = _game->prefab("Spaceship5.012")
		//.set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		//.override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with
	auto enemyPrefab13 = _game->prefab("Spaceship5.013")
		//.set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		//.override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with
	auto enemyPrefab14 = _game->prefab("Spaceship5.014")
		//.set<> in a prefab means components are shared (instanced)
		.set<Material>({ red, green, blue })
		.set<Orientation>({ world })
		//.override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<Acceleration>()
		.override<Velocity>()
		.override<Position>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>(); // can be collided with

	auto enemy1 = _game->lookup("Spaceship5.014");
	if (enemy1.is_valid()) {
		enemy1.override<Enemy>();
		enemy1.set_override<Health>({ health });
		enemy1.add<Orientation>();
		enemy1.add<Position>();
		enemy1.add<Collidable>();
	}
	auto enemy2 = _game->lookup("Spaceship5.013");
	if (enemy2.is_valid()) {
		enemy2.override<Enemy>();
		enemy2.set_override<Health>({ health });
		enemy2.add<Orientation>();
		enemy2.add<Position>();
		enemy2.add<Collidable>();
	}
	auto enemy3 = _game->lookup("Spaceship5.012");
	if (enemy3.is_valid()) {
		enemy3.override<Enemy>();
		enemy3.set_override<Health>({ health });
		enemy3.add<Orientation>();
		enemy3.add<Position>();
		enemy3.add<Collidable>();
	}
	auto enemy4 = _game->lookup("Spaceship5.011");
	if (enemy4.is_valid()) {
		enemy4.override<Enemy>();
		enemy4.set_override<Health>({ health });
		enemy4.add<Orientation>();
		enemy4.add<Position>();
		enemy4.add<Collidable>();
	}
	auto enemy5 = _game->lookup("Spaceship5.0010");
	if (enemy5.is_valid()) {
		enemy5.override<Enemy>();
		enemy5.set_override<Health>({ health });
		enemy5.add<Orientation>();
		enemy5.add<Position>();
		enemy5.add<Collidable>();
	}
	auto enemy6 = _game->lookup("Spaceship5.009");
	if (enemy6.is_valid()) {
		enemy6.override<Enemy>();
		enemy6.set_override<Health>({ health });
		enemy6.add<Orientation>();
		enemy6.add<Position>();
		enemy6.add<Collidable>();
	}
	auto enemy7 = _game->lookup("Spaceship5.008");
	if (enemy7.is_valid()) {
		enemy7.override<Enemy>();
		enemy7.set_override<Health>({ health });
		enemy7.add<Orientation>();
		enemy7.add<Position>();
		enemy7.add<Collidable>();
	}
	auto enemy8 = _game->lookup("Spaceship5.007");
	if (enemy8.is_valid()) {
		enemy8.override<Enemy>();
		enemy8.add<Orientation>();
		enemy8.add<Position>();
		enemy8.add<Collidable>();
	}
	auto enemy9 = _game->lookup("Spaceship5.006");
	if (enemy9.is_valid()) {
		enemy9.override<Enemy>();
		enemy9.add<Orientation>();
		enemy9.add<Position>();
		enemy9.add<Collidable>();
	}
	auto enemy10 = _game->lookup("Spaceship5.005");
	if (enemy9.is_valid()) {
		enemy9.override<Enemy>();
		enemy9.add<Orientation>();
		enemy9.add<Position>();
		enemy9.add<Collidable>();
	}
	auto enemy11 = _game->lookup("Spaceship5.004");
	if (enemy10.is_valid()) {
		enemy10.override<Enemy>();
		enemy10.add<Orientation>();
		enemy10.add<Position>();
		enemy10.add<Collidable>();
	}
	auto enemy12 = _game->lookup("Spaceship5.003");
	if (enemy11.is_valid()) {
		enemy11.override<Enemy>();
		enemy11.add<Orientation>();
		enemy11.add<Position>();
		enemy11.add<Collidable>();
	}
	auto enemy13 = _game->lookup("Spaceship5.002");
	if (enemy12.is_valid()) {
		enemy12.override<Enemy>();
		enemy12.add<Orientation>();
		enemy12.add<Position>();
		enemy12.add<Collidable>();
	}
	auto enemy14 = _game->lookup("Spaceship5.001");
	if (enemy13.is_valid()) {
		enemy13.override<Enemy>();
		enemy13.add<Orientation>();
		enemy13.add<Position>();
		enemy13.add<Collidable>();
	}
	auto enemy15 = _game->lookup("Spaceship5");
	if (enemy14.is_valid()) {
		enemy14.override<Enemy>();
		enemy14.add<Orientation>();
		enemy14.add<Position>();
		enemy14.add<Collidable>();
	}
		 

	// register this prefab by name so other systems can use it
	RegisterPrefab("Spaceship5", enemyPrefab);
	RegisterPrefab("Enemy Type2", enemyPrefab1);
	RegisterPrefab("Enemy Type3", enemyPrefab2);
	RegisterPrefab("Enemy Type4", enemyPrefab3);
	RegisterPrefab("Enemy Type5", enemyPrefab4);
	RegisterPrefab("Enemy Type6", enemyPrefab5);
	RegisterPrefab("Enemy Type7", enemyPrefab6);
	RegisterPrefab("Enemy Type8", enemyPrefab7);
	RegisterPrefab("Enemy Type9", enemyPrefab8);
	RegisterPrefab("Enemy Type10", enemyPrefab9);
	RegisterPrefab("Enemy Type11", enemyPrefab10);
	RegisterPrefab("Enemy Type12", enemyPrefab11);
	RegisterPrefab("Enemy Type13", enemyPrefab12);
	RegisterPrefab("Enemy Type14", enemyPrefab13);
	RegisterPrefab("Enemy Type15", enemyPrefab14);

	return true;
}

bool GA::EnemyData::Unload(std::shared_ptr<flecs::world> _game)
{
	// remove all bullets and their prefabs
	_game->defer_begin(); // required when removing while iterating!
	_game->each([](flecs::entity e, Enemy&) {
		e.destruct(); // destroy this entitiy (happens at frame end)
	});
	_game->defer_end(); // required when removing while iterating!

	return true;
}
