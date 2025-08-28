#pragma once

#include "Curve.h"

class Circle : public Curve
{
public:
	explicit Circle(const double r) : radius{ std::abs(r) } {}

	std::array<double, 3> getPoint(const double t) const override
	{
		return { radius * std::cos(t), radius * sin(t), 0.0 };
	}

	std::array<double, 3> getFirstDerivative(const double t) const override
	{
		return { -radius * std::sin(t), radius * std::cos(t), 0.0 };
	}

	double getRadius() const { return radius; }
	std::string getCurveType() const override { return "Circle"; }

private:
	const double radius{};
};