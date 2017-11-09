// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "User.generated.h"

/**
 * 
 */
UCLASS()
class SEGUNDAATIVIDADE_API AUser : public APaperCharacter
{
	GENERATED_BODY()

	AUser();
	
public:


	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void IncreaseDestroyedEnemy();

private:

	int16 DestroyedEnemies;

	void MoveLeftRight(float Value);
	
	UPROPERTY(EditAnywhere)
		int16 Life;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AUserProjectile> MyProjectile;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

	void Shot();

};
