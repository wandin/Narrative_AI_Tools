using UnrealBuildTool;

public class NarrativeAITools_UEEditor : ModuleRules
{
    public NarrativeAITools_UEEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "NarrativeAITools_UE",   // runtime module
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "Blutility",
                "UMG",
                "Slate",
                "SlateCore",
                "EditorSubsystem",
                "PropertyEditor",
                "LevelEditor",
                "ScriptableEditorWidgets",
                "GameplayTags"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
    }
}