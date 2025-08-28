#include <iostream>
#include <vector>
#include <memory>
#include <numbers>
#include <random>
#include <numeric>
#include <algorithm>
#include <format>

#include "Curve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"

static std::vector<std::shared_ptr<Curve>> generateRandomCurves(const unsigned short count);

static void printAllCurves(const std::vector<std::shared_ptr<Curve>>& curves);

static std::vector<std::shared_ptr<Circle>> filterCircles(
	const std::vector<std::shared_ptr<Curve>>& curves);

static void printAllCircles(const std::vector<std::shared_ptr<Circle>>& circles);

int main()
{
	const unsigned short count_of_curves = 10;
	const auto curves = generateRandomCurves(count_of_curves);
	printAllCurves(curves);

	auto circles = filterCircles(curves);

	std::cout << "\nCircles before sorting by radius:\n\n";
	printAllCircles(circles);

	std::sort(circles.begin(), circles.end(),
		[](const auto& a, const auto& b) {
			return a->getRadius() < b->getRadius(); });

	std::cout << "\nCircles after sorting by radius:\n\n";
	printAllCircles(circles);

	const auto sum_of_radii = std::accumulate(circles.cbegin(), circles.cend(), 0.0,
		[](const double sum, const auto& circle) {
			return sum + circle->getRadius(); });
	std::cout << "\nSum of radii of all circles: " << sum_of_radii << '\n';

	return 0;
}

static std::vector<std::shared_ptr<Curve>> generateRandomCurves(
	const unsigned short count)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> curveType(1, 3);
	static std::uniform_real_distribution<> val(1, 10);

	std::vector<std::shared_ptr<Curve>> curves(count);

	for (auto& curve : curves)
		switch (curveType(gen))
		{
		case 1:
			curve = std::make_shared<Circle>(val(gen));
			break;
		case 2:
			curve = std::make_shared<Ellipse>(val(gen), val(gen));
			break;
		case 3:
			curve = std::make_shared<Helix>(val(gen), val(gen));
			break;
		default:
			curve = nullptr;
		}

	return curves;
}

static void printAllCurves(const std::vector<std::shared_ptr<Curve>>& curves)
{
	std::cout << "Curve type\tCoordinates of the point\tFirst derivatives"
		<< "\tAt t = PI / 4:\n\n";

	for (const auto& curve : curves)
	{
		std::cout << curve->getCurveType() << "\t\t";

		const auto point = curve->getPoint(std::numbers::pi / 4);
		std::cout << std::format("{{ {:.3f}, {:.3f}, {:.3f} }}\t\t",
			point[0], point[1], point[2]);

		const auto derivative = curve->getFirstDerivative(std::numbers::pi / 4);
		std::cout << std::format("{{ {:.3f}, {:.3f}, {:.3f} }}\n",
			derivative[0], derivative[1], derivative[2]);
	}
}

static std::vector<std::shared_ptr<Circle>> filterCircles(
	const std::vector<std::shared_ptr<Curve>>& curves)
{
	std::vector<std::shared_ptr<Circle>> circles;
	for (const auto& curve : curves)
	{
		const auto circle = std::dynamic_pointer_cast<Circle>(curve);
		if (circle)
			circles.emplace_back(circle);
	}
	return circles;
}

void printAllCircles(const std::vector<std::shared_ptr<Circle>>& circles)
{
	for (const auto& circle : circles)
		std::cout << circle->getCurveType() << " with radius: "
		<< circle->getRadius() << '\n';
}