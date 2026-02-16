// Narrative AI Tools – Wanderson Lopes (2025)

#include "AIResponseProvider.h"

FDialogueResponse UAIResponseProvider::GenerateResponse_Implementation(const FDialogueRequest& Request)
{
	// Base implementation returns an invalid response.
	FDialogueResponse Response;
	Response.bIsValid = false;
	Response.ValidationMessage = TEXT("Base AIResponseProvider does not implement GenerateResponse.");

	return Response;
}
