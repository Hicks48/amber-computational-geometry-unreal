#pragma once

#include "Math/Vector2D.h"

#include "../MovementConfiguration.h"
#include "../MovementConstraints.h"
#include "../Journey/Journey.h"

namespace AmberScience::MotionPlanning {
	// Plan for CS paths for which only the start configuration is provided and the end point is only a postion without the heading.
	Journey Plan(const MovementConfiguration& start, const FVector2D& end, const MovementConstraints& constraints);

	// Plan for CSC and CCC paths for which both end and start movement configurations are allowed.
	Journey Plan(const MovementConfiguration& start, const MovementConfiguration& end, const MovementConstraints& constraints);
}
