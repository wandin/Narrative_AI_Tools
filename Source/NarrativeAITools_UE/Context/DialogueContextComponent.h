// Narrative AI Tools – Wanderson Lopes (2025)
#pragma once

#include "CoreMinimal.h"
#include "DialogueContextTypes.h"
#include "Components/ActorComponent.h"
#include "DialogueContextComponent.generated.h"

/*
 * Stores explicit narrative state for an Actor (typically an NPC).
 * Produces a data-only snapshot (FDialogueContext) used by dialogue/validation systems.
 *
 * No AI logic lives here.
 */
UCLASS(ClassGroup=(Narrative), meta=(BlueprintSpawnableComponent))
class NARRATIVEAITOOLS_UE_API UDialogueContextComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UDialogueContextComponent();

	/**
	* Builds an immutable snapshot of the current narrative context.
	*
	* This snapshot is safe to pass to dialogue generation,
	* validation, logging, or async systems.
	*/
	UFUNCTION(BlueprintCallable, Category="Narrative|Context")
	FNarrativeDialogueContext BuildContextSnapshot() const;

	// --- Mood ---
	UFUNCTION(BlueprintCallable, Category="Narrative|Context")
	void SetNPCMood(ENPCNarrativeMood NewMood);
	
	UFUNCTION(BlueprintPure, Category="Narrative|Context")
	ENPCNarrativeMood GetNPCMood() const { return NPCMood; }

	UFUNCTION(BlueprintPure, Category="Narrative|Context")
	FGameplayTagContainer GetAllowedTopics() const { return AllowedTopics; }

	UFUNCTION(BlueprintPure, Category="Narrative|Context")
	FGameplayTagContainer GetForbiddenTopics() const { return ForbiddenTopics; }

	// --- Narrative tags ---
	UFUNCTION(BlueprintCallable, Category="Narrative|Context")
	void AddPlayerTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="Narrative|Context")
	void RemovePlayerTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="Narrative|Context")
	void AddNPCTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="Narrative|Context")
	void RemoveNPCTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="Narrative|Context")
	void AddWorldStateTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="Narrative|Context")
	void RemoveWorldStateTag(FGameplayTag Tag);

	// --- Topic constraints ---
	UFUNCTION(BlueprintCallable, Category="Narrative|Constraints")
	void AddAllowedTopic(FGameplayTag TopicTag);
	
	UFUNCTION(BlueprintCallable, Category="Narrative|Constraints")
	void RemoveAllowedTopic(FGameplayTag TopicTag);

	UFUNCTION(BlueprintCallable, Category="Narrative")
	void SetAllowedTopics(const FGameplayTagContainer& NewAllowedTopics);

	UFUNCTION(BlueprintCallable, Category="Narrative")
	void SetForbiddenTopics(const FGameplayTagContainer& NewForbiddenTopics);

	UFUNCTION(BlueprintCallable, Category="Narrative|Constraints")
	void AddForbiddenTopic(FGameplayTag TopicTag);

	UFUNCTION(BlueprintCallable, Category="Narrative|Constraints")
	void RemoveForbiddenTopic(FGameplayTag TopicTag);

	// --- Debug ---
	UFUNCTION(BlueprintCallable, Category="Narrative|Debug")
	void SetDebugNotes(const FString& Notes);

    UFUNCTION(BlueprintPure, Category="Narrative|Debug")
	const FString& GetDebugNotes() const {return DebugNotes; }


protected:

	// If we later want replication, we can add it cleanly here
	// but keeping it simple for now.

	/** Current mood for the owning actor's narrative stance. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Narrative")
	ENPCNarrativeMood NPCMood = ENPCNarrativeMood::Neutral;

	/** Tags describing the player from this actor's POV (reputation, affiliations, flags). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Narrative")
	FGameplayTagContainer PlayerNarrativeTags;

	/** Tags describing the owning actor (NPC). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Narrative")
	FGameplayTagContainer NPCNarrativeTags;

	/** Tags describing world/quest state relevant to this actor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Narrative")
	FGameplayTagContainer WorldStateTags;

	/** Explicitly allowed dialogue topics for this actor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Narrative|Constraints")
	FGameplayTagContainer AllowedTopics;

	/** Explicitly forbidden dialogue topics for this actor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Narrative|Constraints")
	FGameplayTagContainer ForbiddenTopics;
	
	/** Free-form notes for tooling/debug visibility (not used for logic). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Narrative|Debug")
	FString DebugNotes;

private:

	/**
	* Ensures that forbidden topics always take precedence
	* over allowed topics.
	*/
	void NormalizeConstraints();
};
