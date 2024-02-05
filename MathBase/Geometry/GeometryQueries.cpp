#include "GeometryQueries.h"

#include "../Trigonometry/UnitCircle.h"
#include "../Vectors/VectorLocationQueries.h"

#include "Math/Vector2D.h"

#include <utility>

using namespace AmberScience::MathBase::Vectors;
using namespace AmberScience::MathBase::Trigonometry;

namespace AmberScience::MathBase::Geometry::GeometryQueries {

	std::pair<Circle, Circle> CircleFromCircumferencePointTangentAndRadius(const FVector2D& circumferencePoint, const FVector2D& tangent, const float radius) {
        auto fromTangentToCircleCenter = tangent.GetRotated(90).GetSafeNormal() * radius;

        auto circleACenter = circumferencePoint + fromTangentToCircleCenter;
        auto circleBCenter = circumferencePoint - fromTangentToCircleCenter;

        return VectorLocationQueries::IsLeftOf(tangent, circleACenter)
            ? std::make_pair(Circle{ radius, circleACenter },  Circle{ radius, circleBCenter })
            : std::make_pair(Circle{ radius, circleBCenter }, Circle{ radius, circleACenter });
	}

    UnitCircle::RotationDirection GetRotationDirection(const FVector2D& tangent, const FVector2D& circumferencePoint, const FVector2D& circleCenter) {
        return VectorLocationQueries::IsLeftOf(tangent, circumferencePoint - circleCenter)
            ? UnitCircle::RotationDirection::Clockwise
            : UnitCircle::RotationDirection::Counterclockwise;
    }
}
