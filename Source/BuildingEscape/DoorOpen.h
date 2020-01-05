// Light's NiHan in 2019.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

	/// 获取触发器中所有物体的质量.
	float GetTotalMassOnTrigger() const;

public:
	/// 蓝图开门事件.
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpenRequest;

	/// 蓝图关门事件.
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnCloseRequest;

private:
	/// 开门的触发器.
	UPROPERTY(EditAnywhere)
	ATriggerVolume* OpenDoorTrigger = nullptr;
};
