#pragma once

#include "trajectory.hpp"
#include "vector.hpp"

class Maneuver
{
	static constexpr size_t max_size = 300;
public:
	Maneuver(unsigned int path_id, unsigned int path_position)
	{
		unsigned int path_id_ = path_id;
		unsigned int path_position_ = path_position;
	}

	void ChangeForce(Vector force)
	{
		applied_force_.x += force.x;
		applied_force_.y += force.y;
		applied_force_.z += force.z;
	}

private:
	Trajectory redirected_path_{max_size};
	Vector applied_force_;
	unsigned int path_id_;
	unsigned int path_position_;
};