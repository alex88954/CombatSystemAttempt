// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "CharacterBase.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class COMBATSYSTEMATTEMPT_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;

public:
	UFUNCTION(BlueprintCallable)
	void SetDamageable(TScriptInterface<IDamageable> InDamageable);

protected:
	UPROPERTY()
	TScriptInterface<IDamageable> Damageable;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float NewPercent);

private:
	float GetHealthPercent();

};
