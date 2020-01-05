// Light's NiHan in 2019.


#include "DoorOpen.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OpenDoor();
	CloseDoor();
}

void UDoorOpen::OpenDoor()
{
	if (GetTotalMassOnTrigger() > 40)
	{
		OnOpenRequest.Broadcast();
	}
}

void UDoorOpen::CloseDoor()
{
	if (GetTotalMassOnTrigger() <= 40)
	{
		OnCloseRequest.Broadcast();
	}
}

float UDoorOpen::GetTotalMassOnTrigger() const
{
	float TotalMass = 0.0f;

	// 获取触发器中所有的物体, 遍历获取质量.
	TArray<AActor*> OverlappingActores;
	if (OpenDoorTrigger != nullptr)
		OpenDoorTrigger->GetOverlappingActors(OUT OverlappingActores);

	for (const auto& Actor : OverlappingActores)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}
