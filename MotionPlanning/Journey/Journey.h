#pragma once

#include "./SimpleJourney.h"
#include "../MovementConfiguration.h"

#include <vector>

namespace AmberScience::MotionPlanning {

	class Journey {
		public:
			Journey();
			Journey(const std::vector<SimpleJourney>& journeys);
			~Journey() = default;

			bool IsAtTheEnd() const;
			float GetLength() const;
			float GetRemainingDistance() const;

			const std::vector<SimpleJourney>& GetSimpleJourneys() const;
			std::vector<SimpleJourney> GetRemainingSimpleJourneys() const;

			MovementConfiguration Advance(const float deltaDistance);

		private:
			std::vector<SimpleJourney> simpleJourneys;
			std::vector<SimpleJourney>::size_type currentJourneyIndex;
	};
}
