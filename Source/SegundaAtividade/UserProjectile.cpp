// Fill out your copyright notice in the Description page of Project Settings.

#include "UserProjectile.h"
#include "Enemy.h"


void AUserProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(AEnemy::StaticClass())) {
		Destroy();
	}
}