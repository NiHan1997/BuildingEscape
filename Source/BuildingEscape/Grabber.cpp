// Light's NiHan in 2019.


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

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
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPhysicsHandleComponent 组件成功获取"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s 缺少 UPhysicsHandleComponent 组件"), *GetOwner()->GetName());
	}
}

void UGrabber::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent 组件成功获取"));

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

	FHitResult hitResult = PlayerLineTrace();
	if (hitResult.Actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("射线检测碰撞的物体是: %s"), *hitResult.Actor->GetName());
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release 方法执行!"));
}

FHitResult UGrabber::PlayerLineTrace() const
{	
	// 获取当前视口的位置和旋转.
	FVector playerLocation;
	FRotator playerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);

	// 绘制测试射线.
	FVector lineTraceEnd = playerLocation + playerRotation.Vector() * 1000;
	/*DrawDebugLine(GetWorld(), playerLocation, lineTraceEnd,
		FColor::Red, false, 0.0f, 0, 5.0f);*/

		// 射线检测碰撞逻辑.
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByObjectType(OUT hitResult, playerLocation, lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),	// 射线检测的碰撞层.
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));			// 射线检测忽略的对象.

	return hitResult;
}
