#include <random>
#include "ShieldLogic.h"
#include "../Components/Identification.h"
#include "../Components/Physics.h"
#include "../Components/Gameplay.h"

using namespace GA; // Example Space Game

// Connects logic to traverse any players and allow a controller to manipulate them
bool GA::ShieldLogic::Init(std::shared_ptr<flecs::world> _game,
	std::weak_ptr<const GameConfig> _gameConfig)
{
	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;

	// destroy any bullets that have the CollidedWith relationship
	game->system<Shield, Damage>("Shield System")
		.each([](flecs::entity e, Shield, Damage& d) {
		// damage anything we come into contact with
		e.each<CollidedWith>([&e, d](flecs::entity hit) {
			if (hit.has<Health>()) {
				int current = hit.get<Health>()->value;
				hit.set<Health>({ current - d.value });
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
			});

	return true;
}

// Free any resources used to run this system
bool GA::ShieldLogic::Shutdown()
{
	game->entity("Shield System").destruct();
	// invalidate the shared pointers
	game.reset();
	gameConfig.reset();
	return true;
}

// Toggle if a system's Logic is actively running
bool GA::ShieldLogic::Activate(bool runSystem)
{
	if (runSystem) {
		game->entity("Shield System").enable();
	}
	else {
		game->entity("Shield System").disable();
	}
	return false;
}