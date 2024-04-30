#ifndef APPLICATION_H
#define APPLICATION_H

// include events
#include "Events/Playevents.h"
// Contains our global game settings
#include "GameConfig.h"
// Load all entities+prefabs used by the game 
#include "Entities/BulletData.h"
#include "Entities/PlayerData.h"
#include "Entities/EnemyData.h"
// Include all systems used by the game and their associated components
#include "Systems/PlayerLogic.h"
#include "Systems/RendererLogic.h"
#include "Systems/LevelLogic.h"
#include "Systems/PhysicsLogic.h"
#include "Systems/BulletLogic.h"
#include "Systems/EnemyLogic.h"

#include "Components/Components.h"

// Allocates and runs all sub-systems essential to operating the game
class Application 
{
	
	// gateware libs used to access operating system
	GW::SYSTEM::GWindow window; // gateware multi-platform window
	GW::SYSTEM::GLog log;
	GW::GRAPHICS::GDirectX11Surface d3d11;
	
	//GW::GRAPHICS::GVulkanSurface vulkan; // gateware vulkan API wrapper
	GW::INPUT::GController gamePads; // controller support
	GW::INPUT::GInput immediateInput; // twitch keybaord/mouse
	GW::INPUT::GBufferedInput bufferedInput; // event keyboard/mouse
	GW::AUDIO::GAudio audioEngine; // can create music & sound effects
	// thrd-party gameplay & utility libraries
	std::shared_ptr<flecs::world> game; // ECS database for gameplay
	std::shared_ptr<GameConfig> gameConfig; // .ini file game settings
	std::shared_ptr<Level_Data> levelData;
	std::shared_ptr<int> currentLevel;
	std::shared_ptr<int> enemyCount;
	std::shared_ptr<int> score;
	std::shared_ptr<bool> levelChange;
	std::shared_ptr<bool> youWin;
	std::shared_ptr<bool> youLose;
	std::shared_ptr<bool> pause;
	bool ispaused;
	std::vector<flecs::entity> entityVec;
	std::string level;
	std::string models;
	// ECS Entities and Prefabs that need to be loaded
	GA::BulletData weapons;
	GA::PlayerData players;
	GA::EnemyData enemies;
	// specific ECS systems used to run the game
	GA::PlayerLogic playerSystem;
	GA::D3DRendererLogic d3dRenderingSystem;
	GA::LevelLogic levelSystem;
	GA::PhysicsLogic physicsSystem;
	GA::BulletLogic bulletSystem;
	GA::EnemyLogic enemySystem;
	// EventGenerator for Game Events
	GW::CORE::GEventGenerator eventPusher;

public:
	bool Init();
	bool Run();
	bool Shutdown();
private:
	bool InitWindow();
	bool InitInput();
	bool InitAudio();
	bool InitGraphics();
	bool InitEntities();
	bool InitSystems();
	bool GameLoop();
	void UpdateLevelData();
	void LoadLevel(int currentLevel);
};

#endif 