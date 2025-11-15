// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomCharacterSave.h"
#include "CustomCharacterFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "ClassStruct.h"
#include "Engine/DataTable.h"
#include "CustomizationCharacter.h"
#include "CustomCharacter.generated.h"


UCLASS()
class CUSTOMIZATION_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	USkeletalMeshComponent* HairComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	USkeletalMeshComponent* ChestComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	USkeletalMeshComponent* HandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	USkeletalMeshComponent* LegComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	TArray<FCharacter_Base_Struct> AllItems;


	UFUNCTION(BlueprintCallable, Category = "Customization")
	void ChangeMesh(EItemType ItemType,int64& SelectedItemId, USkeletalMesh*& MeshType);




};
