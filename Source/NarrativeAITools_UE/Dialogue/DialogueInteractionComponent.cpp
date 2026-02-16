// Narrative AI Tools – Wanderson Lopes (2025)

#include "DialogueInteractionComponent.h"

#include "Debug/NarrativeDebugSubsystem.h"
#include "Prompt/DialoguePromptBuilder.h"

DEFINE_LOG_CATEGORY(LogDialogueInteractionComponent);


// Sets default values for this component's properties
UDialogueInteractionComponent::UDialogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDialogueInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	DialogueContextComponent = GetOwner()->FindComponentByClass<UDialogueContextComponent>();
}

void UDialogueInteractionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ActiveProvider)
	{
		ActiveProvider->OnResponseReady.RemoveAll(this);
		ActiveProvider = nullptr;
	}
	
	Super::EndPlay(EndPlayReason);
}

void UDialogueInteractionComponent::ExecuteDialogue(EDialogueIntent Intent)
{
	if (!DialogueContextComponent || !ResponseProviderClass)
	{
		return;
	}

	// 1. Build request
	LastDialogueRequest = {};
	LastDialogueRequest.Intent = Intent;
	LastDialogueRequest.Context =
	DialogueContextComponent->BuildContextSnapshot();

	// (Optional debug)
	const FDialoguePrompt Prompt = FDialoguePromptBuilder::BuildPrompt(LastDialogueRequest);

	UE_LOG(LogDialogueInteractionComponent, Warning, TEXT("=== SYSTEM PROMPT ===\n%s"),	*Prompt.System);

	UE_LOG(LogDialogueInteractionComponent, Warning, TEXT("=== USER PROMPT ===\n%s"), *Prompt.User);

	// if we don't have a provider 
	if (!ActiveProvider)
	{
		// 2. Create provider
		ActiveProvider = CreateProviderInstance();
	}
	
	if (!ActiveProvider)
	{
		return;
	}

	// 3. Bind async callback
	ActiveProvider->OnResponseReady.AddUniqueDynamic(this, &UDialogueInteractionComponent::HandleProviderResponse);

	// 4. Fire async request
	ActiveProvider->GenerateResponse(LastDialogueRequest);
}

void UDialogueInteractionComponent::HandleProviderResponse(const FDialogueResponse& Response)
{
	LastDialogueResponse = Response;

	// debug recording
	if (UWorld* World = GetWorld())
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			if (UNarrativeDebugSubsystem* Debug = GI->GetSubsystem<UNarrativeDebugSubsystem>())
			{
				Debug->RecordDialogueInteraction(LastDialogueRequest, LastDialogueResponse);
			}
		}
	}

	OnDialogueResponseReceived.Broadcast(Response);

	UE_LOG(LogDialogueInteractionComponent, Warning, TEXT("Dialogue response received: %s"), *Response.DialogueText.ToString());
}

UAIResponseProvider* UDialogueInteractionComponent::CreateProviderInstance()
{
	if (!ResponseProviderClass)
	{
		return nullptr;
	}

	return NewObject<UAIResponseProvider>(this, ResponseProviderClass);
}
