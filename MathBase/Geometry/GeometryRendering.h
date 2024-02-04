#pragma once

#include "./Circle.h"

#include "Math/Vector2D.h"

#include <vector>

namespace AmberScience::MathBase::Geometry::GeometryRendering {

	std::vector<FVector2D> GetRenderingPointsForCircle(const Circle& circle, const float pointsPerUnit);
}
