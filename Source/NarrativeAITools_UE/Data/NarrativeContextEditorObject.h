// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "Context/DialogueContextTypes.h"
#include "UObject/Object.h"
#include "NarrativeContextEditorObject.generated.h"

/**
 * Editor-only object used as a transient buffer
 * to author narrative context via DetailsView.
 *
 * Values are explicitly applied back to runtime
 * DialogueContextComponents.
 */
UCLASS(BlueprintType)
class NARRATIVEAITOOLS_UE_API UNarrativeContextEditorObject : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Narrative|Mood")
	ENPCNarrativeMood NPCMood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Narrative|Constraints")
	FGameplayTagContainer AllowedTopics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Narrative|Constraints")
	FGameplayTagContainer ForbiddenTopics;
};
