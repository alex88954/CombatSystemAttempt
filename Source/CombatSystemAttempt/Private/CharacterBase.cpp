// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/WidgetComponent.h"
#include "HealthBar.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DamageSystem = CreateDefaultSubobject<UDamageSystem>(TEXT("Damage System"));

	if (DamageSystem) {
		DamageSystem->OnDamageTaken.AddDynamic(this, &ACharacterBase::RespondToDamageTaken);
		DamageSystem->OnHealReceived.AddDynamic(this, &ACharacterBase::RespondToHealReceived);
		DamageSystem->OnDeath.AddDynamic(this, &ACharacterBase::RespondToDeath);
	}

	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBarComponent->SetupAttachment(RootComponent);
	HealthBarComponent->SetWidgetSpace(EWidgetSpace::World);
	HealthBarComponent->SetDrawSize(FVector2D(200.f, 20.f));
	HealthBarComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	HealthBarComponent->SetWidgetClass(HealthBarClass);
	HealthBarComponent->InitWidget();

	if (UUserWidget* Widget = HealthBarComponent->GetWidget())
	{
		if (UHealthBar* HealthBarWidget = Cast<UHealthBar>(Widget))
		{
			HealthBarWidget->SetDamageable(TScriptInterface<IDamageable>(this));
		}
	}
}

void ACharacterBase::RespondToDamageTaken_Implementation(float Damage)
{
	float Current = Execute_GetCurrentHealth(this);
	float Max = Execute_GetMaxHealth(this);
	float Percent = Current / Max;
	OnHealthChanged.ExecuteIfBound(Percent);

	/*if (UUserWidget* Widget = HealthBarComponent->GetWidget())
	{
		if (UHealthBar* Bar = Cast<UHealthBar>(Widget))
		{
			float Current = Execute_GetCurrentHealth(this);
			float Max = Execute_GetMaxHealth(this);
			float Percent = Current / Max;
			Bar->UpdateHealth(Percent);
		}
	}*/
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, "Took Damage");
	}
}

void ACharacterBase::RespondToHealReceived_Implementation(AActor* Healer, float Amount)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, "Received Heal");
	}
}

void ACharacterBase::RespondToDeath_Implementation()
{
	if (GetMesh())
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		if (APlayerController* PlayerC = Cast<APlayerController>(GetController()))
		{
			DisableInput(PlayerC);
		}
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, "Died");
	}
}

float ACharacterBase::GetMaxHealth_Implementation()
{
	return DamageSystem->GetMaxHealth();
}

float ACharacterBase::GetCurrentHealth_Implementation()
{
	return DamageSystem->GetCurrentHealth();
}

void ACharacterBase::TakeDamage_Implementation(float Damage)
{
	DamageSystem->HandleDamageTaken(Damage);
}

void ACharacterBase::ReceiveHeal_Implementation(AActor* Healer, float Amount)
{
	DamageSystem->HandleHealReceived(Healer, Amount);
}

void ACharacterBase::Attack()
{
	if (!GetWorld()) return;
	if (DamageSystem->GetIsDead()) return;
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * 150.f);
	float Radius = 50.f;

	TArray<FHitResult> HitResults;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	// Add the Pawn object type to the trace
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		Start,
		End,
		Radius,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResults,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.0f
	);

	if (bHit && HitResults.Num() > 0)
	{
		TArray<AActor*> DamageableActors;

		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor->Implements<UDamageable>())
			{
				if (!DamageableActors.Contains(HitActor))
				{
					DamageableActors.Add(HitActor);
				}
			}
		}

		for (AActor* DamageableActor : DamageableActors)
		{
			IDamageable::Execute_TakeDamage(DamageableActor, 25.f);
		}

		//UNiagaraFunctionLibrary::SpawnSystemAtLocation();
	}
}

