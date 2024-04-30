#include <random>
#include "LevelLogic.h"
#include "../Components/Identification.h"
#include "../Components/Physics.h"
#include "../Components/Components.h"
#include "../Entities/Prefabs.h"
#include "../Utils/Macros.h"

using namespace GA; // Example Space Game

// Connects logic to traverse any players and allow a controller to manipulate them
bool GA::LevelLogic::Init(	std::shared_ptr<flecs::world> _game,
							std::weak_ptr<const GameConfig> _gameConfig,
							GW::AUDIO::GAudio _audioEngine,
							std::shared_ptr<Level_Data> _levelData)
{
	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;
	audioEngine = _audioEngine;
	levelData = _levelData;
	// create an asynchronus version of the world
	gameAsync = game->async_stage(); // just used for adding stuff, don't try to read data
	gameLock.Create();
	// Pull enemy Y start location from config file
	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();
	float enemy1startY = (*readCfg).at("Enemy1").at("ystart").as<float>();
	float enemy1accmax = (*readCfg).at("Enemy1").at("accmax").as<float>();
	float enemy1accmin = (*readCfg).at("Enemy1").at("accmin").as<float>();
	// level one info
	float spawnDelay = (*readCfg).at("Level1").at("spawndelay").as<float>();
	
	// spins up a job in a thread pool to invoke a function at a regular interval
	timedEvents.Create(spawnDelay * 100000, [this, enemy1startY, enemy1accmax, enemy1accmin]() {
		// compute random spawn location
		std::random_device rd;  // Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<float> x_range(-0.9f, +0.9f);
		std::uniform_real_distribution<float> a_range(enemy1accmin, enemy1accmax);
		float Xstart = x_range(gen); // normal rand() doesn't work great multi-threaded
		float accel = a_range(gen);
		// grab enemy type 1 prefab
		flecs::entity et1;
		flecs::entity et2;
		flecs::entity et3;
		flecs::entity et4;
		flecs::entity et5;
		flecs::entity et6;
		flecs::entity et7;
		flecs::entity et8;
		flecs::entity et9;
		flecs::entity et10;
		flecs::entity et11;
		flecs::entity et12;

		if (RetreivePrefab("Spaceship5", et1)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et1)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type2", et2)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et2)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type3", et3)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et3)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type4", et4)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et4)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type5", et5)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et5)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type6", et6)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et6)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type7", et7)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et7)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type8", et8)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et8)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type9", et9)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et9)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type10", et10)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et10)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type11", et11)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et11)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
		if (RetreivePrefab("Enemy Type12", et12)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et12)
				.set<Velocity>({ 0,0 })
				.set<Acceleration>({ 0, accel })
				.set<Position>({ Xstart, enemy1startY });
			///provide a set matrix     
			// be sure to unlock when done so the main thread can safely merge the changes
			gameLock.UnlockSyncWrite();
		}
	}, 1000); // wait 5 seconds to start enemy wave

	// create a system the runs at the end of the frame only once to merge async changes
	struct LevelSystem {}; // local definition so we control iteration counts
	game->entity("Level System").add<LevelSystem>();
	// only happens once per frame at the very start of the frame
	game->system<LevelSystem>().kind(flecs::OnLoad) // first defined phase
		.each([this](flecs::entity e, LevelSystem& s) {
		// merge any waiting changes from the last frame that happened on other threads
		gameLock.LockSyncWrite();
		gameAsync.merge();
		gameLock.UnlockSyncWrite();
	});

	// Load and play level one's music
	currentTrack.Create("../Music/space-ambient-sci-fi-121842.wav", audioEngine, 0.15f);
	currentTrack.Play(false);

	return true;
}

// Free any resources used to run this system
bool GA::LevelLogic::Shutdown()
{
	timedEvents = nullptr; // stop adding enemies
	gameAsync.merge(); // get rid of any remaining commands
	game->entity("Level System").destruct();
	// invalidate the shared pointers
	game.reset();
	gameConfig.reset();
	return true;
}

// Toggle if a system's Logic is actively running
bool GA::LevelLogic::Activate(bool runSystem)
{
	if (runSystem) {
		game->entity("Level System").enable();
	}
	else {
		game->entity("Level System").disable();
	}
	return false;
}

// **** SAMPLE OF MULTI_THREADED USE ****
//flecs::world world; // main world
//flecs::world async_stage = world.async_stage();
//
//// From thread
//lock(async_stage_lock);
//flecs::entity e = async_stage.entity().child_of(parent)...
//unlock(async_stage_lock);
//
//// From main thread, periodic
//lock(async_stage_lock);
//async_stage.merge(); // merge all commands to main world
//unlock(async_stage_lock);