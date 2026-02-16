// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "NPCRowWidget.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Characters/NarrativeNPCCharacter.h"
#include "Data/NarrativeContextEditorObject.h"

#include "EUW_NarrativeEditor.generated.h"

class UScrollBox;
class UDetailsView;
class UButton;

/**
 * Editor-only utility widget that allows designers to:
 * - Browse selected NPCs in the level
 * - Edit narrative context (mood, allowed/forbidden topics)
 * - Apply changes directly to NPC DialogueContextComponents
 */

UCLASS(Blueprintable)
class NARRATIVEAITOOLS_UEEDITOR_API UEUW_NarrativeEditor : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

private:

	UFUNCTION(BlueprintCallable)
	void RefreshSelection();

	UFUNCTION()
	void SetActiveNPC(ANarrativeNPCCharacter* NewNPC);

	UFUNCTION()
	void ApplyToActiveNPC();

	UFUNCTION()
	void RefreshEditorFromNPC();

protected:
	
	/** ScrollBox that lists NPC rows */
	UPROPERTY(meta=(BindWidget))
	UScrollBox* NPCListScrollBox;

	/** DetailsView that edits EditorContextObject */
	UPROPERTY(meta=(BindWidget))
	UDetailsView* DetailsView;

	UPROPERTY(meta=(BindWidget))
	UButton* ApplyButton;

	UPROPERTY(meta=(BindWidget))
	UButton* RefreshSelectionButton;
	
	UPROPERTY()
	TArray<TObjectPtr<ANarrativeNPCCharacter>> SelectedNPCs;

	UPROPERTY()
	TObjectPtr<ANarrativeNPCCharacter> ActiveNPC;

	UPROPERTY()
	TObjectPtr<UNarrativeContextEditorObject> EditorContextObject;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNPCRowWidget> NPCRowClass;
};