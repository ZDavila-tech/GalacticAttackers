#include "../Components/Components.h"
#include "../Components/Gameplay.h"
#include "../Components/Identification.h"
#include "../Components/Physics.h"
#include "BulletLogic.h"
#include <random>

using namespace GA; // Example Space Game

// Connects logic to traverse any players and allow a controller to manipulate them
bool GA::BulletLogic::Init(std::shared_ptr<flecs::world> _game,
	std::weak_ptr<const GameConfig> _gameConfig,
	std::shared_ptr<Level_Data> _levelData)
{
	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;
	levelData = _levelData;
	// destroy any bullets that have the CollidedWith relationship
	game->system<Bullet, Damage, Position>("Bullet System")
		.each([this](flecs::entity e, Bullet, Damage& d, Position& p) {
		// damage anything we come into contact with

		auto pos = p.value;
		{
			e.each<CollidedWith>([&e, d, p, this](flecs::entity hit) {
				if (hit.has<Health>() && hit.has<Enemy>()) {
					auto enemy = hit.get<Position>()->value.y;
					auto bullet = e.get<Position>()->value.y;
					int currentHealth = hit.get<Health>()->value;
					hit.set<Health>({ currentHealth - d.value });
					ModelTransform* bulletT = e.get_mut<ModelTransform>();
					levelData->levelTransforms[bulletT->rendererIndex] = bulletT->matrix;
					bulletT->matrix.row4.x = 0;
					bulletT->matrix.row4.y = 0;
					e.destruct();


					if (hit.get<Health>()->value <= 0)
					{
						ModelTransform* enemyT = hit.get_mut<ModelTransform>();
						levelData->levelTransforms[enemyT->rendererIndex] = enemyT->matrix;
						enemyT->matrix.row4.x = 200;
						enemyT->matrix.row4.y = 200;
						hit.destruct();
					}

					// reduce the amount of hits but the charged shot
					if (e.has<ChargedShot>() && hit.get<Health>()->value <= 0)
					{
						int md_count = e.get<ChargedShot>()->max_destroy;
						e.set<ChargedShot>({ md_count - 1 });
					}
				}
				});
			// if you have collidedWith realtionship then be destroyed
			if (e.has<CollidedWith>(flecs::Wildcard)) {

				if (e.has<ChargedShot>()) {

					if (e.get<ChargedShot>()->max_destroy <= 0)
						e.destruct();
				}
				else {
					// play hit sound
					e.destruct();
				}
			}
		}
			});

	return true;
}

// Free any resources used to run this system
bool GA::BulletLogic::Shutdown()
{
	game->entity("Bullet System").destruct();
	// invalidate the shared pointers
	game.reset();
	gameConfig.reset();
	return true;
}

// Toggle if a system's Logic is actively running
bool GA::BulletLogic::Activate(bool runSystem)
{
	if (runSystem) {
		game->entity("Bullet System").enable();
	}
	else {
		game->entity("Bullet System").disable();
	}
	return false;
}
