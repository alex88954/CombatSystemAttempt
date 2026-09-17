// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"

void UHealthBar::SetDamageable(TScriptInterface<IDamageable> InDamageable)
{
	Damageable = InDamageable;
	if (ACharacterBase* Char = Cast<ACharacterBase>(Damageable.GetObject()))
	{
		Char->OnHealthChanged.BindUObject(this, &UHealthBar::UpdateHealth);
	}
	UpdateHealth(GetHealthPercent());
}

void UHealthBar::UpdateHealth(float NewPercent)
{
	if (ProgressBar) 
	{
		ProgressBar->SetPercent(NewPercent);
	}
}

float UHealthBar::GetHealthPercent()
{
	if (Damageable)
	{
		float Current = Damageable->Execute_GetCurrentHealth(Damageable.GetObject());
		float Max = Damageable->Execute_GetMaxHealth(Damageable.GetObject());
		return Current / Max;
	}

	return 0.0f;
}
