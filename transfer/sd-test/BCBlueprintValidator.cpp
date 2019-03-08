#include "BCBlueprintValidator.h"

#include "ConfigCacheIni.h"
#include "CoreEditor.h"
#include "CoreGlobals.h"
#include "EdGraphNode_Comment.h"
#include "Engine/Blueprint.h"
#include "Engine/ObjectLibrary.h"
#include "GameFramework/Actor.h"
#include "KismetEditorUtilities.h"

#include "BCBlueprintStatRecord.h"
#include "BCEnumParameterTypes.h"

#define LOCTEXT_NAMESPACE "Blueprint Validator" 

void UBCBlueprintValidator::ValidateContent()
{
	BCBlueprintValidatorHelper::ValidateBlueprints();
}

void BCBlueprintValidatorHelper::ValidateBlueprints()
{
	if (UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(nullptr, true, false))
	{
		const int32 AssetDataCount = ObjectLibrary->LoadBlueprintAssetDataFromPath("/Game/");
		TArray<FAssetData> AssetDatas;
		AssetDatas.Reserve(AssetDataCount);
		ObjectLibrary->GetAssetDataList(AssetDatas);

		//Grab ignore paths from DefaultEditor config
		FConfigFile EditorConfigFile;
		GConfig->LoadLocalIniFile(EditorConfigFile, TEXT("Editor"), true);
		TArray<FString> IgnorePaths;
		EditorConfigFile.GetArray(TEXT("ContentValidation/Blueprint"), TEXT("IgnorePaths"), IgnorePaths);

		for (FAssetData& AssetData : AssetDatas)
		{
			const FString& ObjectPath = AssetData.ObjectPath.GetPlainNameString();
			bool ShouldIgnorePath = false;
			for (const FString IgnorePath : IgnorePaths)
			{
				ShouldIgnorePath |= ObjectPath.Contains(IgnorePath);
			}
			if (ShouldIgnorePath)
			{
				continue;
			}

			FStringAssetReference AssetRef(ObjectPath);
			if (auto* BPAsset = Cast<UBlueprint>(AssetRef.TryLoad()))
			{
				ValidateBlueprint(BPAsset);
			}
		}
	}
}

EBCResult BCBlueprintValidatorHelper::ValidateBlueprint(UBlueprint* BPAsset)
{
	FBCBlueprintStatRecord BlueprintStatRecord(BPAsset);

	EBCResult ValidatorResult = EBCResult::Succeeded;
	if (CheckHasCommentsIfHaveNodes(BlueprintStatRecord) == EBCResult::Failed)
	{
		ValidatorResult = EBCResult::Failed;
	}
	if (CheckPublicFunctionsHaveTooltips(BlueprintStatRecord) == EBCResult::Failed)
	{
		ValidatorResult = EBCResult::Failed;
	}
	if (CheckPublicVariablesHaveTooltips(BlueprintStatRecord) == EBCResult::Failed)
	{
		ValidatorResult = EBCResult::Failed;
	}
	if (CheckNoFunctionsWithDefaultName(BlueprintStatRecord) == EBCResult::Failed)
	{
		ValidatorResult = EBCResult::Failed;
	}
	if (CheckNoVariablesWithDefaultName(BlueprintStatRecord) == EBCResult::Failed)
	{
		ValidatorResult = EBCResult::Failed;
	}
	if (CheckCompiles(BlueprintStatRecord) == EBCResult::Failed)
	{
		ValidatorResult = EBCResult::Failed;
	}

	if (ValidatorResult == EBCResult::Succeeded)
	{
		UE_LOG(CoreEditor
			, Log
			, TEXT("Blueprint %s validation completed succesfully")
			, *BlueprintStatRecord.BlueprintName);
	}

	return ValidatorResult;
}

EBCResult BCBlueprintValidatorHelper::CheckHasCommentsIfHaveNodes(const FBCBlueprintStatRecord& BPStats)
{
	//If we have more than these number of nodes we need at least one comment
	constexpr static int32 NeedsCommentNodeCount = 5;

	const int32* FoundCommentNodesValue = BPStats.NodeCount.Find(UEdGraphNode_Comment::StaticClass());
	bool HasCommentNodes = FoundCommentNodesValue != nullptr;
	//We're using function count here as NodeCount includes nodes such as entry nodes, comment nodes, etc
	//that we are not interested in. We want to check the function call nodes.
	int32 FunctionCallCount = BPStats.FunctionCount.Num();

	if (HasCommentNodes == false && FunctionCallCount > NeedsCommentNodeCount)
	{
		UE_LOG(CoreEditor
			, Error
			, TEXT("Blueprint %s has no comment nodes")
			, *BPStats.BlueprintName);

		return EBCResult::Failed;
	}

	return EBCResult::Succeeded;
}

