#pragma once
#include "Private/ContentValidation/BCContentValidator.h"

#include "BCBlueprintValidator.generated.h"

class FBCBlueprintStatRecord;
enum class EBCResult : uint8;

UCLASS()
class UBCBlueprintValidator : public UBCContentValidator
{
	GENERATED_BODY()

public:
	// Begin UBCContentValidator override
	virtual void ValidateContent() override;
	// End UBCContentValidator override

};

//Helper namespace where all the validation takes place. 
//Allows the validation to be called both from an editor menu and a commandlet
namespace BCBlueprintValidatorHelper
{
	void ValidateBlueprints();
	COREEDITOR_TEST_API EBCResult ValidateBlueprint(UBlueprint* BPAsset);

	COREEDITOR_TEST_API EBCResult CheckHasCommentsIfHaveNodes(const FBCBlueprintStatRecord& BPStats);
	COREEDITOR_TEST_API EBCResult CheckPublicFunctionsHaveTooltips(const FBCBlueprintStatRecord& BPStats);
	COREEDITOR_TEST_API EBCResult CheckPublicVariablesHaveTooltips(const FBCBlueprintStatRecord& BPStats);
	COREEDITOR_TEST_API EBCResult CheckNoFunctionsWithDefaultName(const FBCBlueprintStatRecord& BPStats);
	COREEDITOR_TEST_API EBCResult CheckNoVariablesWithDefaultName(const FBCBlueprintStatRecord& BPStats);
	EBCResult CheckCompiles(const FBCBlueprintStatRecord& BPStats);
}