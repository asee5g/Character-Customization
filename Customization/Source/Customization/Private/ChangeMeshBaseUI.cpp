// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeMeshBaseUI.h"
#include "Kismet/GameplayStatics.h"
#include "CustomCharacter.h"
#include "Item_Base_Widget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/WrapBoxSlot.h"

void UChangeMeshBaseUI::NativeConstruct()
{
	Super::NativeConstruct();
    

    CurrentSelectedItem = nullptr;
}

void UChangeMeshBaseUI::PopulateItems(EItemType a_ItemType, int64& SelectedMeshID, int64 loadedSelectedID)
{
    
    if (!CharacterDataTable || !MyWrapBox)
    {
        UE_LOG(LogTemp, Error, TEXT("❌ Missing datatable or wrapbox"));
        return;
    }

    MyWrapBox->ClearChildren();

    const FString Context(TEXT("MeshData"));
    TArray<FCharacter_Base_Struct*> AllRows;
    CharacterDataTable->GetAllRows(Context, AllRows);

    ACustomCharacter* PlayerCharacter = Cast<ACustomCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    UE_LOG(LogTemp, Warning, TEXT("Checking Contains for type: %s"),
        *UEnum::GetValueAsString(a_ItemType));


    int32 Count = 0;
    for (auto Row : AllRows)
    {
        if (Row && Row->ItemType == a_ItemType)                                                                                                                        
        {
            Count++;
            UItem_Base_Widget* BaseWidget = CreateWidget<UItem_Base_Widget>(GetWorld(), WidgetClasstoSpawn);
            if (!BaseWidget)
            {
                UE_LOG(LogTemp, Error, TEXT("❌ Failed to create item widget instance"));
                continue;
            }

            BaseWidget->ItemMeshStruct = *Row;
            BaseWidget->CharacterDataTable = CharacterDataTable;

            if (BaseWidget->MeshImage && Row->ItemImage)
            {
                BaseWidget->MeshImage->SetBrushFromTexture(Row->ItemImage, true);
            }
            BaseWidget->OnItemSelected.AddDynamic(this, &UChangeMeshBaseUI::OnItemWidgetClicked);
            //SelectedMeshID->AllRows->ItemID;
            if (Row->ItemID == loadedSelectedID)
            {
                BaseWidget->SetSelectedItem(true);
                CurrentSelectedItem = BaseWidget;
                //BaseWidget->ImageSetUP();
                UE_LOG(LogTemp, Warning, TEXT("✔ Tick shown for ItemID: %lld"), Row->ItemID);
            }
            else
            {
                BaseWidget->SetSelectedItem(false);
            }
            MyWrapBox->AddChildToWrapBox(BaseWidget);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("✅ Created %d items for type %d and Itemid : %d"), Count, (int32)a_ItemType, SelectedMeshID);
}

void UChangeMeshBaseUI::OnItemWidgetClicked(UItem_Base_Widget* ClickedWidget)
{
    if (CurrentSelectedItem && CurrentSelectedItem != ClickedWidget)
    {
        CurrentSelectedItem->SetSelectedItem(false);
    }
    UE_LOG(LogTemp, Error, TEXT("🔥 OnItemWidgetClicked Fired! 🔥"));

    ClickedWidget->SetSelectedItem(true);
    CurrentSelectedItem = ClickedWidget;
}






