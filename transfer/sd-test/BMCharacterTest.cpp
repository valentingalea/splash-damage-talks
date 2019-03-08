#include "BMCharacterTest.h"

#include "Engine/World.h"
#include "SDAutomationTestMacros.h"

#include "BMCharacter.h"

#define MODULE_TEST_NAME BlackMass.Character.BMCharacter
#define MODULE_TEST_FLAGS EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter
#define IMPLEMENT_MODULE_TEST(TestName) IMPLEMENT_SD_SIMPLE_AUTOMATION_TEST(TestName, MODULE_TEST_NAME, MODULE_TEST_FLAGS)

namespace BMCharacterTestHelpers
{
	ATBMCharacterChildActor* SpawnAndAttachChildActor(UWorld& World, ABMCharacter& Character)
	{
		UChildActorComponent* ChildActorComponent = NewObject<UChildActorComponent>(&Character);
		
		if (!ChildActorComponent)
		{
			return nullptr;
		}
		ChildActorComponent->SetChildActorClass(ATBMCharacterChildActor::StaticClass());
		ChildActorComponent->RegisterComponent();

		return Cast<ATBMCharacterChildActor>(ChildActorComponent->GetChildActor());
	}
}

IMPLEMENT_MODULE_TEST(FBMCharacterWithChildActor_SetLifecycleState_ChildActorHasSameLifecycleState)
{
	// GIVEN: BMCharacter with attached child actor
	UWorld* World = CreateWorld();
	ABMCharacter* Character = World->SpawnActor<ABMCharacter>();
	ABORT_TEST_IF_NULL(Character);
	Character->SetLifecycleState(EBCLifecycleState::Inactive);

	ATBMCharacterChildActor* ChildActor = BMCharacterTestHelpers::SpawnAndAttachChildActor(*World, *Character);
	ABORT_TEST_IF_NULL(ChildActor);
	const EBCLifecycleState OriginalChildState = ChildActor->GetLifecycleState();

	// WHEN: Set lifecycle state on parent character
	Character->SetLifecycleState(EBCLifecycleState::Alive);

	// THEN: Lifecycle state on child actor has changed to the new state
	const EBCLifecycleState CurrentChildState = ChildActor->GetLifecycleState();
	TestEnumEqual<EBCLifecycleState>(TEXT("CurrentChildState"), CurrentChildState, EBCLifecycleState::Alive);
	TestTrue(TEXT("OriginalChildState != CurrentChildState"), OriginalChildState != CurrentChildState);

	return true;
}

IMPLEMENT_MODULE_TEST(FBMCharacterWithChildActor_SetTeamId_ChildActorHasSameTeamId)
{
	// GIVEN: BMCharacter with attached child actor
	UWorld* World = CreateWorld();
	ABMCharacter* Character = World->SpawnActor<ABMCharacter>();
	ABORT_TEST_IF_NULL(Character);
	const FGenericTeamId InitialTeamId(0);
	Character->SetGenericTeamId(InitialTeamId);

	ATBMCharacterChildActor* ChildActor = BMCharacterTestHelpers::SpawnAndAttachChildActor(*World, *Character);
	ABORT_TEST_IF_NULL(ChildActor);
	const FGenericTeamId OriginalTeamId = ChildActor->GetGenericTeamId();

	// WHEN: Set TeamID on parent character
	const FGenericTeamId NewTeamId(37);
	Character->SetGenericTeamId(NewTeamId);

	// THEN: TeamId on child actor has changed to the new TeamId
	const FGenericTeamId CurrentTeamId = ChildActor->GetGenericTeamId();
	TestEqual(TEXT("CurrentTeamId"), CurrentTeamId.GetId(), NewTeamId.GetId());
	TestTrue(TEXT("OriginalTeamId != CurrentTeamId"), OriginalTeamId.GetId() != CurrentTeamId.GetId());
	
	return true;
}

#undef IMPLEMENT_MODULE_TEST
#undef MODULE_TEST_FLAGS
#undef MODULE_TEST_NAME