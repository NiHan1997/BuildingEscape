// Light's NiHan in 2019.


#include "DoorOpen.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
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
	OpenDoorActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (OpenDoorActor != nullptr && OpenDoorTrigger->IsOverlappingActor(OpenDoorActor))
	{
		GetOwner()->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
}

void UDoorOpen::CloseDoor()
{
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		if (OpenDoorActor != nullptr && OpenDoorTrigger->IsOverlappingActor(OpenDoorActor) == false)
		{			
			GetOwner()->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}
