#pragma once

#include <sfml/Graphics.hpp>
#include <deque>
#include "vector.hpp"


class Trajectory
{
public:
	Trajectory(size_t max_size) : max_size_(max_size)
	{
	}

	void Render(sf::RenderWindow& window, double const scale, sf::Vector2f camera_pos)
	{
		const auto size = window.getSize();
		std::vector<sf::Vertex> verticies;
		verticies.reserve(points_.size());
		for (const auto& point : points_) {
			verticies.emplace_back(sf::Vector2f{  
				float(point.x / scale + camera_pos.x + size.x / 2),
				float(point.y / scale + camera_pos.y + size.y / 2)});
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