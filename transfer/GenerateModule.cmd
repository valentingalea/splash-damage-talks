@echo off
cls
echo "    ____  __           __      __  ___                "
echo "   / __ )/ /___ ______/ /__   /  |/  /___ ___________ "
echo "  / __  / / __ `/ ___/ //_/  / /|_/ / __ `/ ___/ ___/ "
echo " / /_/ / / /_/ / /__/ ,<    / /  / / /_/ (__  |__  )  "
echo "/_____/_/\__,_/\___/_/|_|  /_/  /_/\__,_/____/____/   "
echo "                                                      "
echo:                                                      
echo Module generator
echo:                                                      

rem get the location of this script no mater from where we get executed
set GETROOT=%~dp0

set /p NAME=Enter the name of the new module:
IF [%NAME%] == [] goto :invalid_name

set /P GENERATE_INTERFACE=Would you like to also generate an interface module[Y/N]?
if /I "%GENERATE_INTERFACE%" EQU "Y" (
	set INTERFACE_NAME=%NAME%Interface
) else if /I "%GENERATE_INTERFACE%" EQU "N" (
	set INTERFACE_NAME=
) else goto :invalid_choice

set /P GENERATE_TESTS=Would you like to also generate a test module[Y/N]?
if /I "%GENERATE_TESTS%" EQU "Y" (
	set TEST_NAME=%NAME%Test
) else if /I "%GENERATE_TESTS%" EQU "N" (
	set TEST_NAME=
) else goto :invalid_choice

set /P GENERATE_EDITOR=Would you like to also generate an editor only module[Y/N]?
if /I "%GENERATE_EDITOR%" EQU "Y" (
	set EDITOR_NAME=%NAME%Editor
) else if /I "%GENERATE_EDITOR%" EQU "N" (
	set EDITOR_NAME=
) else goto :invalid_choice

rem ***************************************************************************
echo:
echo Generating modules:
echo %NAME%
if not [%INTERFACE_NAME%] == [] echo %INTERFACE_NAME%
if not [%TEST_NAME%] == [] echo %TEST_NAME%
if not [%EDITOR_NAME%] == [] echo %EDITOR_NAME%

echo *** creating folder structure...
mkdir %NAME%
cd %NAME%
set ROOT=%CD%
mkdir Runtime
mkdir Runtime\Public
mkdir Runtime\Private
set RUNTIME_ROOT= %ROOT%\Runtime
if not [%INTERFACE_NAME%] == [] (
	mkdir Interface
	mkdir Interface\Public
	mkdir Interface\Private
	set INTERFACE_ROOT= %ROOT%\Interface
) else (
	set INTERFACE_ROOT=
)
if not [%TEST_NAME%] == [] (
	mkdir Test
	mkdir Test\Public
	mkdir Test\Private
	set TEST_ROOT= %ROOT%\Test
) else (
	set TEST_ROOT=
)
if not [%EDITOR_NAME%] == [] (
	mkdir Editor
	mkdir Editor\Public
	mkdir Editor\Private
	set EDITOR_ROOT= %ROOT%\Editor
) else (
	set EDITOR_ROOT=
)

rem ***************************************************************************
echo *** creating %NAME% main header
cd %RUNTIME_ROOT%\Public
(
echo #pragma once
echo:
echo #include "CoreMinimal.h"
) > %NAME%.h

rem ***************************************************************************
echo *** creating %NAME% main file
cd %RUNTIME_ROOT%\Private
(
echo #include "%NAME%.h"
echo #include "Modules/ModuleManager.h"
echo:
echo IMPLEMENT_GAME_MODULE( FDefaultGameModuleImpl, %NAME% ^);
) > %NAME%.cpp

