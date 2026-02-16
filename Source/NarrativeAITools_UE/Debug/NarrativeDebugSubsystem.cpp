// Narrative AI Tools – Wanderson Lopes (2025)

#include "NarrativeDebugSubsystem.h"

void UNarrativeDebugSubsystem::RecordDialogueInteraction(const FDialogueRequest& Request, const FDialogueResponse& Response)
{
	FNarrativeDialogueDebugEntry Entry;
	Entry.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	Entry.Request = Request;
	Entry.Response = Response;
	
	DialogueHistory.Add(Entry);
}

void UNarrativeDebugSubsystem::ClearHistory()
{
	DialogueHistory.Reset();
}
