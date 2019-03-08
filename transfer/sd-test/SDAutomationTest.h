#pragma once

#include "Misc/AutomationTest.h"
#include "Misc/EnumGeneratedDeclaration.h"

class SDTESTHARNESS_API FSDAutomationTest : public FAutomationTestBase
{
public:
	FSDAutomationTest(const FString& InName, const bool bInComplexTask);
	void TestStringEqual(const FString& Description, const FString& A, const FString& B, ESearchCase::Type SearchType = ESearchCase::CaseSensitive);

	template<typename EnumType>
	void TestEnumEqual(const FString& Description, EnumType A, EnumType B);

protected:
	UWorld* CreateWorld();

	// Begin FAutomationTestBase override
	virtual void PreRunTest() override;
	virtual void PostRunTest() override;
	virtual void AddError(const FString& InError, int32 StackOffset = 0) override;
	virtual void AddErrorS(const FString& InError, const FString& InFilename, int32 InLineNumber) override;
	virtual void AddWarning(const FString& InWarning, int32 StackOffset = 0) override;
	virtual void AddWarningS(const FString& InWarning, const FString& InFilename, int32 InLineNumber) override;
	// End FAutomationTestBase override

private:
	// Begin FAutomationTestBase override
	virtual void AddInfo(const FString& InLogItem, int32 StackOffset = 0) override;

	virtual void SetSuccessState(bool bSuccessful) override;
	// End FAutomationTestBase override

	UWorld* TestWorld = nullptr;
	bool LogTeamCityTestMessages = true;
	class RecursionGuard
	{
		FSDAutomationTest* const Test;
	public: 
		RecursionGuard(FSDAutomationTest* const test): Test(test) { Test->IsLoggingMessages = true;  }
		~RecursionGuard() { Test->IsLoggingMessages = false; }
	};
	bool IsLoggingMessages = false; 
};

template<typename EnumType>
inline void FSDAutomationTest::TestEnumEqual(const FString& Description, EnumType A, EnumType B)
{
	if (A != B)
	{
		AddError(
			FString::Printf(
				TEXT("%s: The two enum values are not equal.\nActual: '%s'\nExpected: '%s'"),
				*Description,
				EnumAutoGen::GetEnumString<EnumType>(A),
				EnumAutoGen::GetEnumString<EnumType>(B)),
			1);
	}
}