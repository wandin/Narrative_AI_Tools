// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "NarrativeDialogueTypes.h"
#include "Components/ActorComponent.h"
#include "Context/DialogueContextComponent.h"
#include "Providers/AIResponseProvider.h"
#include "DialogueInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueResponseReceived, const FDialogueResponse&, Response);

DECLARE_LOG_CATEGORY_EXTERN(LogDialogueInteractionComponent, Log, All);

/**
* Orchestrates a single dialogue interaction:
* - Builds the dialogue request
* - Dispatches it to a response provider
* - Broadcasts the resulting response
*
* This component contains no AI, networking, or UI logic.
*/

UCLASS(ClassGroup=(Narrative), meta=(BlueprintSpawnableComponent))
class NARRATIVEAITOOLS_UE_API UDialogueInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogueInteractionComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* Starts a dialogue interaction (async) */
	UFUNCTION(BlueprintCallable, Category="Narrative|Dialogue")
	void ExecuteDialogue(EDialogueIntent Intent);

	/* Last request (debug/tooling) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Narrative|Debug")
	FDialogueRequest LastDialogueRequest;

	/* Last response (debug/tooling) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Narrative|Debug")
	FDialogueResponse LastDialogueResponse;

	/* Fired when a dialogue response is ready */
	UPROPERTY(BlueprintAssignable, Category="Narrative|Dialogue")
	FOnDialogueResponseReceived OnDialogueResponseReceived;

protected:
	/* Dialogue context source (typically on the same actor) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Narrative")
	TObjectPtr<UDialogueContextComponent> DialogueContextComponent;

	/* Provider used to generate dialogue responses */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Narrative")
	TSubclassOf<UAIResponseProvider> ResponseProviderClass;

private:

	UFUNCTION()
	void HandleProviderResponse(const FDialogueResponse& Response);

	UAIResponseProvider* CreateProviderInstance();

	UPROPERTY()
	TObjectPtr<UAIResponseProvider> ActiveProvider;
};
