#pragma once

#include <array>
#include <cmath>
#include <string>

class Curve
{
public:
	virtual ~Curve() = default;
	virtual std::array<double, 3> getPoint(const double t) const = 0;
	virtual std::array<double, 3> getFirstDerivative(const double t) const = 0;
	virtual std::string getCurveType() const = 0;
};