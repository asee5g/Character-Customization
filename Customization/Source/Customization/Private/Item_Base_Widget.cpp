// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Base_Widget.h"
#include "CustomCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "CustomCharacterFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/OverlaySlot.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"



void UItem_Base_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("Item Base Widget Called"));


	if (MeshButton)
	{
		// 🔹 Bind button click event
		MeshButton->OnClicked.AddDynamic(this, &UItem_Base_Widget::OnApplyMeshClicked);
		UE_LOG(LogTemp, Warning, TEXT("✅ MeshButton Bound Successfully: %s"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ MeshButton is NULL in %s"), *GetName());
	}
	if (SelectedImage)
	{
		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(SelectedImage->Slot))
		{
			OverlaySlot->SetPadding(FMargin(10.0f, 5.0f, 10.0f, 5.0f));
		}
		//SelectedImage->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("[%s] SelectedImage pointer valid - forced visible"), *GetName());
	}
	//ACustomCharacter* MyCharacter = Cast<ACustomCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//int64 Equippedid = -1;
	//if (MyCharacter && MyCharacter->EquippedItemId.Add(ItemMeshStruct.ItemType, ItemMeshStruct.ItemID))
	//{

	//}
}


void UItem_Base_Widget::OnApplyMeshClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("OnApplyMeshClicked Called"));
	if (!ItemMeshStruct.ItemMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Mesh Not Assigned"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked : Mesh Name %s"), *ItemMeshStruct.ItemName);

	ApplyMeshToCharacter(ItemMeshStruct.ItemID, ItemMeshStruct.ItemType);
	UE_LOG(LogTemp, Error, TEXT("Mesg Type : %s"), *UEnum::GetValueAsString(ItemMeshStruct.ItemType));
	OnItemSelected.Broadcast(this);
}


void UItem_Base_Widget::SetSelectedItem(bool bIsSelected)
{
	if (SelectedImage)
	{
		//UE_LOG(LogTemp, Error, TEXT("Selected Image Called.."));

		SelectedImage->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Display, TEXT("Set Selected Item Triggered"));
	}
}

void UItem_Base_Widget::ApplyMeshToCharacter(int64& SelectedItemId, EItemType& SelectedItemType)
{
	UE_LOG(LogTemp, Warning, TEXT("ApplyMeshToCharacter Called"));
	SelectedImage->SetVisibility(ESlateVisibility::Hidden);
	ACustomCharacter* MyCharacter = Cast<ACustomCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


	UE_LOG(LogTemp, Error, TEXT(" ItemId : %d, ItemType : %s"), SelectedItemId, *UEnum::GetValueAsString(SelectedItemType));

	if (!CharacterDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDataTable not assigned!"));
		return;
	}

	static const FString Context(TEXT("DataMeshUp"));
	TArray<FCharacter_Base_Struct*> AllRows;
	CharacterDataTable->GetAllRows<FCharacter_Base_Struct>(Context, AllRows);

	FCharacter_Base_Struct* SelectedRow = nullptr;
	for (FCharacter_Base_Struct* Row : AllRows)
	{
		if (Row && Row->ItemID == ItemMeshStruct.ItemID && Row->ItemMesh)
		{
			SelectedRow = Row;
			break;
		}
	}
	if (!SelectedRow )
	{
		UE_LOG(LogTemp, Error, TEXT("No valid items found in DataTable!"));
		return;
	}

	if (!MyCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Failed to get Player Character"));
		return;
	}
	switch (ItemMeshStruct.ItemType)
	{

	case EItemType::Hair:

		if (MyCharacter->HairComponent)
		{
			MyCharacter->HairComponent->SetSkeletalMesh(SelectedRow->ItemMesh);
			SelectedItemId = SelectedRow->ItemID;
			SelectedItemType = SelectedRow->ItemType;
			//MyCharacter->EquippedItemId.Add(SelectedItemType, SelectedItemId);

			UE_LOG(LogTemp, Warning, TEXT("Hair changed to: %s"), *SelectedRow->ItemName);
			UE_LOG(LogTemp, Warning, TEXT("Hair changed to: %d"), SelectedItemId);
			UE_LOG(LogTemp, Warning, TEXT("CHaracter Name : %s"), *MyCharacter->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ HairComponent is NULL!"));
		}
		break;

	case EItemType::Chest:

		if (MyCharacter->ChestComponent)
		{
			MyCharacter->ChestComponent->SetSkeletalMesh(SelectedRow->ItemMesh);
			SelectedItemId = SelectedRow->ItemID;
			SelectedItemType = SelectedRow->ItemType;
			//MyCharacter->EquippedItemId.Add(SelectedItemType, SelectedItemId);

			UE_LOG(LogTemp, Warning, TEXT("hest changed to: %s"), *SelectedRow->ItemName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ ChestComponent is NULL!"));
		}
		break;

	case EItemType::Hand:

		if (MyCharacter->HandComponent)
		{
			MyCharacter->HandComponent->SetSkeletalMesh(SelectedRow->ItemMesh);
			SelectedItemId = SelectedRow->ItemID;
			SelectedItemType = SelectedRow->ItemType;
			//MyCharacter->EquippedItemId.Add(SelectedItemType, SelectedItemId);

			UE_LOG(LogTemp, Warning, TEXT("Hand changed to: %s"), *SelectedRow->ItemName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ HandComponent is NULL!"));
		}
		break;

	case EItemType::Leg:

		if (MyCharacter->LegComponent)
		{
			MyCharacter->LegComponent->SetSkeletalMesh(SelectedRow->ItemMesh);
			SelectedItemId = SelectedRow->ItemID;
			SelectedItemType = SelectedRow->ItemType;
			//MyCharacter->EquippedItemId.Add(SelectedItemType, SelectedItemId);

			UE_LOG(LogTemp, Warning, TEXT("Leg changed to: %s"), *SelectedRow->ItemName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ LegComponent is NULL!"));
		}
		break;
	default:
		break;
	}
	//ItemMeshStruct.ItemMesh = SelectedRow->ItemMesh;
	//ItemMeshStruct.ItemName = SelectedRow->ItemName;
	//ItemMeshStruct.ItemType = SelectedRow->ItemType;
	//ItemMeshStruct.ItemID = SelectedRow->ItemID;

	SelectedItemId = SelectedRow->ItemID;
	SelectedItemType = SelectedRow->ItemType;


	UE_LOG(LogTemp, Error, TEXT("Mesh Type : %s , Mesh ID : %d"), *UEnum::GetValueAsString(SelectedItemType), SelectedItemId);

	SetSelectedItem(true);
}
