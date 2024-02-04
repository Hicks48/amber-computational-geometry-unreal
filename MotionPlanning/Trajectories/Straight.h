#pragma once

#include "./ITrajectory.h"
#include "../MovementConfiguration.h"

#include "Math/Vector2D.h"

namespace AmberScience::MotionPlanning::Trajectories {

	class Straight : public ITrajectory {
		public:
			Straight();
			Straight(const FVector2D& startPosition, const FVector2D& endPosition);
			~Straight() = default;

			FVector2D GetStartPosition() const final;
			FVector2D GetEndPosition() const final;
			float GetLength() const final;

			MovementConfiguration GetMovementConfiguration(const float travelDistance) const final;

		private:
			FVector2D startPosition;
			FVector2D endPosition;
	};

}
