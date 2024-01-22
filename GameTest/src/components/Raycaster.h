#pragma once
#include "../entities/Entity.h"
#include "../components/Player.h"
#include "../src/levels/Level.h"
#include "../src/math/Vector3.h"
#include "../App/main.h"

// Stored data of rays calculated by the Raycaster.
// Used for rendering
struct ray
{
	float start_x;
	float start_y;
	float end_x;
	float end_y;
	float angle;
	float player_angle;
	float distance;
	bool goal = false;
	bool hazard = false;
	bool breakable = false;
	float correction_factor;
};

// Used to cast rays from any point
// Note: This should be refactored to a Component if I have time 
class Raycaster
{
public:

	void RenderRays();
	std::vector<ray> CalculateRays(const Entity<Player>& playerEntity, Level* level);
	void Render3D();

	// data members
	std::vector<ray> rays;
	float fov_degrees = 15.0f;
	int num_rays = 15;
	float cell_render_size = static_cast<float>(WINDOW_WIDTH) / 100; // for rendering in 3D
	int max_distance = 1000;			// Maximum allowed distance without ray collision
	int max_steps = 1000;				// Maximum number of steps
};

