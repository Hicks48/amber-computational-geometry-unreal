#pragma once

#include "Circle.h"
#include "../Trigonometry/UnitCircle.h"

#include "Math/Vector2D.h"

#include <utility>

namespace AmberScience::MathBase::Geometry::GeometryQueries {

	std::pair<Circle, Circle> CircleFromCircumferencePointTangentAndRadius(const FVector2D& circumferencePoint, const FVector2D& tangent, const float radius);

	AmberScience::MathBase::Trigonometry::UnitCircle::RotationDirection GetRotationDirection(const FVector2D& tangent, const FVector2D& circumferencePoint, const FVector2D& circleCenter);
}
