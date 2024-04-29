#pragma once

#include <sfml/Graphics.hpp>
#include <deque>
#include "vector.hpp"
#include "projection.hpp"


class Trajectory
{
public:
	Trajectory(size_t max_size) : max_size_(max_size)
	{
	}

	void Render(sf::RenderWindow& window, double const scale, Vector camera_pos, sf::Vector2<double> camera_rotation, double focal_lenght)
	{
		const auto size = window.getSize();
		std::vector<sf::Vertex> verticies;
		verticies.reserve(points_.size());
		for (const auto& point : points_) {
			Vector local_position = GetLocalPosition(point, camera_pos, camera_rotation);
			sf::Vector2f projected_position = Project(local_position, focal_lenght);
			verticies.emplace_back(sf::Vector2f{ 
				projected_position.x + size.x / 2,
				projected_position.y + size.y / 2 });
		}

		window.draw(verticies.data(), points_.size(), sf::LineStrip);
	}

	void NewPoint(const Vector point)
	{
		points_.push_back(point);
		while (points_.size() > max_size_)
		{
			points_.pop_front();
		}
	}
private:
	std::deque<Vector> points_;
	size_t max_size_;
};