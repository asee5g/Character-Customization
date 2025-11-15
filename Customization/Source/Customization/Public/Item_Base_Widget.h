// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Delegates/Delegate.h"
#include "Components/Button.h"
#include "ClassStruct.h"
#include "MeshIdStruct.h"
#include "Item_Base_Widget.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSelected, UItem_Base_Widget*, ClickedWidget);
/**
 * 
 */
UCLASS()
class CUSTOMIZATION_API UItem_Base_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FCharacter_Base_Struct ItemMeshStruct;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* MeshImage;


	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	UImage* SelectedImage;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ImageSetUP();


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MeshButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UDataTable* CharacterDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	USkeletalMeshComponent* MeshComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	FOnItemSelected OnItemSelected;

	UFUNCTION()
	void OnApplyMeshClicked();


	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetSelectedItem(bool bIsSelected);

	UFUNCTION(BlueprintCallable, Category = "Customization")
	void ApplyMeshToCharacter(int64& SelectedItemId, EItemType& SelectedItemType);
};
