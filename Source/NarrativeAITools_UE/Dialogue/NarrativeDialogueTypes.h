// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "Context/DialogueContextTypes.h"

#include "NarrativeDialogueTypes.generated.h"

/**
 * High-level narrative intent behind a dialogue request.
 * Intentionally coarse-grained to preserve authorial control.
 */
UENUM(BlueprintType)
enum class EDialogueIntent : uint8
{
	Greeting		UMETA(DisplayName = "Greeting"),
	SmallTalk		UMETA(DisplayName = "SmallTalk"),
	Quest			UMETA(DisplayName = "Quest"),
	Information		UMETA(DisplayName = "Information"),
	Reaction		UMETA(DisplayName = "Reaction")
};

/*
 * Represents a single dialogue request constructed
 * from narrative context and player intent.
 */
USTRUCT(BlueprintType)
struct FDialogueRequest
{
	GENERATED_BODY()

public:
	
	/* Narrative intent of this interaction*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	EDialogueIntent Intent = EDialogueIntent::Greeting;

	/* Explicit narrative context snapshot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	FNarrativeDialogueContext Context;

	/* Topics the player is explicitly attempting to discuss */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	FGameplayTagContainer RequestedTopics;

	/* Optional debug notes (tooling only) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
	FString DebugNotes;
};


USTRUCT(BlueprintType)
struct FDialogueResponse
{
	GENERATED_BODY()

public:

	/* Final dialogue line presented to the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	FText DialogueText;

	/* Whether the response passed validation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	bool bIsValid = true;

	/* Topics referenced by this response */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	FGameplayTagContainer UsedTopics;

	/* Narrative tags to be applied after this interaction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	FGameplayTagContainer ResultingNarrativeTags;

	/* Optional failure or validation reason */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
	FString ValidationMessage;
};