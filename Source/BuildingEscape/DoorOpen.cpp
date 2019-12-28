// Light's NiHan in 2019.


#include "DoorOpen.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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
	// 防止开门逻辑反复执行.
	if (IsDoorOpen)
		return;

	OpenDoorActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (OpenDoorActor != nullptr && OpenDoorTrigger->IsOverlappingActor(OpenDoorActor))
	{
		FRotator rotation(0.0f, OpenAngle, 0.0f);
		GetOwner()->SetActorRotation(rotation);

		IsDoorOpen = true;
	}
}

void UDoorOpen::CloseDoor()
{
	// 防止关门逻辑反复执行.
	if (IsDoorOpen == false)
		return;

	if (OpenDoorActor != nullptr && OpenDoorTrigger->IsOverlappingActor(OpenDoorActor) == false)
	{
		FRotator rotation(0.0f, 0.0f, 0.0f);
		GetOwner()->SetActorRotation(rotation);

		IsDoorOpen = false;
	}
}

