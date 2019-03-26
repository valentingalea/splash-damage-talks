#include "SDCharacterTest.h"

#include "Engine/World.h"
#include "SDAutomationTestMacros.h"

#include "SDCharacter.h"

#define MODULE_TEST_NAME Game.Character.SDCharacter
#define MODULE_TEST_FLAGS EAutomationTestFlags::ApplicationContextMask | EAutoma
#define IMPLEMENT_MODULE_TEST(TestName) IMPLEMENT_SD_SIMPLE_AUTOMATION_TEST(Test

namespace SDCharacterTestHelpers
{
    ATSDCharacterChildActor* SpawnAndAttachChildActor(UWorld& World, ASDCharacte
    {
        UChildActorComponent* ChildActorComponent = NewObject<UChildActorCompone
        
        if (!ChildActorComponent)
        {
            return nullptr;
        }
        ChildActorComponent->SetChildActorClass(ATSDCharacterChildActor::StaticC
        ChildActorComponent->RegisterComponent();

        return Cast<ATSDCharacterChildActor>(ChildActorComponent->GetChildActor(
    }
}

IMPLEMENT_MODULE_TEST(FSDCharacterWithChildActor_SetLifecycleState_ChildActorHas
{
    // GIVEN: SDCharacter with attached child actor
    UWorld* World = CreateWorld();
    ASDCharacter* Character = World->SpawnActor<ASDCharacter>();
    ABORT_TEST_IF_NULL(Character);
    Character->SetLifecycleState(EBCLifecycleState::Inactive);

    ATSDCharacterChildActor* ChildActor = SDCharacterTestHelpers::SpawnAndAttach
    ABORT_TEST_IF_NULL(ChildActor);
    const EBCLifecycleState OriginalChildState = ChildActor->GetLifecycleState();

    // WHEN: Set lifecycle state on parent character
    Character->SetLifecycleState(EBCLifecycleState::Alive);

    // THEN: Lifecycle state on child actor has changed to the new state
    const EBCLifecycleState CurrentChildState = ChildActor->GetLifecycleState();
    TestEnumEqual<EBCLifecycleState>(TEXT("CurrentChildState"), CurrentChildStat
    TestTrue(TEXT("OriginalChildState != CurrentChildState"), OriginalChildState

    return true;
}

IMPLEMENT_MODULE_TEST(FSDCharacterWithChildActor_SetTeamId_ChildActorHasSameTeam
{
    // GIVEN: SDCharacter with attached child actor
    UWorld* World = CreateWorld();
    ASDCharacter* Character = World->SpawnActor<ASDCharacter>();
    ABORT_TEST_IF_NULL(Character);
    const FGenericTeamId InitialTeamId(0);
    Character->SetGenericTeamId(InitialTeamId);

    ATSDCharacterChildActor* ChildActor = SDCharacterTestHelpers::SpawnAndAttach
    ABORT_TEST_IF_NULL(ChildActor);
    const FGenericTeamId OriginalTeamId = ChildActor->GetGenericTeamId();

    // WHEN: Set TeamID on parent character
    const FGenericTeamId NewTeamId(37);
    Character->SetGenericTeamId(NewTeamId);

    // THEN: TeamId on child actor has changed to the new TeamId
    const FGenericTeamId CurrentTeamId = ChildActor->GetGenericTeamId();
    TestEqual(TEXT("CurrentTeamId"), CurrentTeamId.GetId(), NewTeamId.GetId());
    TestTrue(TEXT("OriginalTeamId != CurrentTeamId"), OriginalTeamId.GetId() != 
    
    return true;
}

#undef IMPLEMENT_MODULE_TEST
#undef MODULE_TEST_FLAGS
#undef MODULE_TEST_NAME