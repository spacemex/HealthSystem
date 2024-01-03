/*
 * Copyright (c) 2023 Space_Mex
 * 
 * All rights reserved.
 * 
 * This file is part of the HealthSystem Plugin.
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 * Proprietary and confidential.
 */
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEALTHSYSTEM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//Variables

	/**
	 * @var Health This Is The Current Health This Is What Is Changed WHen Actor Is Damaged (Default is MaxHealth).
	 * @var MaxHealth This Is The MaxHealth  This Is What The Default Starting Health Is And What Health Clamps To (Default is 100).
	 * @var RegenHealth This Is How You Would Enable Regenerating Of Health (Default Is True).
	 * @var HealthRegenSpeed This Is The HealthRegenSpeed This Is How Fast Your Players Will Regen Health (Default 2.5).
	 * @var RegenAfterDamagedDelay This Is The RegenAfterDamagedDelay This Is How Fast Your Players Will Start To Regen Health Again After Taking Damage (Requires RegenHealth To Be True Defaults To 10.0).
	 */

	// Health
	/**MaxHealth This Is The MaxHealth  This Is What The Default Starting Health Is And What Health Clamps To (Default is 100).*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "HealthSystem | Health")
	float MaxHealth = 100;
	
	/**Health This Is The Current Health This Is What Is Changed WHen Actor Is Damaged (Default is MaxHealth).*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "HealthSystem | Health")
	float Health = MaxHealth;
	
	
	/**RegenHealth This Is How You Would Enable Regenerating Of Health (Default Is True).*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "HealthSystem | Health")
	bool RegenHealth = true;

	/**HealthRegenSpeed This Is The HealthRegenSpeed This Is How Fast Your Players Will Regen Health (Default 2.5)*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "HealthSystem | Health")
	float HealthRegenSpeed = 2.5;

	// Misc
	
	/**RegenAfterDamagedDelay This Is The RegenAfterDamagedDelay
	 *This Is How Fast Your Players Will Start To Regen Health
	 *Again After Taking Damage (Requires RegenHealth To Be True Defaults To 10.0).*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HealthSystem | Timers | Delays")
	float RegenAfterDamagedDelay = 10.0;

	/**
	* @var Armor This Is The Current Armor This Is What Is Changed When Actor Is Damaged (Default is 0).
	* @var MaxArmor This Is The MaxArmor  This Is And What Health Clamps To (Default is 50).
	* @var RegenArmor This Is How You Would Enable Regenerating Of Armor (Default Is false).
	* @var ArmorRegenSpeed This Is The ArmorRegenSpeed This Is How Fast Your Players Will Regen Armor (Default 5.5).
	 */


	// Armor
	
	/**MaxArmor This Is The MaxArmor  This Is And What Health Clamps To (Default is 50).*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "HealthSystem | Armor")
	float MaxArmor = 50;

	/**Armor This Is The Current Armor This Is What Is Changed When Actor Is Damaged (Default is 0).*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "HealthSystem | Armor")
	float Armor = 0;
	
	/**RegenArmor This Is How You Would Enable Regenerating Of Armor (Default Is false).*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "HealthSystem | Armor")
	bool RegenArmor = false;

	/**ArmorRegenSpeed This Is The ArmorRegenSpeed This Is How Fast Your Players Will Regen Armor (Default 5.5)*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "HealthSystem | Armor")
	float ArmorRegenSpeed = 5.5;

	


	//Functions

	/**Set The CurrentHealth*/
	UFUNCTION(BlueprintCallable, Category = "HealthSystem | Health")
	void SetHealth(float NewHealth);

	/**Set The MaxHealth*/
	UFUNCTION(BlueprintCallable, Category = "HealthSystem | Health")
	void SetMaxHealth(float NewMaxHealth);

	/**Sets CanRegenHealth*/
	UFUNCTION(BlueprintCallable, Category = "HealthSystem | Health")
	void SetRegenHealth(bool NewRegenHealth);

	/**Sets The HealthRegenSpeed*/
	UFUNCTION(BlueprintCallable, Category = "HealthSystem | Health")
	void SetHealthRegen(float NewRegenSpeed);


	/**Set The CurrentArmor*/
	UFUNCTION(BlueprintCallable, Category = "HealthSystem | Health")
	void SetArmor(float NewArmor);

	/**Set The MaxArmor*/
	UFUNCTION(BlueprintCallable, Category = "HealthSystem | Health")
	void SetMaxArmor(float NewMaxArmor);

	/**Sets CanRegenArmor*/
	UFUNCTION(BlueprintCallable, Category = "HealthSystem | Health")
	void SetRegenArmor(bool NewRegenArmor);

	/**Sets The ArmorRegenSpeed*/
	UFUNCTION(BlueprintCallable, Category = "HealthSystem | Health")
	void SetArmorRegen(float NewRegenSpeed);



	/**Actual Function To Deal Damage*/
	UFUNCTION(BlueprintCallable, Category = "HealthSystem | Damage")
	void Damage(float AfflictedDamage);

	UFUNCTION(BlueprintCallable,Category = "HealthSystem | Main")
	void AddHealthAndArmor(float HealthAmount, float ArmorAmount);

private:
	FTimerHandle HealthRegenTimerHandle;
	FTimerHandle ArmorRegenTimerHandle;

	void RegenerateArmor();
	void RegenerateHealth();
	void RegenArmorTimer();
	void RegenHealthTimer();

};
