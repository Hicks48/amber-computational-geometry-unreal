#pragma once

#include "../MovementConfiguration.h"

#include "Math/Vector2D.h"

namespace AmberScience::MotionPlanning::Trajectories {

	class ITrajectory {
		public:
			ITrajectory() = default;
			~ITrajectory() = default;

			virtual FVector2D GetStartPosition() const = 0;
			virtual FVector2D GetEndPosition() const = 0;
			virtual float GetLength() const = 0;

			virtual MovementConfiguration GetMovementConfiguration(const float travelDistance) const = 0;
	};
}

