#include "./MovementConfigurationProvider.h"

#include "Math/Vector2D.h"

UMovementConfigurationProvider::UMovementConfigurationProvider() {
	PrimaryComponentTick.bCanEverTick = false;
}

AmberScience::MotionPlanning::MovementConfiguration UMovementConfigurationProvider::GetMovementConfiguration() const {
	auto location = this->GetOwner()->GetActorLocation();
	auto heading = this->GetOwner()->GetActorForwardVector();

	return AmberScience::MotionPlanning::MovementConfiguration{
		FVector2D{ location.X, location.Y },
		FVector2D{ heading.X, heading.Y }
	};
}

void UMovementConfigurationProvider::SetMovementConfiguration(const AmberScience::MotionPlanning::MovementConfiguration& movementConfiguration) {
	auto location = this->GetOwner()->GetActorLocation();
	auto heading = this->GetOwner()->GetActorForwardVector();

	location.X = movementConfiguration.Position.X;
	location.Y = movementConfiguration.Position.Y;

	heading.X = movementConfiguration.Heading.X;
	heading.Y = movementConfiguration.Heading.Y;

	this->GetOwner()->SetActorLocation(location);
	this->GetOwner()->SetActorRotation(heading.Rotation());
}
