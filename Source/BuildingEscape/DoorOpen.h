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
	/// �����߼�.
	void OpenDoor();

	/// �����߼�.
	void CloseDoor();

private:
	/// ���ŵĽǶ�.
	UPROPERTY(EditAnywhere)
	float OpenAngle = -70.0f;

	/// ���ŵĴ�����.
	UPROPERTY(EditAnywhere)
	ATriggerVolume* OpenDoorTrigger = nullptr;

	/// ������Ҫ�����Ľ�ɫ.
	AActor* OpenDoorActor = nullptr;

	/// ��ǰ�Ƿ��Ѿ�����.
	bool IsDoorOpen = false;
};
