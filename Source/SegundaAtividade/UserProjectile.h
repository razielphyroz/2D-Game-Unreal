// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "UserProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SEGUNDAATIVIDADE_API AUserProjectile : public AProjectile
{
	GENERATED_BODY()
	
	
protected:

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
