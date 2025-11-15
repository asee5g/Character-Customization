// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CustomCharacter.h"

void UCustomCharacterFunctionLibrary::SaveCustomization(const FMeshIdStruct& MeshData, bool& bSaveGameExist, FMeshIdStruct& MeshSaveData)
{


    const FString SlotName = TEXT("CustomSlot");
    const int32 UserIndex = 0;

    bool l_SaveGameExist = UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex);

    if (l_SaveGameExist)
    {

        //creating
        UCustomCharacterSave* l_customSaveGameInstance = Cast<UCustomCharacterSave>(
            UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
        if (l_customSaveGameInstance != nullptr)
        {
            l_customSaveGameInstance->SavedMeshData = MeshData;

            UGameplayStatics::SaveGameToSlot(l_customSaveGameInstance, SlotName, UserIndex);
        }
    }

    else 
    {
        UCustomCharacterSave* l_customSaveGameInstance = Cast<UCustomCharacterSave>(
            UGameplayStatics::CreateSaveGameObject(UCustomCharacterSave::StaticClass()));

        if (l_customSaveGameInstance)
        {
            l_customSaveGameInstance->SavedMeshData = MeshData;

            UGameplayStatics::SaveGameToSlot(l_customSaveGameInstance, SlotName, UserIndex);
        }
    }

}

void UCustomCharacterFunctionLibrary::LoadCustomization(FMeshIdStruct& LoadedMeshData, bool& SaveGameExist)
{

	const FString SlotName = TEXT("CustomSlot");
	const int32 UserIndex = 0;


	bool l_SaveGameExist = UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex);

	//we have data
	if (l_SaveGameExist)
	{
		//creating
        UCustomCharacterSave* l_customSaveGameInstance = Cast<UCustomCharacterSave>(
			UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

		if (l_customSaveGameInstance != nullptr)
		{
            LoadedMeshData = l_customSaveGameInstance->SavedMeshData;
		}
	}


	else
	{
        UCustomCharacterSave* l_customSaveGameInstance = Cast<UCustomCharacterSave>(
			UGameplayStatics::CreateSaveGameObject(UCustomCharacterSave::StaticClass()));

		if (l_customSaveGameInstance)
		{
            l_customSaveGameInstance->SavedMeshData = LoadedMeshData;
			
			UGameplayStatics::SaveGameToSlot(l_customSaveGameInstance, SlotName, UserIndex);
		}
	}

    
}

void UCustomCharacterFunctionLibrary::ApplyCustomization(const FMeshIdStruct& ApplyMeshData, ACustomCharacter* Character, UDataTable* a_DataTable)
{
    if (!Character || !a_DataTable)
    {
        return;
    }
    if (Character->HairComponent)
    {
        if (USkeletalMesh* HairMesh = GetMeshByItemId(a_DataTable, ApplyMeshData.HairID))
        {
            Character->HairComponent->SetSkeletalMesh(HairMesh);
        }
    }
    if (Character->ChestComponent)
    {
        if (USkeletalMesh* ChestMesh = GetMeshByItemId(a_DataTable, ApplyMeshData.ChestID))
        {
            Character->ChestComponent->SetSkeletalMesh(ChestMesh);
        }
    }
    if (Character->HandComponent)
    {
        if (USkeletalMesh* HandMesh = GetMeshByItemId(a_DataTable, ApplyMeshData.HandID))
        {
            Character->HandComponent->SetSkeletalMesh(HandMesh);
        }
    }
    if (Character->LegComponent)
    {
        if (USkeletalMesh* LegMesh = GetMeshByItemId(a_DataTable, ApplyMeshData.LegID))
        {
            Character->LegComponent->SetSkeletalMesh(LegMesh);
        }
    }
}

USkeletalMesh* UCustomCharacterFunctionLibrary::GetMeshByItemId(UDataTable* a_DataTable, int64 a_meshID)
{
    if (!a_DataTable) return nullptr;

    TArray<FCharacter_Base_Struct*> AllRows;
    a_DataTable->GetAllRows(TEXT("GetMeshByItemId"), AllRows);

    for (auto* Rows : AllRows)
    {
        if (Rows && Rows->ItemID == a_meshID)
        {
            return Rows->ItemMesh;
        }
    }

    return nullptr;
}

