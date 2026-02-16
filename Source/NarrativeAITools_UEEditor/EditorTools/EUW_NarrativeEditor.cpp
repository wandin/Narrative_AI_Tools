// Narrative AI Tools – Wanderson Lopes (2025)

#include "EUW_NarrativeEditor.h"

#include "Selection.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Editor/ScriptableEditorWidgets/Public/Components/DetailsView.h"
#include "Context/DialogueContextComponent.h"

void UEUW_NarrativeEditor::NativeConstruct()
{
	Super::NativeConstruct();

	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddDynamic(this, &UEUW_NarrativeEditor::ApplyToActiveNPC);
	}
	if (RefreshSelectionButton)
	{
		RefreshSelectionButton->OnClicked.AddDynamic(this, &UEUW_NarrativeEditor::RefreshSelection);
	}
}

void UEUW_NarrativeEditor::RefreshSelection()
{
	SelectedNPCs.Reset();

	if (!NPCListScrollBox)
	{
		return;
	}

	NPCListScrollBox->ClearChildren();

	TArray<AActor*> Actors;
	GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(Actors);

	for (AActor* Actor : Actors)
	{
		if (ANarrativeNPCCharacter* NPC = Cast<ANarrativeNPCCharacter>(Actor))
		{
			SelectedNPCs.Add(NPC);

			if (!NPCRowClass)
			{
				continue;
			}

			UNPCRowWidget* Row = CreateWidget<UNPCRowWidget>(this, NPCRowClass);
			
			Row->SetNPC(NPC);
			Row->OnNPCSelected.AddDynamic(this, &UEUW_NarrativeEditor::SetActiveNPC);

			NPCListScrollBox->AddChild(Row);
		}
	}

	//Auto-select first NPC (UX nice)
	if (SelectedNPCs.Num() > 0)
	{
		SetActiveNPC(SelectedNPCs[0]);
	}
}

void UEUW_NarrativeEditor::SetActiveNPC(ANarrativeNPCCharacter* NewNPC)
{
	ActiveNPC = NewNPC;

	if (!EditorContextObject)
	{
		EditorContextObject = NewObject<UNarrativeContextEditorObject>(this);
	}

	auto* Context = NewNPC->FindComponentByClass<UDialogueContextComponent>();
	if (!Context)
	{
		return;
	}
	EditorContextObject->NPCMood = Context->GetNPCMood();
	EditorContextObject->AllowedTopics = Context->GetAllowedTopics();
	EditorContextObject->ForbiddenTopics = Context->GetForbiddenTopics();
	
	DetailsView->SetObject(EditorContextObject);
}

void UEUW_NarrativeEditor::ApplyToActiveNPC()
{
	if (!ActiveNPC || !EditorContextObject)
	{
		return;
	}

	auto* Context = ActiveNPC->FindComponentByClass<UDialogueContextComponent>();
	if (!Context)
	{
		return;
	}
	Context->SetNPCMood(EditorContextObject->NPCMood);
	Context->SetAllowedTopics(EditorContextObject->AllowedTopics);
	Context->SetForbiddenTopics(EditorContextObject->ForbiddenTopics);
}

void UEUW_NarrativeEditor::RefreshEditorFromNPC()
{
	if (!ActiveNPC || !EditorContextObject || !DetailsView)
	{
		return;	
	}
	DetailsView->SetObject(EditorContextObject);
}
