#pragma once

#include "../MovementConstraints.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementConstraintsProvider.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYSANDBOX_API UMovementConstraintsProvider : public UActorComponent {
	GENERATED_BODY()

	public:	
		UMovementConstraintsProvider();
		
		AmberScience::MotionPlanning::MovementConstraints GetMovementConstraints() const;

	private:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Planning", meta = (AllowPrivateAccess = "true"))
		float TurningRadius;
};
