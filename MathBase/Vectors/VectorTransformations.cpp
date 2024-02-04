#include "VectorTransformations.h"

#include "Math/Vector2D.h"

#include <cmath>

namespace AmberScience::MathBase::Vectors::VectorTransformations {

	FVector2D RotateVector(const FVector2D& v, const float radians) {
		return FVector2D{
			v.X * std::cos(radians) - v.Y * std::sin(radians),
			v.X * std::sin(radians) + v.Y * std::cos(radians)
		};
	}
}
