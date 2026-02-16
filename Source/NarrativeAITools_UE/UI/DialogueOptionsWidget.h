// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dialogue/DialogueInteractionComponent.h"

#include "DialogueOptionsWidget.generated.h"

UCLASS()
class NARRATIVEAITOOLS_UE_API UDialogueOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/**
	 * Initializes the widget and binds to a dialogue interaction component.
	 * The widget does not own the component.
	 */
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void Init(UDialogueInteractionComponent* InInteractionComponent);

	virtual void NativeDestruct() override;
	
protected:

	UPROPERTY(BlueprintReadOnly, Category="Dialogue")
	TObjectPtr<UDialogueInteractionComponent> DialogueInteractionComponent;

	UFUNCTION(BlueprintNativeEvent, Category="Dialogue")
	void HandleDialogueResponse(const FDialogueResponse& Response);
};
