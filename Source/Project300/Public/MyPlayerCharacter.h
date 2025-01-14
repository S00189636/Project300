// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"


UCLASS()
class PROJECT300_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Seconds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Minutes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void PlayHitSound();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void OnCreateFootstep();
};
