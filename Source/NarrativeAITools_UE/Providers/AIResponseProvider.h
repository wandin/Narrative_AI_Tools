// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "Dialogue/NarrativeDialogueTypes.h"
#include "UObject/Object.h"
#include "AIResponseProvider.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIResponseReady,const FDialogueResponse&, Response);

/**
* Base class for all dialogue response providers.
*
* Providers are responsible only for generating dialogue responses
* based on a request. They do NOT own gameplay state.
*/

UCLASS(Abstract, Blueprintable)
class NARRATIVEAITOOLS_UE_API UAIResponseProvider : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category="Narrative|AI")
	FDialogueResponse GenerateResponse(const FDialogueRequest& Request);

	UPROPERTY(BlueprintAssignable)
	FAIResponseReady OnResponseReady;
};
