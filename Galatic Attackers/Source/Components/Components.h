// define all ECS components related to identification
#ifndef COMPONENTS_H
#define COMPONENTS_H

// example space game (avoid name collisions)
namespace GA
{
	struct BlenderName { std::string name; };
	struct ModelBoundary { GW::MATH::GOBBF obb; };
	struct ModelTransform {
		GW::MATH::GMATRIXF matrix;
		unsigned int rendererIndex;
	};
	struct Instance { 
		unsigned int transformStart, transformCount;
	};
	struct Object {
		unsigned vertexCount, indexCount, materialCount, meshCount;
		unsigned vertexStart, indexStart, materialStart, meshStart;
	};
	struct Mesh {
		unsigned indexCount, indexOffset, materialIndex;
	};
	struct RenderingSystem {};
	struct BulletTest {};
	struct Enable{};
	struct TimesMoved { int timesMoved = 0; };
	struct Movement { bool moveRight = true; };
	struct Location { float location = 0; };
	//struct Material { float red, greem, blue; };
}
#endif