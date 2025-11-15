// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeshIdStruct.h"
#include "GameFramework/SaveGame.h"
#include "CustomCharacterSave.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMIZATION_API UCustomCharacterSave : public USaveGame
{
	GENERATED_BODY()
	
public:

    UPROPERTY(BlueprintReadWrite, Category = "Customization")
    FMeshIdStruct SavedMeshData;


};
