#include "./SimpleJourney.h"

#include "../Trajectories/ITrajectory.h"
#include "../MovementConfiguration.h"

#include <memory>
#include <cmath>

using namespace AmberScience::MotionPlanning::Trajectories;

namespace AmberScience::MotionPlanning {
	
	// Since in unreal the units are in meters the tolerance does not need to be too small.
	constexpr auto TOLERANCE = 0.0001F;

	SimpleJourney::SimpleJourney() : trajectory(nullptr), currentDistanceOnTrajectory(0.0F) {}

	SimpleJourney::SimpleJourney(std::shared_ptr<Trajectories::ITrajectory> trajectory) : trajectory(trajectory), currentDistanceOnTrajectory(0.0F) {}

	bool SimpleJourney::IsAtEnd() const {
		if (!this->trajectory) {
			return true;
		}

		return this->currentDistanceOnTrajectory >= this->trajectory->GetLength() - TOLERANCE;
	}

	float SimpleJourney::GetCurrentCurrentDistanceOnTrajectory() const {
		return this->currentDistanceOnTrajectory;
	}

	float SimpleJourney::GetRemainingDistance() const {
		if (!this->trajectory) {
			return 0.0F;
		}

		return this->trajectory->GetLength() - this->currentDistanceOnTrajectory;
	}

	float SimpleJourney::GetLength() const {
		if (!this->trajectory) {
			return 0.0F;
		}

		return this->trajectory->GetLength();
	}

	MovementConfiguration SimpleJourney::Advance(const float deltaDistance) {
		if (!this->trajectory) {
			return MovementConfiguration{};
		}

		this->currentDistanceOnTrajectory = std::min(this->currentDistanceOnTrajectory + deltaDistance, this->trajectory->GetLength());
		return this->trajectory->GetMovementConfiguration(this->currentDistanceOnTrajectory);
	}
}
