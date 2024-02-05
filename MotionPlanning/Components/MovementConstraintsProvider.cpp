#include "./MovementConstraintsProvider.h"

UMovementConstraintsProvider::UMovementConstraintsProvider() {
	PrimaryComponentTick.bCanEverTick = false;
	this->TurningRadius = 1.0F;
}

AmberScience::MotionPlanning::MovementConstraints UMovementConstraintsProvider::GetMovementConstraints() const {
	return AmberScience::MotionPlanning::MovementConstraints{ this->TurningRadius };
}
