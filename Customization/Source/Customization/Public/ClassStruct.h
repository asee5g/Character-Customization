#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "ClassStruct.generated.h"
/**
 *
 */

UENUM(BluePrintType)

enum class EItemType : uint8
{
    Hair UMETA(DisplayName = "Hair"),
    Chest UMETA(DisplayName = "Chest"),
    Hand UMETA(DisplayName = "Hand"),
    Leg UMETA(DisplayName = "Leg")
};




USTRUCT(BlueprintType)
struct FCharacter_Base_Struct : public FTableRowBase // Inherit from FTableRowBase for DataTable
{
    GENERATED_BODY()

public:
    // Example properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int64 ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    FString ItemName;

    // Reference to Static Mesh
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    USkeletalMesh* ItemMesh;

    //Add Image in Structure
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    UTexture2D* ItemImage;

    // Description
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    EItemType ItemType;


};

