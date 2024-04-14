#include "vector.hpp"
#include <cmath>
#include <sfml/Graphics.hpp>
#include "trajectory.hpp"

using namespace sf;

class GravitationalObject
{
public:

	static constexpr double kG = 6.6743e-11;
	static constexpr size_t max_size = 300;

	GravitationalObject(const Vector& position, const Vector& velocity, const double mass, const double radius, const Color color)
	{
		position_ = position;
		velocity_ = velocity;
		mass_ = mass;
		radius_ = radius;
		color_ = color;
	}

	//void CalcF(const GravitationalObject& other, ) {}

	void CalcGravForce(const GravitationalObject& other, const double delta_time)
	{
		double dist_2 = (position_.x - other.position_.x) * (position_.x - other.position_.x) +
			(position_.y - other.position_.y) * (position_.y - other.position_.y) +
			(position_.z - other.position_.z) * (position_.z - other.position_.z);
		double dist = sqrt(dist_2);
		velocity_.x += ((other.position_.x - position_.x) * other.mass_ * delta_time * kG) / (dist_2 * dist);
		velocity_.y += ((other.position_.y - position_.y) * other.mass_ * delta_time * kG) / (dist_2 * dist);
		velocity_.z += ((other.position_.z - position_.z) * other.mass_ * delta_time * kG) / (dist_2 * dist);
	}

	void MoveOnestep(const double delta_time)
	{
		position_.x += velocity_.x * delta_time;
		position_.y += velocity_.y * delta_time;
		position_.z += velocity_.z * delta_time;
		trajectory_.NewPoint(position_);
	}

	void Render(RenderWindow& window, double const scale, Vector2f camera_pos)
	{
		const auto size = window.getSize();
		CircleShape shape(radius_ / scale, 100.0f);
		shape.setFillColor(color_);
		shape.setPosition((position_.x - radius_) / scale + size.x / 2 + camera_pos.x,
			(position_.y - radius_) / scale + size.y / 2 + camera_pos.y);
		window.draw(shape);
		trajectory_.Render(window, scale, camera_pos);
	}

	double GetMass() { return mass_; }
	Vector GetPosition() { return position_; }
	double GetRadius() { return radius_; }
	Color GetColor() { return color_; }
	Vector GetVelocity() { return velocity_; }
private:
	Vector position_;
	Vector velocity_;
	double mass_;
	double radius_;
	Color color_;
	Trajectory trajectory_{max_size};

};