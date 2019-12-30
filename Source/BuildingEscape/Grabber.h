// Light's NiHan in 2019.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

/// 角色的基本信息结构体.
struct PlayerTransform
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/// 获取搬运物体的工具组件.
	void FindPhysicsHandleComponent();

	/// 按键检测组件获取并绑定按键检测事件.
	void SetUpInputComponent();

	/// 搬运物体.
	void Grab();

	/// 放下物体.
	void Release();

	/// 获取射线的结尾.
	FVector GetLineTraceEnd();

	/// 射线检测逻辑.
	FHitResult PlayerLineTrace();

private:
	/// 角色的位置、旋转信息.
	PlayerTransform GrabberTransform;

	/// 搬运物体工具组件.
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	/// 鼠标键盘按键检测组件.
	UInputComponent* InputComponent = nullptr;
};
