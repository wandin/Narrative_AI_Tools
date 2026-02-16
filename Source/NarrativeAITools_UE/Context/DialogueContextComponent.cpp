// Narrative AI Tools – Wanderson Lopes (2025)

#include "DialogueContextComponent.h"


UDialogueContextComponent::UDialogueContextComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FNarrativeDialogueContext UDialogueContextComponent::BuildContextSnapshot() const
{
	FNarrativeDialogueContext OutContext;
	OutContext.NPCMood = NPCMood;
	OutContext.PlayerNarrativeTags = PlayerNarrativeTags;
	OutContext.NPCNarrativeTags = NPCNarrativeTags;
	OutContext.WorldStateTags = WorldStateTags;
	OutContext.AllowedTopics = AllowedTopics;
	OutContext.ForbiddenTopics = ForbiddenTopics;
	OutContext.DebugNotes = DebugNotes;

	return OutContext;
}

void UDialogueContextComponent::SetNPCMood(ENPCNarrativeMood NewMood)
{
	NPCMood = NewMood;
}

void UDialogueContextComponent::AddPlayerTag(FGameplayTag Tag)
{
	if(Tag.IsValid())
	{
		PlayerNarrativeTags.AddTag(Tag);
	}
}

void UDialogueContextComponent::RemovePlayerTag(FGameplayTag Tag)
{
	if(Tag.IsValid())
	{
		PlayerNarrativeTags.RemoveTag(Tag);
	}
}

void UDialogueContextComponent::AddNPCTag(FGameplayTag Tag)
{
	if (Tag.IsValid())
	{
		NPCNarrativeTags.AddTag(Tag);
	}
}

void UDialogueContextComponent::RemoveNPCTag(FGameplayTag Tag)
{
	if (Tag.IsValid())
	{
		NPCNarrativeTags.RemoveTag(Tag);
	}
}

void UDialogueContextComponent::AddWorldStateTag(FGameplayTag Tag)
{
	if (Tag.IsValid())
	{
		WorldStateTags.AddTag(Tag);
	}
}

void UDialogueContextComponent::RemoveWorldStateTag(FGameplayTag Tag)
{
	if (Tag.IsValid())
	{
		WorldStateTags.RemoveTag(Tag);
	}
}

void UDialogueContextComponent::AddAllowedTopic(FGameplayTag TopicTag)
{
	if (TopicTag.IsValid())
	{
		AllowedTopics.AddTag(TopicTag);
		NormalizeConstraints();
	}
}

void UDialogueContextComponent::RemoveAllowedTopic(FGameplayTag TopicTag)
{
	if (TopicTag.IsValid())
	{
		AllowedTopics.RemoveTag(TopicTag);
	}
}

void UDialogueContextComponent::SetAllowedTopics(const FGameplayTagContainer& NewAllowedTopics)
{
	AllowedTopics = NewAllowedTopics;
	NormalizeConstraints();
}

void UDialogueContextComponent::SetForbiddenTopics(const FGameplayTagContainer& NewForbiddenTopics)
{
	ForbiddenTopics = NewForbiddenTopics;
	NormalizeConstraints();
}

void UDialogueContextComponent::AddForbiddenTopic(FGameplayTag TopicTag)
{
	if (TopicTag.IsValid())
	{
		ForbiddenTopics.AddTag(TopicTag);
		NormalizeConstraints();
	}
}

void UDialogueContextComponent::RemoveForbiddenTopic(FGameplayTag TopicTag)
{
	if (TopicTag.IsValid())
	{
		ForbiddenTopics.RemoveTag(TopicTag);
	}
}

void UDialogueContextComponent::SetDebugNotes(const FString& Notes)
{
	DebugNotes = Notes;
}

void UDialogueContextComponent::NormalizeConstraints()
{
	if (!ForbiddenTopics.IsEmpty())
	{
		AllowedTopics.RemoveTags(ForbiddenTopics);
	}
}
