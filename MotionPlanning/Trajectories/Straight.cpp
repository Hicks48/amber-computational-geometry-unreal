#include "./Straight.h"

#include "../MovementConfiguration.h"

#include "Math/Vector2D.h"

#include <cmath>

namespace AmberScience::MotionPlanning::Trajectories {
	
	Straight::Straight() : startPosition(FVector2D::ZeroVector), endPosition(FVector2D::ZeroVector) {}

	Straight::Straight(const FVector2D& startPosition, const FVector2D& endPosition) : startPosition(startPosition), endPosition(endPosition) {}

	FVector2D Straight::GetStartPosition() const {
		return this->startPosition;
	}

	FVector2D Straight::GetEndPosition() const {
		return this->endPosition;
	}

	float Straight::GetLength() const {
		return (this->endPosition - this->startPosition).Length();
	}

	MovementConfiguration Straight::GetMovementConfiguration(const float travelDistance) const {
		auto direction = (this->endPosition - this->startPosition).GetSafeNormal();
		auto position = this->startPosition + direction * std::min(travelDistance, this->GetLength());
		return MovementConfiguration{ position, direction };
	}
}
