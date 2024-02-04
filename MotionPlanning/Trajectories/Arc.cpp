#include "./Arc.h"

#include "Math/Vector2D.h"

#include "./ITrajectory.h"
#include "../MovementConfiguration.h"
#include "../../MathBase/Geometry/Circle.h"
#include "../../MathBase/Trigonometry/UnitCircle.h"

#include <cstdint>
#include <cmath>

using namespace AmberScience::MathBase::Geometry;
using namespace AmberScience::MathBase::Trigonometry;

namespace AmberScience::MotionPlanning::Trajectories {

	Arc::Arc() : turningBase(Circle{}), startAngleRad(0.0F), endAngleRad(0.0F), directionOfRotation(UnitCircle::RotationDirection::Clockwise) {}

	Arc::Arc(const Circle& turningBase, const float startAngleRad, const float endAngleRad, const UnitCircle::RotationDirection directionOfRotation) :
		turningBase(turningBase),
		startAngleRad(startAngleRad),
		endAngleRad(endAngleRad),
		directionOfRotation(directionOfRotation) {}

	FVector2D Arc::GetStartPosition() const {
		return this->turningBase.GetCircumferencePoint(this->startAngleRad);
	}

	FVector2D Arc::GetEndPosition() const {
		return this->turningBase.GetCircumferencePoint(this->endAngleRad);
	}

	float Arc::GetLength() const {
		auto arcLength = std::abs(UnitCircle::AngleBetweenTwoAgles(this->startAngleRad, this->endAngleRad, this->directionOfRotation));
		return this->turningBase.GetDeltaArc(arcLength);
	}

	MovementConfiguration Arc::GetMovementConfiguration(const float travelDistance) const {
		auto targetAngle = this->startAngleRad + static_cast<std::int32_t>(this->directionOfRotation) * this->turningBase.GetDeltaAngleRad(travelDistance);

		auto targetPosition = this->turningBase.GetCircumferencePoint(targetAngle);
		auto targetHeading = static_cast<std::int32_t>(this->directionOfRotation) * (targetPosition - this->turningBase.GetCenter()).GetRotated(90);

		return MovementConfiguration{ targetPosition, targetHeading };
	}
}
