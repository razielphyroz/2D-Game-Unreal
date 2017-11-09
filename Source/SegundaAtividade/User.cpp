// Fill out your copyright notice in the Description page of Project Settings.

#include "User.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "UserProjectile.h"

AUser::AUser()
{
	
	GetCapsuleComponent()->bGenerateOverlapEvents = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AUser::OnOverlapBegin);
	CollisionComp->SetupAttachment(RootComponent);

	Life = 5;
}

void AUser::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AUser::MoveLeftRight);
	PlayerInputComponent->BindAction("Shot", IE_Pressed, this, &AUser::Shot);
}

void AUser::MoveLeftRight(float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AUser::Shot()
{
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		AUserProjectile* Projectile = World->SpawnActor<AUserProjectile>(MyProjectile, GetActorLocation(), GetActorRotation(), SpawnParameters);
	}
}

void AUser::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && !OtherActor->IsA(AUserProjectile::StaticClass())) {
		Life--;
		UE_LOG(LogTemp, Warning, TEXT("Jogador Atingido."));
		if (Life <= 0) {
			UE_LOG(LogTemp, Warning, TEXT("Você Perdeu!"));
			GetWorld()->GetFirstPlayerController()->ConsoleCommand("exit");
			Destroy();
		}
	}
}

void AUser::IncreaseDestroyedEnemy()
{
	DestroyedEnemies++;
	if (DestroyedEnemies >= 16) {
		UE_LOG(LogTemp, Warning, TEXT("Parabéns!Você Ganhou!"));
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("exit");
	}
}
