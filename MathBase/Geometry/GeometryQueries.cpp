#include "GeometryQueries.h"

#include "../Trigonometry/UnitCircle.h"
#include "../Vectors/VectorLocationQueries.h"

#include "Math/Vector2D.h"

#include <utility>

using namespace AmberScience::MathBase::Vectors;
using namespace AmberScience::MathBase::Trigonometry;

namespace AmberScience::MathBase::Geometry::GeometryQueries {

	std::pair<Circle, Circle> CircleFromCircumferencePointTangentAndRadious(const FVector2D& circumferencePoint, const FVector2D& tangent, const float radious) {
        auto fromTangentToCircleCenter = tangent.GetRotated(90).GetSafeNormal() * radious;

        auto circleACenter = circumferencePoint + fromTangentToCircleCenter;
        auto circleBCenter = circumferencePoint - fromTangentToCircleCenter;

        return VectorLocationQueries::IsLeftOf(tangent, circleACenter)
            ? std::make_pair(Circle{ radious, circleACenter },  Circle{ radious, circleBCenter })
            : std::make_pair(Circle{ radious, circleBCenter }, Circle{ radious, circleACenter });
	}

    UnitCircle::RotationDirection GetRotationDirection(const FVector2D& tangent, const FVector2D& circumferencePoint, const FVector2D& circleCenter) {
        return VectorLocationQueries::IsLeftOf(tangent, circumferencePoint - circleCenter)
            ? UnitCircle::RotationDirection::Clockwise
            : UnitCircle::RotationDirection::Counterclockwise;
    }
}
