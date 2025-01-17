// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerState.h"
#include "MyCppGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerCharacter.h"


// keys 
void AMainPlayerState::AddKey(FName id) {

	if (HasKey(id))
		return;
	Keys.Add(id);
}

bool AMainPlayerState::HasKey(FName id)
{
	return Keys.Contains(id);
}

// health 
void AMainPlayerState::AddHealth(float amount)
{
	CurrentHealth += amount;
	if (CurrentHealth >= MaxHealth) {
		CurrentHealth = MaxHealth;
		NeedHealth = false;
	}

	Cast<UMyCppGameInstance, UGameInstance>(GetGameInstance())
		->SetHealthHUDValueFromAmount(CurrentHealth, MaxHealth);
}

void AMainPlayerState::TakeDamageToHealth(float amount)
{
	CurrentHealth -= amount;
	if (CurrentHealth < MaxHealth)
		NeedHealth = true;
	if (CurrentHealth <= 0){
		/*UGameplayStatics::OpenLevel(GetWorld(), "Death");*/
		Cast<UMyCppGameInstance, UGameInstance>(GetGameInstance())->Die();
	}

	GetPawn<AMyPlayerCharacter>()->PlayHitSound();

	Cast<UMyCppGameInstance, UGameInstance>(GetGameInstance())
		->SetHealthHUDValueFromAmount(CurrentHealth, MaxHealth);
}

// mana 
void AMainPlayerState::AddMana(float amount)
{
	CurrentMana += amount;
	if (CurrentMana >= MaxMana) {
		CurrentMana = MaxMana;
		NeedMana = false;
	}

	Cast<UMyCppGameInstance, UGameInstance>(GetGameInstance())
		->SetManaHUDValueFromAmount(CurrentMana, MaxMana);
}


bool AMainPlayerState::UseMana(float amount)
{

	if (CurrentMana-amount < 0)
		return false;
	CurrentMana -= amount;
	if (CurrentMana < MaxMana)
		NeedMana = true;

	Cast<UMyCppGameInstance, UGameInstance>(GetGameInstance())
		->SetManaHUDValueFromAmount(CurrentMana, MaxMana);

	return  true;
}

// Handel collecting items
bool AMainPlayerState::HandelCollectableItem(ACollectable* item)
{
	
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, item->ID.ToString());
	if (item->ID == "Health") {

		if (!NeedHealth)
			return false;
		AddHealth(item->ValueAmount);
	}
	else if (item->ID == "Mana")
	{
		if (!NeedMana)
			return false;
		AddMana(item->ValueAmount);
	}

	return true;
}


