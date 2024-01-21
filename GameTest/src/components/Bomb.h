#pragma once
#include "Particle.h"
#include "../pools/Pool.h"
#include "Bullet.h"
#include "../levels/Level.h"


struct Bomb : public Bullet
{
	friend class Level;
	Bomb()
	{
		m_id = TypeIDGenerator<Bullet>::GenerateNewID<Bullet>();
	}

	void Update(float delta_time)
	{
		if (bursting)
		{
			Explode(delta_time);
		}
		if (active &&   !exploded)
		{
			ClearParticles();

			// Update position based on speed and direction
			float new_x = transform.position.GetX() + delta_x * physics.current_speed * delta_time;
			float new_y = transform.position.GetY() + delta_y * physics.current_speed * delta_time;
			float curr_x = MathUtility::ScaleToVirtualWidth(transform.position.GetX());
			float curr_y = MathUtility::ScaleToVirtualHeight(transform.position.GetY());
			current_coordinates = MathUtility::GetCell(Vector3(curr_x, curr_y));




			// check horizontal collision first
			if (collision_callback && collision_callback(MathUtility::ScaleToVirtualWidth(new_x), curr_y))
			{
				//col = Vector3(1, 0, 1);
				delta_x = 0;
			}

			// check vertical collision
			if (collision_callback && collision_callback(curr_x, MathUtility::ScaleToVirtualHeight(new_y)))
			{
				//col = Vector3(1, .5, 0.7);
				delta_y = 0;
			}

			transform.position.SetX(transform.position.GetX() + delta_x * physics.current_speed * delta_time);
			transform.position.SetY(transform.position.GetY() + delta_y * physics.current_speed * delta_time);
			//lifetime -= delta_time;
		}
	}

	void Render()
	{
		for (auto& particle : active_bomb_particles)
		{
			particle->Render();
		}
		if (active) ShapeRenderer::RenderShapeWithNSides
		(
			MathUtility::ScaleToVirtualWidth(transform.position.GetX()),
			MathUtility::ScaleToVirtualHeight(transform.position.GetY()),
			size,
			col.GetX(), col.GetY() * bomb_timer, col.GetZ() * bomb_timer,
			6
		);
		App::Print(100, 500, current_coordinates.ToString().c_str());
		App::Print(350, 500, std::to_string(active_bomb_particles.size()).c_str());

	}

	void Launch(const Transform& launch_point)
	{
		launched = true;
		active = true;
		transform.SetPosition(launch_point.position);

		CalculateDeltas(launch_point.direction_angle);
		physics.current_speed = launch_speed;
	}

	void ClearParticles()
	{
		for (int i = 0; i < active_bomb_particles.size(); i++)
		{
			bomb_particles->ReturnPoolObject(active_bomb_particles[i]);
			active_bomb_particles.erase(active_bomb_particles.begin() + i);
		}
	}

	void CalculateDeltas(float direction)
	{
		delta_x = Mathf::Cos(MathUtility::DegreeToRadians(direction));
		delta_y = Mathf::Sin(MathUtility::DegreeToRadians(direction));
	}
	void SetCollisionCallback(std::function<bool(float, float)> callback)
	{
		collision_callback = std::move(callback);
	}
	void SetLevelCallback(std::function<Level* ()> callback)
	{
		level_callback = std::move(callback);
	}

