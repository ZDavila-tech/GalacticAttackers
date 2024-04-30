#include <random>
#include "EnemyLogic.h"
#include "../Components/Physics.h"
#include "../Components/Identification.h"
#include "../Components/Gameplay.h"
#include "../Components/Visuals.h"
#include "../Events/Playevents.h"
#include "../Components/Components.h"
#include "../Entities/Prefabs.h"

using namespace GA; // Galactic Attackers

// Connects logic to traverse any players and allow a controller to manipulate them
bool GA::EnemyLogic::Init(std::shared_ptr<flecs::world> _game,
	std::weak_ptr<const GameConfig> _gameConfig,
	GW::CORE::GEventGenerator _eventPusher,
	std::shared_ptr<Level_Data> _levelData,
	std::shared_ptr<bool> _pause,
	std::vector<flecs::entity> _entityVect,
	std::shared_ptr<bool> _youWin,
	std::shared_ptr<int> _enemyCount,
	std::shared_ptr<int> _score)
{
	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;
	eventPusher = _eventPusher;
	levelData = _levelData;
	pause = _pause;
	entityVect = _entityVect;
	youWin = _youWin;
	enemyCount = _enemyCount;
	(*enemyCount) = 12;
	score = _score;

	// destroy any bullets that have the CollidedWith relationship
	game->system<Enemy, Health, Position>("Enemy System")
		.each([this](flecs::entity e, Enemy, Health& h, Position& p) {
		// if you have no health left be destroyed
		if (!(*pause))
		{
			if (e.get<Health>()->value <= 0) {
				// play explode sound
				GA::PLAY_EVENT_DATA x;
				GW::GEvent explode;
				explode.Write(GA::PLAY_EVENT::ENEMY_DESTROYED, x);
				eventPusher.Push(explode);
				e.destruct();
				(*enemyCount)--;
				*score += 100;
			}

			ModelTransform* edit = e.get_mut<ModelTransform>();
			TimesMoved* tm = e.get_mut<TimesMoved>();
			Movement* move = e.get_mut<Movement>();
			Location* loc = e.get_mut<Location>();
			timer = 0;
			loc->location = 60.0f;
			if (move->moveRight)
			{
				timer--;
				if (timer <= 0)
				{
					GW::MATH::GMatrix::TranslateGlobalF(edit->matrix, GW::MATH::GVECTORF{ 0.75, 0, 0, 1 }, edit->matrix);
					levelData->levelTransforms[edit->rendererIndex] = edit->matrix;
					e.get_mut<ModelBoundary>()->obb.center.x = edit->matrix.row4.x;
					e.get_mut<ModelBoundary>()->obb.center.y = edit->matrix.row4.y;

					tm->timesMoved++;
					timer = e.delta_time() * 20;

					if (tm->timesMoved >= 28)
					{
						GW::MATH::GMatrix::TranslateGlobalF(edit->matrix, GW::MATH::GVECTORF{ 0, -3, 0, 1 }, edit->matrix);
						levelData->levelTransforms[edit->rendererIndex] = edit->matrix;
						e.get_mut<ModelBoundary>()->obb.center.x = edit->matrix.row4.x;
						e.get_mut<ModelBoundary>()->obb.center.y = edit->matrix.row4.y;

						move->moveRight = false;
					}
				}

			}
			else if (!move->moveRight)
			{
				timer--;
				if (timer <= 0)
				{
					GW::MATH::GMatrix::TranslateGlobalF(edit->matrix, GW::MATH::GVECTORF{ -0.75, 0, 0, 1 }, edit->matrix);
					levelData->levelTransforms[edit->rendererIndex] = edit->matrix;
					e.get_mut<ModelBoundary>()->obb.center.x = edit->matrix.row4.x;
					e.get_mut<ModelBoundary>()->obb.center.y = edit->matrix.row4.y;

					tm->timesMoved--;
					timer = e.delta_time() * 20;

					if (tm->timesMoved <= 0)
					{
						GW::MATH::GMatrix::TranslateGlobalF(edit->matrix, GW::MATH::GVECTORF{ 0, -3, 0, 1 }, edit->matrix);
						levelData->levelTransforms[edit->rendererIndex] = edit->matrix;
						e.get_mut<ModelBoundary>()->obb.center.x = edit->matrix.row4.x;
						e.get_mut<ModelBoundary>()->obb.center.y = edit->matrix.row4.y;

						move->moveRight = true;
					}
				}
			}

			if (shieldon1)
			{
				if (edit->matrix.row4.y <= loc->location)
				{
					GW::MATH::GMatrix::TranslateGlobalF(edit->matrix, GW::MATH::GVECTORF{ 0, 500, 0, 1 }, edit->matrix);
					levelData->levelTransforms[edit->rendererIndex] = edit->matrix;
					auto a = game->lookup("shield");
					if (a.is_valid()) {
						a.destruct();
						(*enemyCount)--;
					}
					shieldon1 = false;
				}
			}

			if (edit->matrix.row4.y <= 30)
			{
				GW::MATH::GMatrix::TranslateGlobalF(edit->matrix, GW::MATH::GVECTORF{ 0, 500, 0, 1 }, edit->matrix);
				levelData->levelTransforms[edit->rendererIndex] = edit->matrix;
				flecs::entity playerDeath;
				RetreivePrefab("Death", playerDeath);
				GW::AUDIO::GSound death = *playerDeath.get<GW::AUDIO::GSound>();
				death.Play();
				auto live = game->lookup("life 1");
				if (live.is_valid())
				{
					live.destruct();
				}
				else {
					auto live2 = game->lookup("life 2");
					if (live2.is_valid())
					{
						live2.destruct();

					}
					else
					{
						auto live3 = game->lookup("life 3");
						if (live3.is_valid())
						{
							live3.destruct();
							auto player = game->lookup("Player");
							player.destruct();

							GA::PLAY_EVENT_DATA y;
							GW::GEvent youLose;
							youLose.Write(GA::PLAY_EVENT::LOSE, y);
							eventPusher.Push(youLose);
							std::cout << "Player Dies...You Lose";
						}
					}
				}
			}
			p.value = { 0, 0 };
		}

			});

	return true;

}

// Free any resources used to run this system
bool GA::EnemyLogic::Shutdown()
{
	game->entity("Enemy System").destruct();
	// invalidate the shared pointers
	game.reset();
	gameConfig.reset();
	return true;
}

// Toggle if a system's Logic is actively running
bool GA::EnemyLogic::Activate(bool runSystem)
{
	if (runSystem) {
		game->entity("Enemy System").enable();
	}
	else {
		game->entity("Enemy System").disable();
	}
	return false;
}

bool GA::EnemyLogic::FireLasersEnemy(flecs::world& stage, Position origin)
{
	// Grab laser prefab
	flecs::entity bullet;
	RetreivePrefab("Lazer Bullet", bullet);

	// Laser start shoot position
	origin.value.x -= 0.05f;
	auto laserLeft = stage.entity().is_a(bullet)
		.set<Position>(origin);
	origin.value.x += 0.1f;
	auto laserRight = stage.entity().is_a(bullet)
		.set<Position>(origin);

	return true;
}