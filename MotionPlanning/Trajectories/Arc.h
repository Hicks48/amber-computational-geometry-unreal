#pragma once

#include "Math/Vector2D.h"

#include "./ITrajectory.h"
#include "../MovementConfiguration.h"
#include "../../MathBase/Geometry/Circle.h"
#include "../../MathBase/Trigonometry/UnitCircle.h"

namespace AmberScience::MotionPlanning::Trajectories {

	class Arc : public ITrajectory {
		public:
			Arc();
			Arc(const AmberScience::MathBase::Geometry::Circle& turningBase, const float startAngleRad, const float endAngleRad, const AmberScience::MathBase::Trigonometry::UnitCircle::RotationDirection directionOfRotation);
			~Arc() = default;

			FVector2D GetStartPosition() const final;
			FVector2D GetEndPosition() const final;
			float GetLength() const final;

			MovementConfiguration GetMovementConfiguration(const float travelDistance) const final;

		private:
			AmberScience::MathBase::Geometry::Circle turningBase;
			float startAngleRad;
			float endAngleRad;
			AmberScience::MathBase::Trigonometry::UnitCircle::RotationDirection directionOfRotation;
	};
}
