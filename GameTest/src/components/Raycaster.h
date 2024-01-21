#pragma once
#include "../entities/Entity.h"
#include "../components/Player.h"
#include "../src/levels/Level.h"
#include "../src/math/Vector3.h"
#include "../App/main.h"

constexpr auto RAY_REFLECTION = true; // false for 3d raycasting, true for line ray bounces
constexpr auto REFLECTION_LENGTH = 50;


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
	float reflection_angle;
};


class Raycaster
{
public:
	float cell_render_size = static_cast<float>(WINDOW_WIDTH) / 100;

	void RenderRays();
	std::vector<ray> CalculateRays(const Entity<Player>& playerEntity, Level* level);
	void Render3D();


	std::vector<ray> rays;
	float fov_degrees = 10.0f;
	//int num_rays = WINDOW_WIDTH;
	int num_rays = 15;

	int max_distance = 500;			// Maximum allowed distance without collision
	int max_steps = 1000;			// Maximum number of steps
};