EBCResult BCBlueprintValidatorHelper::CheckPublicFunctionsHaveTooltips(const FBCBlueprintStatRecord& BPStats)
{
	EBCResult ReturnResult = EBCResult::Succeeded;

	//All native public functions should have a description
	for (const auto& FunctionPair : BPStats.NativeFunctionCount)
	{
		const UFunction* Function = FunctionPair.Key;
		if (Function->HasAnyFunctionFlags(FUNC_Public) == false)
		{
			continue;
		}

		if (Function->HasMetaData(TEXT("Tooltip")) == false)
		{
			UE_LOG(CoreEditor
				, Error
				, TEXT("Public function %s in Blueprint %s has no tooltip")
				, *Function->GetName()
				, *BPStats.BlueprintName);

			ReturnResult = EBCResult::Failed;
		}
	}

	return ReturnResult;
}

EBCResult BCBlueprintValidatorHelper::CheckPublicVariablesHaveTooltips(const FBCBlueprintStatRecord& BPStats)
{
	EBCResult ReturnResult = EBCResult::Succeeded;

	for (const auto& VariableDescription : BPStats.SourceBlueprint->NewVariables)
	{
		if ((VariableDescription.PropertyFlags & CPF_DisableEditOnInstance) != 0)
		{
			//property is not public
			continue;
		}

		if (VariableDescription.HasMetaData(TEXT("Tooltip")) == false)
		{
			UE_LOG(CoreEditor
				, Error
				, TEXT("Public variable %s in Blueprint %s has no tooltip")
				, *VariableDescription.FriendlyName
				, *BPStats.BlueprintName);

			ReturnResult = EBCResult::Failed;
		}
	}

	return ReturnResult;
}

EBCResult BCBlueprintValidatorHelper::CheckNoFunctionsWithDefaultName(const FBCBlueprintStatRecord& BPStats)
{
	const FString NewPrefix = TEXT("NewFunction");
	EBCResult ReturnResult = EBCResult::Succeeded;

	for (const auto& FunctionPair : BPStats.NativeFunctionCount)
	{
		const UFunction* Function = FunctionPair.Key;
		if (Function->GetName().StartsWith(NewPrefix))
		{
			UE_LOG(CoreEditor
				, Error
				, TEXT("Function %s in Blueprint %s has default NewFunction name. Please rename")
				, *Function->GetName()
				, *BPStats.BlueprintName);

			ReturnResult = EBCResult::Failed;
		}
	}

	return ReturnResult;
}

EBCResult BCBlueprintValidatorHelper::CheckNoVariablesWithDefaultName(const FBCBlueprintStatRecord& BPStats)
{
	const FString NewPrefix = TEXT("NewVar");
	EBCResult ReturnResult = EBCResult::Succeeded;

	for (const auto& VariableDescription : BPStats.SourceBlueprint->NewVariables)
	{
		if (VariableDescription.VarName.ToString().StartsWith(NewPrefix))
		{
			UE_LOG(CoreEditor
				, Error
				, TEXT("Variable %s in Blueprint %s has default NewVar name. Please rename")
				, *VariableDescription.VarName.ToString()
				, *BPStats.BlueprintName);

			ReturnResult = EBCResult::Failed;
		}
	}

	return ReturnResult;
}

EBCResult BCBlueprintValidatorHelper::CheckCompiles(const FBCBlueprintStatRecord& BPStats)
{
	EBCResult ReturnResult = EBCResult::Succeeded;
	FKismetEditorUtilities::CompileBlueprint(BPStats.SourceBlueprint, EBlueprintCompileOptions::SkipGarbageCollection);

	if (BPStats.SourceBlueprint->Status == EBlueprintStatus::BS_UpToDateWithWarnings ||
		BPStats.SourceBlueprint->Status == EBlueprintStatus::BS_Error)
	{
		UE_LOG(CoreEditor
			, Error
			, TEXT("Blueprint %s failed to compile without errors or warnings")
			, *BPStats.BlueprintName);

		ReturnResult = EBCResult::Failed;
	}
	else if (BPStats.SourceBlueprint->Status != EBlueprintStatus::BS_UpToDate)
	{
		UE_LOG(CoreEditor
			, Error
			, TEXT("Blueprint %s is in an unexpected state after compiling")
			, *BPStats.BlueprintName);

		ReturnResult = EBCResult::Failed;
	}

	return ReturnResult;
}

#undef LOCTEXT_NAMESPACE