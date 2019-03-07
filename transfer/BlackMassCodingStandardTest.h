#pragma once
// [test.basic_rule] Follow the non-test standard for headers in BlackMassCodingStandard.h

//
// [test.header.name] There are three types of test header, which should be named differently
// to avoid confusion:
//
//  1) Files containing helper UClasses that help test a certain real class.  These should be
//     named to match the corresponding test cpp. (e.g. "BCActorHelpersTest.cpp")
//
//  2) Files containing a single mock implementation for an interface.  These should be named
//     to match the mock class itself. (e.g. "TBMBossState.h")
//
//  3) Files containing a single wrapper UClass for a corresponding real class (these derive
//     from a real class but expose certain protected variables and functions to mimic blueprint
//     access).  These should be named to match the wrapper class itself. (e.g. "TBMBossStateWrapper.h")
//

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackMassCodingStandardTest.generated.h"

// [test.name.class] classes in test modules should also follow our naming convention
//	- Classes, Struct & Enums in Core test modules should be prefixed with TBC
//	- Classes, Struct & Enums in Game test modules should be prefixed with TBM
UCLASS()
class ATBMTestActor : public AActor
{
	GENERATED_BODY()
public:
	bool IsRunning() const;
	void Run();

private:
	bool IsCurrentlyRunning = false;
};

inline bool ATBMTestActor::IsRunning() const
{
	return IsCurrentlyRunning;
}

inline void ATBMTestActor::Run()
{
	IsCurrentlyRunning = true;
}

// [test.name.mock] Mock classes are intended to implement some IInterface in a
// minimal fashion.  They should be named using [test.name.class], matching the
// interface name as closely as possible. (e.g. IBIBossState --> UTBMBossState)

// [test.name.wrapper] Wrapper classes derive from some real class under test
// and expose certain protected variables and functions to simulate access from
// blueprint.  They should be named using [test.name.class], except with an
// additional "Wrapper" suffix. (e.g. UBMBossState --> UTBMBossStateWrapper)
