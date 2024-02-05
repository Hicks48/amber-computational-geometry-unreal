#include "./Journey.h"

#include "./SimpleJourney.h"
#include "../MovementConfiguration.h"

#include <vector>

namespace AmberScience::MotionPlanning {
	
	Journey::Journey() : simpleJourneys(std::vector<SimpleJourney>{}), currentJourneyIndex(0) {}

	Journey::Journey(const std::vector<SimpleJourney>& journeys) : simpleJourneys(journeys), currentJourneyIndex(0) {}

	bool Journey::IsAtTheEnd() const {

		if (this->simpleJourneys.size() == 0) {
			return true;
		}

		if (this->currentJourneyIndex < this->simpleJourneys.size() - 1) {
			return false;
		}

		return this->simpleJourneys[this->currentJourneyIndex].IsAtEnd();
	}

	float Journey::GetLength() const {
		auto length = 0.0F;
		
		for (const auto& simpleJourney : this->simpleJourneys) {
			length += simpleJourney.GetLength();
		}

		return length;
	}

	float Journey::GetRemainingDistance() const {
		auto remainingDistance = 0.0F;

		for (auto i = this->currentJourneyIndex; i < this->simpleJourneys.size(); i++) {
			remainingDistance += this->simpleJourneys[i].GetRemainingDistance();
		}

		return remainingDistance;
	}

	const std::vector<SimpleJourney>& Journey::GetSimpleJourneys() const {
		return this->simpleJourneys;
	}

	std::vector<SimpleJourney> Journey::GetRemainingSimpleJourneys() const {
		auto remainingSimpleJourneys = std::vector<SimpleJourney>{};
		for (auto i = this->currentJourneyIndex; i < this->simpleJourneys.size(); i++) {
			remainingSimpleJourneys.push_back(this->simpleJourneys[i]);
		}

		return remainingSimpleJourneys;
	}

	MovementConfiguration Journey::Advance(const float deltaDistance) {

		if (this->simpleJourneys.size() == 0) {
			return MovementConfiguration{};
		}

		auto& currentSimpleJourney = this->simpleJourneys[this->currentJourneyIndex];

		auto isOverCurrentJourney = currentSimpleJourney.GetRemainingDistance() < deltaDistance;
		if (!isOverCurrentJourney) {
			return currentSimpleJourney.Advance(deltaDistance);
		}

		if (this->currentJourneyIndex < this->simpleJourneys.size() - 1) {
			this->currentJourneyIndex++;
			auto nextJourney = this->simpleJourneys[this->currentJourneyIndex];
			return nextJourney.Advance(deltaDistance - currentSimpleJourney.GetRemainingDistance());
		}

		// Is at the end since is over current trajectory and does not have a next one so just advance the last one.
		return currentSimpleJourney.Advance(deltaDistance);
	}
}
