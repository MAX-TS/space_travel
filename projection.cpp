#include "projection.hpp"
#include <iostream>


Vector GetLocalPosition(Vector pos1, Vector pos2, sf::Vector2<double> rotation)
{
	Vector local_position = { pos1.x - pos2.x, pos1.y - pos2.y, pos1.z - pos2.z };
	local_position = {
		local_position.x * cos(-rotation.y) - local_position.y * sin(-rotation.y),
		local_position.x * sin(-rotation.y) + local_position.y * cos(-rotation.y),
		local_position.z };
	local_position = {
		local_position.x,
		local_position.z * sin(-rotation.x) + local_position.y * cos(-rotation.x),
		local_position.z * cos(-rotation.x) - local_position.y * sin(-rotation.x) };
	return local_position;
}

sf::Vector2f Project(Vector local_position, double focal_length)
{
	sf::Vector2f projected_point = {
	float(local_position.x * focal_length / (local_position.y + focal_length)),
	float(local_position.z * focal_length / (local_position.y + focal_length)) };
	return projected_point;
}
