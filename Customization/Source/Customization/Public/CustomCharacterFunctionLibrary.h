// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeshIdStruct.h"
#include "ClassStruct.h"
#include "CustomCharacterSave.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomCharacterFunctionLibrary.generated.h"

/**
 * 
 */

class ACustomCharacter; // Forward declaration

UCLASS()
class CUSTOMIZATION_API UCustomCharacterFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:


    UFUNCTION(BlueprintCallable, Category = "Customization")
    static void SaveCustomization(const FMeshIdStruct& MeshData, bool& bSaveGameExist, FMeshIdStruct& MeshSaveData);

	UFUNCTION(BlueprintCallable, Category = "Customization")
    static void LoadCustomization(FMeshIdStruct& LoadedMeshData, bool& SaveGameExist);

    UFUNCTION(BlueprintCallable, Category = "Customization")
    static void ApplyCustomization(const FMeshIdStruct& ApplyMeshData, ACustomCharacter* Character, UDataTable* a_DataTable);

    UFUNCTION(BlueprintCallable, Category = "Customization")
    static USkeletalMesh* GetMeshByItemId(UDataTable* a_DataTable, int64 a_meshID);

};


