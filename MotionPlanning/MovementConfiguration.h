#pragma once

#include "Math/Vector2D.h"

namespace AmberScience::MotionPlanning {

	struct MovementConfiguration {
		FVector2D Position = FVector2D::ZeroVector;
		FVector2D Heading = FVector2D{ 1.0F, 0.0F };
	};
}
