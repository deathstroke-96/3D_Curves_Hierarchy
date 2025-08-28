#pragma once

#include "Curve.h"

class Ellipse : public Curve
{
public:
	explicit Ellipse(const double rX, const double rY)
		: radiusX{ std::abs(rX) }, radiusY{ std::abs(rY) } {}

	std::array<double, 3> getPoint(const double t) const override
	{
		return { radiusX * std::cos(t), radiusY * sin(t), 0.0 };
	}

	std::array<double, 3> getFirstDerivative(const double t) const override
	{
		return { -radiusX * std::sin(t), radiusY * std::cos(t), 0.0 };
	}

	double getRadiusX() const { return radiusX; }
	double getRadiusY() const { return radiusY; }
	std::string getCurveType() const override { return "Ellipse"; }

private:
	const double radiusX{};
	const double radiusY{};
};