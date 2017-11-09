// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SEGUNDAATIVIDADE_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLife(int8 NewLife);

	int8 GetLife();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* MySprite;

	UPROPERTY(EditAnywhere)
	int8 Life;

	int8 Direction;
	FVector InitialPos;
	int8 Vel;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* FriendDetector;

	void Move();
	void Shot();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemyProjectile> MyBulletBP;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
