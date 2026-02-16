// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "AIResponseProvider.h"
#include "LLMResponseProvider.generated.h"

/**
 * Concrete AIResponseProvider that communicates with a local
 * LLM server (e.g. LM Studio) via HTTP.
 */

UCLASS(Blueprintable)
class NARRATIVEAITOOLS_UE_API ULLMResponseProvider : public UAIResponseProvider
{
	GENERATED_BODY()

public:
	virtual FDialogueResponse GenerateResponse_Implementation(const FDialogueRequest& Request) override;

protected:
	FString BuildRequestBody(const FString& SystemPrompt, const FString& UserPrompt) const;

	FString ExtractAssistantText(const FString& JsonResponse) const;
};
