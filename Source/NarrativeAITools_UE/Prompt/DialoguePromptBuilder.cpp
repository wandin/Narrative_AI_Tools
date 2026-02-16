#include "DialoguePromptBuilder.h"

FDialoguePrompt FDialoguePromptBuilder::BuildPrompt(const FDialogueRequest& Request)
{
	FDialoguePrompt Prompt;
	Prompt.System = BuildSystemPrompt(Request);
	Prompt.User = BuildUserPrompt(Request);
	return Prompt;
}

FString FDialoguePromptBuilder::BuildSystemPrompt(const FDialogueRequest& Request)
{
	const FNarrativeDialogueContext& Context = Request.Context;

	FString Result;
	Result += TEXT("You are an NPC in a video game.\n");

	// Mood
	Result += FString::Printf(TEXT("Your current mood is %s.\n"), *MoodToText(Context.NPCMood));

	//Allowed Topics
	if (!Context.AllowedTopics.IsEmpty())
	{
		Result += FString::Printf(TEXT("You may discuss the following topics:\n"));
			for (const FGameplayTag& Tag : Context.AllowedTopics)
			{
				Result += FString::Printf(TEXT("- %s\n"), *Tag.ToString());	
			}
	}

	// Forbidden topics
	if (!Context.ForbiddenTopics.IsEmpty())
	{
		Result += TEXT("You must not discuss the following topics:\n");
		for (const FGameplayTag& Tag : Context.ForbiddenTopics)
		{
			Result += FString::Printf(TEXT("- %s\n"), *Tag.ToString());	
		}
	}

	//Debug Notes
	if (!Context.DebugNotes.IsEmpty())
	{
		Result += TEXT("Additional notes:\n");
		Result += Context.DebugNotes + TEXT("\n");
	}

	// Style & length constraints
	/* Most of these instructions were added because the model is old and I DON'T TRUST IT :) */
	Result += TEXT("Stay in character at all times.\n");
	Result += TEXT("Speak directly as the character.\n");
	Result += TEXT("Never describe your role, tone, or emotions.\n");
	Result += TEXT("Never write dialogue for the player.\n");
	Result += TEXT("Do not simulate conversations or multiple speakers.\n");
	Result += TEXT("Do not use brackets, labels, or stage directions.\n");
	Result += TEXT("Express mood only through word choice and phrasing.\n");
	Result += TEXT("Limit response to 1–2 short sentences.\n");
	return Result;
}

FString FDialoguePromptBuilder::BuildUserPrompt(const FDialogueRequest& Request)
{
	return FString::Printf(TEXT("The player initiates a dialogue with intent: %s"), *IntentToText(Request.Intent));
}

FString FDialoguePromptBuilder::MoodToText(ENPCNarrativeMood Mood)
{
	switch(Mood)
	{		
		case ENPCNarrativeMood::Friendly:
			return TEXT("friendly, warm and welcoming");
		case ENPCNarrativeMood::Hostile:
			return TEXT("hostile, aggressive and distrustful");
		case ENPCNarrativeMood::Fearful:
			return TEXT("fearful and cautious");
		case ENPCNarrativeMood::Curious:
			return TEXT("curious and inquisitive");
		case ENPCNarrativeMood::Neutral:
		default:
			return TEXT("neutral and reserved");
	}
}

FString FDialoguePromptBuilder::IntentToText(EDialogueIntent Intent)
{
	switch (Intent)
	{
		case EDialogueIntent::Greeting:
			return TEXT("greeting");
		case EDialogueIntent::SmallTalk:
			return TEXT("small talk");
		case EDialogueIntent::Quest:
			return TEXT("quest discussion");
		case EDialogueIntent::Information:
			return TEXT("request for information");
		case EDialogueIntent::Reaction:
			return TEXT("reaction to an event");
		default:
			return TEXT("unknown intent");
	}
}
