// Narrative AI Tools – Wanderson Lopes (2025)

#include "DialogueOptionsWidget.h"

void UDialogueOptionsWidget::Init(UDialogueInteractionComponent* InInteractionComponent)
{
	DialogueInteractionComponent = InInteractionComponent;
	
	if (!DialogueInteractionComponent)
	{
		return;
	}
	
	DialogueInteractionComponent->OnDialogueResponseReceived.RemoveAll(this);
	DialogueInteractionComponent->OnDialogueResponseReceived.AddDynamic(this, &UDialogueOptionsWidget::HandleDialogueResponse);
}

void UDialogueOptionsWidget::NativeDestruct()
{
	if (DialogueInteractionComponent)
	{
		DialogueInteractionComponent->OnDialogueResponseReceived.RemoveAll(this);
	}
	Super::NativeDestruct();
}


void UDialogueOptionsWidget::HandleDialogueResponse_Implementation(const FDialogueResponse& Response)
{
	// Implemented on Blueprint.
}
