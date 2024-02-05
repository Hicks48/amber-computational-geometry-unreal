#pragma once

#include "../Trajectories/ITrajectory.h"
#include "../MovementConfiguration.h"

#include <memory>

namespace AmberScience::MotionPlanning {

	class SimpleJourney {
		public:
			SimpleJourney();
			SimpleJourney(std::shared_ptr<Trajectories::ITrajectory> trajectory);
			~SimpleJourney() = default;

			bool IsAtEnd() const;
			float GetCurrentCurrentDistanceOnTrajectory() const;
			float GetRemainingDistance() const;
			float GetLength() const;

			std::shared_ptr<const Trajectories::ITrajectory> GetTrajectory() const;

			MovementConfiguration Advance(const float deltaDistance);

		private:
			std::shared_ptr<Trajectories::ITrajectory> trajectory;
			float currentDistanceOnTrajectory;
	};
}
