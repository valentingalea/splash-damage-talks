#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IBILifecycleStateOwner.h"
#include "GenericTeamAgentInterface.h"
#include "BMCharacterTest.generated.h"

UCLASS()
class ATBMCharacterChildActor
	: public AActor
	, public IBILifecycleStateOwner
	, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Begin IBILifecycleStateOwner override
	virtual EBCLifecycleState GetLifecycleState() const override;
	virtual void SetLifecycleState(EBCLifecycleState NewState) override;
	// End IBILifecycleStateOwner override

	// Begin IGenericTeamAgentInterface override
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	// End IGenericTeamAgentInterface override

	EBCLifecycleState LifecycleState = EBCLifecycleState::Inactive;
	FGenericTeamId TeamId = FGenericTeamId::NoTeam;
};

inline EBCLifecycleState ATBMCharacterChildActor::GetLifecycleState() const
{
	return LifecycleState;
}

inline void ATBMCharacterChildActor::SetLifecycleState(EBCLifecycleState NewState)
{
	LifecycleState = NewState;
}

inline void ATBMCharacterChildActor::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	TeamId = InTeamID;
}

inline FGenericTeamId ATBMCharacterChildActor::GetGenericTeamId() const
{
	return TeamId;
}