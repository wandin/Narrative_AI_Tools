#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DialogueContextTypes.generated.h"


/*
 * High-level emotional or narrative stance of an NPC.
 * Intentionally coarse-grained to keep authorial control.
 */
UENUM(BlueprintType)
enum class ENPCNarrativeMood : uint8
{
	Neutral			UMETA(DisplayName = "Neutral"),
	Friendly		UMETA(DisplayName = "Friendly"),
	Hostile			UMETA(DisplayName = "Hostile"),
	Fearful			UMETA(DisplayName = "Fearful"),
	Curious			UMETA(DisplayName = "Curious")
};

/*
 * Represents all explicit narrative-relevant state
 * used to assist dialogue generation and validation.
 *
 * This struct is intentionally data-only.
 */
USTRUCT(BlueprintType)
struct FNarrativeDialogueContext
{
	GENERATED_BODY()

public:

	/* Narrative mood of the NPC at the moment of interaction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	ENPCNarrativeMood NPCMood = ENPCNarrativeMood::Neutral;

	/* Player-related narrative tags (reputation, affiliations, flags) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FGameplayTagContainer PlayerNarrativeTags;

	/* NPC-related narrative tags */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FGameplayTagContainer NPCNarrativeTags;

	/* World or quest state tags*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FGameplayTagContainer WorldStateTags;

	/* Topics that are explicitly allowed in this interaction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FGameplayTagContainer AllowedTopics;

	/* Topics that are explicitly forbidden in this interaction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narrative")
	FGameplayTagContainer ForbiddenTopics;

	/* Optional free-form notes for debugging and tooling (not used for logic) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	FString DebugNotes;
};
