#pragma once

#include "CoreMinimal.h"
#include "DialoguePromptTypes.h"
#include "Dialogue/NarrativeDialogueTypes.h"


/**
 * Utility class responsible for converting a dialogue request
 * and narrative context into a structured LLM prompt.
 *
 * This class performs no AI calls and owns no state.
 */

class NARRATIVEAITOOLS_UE_API FDialoguePromptBuilder
{

public:
	static FDialoguePrompt BuildPrompt(const FDialogueRequest& Request);

private:

	static FString BuildSystemPrompt(const FDialogueRequest& Request);
	static FString BuildUserPrompt(const FDialogueRequest& Request);

	// Converts the mood enum into natural language for prompt usage
	static FString MoodToText(ENPCNarrativeMood Mood);
	// Converts an intent enum into natural language for prompt usage
	static FString IntentToText(EDialogueIntent Intent);
};
