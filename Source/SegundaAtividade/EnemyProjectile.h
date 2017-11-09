// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "EnemyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SEGUNDAATIVIDADE_API AEnemyProjectile : public AProjectile
{
	GENERATED_BODY()
	
	
private:

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
