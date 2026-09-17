// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageSystem.h"

void UDamageSystem::HandleDamageTaken(float Damage)
{
	if (IsDead) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage,0.f, MaxHealth );
	OnDamageTaken.Broadcast(Damage);

	if (CurrentHealth <= 0) {
		IsDead = true;
		OnDeath.Broadcast();
	}
}

void UDamageSystem::HandleHealReceived(AActor* Healer, float Amount)
{
	if (IsDead) return;

	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.0f, MaxHealth);
	OnHealReceived.Broadcast(Healer, Amount);
}
