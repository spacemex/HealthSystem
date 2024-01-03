/*
 * Copyright (c) 2023 Space_Mex
 * 
 * All rights reserved.
 * 
 * This file is part of the HealthSystem Plugin.
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 * Proprietary and confidential.
 */


#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

void UHealthComponent::SetRegenHealth(bool NewRegenHealth)
{
	RegenHealth = NewRegenHealth;
}

void UHealthComponent::SetHealthRegen(float NewRegenSpeed)
{
	HealthRegenSpeed = NewRegenSpeed;
}

void UHealthComponent::SetArmor(float NewArmor)
{
	Armor = NewArmor;
}

void UHealthComponent::SetMaxArmor(float NewMaxArmor)
{
	MaxArmor = NewMaxArmor;
}

void UHealthComponent::SetRegenArmor(bool NewRegenArmor)
{
	RegenArmor = NewRegenArmor;
}

void UHealthComponent::SetArmorRegen(float NewRegenSpeed)
{
	ArmorRegenSpeed = NewRegenSpeed;
}

void UHealthComponent::Damage(float AfflictedDamage)
{
	if (Armor > AfflictedDamage)
	{
		Armor -= AfflictedDamage;
		
		GetWorld()->GetTimerManager().ClearTimer(ArmorRegenTimerHandle);

		GetWorld()->GetTimerManager().SetTimer(ArmorRegenTimerHandle,this,
	&UHealthComponent::RegenArmorTimer,RegenAfterDamagedDelay, false);

	}
	else
	{
		float DamageAfterArmor = AfflictedDamage - Armor;
		Armor = 0.0;

		Health = FMath::Clamp(Health - DamageAfterArmor, 0.0, MaxHealth);
		
		GetWorld()->GetTimerManager().ClearTimer(HealthRegenTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(ArmorRegenTimerHandle);


		if (RegenHealth && RegenArmor)
		{
			GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle,this,
				&UHealthComponent::RegenHealthTimer,RegenAfterDamagedDelay, false);
			
			GetWorld()->GetTimerManager().SetTimer(ArmorRegenTimerHandle,this,
				&UHealthComponent::RegenArmorTimer,RegenAfterDamagedDelay, false);
		} else if (RegenArmor)
		{
			GetWorld()->GetTimerManager().SetTimer(ArmorRegenTimerHandle,this,
				&UHealthComponent::RegenArmorTimer,RegenAfterDamagedDelay, false);
		} else if (RegenHealth)
		{
			GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle,this,
				&UHealthComponent::RegenHealthTimer,RegenAfterDamagedDelay, false);
		}
	}
}

void UHealthComponent::AddHealthAndArmor(float HealthAmount, float ArmorAmount)
{
	Health = FMath::Clamp(Health + HealthAmount,0,MaxHealth);
	Armor = FMath::Clamp(Armor + ArmorAmount,0,MaxArmor);
}

void UHealthComponent::RegenArmorTimer()
{
	if (RegenArmor)
	{
		GetWorld()->GetTimerManager().SetTimer(ArmorRegenTimerHandle, this,
			&UHealthComponent::RegenerateArmor, ArmorRegenSpeed,true);
	}
	
}

void UHealthComponent::RegenHealthTimer()
{
	if (RegenHealth)
	{
		GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle,this,
			&UHealthComponent::RegenerateHealth, HealthRegenSpeed,true);
	}
	
}

void UHealthComponent::RegenerateArmor()
{
	if (RegenArmor && Armor < MaxArmor)
	{
		Armor = FMath::Clamp(Armor + 1.0f, 0.0f,MaxArmor);
	}
}

void UHealthComponent::RegenerateHealth()
{
	if (RegenHealth && Health < MaxHealth)
	{
		Health = FMath::Clamp(Health + 1.0f,0.0f,MaxHealth);
	}
}