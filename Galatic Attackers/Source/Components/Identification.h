// define all ECS components related to identification
#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

// example space game (avoid name collisions)
namespace GA
{
	struct Player {};
	struct Bullet {};
	struct Shield {};
	struct Enemy {};
	struct Lives {};
	struct ControllerID {
		unsigned index = 0;
	};
};

#endif