	void Explode(float delta_time)
	{
		for (int i = 0; i < active_bomb_particles.size(); i++)
		{
			if (active_bomb_particles[i]->lifetime <= 0)
			{
				bomb_particles->ReturnPoolObject(active_bomb_particles[i]);
				active_bomb_particles.erase(active_bomb_particles.begin() + i);
			}
			else
			{
				active_bomb_particles[i]->Update(delta_time);
			}
		}

		bomb_timer -= delta_time;
		if (bomb_timer <= 0)
		{
			exploded = true;
		}
		if (exploded)
		{
			blast_radius = CalculateBlastRadius(current_coordinates);

			Level* current_level = level_callback();
			for (auto tile : blast_radius)
			{
				if (current_level->level_map[tile] == Cell::GOAL)
				{
					goal_destroyed = true;
					current_level->level_map[tile] = Cell::EMPTY;
					Particle* new_particle = goal_particles->GetPoolObject();
					new_particle->Set(transform, particle_emitter::goal_emitter);
					active_bomb_particles.push_back(new_particle);
				}
				if (current_level->level_map[tile] == Cell::INSTANTDEATH)
				{
					death_hit = true;
					current_level->level_map[tile] = Cell::EMPTY;
					Particle* new_particle = death_particles->GetPoolObject();
					new_particle->Set(transform, particle_emitter::death_emitter);
					active_bomb_particles.push_back(new_particle);
				}
				if (current_level->level_map[tile] == Cell::WALL)
				{
					current_level->level_map[tile] = Cell::EMPTY;
					Particle* new_particle = bomb_particles->GetPoolObject();
					new_particle->Set(transform, particle_emitter::wall_emitter);
					active_bomb_particles.push_back(new_particle);
				}
				if (current_level->level_map[tile] == Cell::BREAKABLE)
				{
					current_level->level_map[tile] = Cell::EMPTY;
					Particle* new_particle = breakable_particles->GetPoolObject();
					new_particle->Set(transform, particle_emitter::breakable_emitter);
					active_bomb_particles.push_back(new_particle);
				}
			}

			Particle* new_particle = bomb_particles->GetPoolObject();
			new_particle->Set(transform, particle_emitter::bomb_emitter);
			active_bomb_particles.push_back(new_particle);




			// start particles, blow up walls

			

			//if no particles remain
			lifetime -= delta_time;
			//active = false;
		}
	}

	std::vector<int> CalculateBlastRadius(Vector3 cell)
	{
		std::vector<int> out;

		// Iterate over neighboring cells (up, down, left, right)
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				// Skip the center cell (i = 0, j = 0)
				if (i == 0 && j == 0)
					continue;

				// Calculate neighboring cell coordinates
				int neighborX = cell.GetX() + i;
				int neighborY = cell.GetY() + j;

				// Check if the neighboring cell is within array bounds
				if (neighborX >= 0 && neighborX < MAP_SIZE && neighborY >= 0 && neighborY < MAP_SIZE)
				{
					// Convert 2D coordinates to a 1D index (assuming row-major order)
					int index = neighborY * MAP_WIDTH + neighborX;
					out.push_back(index);
				}
			}
		}

		return out;
	}

	//Vector3 col = Vector3(0.635, 1, 0.024);
	Vector3 col = Vector3(1, 1, 1);

	Transform transform;
	Vector3 current_coordinates;
	Physics physics;
	bool launched = false;
	float launch_speed = 0.3f;
	projectile_type type = basic;
	float size = 15;
	float delta_y;
	float delta_x;
	float next_x;
	float next_y;
	bool active = false;
	float lifetime = 1;
	ComponentTypeID m_id;
	std::function<bool(float, float)> collision_callback;






	// bomb stuff
	Pool<Particle>* bomb_particles = Pool<Particle>::GetInstance(200);
	Pool<Particle>* wall_particles = Pool<Particle>::GetInstance(200);
	Pool<Particle>* breakable_particles = Pool<Particle>::GetInstance(200);
	Pool<Particle>* goal_particles = Pool<Particle>::GetInstance(200);
	Pool<Particle>* death_particles = Pool<Particle>::GetInstance(200);

	std::vector<Particle*> active_bomb_particles;
	//std::vector<Particle*> active_wall_particles;
	//std::vector<Particle*> active_goal_particles;
	//std::vector<Particle*> active_death_particles;
	//std::vector<Particle*> active_break_a

	bool bursting = false;
	bool exploded = false;
	float bomb_timer = 1;
	std::function<Level* (void)> level_callback; // needed for explosion
	std::vector<int> blast_radius;
	bool goal_destroyed = false;
	bool death_hit = false;

};