rem ***************************************************************************
echo *** creating build rules...
cd %RUNTIME_ROOT%
(
echo using UnrealBuildTool;
echo:
echo public class %NAME% : ModuleRules
echo {
echo 	public %NAME%(ReadOnlyTargetRules Target^) : base(Target^)
echo 	{
echo 		// all options: https://docs.unrealengine.com/latest/INT/Programming/UnrealBuildSystem/ModuleFiles/index.html
echo:
echo 		// enable support for Include-What-You-Use
echo 		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
echo 		bEnforceIWYU = true;
echo:
echo 		// very good guide from Epic staff member:
echo 		// https://answers.unrealengine.com/questions/39838/classinterface-multiple-modules-confusion.html
echo:
echo 		PrivateDependencyModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[dependency.private^] Add modules here when you need to link against public functions or
echo 			// classes contained in those modules. ^(see BlackMass.build.cs for more info^)
echo 			"Core",
echo 			"CoreUObject",
if not [%INTERFACE_NAME%] == [] (
echo				"%INTERFACE_NAME%",
)
echo 		}^);
echo:
echo 		PublicIncludePathModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[include.public^] If you're #including headers from another module inside this module's public headers,
echo 			// add those modules here. ^(see BlackMass.build.cs for more info^)
echo 		}^);
echo:
echo 		PrivateIncludePathModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[include.private^] If you're #including headers from another module inside this module's private h/cpp files,
echo 			// add those modules here. ^(see BlackMass.build.cs for more info^)
echo 		}^);
echo 	}
echo }
) > %NAME%.Build.cs

rem ***************************************************************************
:try_generate_interface_module
if [%INTERFACE_NAME%] == [] goto :try_generate_test_module

rem ***************************************************************************
echo *** creating %INTERFACE_NAME% main header
cd %INTERFACE_ROOT%\Public
(
echo #pragma once
echo:
echo #include "CoreMinimal.h"
) > %INTERFACE_NAME%.h

echo *** creating %INTERFACE_NAME% main file
cd %INTERFACE_ROOT%\Private
(
echo #include "%INTERFACE_NAME%.h"
echo #include "Modules/ModuleManager.h"
echo:
echo IMPLEMENT_GAME_MODULE( FDefaultGameModuleImpl, %INTERFACE_NAME% ^);
) > %INTERFACE_NAME%.cpp

rem ***************************************************************************
echo *** creating build rules...
cd %INTERFACE_ROOT%
(
echo using UnrealBuildTool;
echo:
echo public class %INTERFACE_NAME% : ModuleRules
echo {
echo 	public %INTERFACE_NAME%(ReadOnlyTargetRules Target^) : base(Target^)
echo 	{
echo 		// all options: https://docs.unrealengine.com/latest/INT/Programming/UnrealBuildSystem/ModuleFiles/index.html
echo:
echo 		// enable support for Include-What-You-Use
echo 		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
echo 		bEnforceIWYU = true;
echo:
echo 		// very good guide from Epic staff member:
echo 		// https://answers.unrealengine.com/questions/39838/classinterface-multiple-modules-confusion.html
echo:
echo 		PrivateDependencyModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[dependency.private^] Add modules here when you need to link against public functions or
echo 			// classes contained in those modules. ^(see BlackMass.build.cs for more info^)
echo 			"Core",
echo 			"CoreUObject",
echo 		}^);
echo:
echo 		PublicIncludePathModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[include.public^] If you're #including headers from another module inside this module's public headers,
echo 			// add those modules here. ^(see BlackMass.build.cs for more info^)
echo 		}^);
echo:
echo 		PrivateIncludePathModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[include.private^] If you're #including headers from another module inside this module's private h/cpp files,
echo 			// add those modules here. ^(see BlackMass.build.cs for more info^)
echo 		}^);
echo 	}
echo }
) > %INTERFACE_NAME%.Build.cs

rem ***************************************************************************
:try_generate_test_module
if [%TEST_NAME%] == [] goto :try_generate_editor_module

echo - creating %TEST_NAME% main header...
cd %TEST_ROOT%\Public
(
echo #pragma once
echo:
echo #include "CoreMinimal.h"
) > %TEST_NAME%.h

rem ***************************************************************************
echo - creating %TEST_NAME% main file...
cd %TEST_ROOT%\Private
(
echo #include "%TEST_NAME%.h"
echo #include "Modules/ModuleManager.h"
echo:
echo IMPLEMENT_GAME_MODULE( FDefaultGameModuleImpl, %TEST_NAME% ^);
) > %TEST_NAME%.cpp

