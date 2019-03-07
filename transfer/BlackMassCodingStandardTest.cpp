#include "BlackMassCodingStandardTest.h"
// [test.basic.rule] Follow Black Mass Coding Standard and the UE4 coding guidelines

// [test.header.harness] Include the test harness header
#include "SDAutomationTestMacros.h"
#include "Engine/World.h"

// [test.header.include] Include headers required for tests
// Should only include headers from the engine, or from the
// same game module as where the test resides. If your tests 
// have game dependencies outside of its own module, then 
// this is probably not a unit test.

// [test.macros.flags] Test flags can be used to limit tests to certain contexts, 
// Below is the default which should work for most situations.
// See: https://docs.unrealengine.com/latest/INT/API/Runtime/Core/Misc/EAutomationTestFlags__Type/ for more options
// Remember to undefine this at the end of the file.
#define MODULE_TEST_FLAGS EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter

// [test.macros.modulename] Naming should be BlackMass.<Module Name>.<Sub Directory>....
// The first two parts should be consistent with the project.
// Remember to undefine this at the end of the file.
#define MODULE_TEST_NAME BlackMass.BlackMass.BlackMassCodingStandard

// [test.macros.wrapper] To make writing the actual tests easier, you can define 
// a wrapper around IMPLEMENT_SD_SIMPLE_AUTOMATION_TEST. Remember to undefine 
// it at the end of your test file (see below).
#define IMPLEMENT_MODULE_TEST(TestName) IMPLEMENT_SD_SIMPLE_AUTOMATION_TEST(TestName, MODULE_TEST_NAME, MODULE_TEST_FLAGS)

// [test.helpers] Use a namespace with free functions and fixtures before 
// the tests to define helper functions that will need to be called from any test.
// Prefer to keep them in the same file, unless they relate to core systems,
// that tests for other units will require.
namespace BMBlackMassCodingStandardTestHelpers
{
	constexpr int32 TheNumberOne = 1;

	static ATBMTestActor* CreateTestActor(UWorld* World)
	{
		return World->SpawnActor<ATBMTestActor>();
	}
}

// [test.name] Follow a naming convention of F<Given>_<When>_<Then>
// If your tests can not be described in a simple sentence with a 
// given, when, then structure, then you may need to break it into 
// multiple simpler tests.
//
// Given:   Some initial state
// When:    Some event that causes state to change
// Then:    Some state after the event
//
// E.g. For a test that checks 1 + 1 = 2
// Good: FIntValueOne_AddOne_ResultTwo
// Bad: FIntegerAddTest
IMPLEMENT_MODULE_TEST(FIntValueOne_AddOne_ResultTwo)
{
	// [test.structure] Space and comment your tests with the Given, When, 
	// Then structure. As tests form part of the documentation of the 
	// functionality of the code you are testing they should be easy to read 
	// for reference and review.

	// Given an int with value 1
	int32 One = 1;

	// When you add 1 to it
	int32 Result = One + BMBlackMassCodingStandardTestHelpers::TheNumberOne;
	
	// [test.assert] Use the assertions defined in FAutomationTestBase, 
	// and FSDAutomationTest (the underlying base classes for all tests,
	// so are already available within the tests' scope. Using them will
	// allow the system to output meaningful error messages when they fail.
	//
	// TestEqual(), TestStringEqual(), TestEnumEqual(), TestSame(), TestTrue(), 
	// TestFalse(), and TestNotNull() are just some of the useful assertions 
	// available. See classes FAutomationTestBase in AutomationTest.h and 
	// FSDAutomationTest in SDAutomationTest.h for more.

	// [test.assert.params.order] The order of the params to the assertions is
	// Description, Actual, Expected. 'Actual' should be the result of the 'when'
	// part of your test. Putting Actual and Expected the other way around can 
	// give confusing error messages when tests fail.

	// [test.assert.description] Assertions should be validating the 'Then' part 
	// of your test. Use the description text argument to describe/name the 
	// state you are asserting without assuming anything about its value. 
	// The test will cleanly log the actual and expected values for you.
	//
	// GOOD: 'The result after adding 1'
	// BAD: 'The result was not equal to...'

	// Then the result should equal 2
	TestEqual(TEXT("The result after adding 1"), Result, 2);

	// [test.return.true] TEMPORARY: Currently all tests must return a boolean. 
	// This requirement will be removed in the future.
	return true;
}

IMPLEMENT_MODULE_TEST(FTestActor_CheckIsRunningAfterCreating_IsNotRunning)
{
	// [test.create.world] This function creates a UWorld which will be automatically
	// deleted and garbage collected when the test finishes.  Do not manually destroy
	// this object, or any other objects/actors created in this world during the test.
	UWorld* World = CreateWorld();

	// Given a new test actor
	ATBMTestActor* TestActor = BMBlackMassCodingStandardTestHelpers::CreateTestActor(World);

	// [test.abort.null] If a system not under test can return a null pointer, use the
	// ABORT_TEST_IF_NULL macro to log an error and immediately stop test execution,
	// instead of proceeding and causing a crash.
	ABORT_TEST_IF_NULL(TestActor);

	// When checking if it is running
	bool Result = TestActor->IsRunning();

	// Then should not be running
	TestFalse(TEXT("IsRunning() after creating new test actor"), Result);
	
	return true;
}

IMPLEMENT_MODULE_TEST(FTestActor_CheckIsRunningAfterRun_IsRunning)
{
	UWorld* World = CreateWorld();

	// Given a new test actor
	ATBMTestActor* TestActor = BMBlackMassCodingStandardTestHelpers::CreateTestActor(World);
	ABORT_TEST_IF_NULL(TestActor);

	// When checking if it is running after calling Run()
	TestActor->Run();
	bool Result = TestActor->IsRunning();

	// Then should be running
	TestTrue(TEXT("IsRunning() after calling Run"), Result);

	return true;
}

// [test.macros.undefine] Undefine MODULE_TEST_FLAGS, MODULE_TEST_NAME and IMPLEMENT_MODULE_TEST
// at the end of the file to prevent it from being defined twice in unity builds. 
#undef IMPLEMENT_MODULE_TEST
#undef MODULE_TEST_NAME
#undef MODULE_TEST_FLAGS
