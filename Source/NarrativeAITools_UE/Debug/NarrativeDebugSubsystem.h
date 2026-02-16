// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "NarrativeDebugTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NarrativeDebugSubsystem.generated.h"

/**
 * Centralized narrative debugging subsystem
 * Records dialogue interactions for inspection and replay
 */
UCLASS()
class NARRATIVEAITOOLS_UE_API UNarrativeDebugSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	/* Record a dialogue interaction */
	UFUNCTION(BlueprintCallable, Category="Narrative|Debug")
	void RecordDialogueInteraction(const FDialogueRequest& Request, const FDialogueResponse& Response);

	/* Returns all recorded dialogue interactions */
	const TArray<FNarrativeDialogueDebugEntry>& GetDialogueHistory() const { return DialogueHistory;}

	/* Clears recorded history */
	UFUNCTION(BlueprintCallable, Category="Narrative|Debug")
	void ClearHistory();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Narrative|Debug")
	TArray<FNarrativeDialogueDebugEntry> DialogueHistory;
};
