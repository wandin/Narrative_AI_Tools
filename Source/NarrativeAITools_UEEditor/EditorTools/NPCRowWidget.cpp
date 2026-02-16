// Narrative AI Tools – Wanderson Lopes (2025)

#include "NPCRowWidget.h"

#include "Components/TextBlock.h"

void UNPCRowWidget::SetNPC(ANarrativeNPCCharacter* NewNPC)
{
	NPC = NewNPC;

	if (NPCNameText && NPC)
	{
		NPCNameText->SetText(FText::FromString(NPC->GetActorLabel()));
	}
}

void UNPCRowWidget::HandleClicked()
{
	if (NPC)
	{
		OnNPCSelected.Broadcast(NPC);
	}
}
