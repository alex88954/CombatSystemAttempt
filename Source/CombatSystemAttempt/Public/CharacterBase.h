// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Damageable.h"
#include "Components/WidgetComponent.h"
#include "DamageSystem.h"
#include "CharacterBase.generated.h"

class UHealthBar;

DECLARE_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS()
class COMBATSYSTEMATTEMPT_API ACharacterBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	virtual void BeginPlay() override;

public:
	TObjectPtr<UDamageSystem> DamageSystem = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HealthBarComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHealthBar> HealthBarClass;

public:
	FOnHealthChanged OnHealthChanged;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void RespondToDamageTaken(float Damage);
	virtual void RespondToDamageTaken_Implementation(float Damage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void RespondToHealReceived(AActor* Healer, float Amount);
	virtual void RespondToHealReceived_Implementation(AActor* Healer, float Amount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void RespondToDeath();
	virtual void RespondToDeath_Implementation();

	float GetMaxHealth_Implementation();
	float GetCurrentHealth_Implementation();
	void TakeDamage_Implementation(float Damage);
	void ReceiveHeal_Implementation(AActor* Healer, float Amount);

protected:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Attack();
};
