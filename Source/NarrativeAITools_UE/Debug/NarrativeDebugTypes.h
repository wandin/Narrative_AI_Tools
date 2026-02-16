#pragma once

#include "CoreMinimal.h"
#include "Dialogue/NarrativeDialogueTypes.h"

#include "NarrativeDebugTypes.generated.h"

/*
 * Represents a single recorded dialogue interaction
 * for debugging and analysis purposes.
 */

USTRUCT(BlueprintType)
struct FNarrativeDialogueDebugEntry
{
	GENERATED_BODY()

public:

	/* World time when the interaction occurred */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Debug")
	float Timestamp = 0.0f;

	/* Dialogue request Snapshot */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Debug")
	FDialogueRequest Request;

	/* Dialogue response snapshot */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Debug")
	FDialogueResponse Response;
};
