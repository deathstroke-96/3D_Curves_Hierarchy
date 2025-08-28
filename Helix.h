#pragma once

#include "Curve.h"

class Helix : public Curve
{
public:
	explicit Helix(const double r, const double s)
		: radius{ std::abs(r) }, step{ std::abs(s) } {}

	std::array<double, 3> getPoint(const double t) const override
	{
		return { radius * std::cos(t), radius * sin(t), step * t };
	}

	std::array<double, 3> getFirstDerivative(const double t) const override
	{
		return { -radius * std::sin(t), radius * std::cos(t), step };
	}

	double getRadius() const { return radius; }
	double getStep() const { return step; }
	std::string getCurveType() const override { return "Helix"; }

private:
	const double radius{};
	const double step{};
};