// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "UserProjectile.h"
#include "EnemyProjectile.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "User.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FriendDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("Friend Detector"));
	FriendDetector->bGenerateOverlapEvents = false;
	FriendDetector->SetCollisionProfileName("OverlapAllDyamic");
	FriendDetector->SetRelativeLocation(FVector());
	FriendDetector->SetupAttachment(RootComponent);
	RootComponent = FriendDetector;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	MySprite->SetCollisionProfileName("OverlapAllDynamic");
	MySprite->bGenerateOverlapEvents = true;
	MySprite->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	MySprite->SetupAttachment(RootComponent);

	Vel = 3;
}


// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitialPos = GetActorLocation();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	Shot();
}

void AEnemy::Shot()
{
	int16 Luck = FMath::RandRange(0, 100);
	if (Luck == 0) {

		TArray<AActor*> OverlapedActors;
		FriendDetector->GetOverlappingActors(OverlapedActors);

		UWorld* World = GetWorld();
		if (World && OverlapedActors.Num() == 0) {
			FActorSpawnParameters SpawnParameters;
			AEnemyProjectile* Projectile = World->SpawnActor<AEnemyProjectile>(MyBulletBP, MySprite->GetComponentLocation(), GetActorRotation(), SpawnParameters);
		}
	}
}

void AEnemy::SetLife(int8 NewLife)
{
	Life = NewLife;
}

int8 AEnemy::GetLife()
{
	return Life;
}

void AEnemy::Move()
{
	if (Direction == 0) {
		SetActorLocation(FVector(GetActorLocation().X + Vel, GetActorLocation().Y, GetActorLocation().Z));
		if (GetActorLocation().X >= InitialPos.X + 250.0f) {
			Direction = 1;
			Vel += 0.2f;
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y + 50, GetActorLocation().Z));
		}
	} else {
		SetActorLocation(FVector(GetActorLocation().X - Vel, GetActorLocation().Y, GetActorLocation().Z));
		if (GetActorLocation().X <= InitialPos.X - 250.0f) {
			Direction = 0;
			Vel += 0.2f;
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y + 50, GetActorLocation().Z));
		}
	}
}
void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(AUserProjectile::StaticClass())) {
		Life--;
		if (Life <= 0) {
			UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
			AUser* User = Cast<AUser>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			User->IncreaseDestroyedEnemy();
			Destroy();
		}
	}
}