// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet\GameplayStatics.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



// Sets default values
ACustomCharacter::ACustomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    HairComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairComponent"));
    HairComponent->SetupAttachment(GetMesh());
    HairComponent->SetLeaderPoseComponent(GetMesh());

    ChestComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ChestComponent"));
    ChestComponent->SetupAttachment(GetMesh());
    ChestComponent->SetLeaderPoseComponent(GetMesh());

    HandComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandComponent"));
    HandComponent->SetupAttachment(GetMesh());
    HandComponent->SetLeaderPoseComponent(GetMesh());

    LegComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LegComponent"));
    LegComponent->SetupAttachment(GetMesh());
    LegComponent->SetLeaderPoseComponent(GetMesh());

}

// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
        FTimerHandle Timer;
        GetWorldTimerManager().SetTimer(Timer, [this]()
            {

            }, 0.2f, false);
    }
}

// Called every frame
void ACustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACustomCharacter::Move);
        EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACustomCharacter::Look);
        EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
    }
}

void ACustomCharacter::Move(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // get right vector 
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // add movement 
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ACustomCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}


void ACustomCharacter::ChangeMesh(EItemType ItemType, int64& SelectedItemId, USkeletalMesh*& MeshType)
{
	if (!ItemDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDataTable not assigned!"));
		return;
	}
    if (ItemType == EItemType::Hair)
    {
        static const FString Context(TEXT("HairDataLookup"));
        TArray<FCharacter_Base_Struct*> AllRows;
        ItemDataTable->GetAllRows<FCharacter_Base_Struct>(Context, AllRows);

        // Collect all hair items from DataTable
        TArray<FCharacter_Base_Struct*> HairRows;
        for (FCharacter_Base_Struct* Row : AllRows)
        {
            if (Row && Row->ItemType == EItemType::Hair && Row->ItemMesh)
            {
                HairRows.Add(Row);
            }
        }
        
        // No valid hair entries found
        if (HairRows.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("No valid hair items found in DataTable!"));
            return;
        }

        // Static index that cycles through available hairs
        static int32 CurrentHairIndex = -1;
        CurrentHairIndex = (CurrentHairIndex + 1) % HairRows.Num();

        FCharacter_Base_Struct* SelectedRow = HairRows[CurrentHairIndex];
        if (SelectedRow && SelectedRow->ItemMesh)
        {
            HairComponent->SetSkeletalMesh(SelectedRow->ItemMesh);
            SelectedItemId = SelectedRow->ItemID;
            //EquippedItemId.Add(ItemType, SelectedItemId);

            UE_LOG(LogTemp, Warning, TEXT("Hair changed to %s (ID: %d)"), *SelectedRow->ItemName, SelectedRow->ItemID);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid ItemMesh in row %d"), CurrentHairIndex);
        }
    }

	else if (ItemType == EItemType::Chest)
	{
        static const FString Context(TEXT("ChestDataLookup"));
        TArray<FCharacter_Base_Struct*> AllRows;
        ItemDataTable->GetAllRows<FCharacter_Base_Struct>(Context, AllRows);

        // Collect all hair items from DataTable
        TArray<FCharacter_Base_Struct*> ChestRows;
        for (FCharacter_Base_Struct* Row : AllRows)
        {
            if (Row && Row->ItemType == EItemType::Chest && Row->ItemMesh)
            {
                ChestRows.Add(Row);
            }
        }

        // No valid hair entries found
        if (ChestRows.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("No valid Chest items found in DataTable!"));
            return;
        }

        // Static index that cycles through available hairs
        static int32 CurrentChestIndex = -1;
        CurrentChestIndex = (CurrentChestIndex + 1) % ChestRows.Num();

        FCharacter_Base_Struct* SelectedRow = ChestRows[CurrentChestIndex];
        if (SelectedRow && SelectedRow->ItemMesh)
        {
            ChestComponent->SetSkeletalMesh(SelectedRow->ItemMesh);
            SelectedItemId = SelectedRow->ItemID;
            //EquippedItemId.Add(ItemType, SelectedItemId);

            UE_LOG(LogTemp, Warning, TEXT("Chest changed to %s (ID: %d)"), *SelectedRow->ItemName, SelectedRow->ItemID);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid ItemMesh in row %d"), CurrentChestIndex);
        }
	}
	else if (ItemType == EItemType::Hand)
	{
        static const FString Context(TEXT("HandDataLookup"));
        TArray<FCharacter_Base_Struct*> AllRows;
        ItemDataTable->GetAllRows<FCharacter_Base_Struct>(Context, AllRows);

        // Collect all hair items from DataTable
        TArray<FCharacter_Base_Struct*> HandRows;
        for (FCharacter_Base_Struct* Row : AllRows)
        {
            if (Row && Row->ItemType == EItemType::Hand && Row->ItemMesh)
            {
                HandRows.Add(Row);
            }
        }

        // No valid hair entries found
        if (HandRows.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("No valid Chest items found in DataTable!"));
            return;
        }

        // Static index that cycles through available hairs
        static int32 CurrentHandIndex = -1;
        CurrentHandIndex = (CurrentHandIndex + 1) % HandRows.Num();

        FCharacter_Base_Struct* SelectedRow = HandRows[CurrentHandIndex];
        if (SelectedRow && SelectedRow->ItemMesh)
        {
            HandComponent->SetSkeletalMesh(SelectedRow->ItemMesh);
            SelectedItemId = SelectedRow->ItemID;
            //EquippedItemId.Add(ItemType, SelectedItemId);

            UE_LOG(LogTemp, Warning, TEXT("Hand changed to %s (ID: %d)"), *SelectedRow->ItemName, SelectedRow->ItemID);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid ItemMesh in row %d"), CurrentHandIndex);
        }
	}
	else if (ItemType == EItemType::Leg)
	{
        static const FString Context(TEXT("LegDataLookup"));
        TArray<FCharacter_Base_Struct*> AllRows;
        ItemDataTable->GetAllRows<FCharacter_Base_Struct>(Context, AllRows);

        // Collect all hair items from DataTable
        TArray<FCharacter_Base_Struct*> LegRows;
        for (FCharacter_Base_Struct* Row : AllRows)
        {
            if (Row && Row->ItemType == EItemType::Leg && Row->ItemMesh)
            {
                LegRows.Add(Row);
            }
        }

        // No valid hair entries found
        if (LegRows.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("No valid Chest items found in DataTable!"));
            return;
        }

        // Static index that cycles through available hairs
        static int32 CurrentLegIndex = -1;
        CurrentLegIndex = (CurrentLegIndex + 1) % LegRows.Num();

        FCharacter_Base_Struct* SelectedRow = LegRows[CurrentLegIndex];
        if (SelectedRow && SelectedRow->ItemMesh)
        {
            LegComponent->SetSkeletalMesh(SelectedRow->ItemMesh);
            SelectedItemId = SelectedRow->ItemID;
            //EquippedItemId.Add(ItemType, SelectedItemId);

            UE_LOG(LogTemp, Warning, TEXT("Leg changed to %s (ID: %d)"), *SelectedRow->ItemName, SelectedRow->ItemID);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid ItemMesh in row %d"), CurrentLegIndex);
        }
	}

}


