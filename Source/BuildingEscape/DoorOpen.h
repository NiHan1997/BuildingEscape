// Light's NiHan in 2019.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/// 开门逻辑.
	void OpenDoor();

	/// 关门逻辑.
	void CloseDoor();

private:
	/// 开门的角度.
	UPROPERTY(EditAnywhere)
	float OpenAngle = -70.0f;

	/// 开门的触发器.
	UPROPERTY(EditAnywhere)
	ATriggerVolume* OpenDoorTrigger = nullptr;

	/// 开门需要触发的角色.
	AActor* OpenDoorActor = nullptr;

	/// 当前是否已经开门.
	bool IsDoorOpen = false;
};
