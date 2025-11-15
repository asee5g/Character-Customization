// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClassStruct.h"
#include "Engine/Texture2D.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Item_Base_Widget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/DataTable.h"
#include "ChangeMeshBaseUI.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMIZATION_API UChangeMeshBaseUI : public UUserWidget
{
	GENERATED_BODY()


public:
    virtual void NativeConstruct() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    UDataTable* CharacterDataTable;

    UPROPERTY(meta = (BindWidget))
    UWrapBox* MyWrapBox;

    UPROPERTY(EditAnywhere, Category = "Customization")
    TArray<UButton*> DynamicButtons;

    UFUNCTION(BlueprintCallable, Category = "Customization")
    void PopulateItems(EItemType a_ItemType, int64& SelectedMeshID,int64 loadedSelectedID);

    
    UFUNCTION(BlueprintCallable, Category = "Customization")
    void OnItemWidgetClicked(UItem_Base_Widget* ClickedWidget);


    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> WidgetClasstoSpawn;
    
    

private:
    UPROPERTY();
    UItem_Base_Widget* CurrentSelectedItem;

};
