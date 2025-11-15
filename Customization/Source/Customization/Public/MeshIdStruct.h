#pragma once

#include "CoreMinimal.h"
#include "MeshIdStruct.generated.h"

USTRUCT(BlueprintType)
struct FMeshIdStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    int64 HairID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    int64 ChestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    int64 HandID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    int64 LegID;


};