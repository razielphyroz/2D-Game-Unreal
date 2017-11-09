// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyProjectile.h"
#include "User.h"

void AEnemyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(AUser::StaticClass())) {
		Destroy();
	}
}