rem ***************************************************************************
echo - creating %TEST_NAME% build rules...
cd %TEST_ROOT%
(
echo using UnrealBuildTool;
echo:
echo public class %TEST_NAME% : ModuleRules
echo {
echo 	public %TEST_NAME%(ReadOnlyTargetRules Target^) : base(Target^)
echo 	{
echo 		// all options: https://docs.unrealengine.com/latest/INT/Programming/UnrealBuildSystem/ModuleFiles/index.html
echo:
echo 		// enable support for Include-What-You-Use
echo 		bImportTestModuleSymbols = true;
echo 		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
echo 		bEnforceIWYU = true;
echo:
echo 		// very good guide from Epic staff member:
echo 		// https://answers.unrealengine.com/questions/39838/classinterface-multiple-modules-confusion.html
echo:
echo 		PrivateDependencyModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[dependency.private^] Add modules here when you need to link against public functions or
echo 			// classes contained in those modules. ^(see BlackMass.build.cs for more info^)
echo 			"Core",
echo 			"CoreUObject",
echo 			"SDTestHarness",
if not [%INTERFACE_NAME%] == [] (
echo				"%INTERFACE_NAME%",
)
echo 			"%NAME%",
echo 		}^);
echo:
echo 		PrivateIncludePathModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[include.private^] If you're #including headers from another module inside this module's private h/cpp files,
echo 			// add those modules here. ^(see BlackMass.build.cs for more info^)
echo 		}^);
echo 	}
echo }
) > %TEST_NAME%.Build.cs

rem ***************************************************************************
:try_generate_editor_module
if [%EDITOR_NAME%] == [] goto :module_generation_complete

echo - creating %EDITOR_NAME% main header...
cd %EDITOR_ROOT%\Public
(
echo #pragma once
echo:
echo #include "CoreMinimal.h"
) > %EDITOR_NAME%.h

rem ***************************************************************************
echo - creating %EDITOR_NAME% main file...
cd %EDITOR_ROOT%\Private
(
echo #include "%EDITOR_NAME%.h"
echo #include "Modules/ModuleManager.h"
echo:
echo IMPLEMENT_GAME_MODULE( FDefaultGameModuleImpl, %EDITOR_NAME% ^);
) > %EDITOR_NAME%.cpp

rem ***************************************************************************
echo - creating %EDITOR_NAME% build rules...
cd %EDITOR_ROOT%
(
echo using UnrealBuildTool;
echo:
echo public class %EDITOR_NAME% : ModuleRules
echo {
echo 	public %EDITOR_NAME%(ReadOnlyTargetRules Target^) : base(Target^)
echo 	{
echo 		// all options: https://docs.unrealengine.com/latest/INT/Programming/UnrealBuildSystem/ModuleFiles/index.html
echo:
echo 		// enable support for Include-What-You-Use
echo 		bImportTestModuleSymbols = true;
echo 		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
echo 		bEnforceIWYU = true;
echo:
echo 		// very good guide from Epic staff member:
echo 		// https://answers.unrealengine.com/questions/39838/classinterface-multiple-modules-confusion.html
echo:
echo 		PrivateDependencyModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[dependency.private^] Add modules here when you need to link against public functions or
echo 			// classes contained in those modules. ^(see BlackMass.build.cs for more info^)
echo 			"Core",
echo 			"CoreUObject",
if not [%INTERFACE_NAME%] == [] (
echo				"%INTERFACE_NAME%",
)
echo 			"%NAME%",
echo 		}^);
echo:
echo 		PrivateIncludePathModuleNames.AddRange(new string[]
echo 		{
echo 			// ^[include.private^] If you're #including headers from another module inside this module's private h/cpp files,
echo 			// add those modules here. ^(see BlackMass.build.cs for more info^)
echo 		}^);
echo 	}
echo }
) > %EDITOR_NAME%.Build.cs

rem ***************************************************************************

:module_generation_complete
echo *** %NAME% All done. Module(s) generated! Press any key to quit.
cd %GETROOT%
goto :end

:invalid_choice
echo The choice was invalid. Aborting!
goto :end

:invalid_name
echo The specified name was invalid. Aborting!
goto :end

:end
rem TODO: don't pause when triggered from cmd line, see https://stackoverflow.com/questions/886848/how-to-make-windows-batch-file-pause-when-double-clicked
pause
