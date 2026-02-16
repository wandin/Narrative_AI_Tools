#pragma once

#include "CoreMinimal.h"

#include "DialoguePromptTypes.generated.h"

/**
 * Represents a fully constructed prompt sent to the LLM.
 * This struct is a pure data container (no logic).
 */

USTRUCT(BlueprintType)
struct FDialoguePrompt
{
	GENERATED_BODY()

public:

	// System-level instruction (who the NPC is, rules, constraints)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Narrative|Prompt")
	FString System;

	// User-level request (what the player just did / asked)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Narrative|Prompt")
	FString User;
};
