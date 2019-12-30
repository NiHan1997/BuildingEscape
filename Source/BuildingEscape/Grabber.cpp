// Light's NiHan in 2019.


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetUpInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent != nullptr)
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s 缺少 UPhysicsHandleComponent 组件"), *GetOwner()->GetName());
	}
}

void UGrabber::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent != nullptr)
	{
		// 绑定按键事件.
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s 缺少 InputComponent 组件"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab 方法执行!"));

	FHitResult HitResult = PlayerLineTrace();
	if (HitResult.Actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("射线检测碰撞的物体是: %s"), *HitResult.Actor->GetName());

		// 物体搬运逻辑.
		PhysicsHandle->GrabComponent(HitResult.GetComponent(), NAME_None,
			HitResult.GetComponent()->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release 方法执行!"));

	// 物品放下逻辑.
	if (PhysicsHandle != nullptr)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

FVector UGrabber::GetLineTraceEnd()
{
	// 获取当前视口的位置和旋转.
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT GrabberTransform.PlayerLocation,
		OUT GrabberTransform.PlayerRotation);

	// 绘制测试射线.
	FVector LineTraceEnd = GrabberTransform.PlayerLocation +
		GrabberTransform.PlayerRotation.Vector() * 100;
	/*DrawDebugLine(GetWorld(), GrabberTransform.PlayerLocation, LineTraceEnd,
		FColor::Red, false, 0.0f, 0, 5.0f);*/

	return LineTraceEnd;
}

FHitResult UGrabber::PlayerLineTrace()
{
	// 射线检测碰撞逻辑.
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GrabberTransform.PlayerLocation,
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),	// 射线检测的碰撞层.
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));			// 射线检测忽略的对象.

	return HitResult;
}
