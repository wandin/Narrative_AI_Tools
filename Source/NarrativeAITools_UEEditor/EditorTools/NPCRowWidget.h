// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Characters/NarrativeNPCCharacter.h"

#include "NPCRowWidget.generated.h"

/**
 * Editor-only widget that represents a single NPC row
 * in the Narrative Editor UI.
 *
 * Responsible only for:
 * - Displaying basic NPC information (name/label)
 * - Emitting a selection event when clicked
 *
 * This widget contains no editing logic.
 */

class UTextBlock;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNPCSelected, ANarrativeNPCCharacter*, NPC);

UCLASS(Abstract, Blueprintable)
class NARRATIVEAITOOLS_UEEDITOR_API UNPCRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category="NPC")
	TObjectPtr<ANarrativeNPCCharacter> NPC;

	UPROPERTY(BlueprintAssignable, Category="NPC")
	FOnNPCSelected OnNPCSelected;

	UFUNCTION(BlueprintCallable)
	void SetNPC(ANarrativeNPCCharacter* NewNPC);

	UFUNCTION(BlueprintCallable)
	void HandleClicked();

protected:

	UPROPERTY(meta=(BindWidget))
	UTextBlock* NPCNameText;
};
