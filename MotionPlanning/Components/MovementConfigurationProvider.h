#pragma once

#include "../MovementConfiguration.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementConfigurationProvider.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYSANDBOX_API UMovementConfigurationProvider : public UActorComponent {
	GENERATED_BODY()

	public:	
		UMovementConfigurationProvider();

		AmberScience::MotionPlanning::MovementConfiguration GetMovementConfiguration() const;
		void SetMovementConfiguration(const AmberScience::MotionPlanning::MovementConfiguration& movementConfiguration);
};
