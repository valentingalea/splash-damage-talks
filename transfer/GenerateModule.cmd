@echo off
cls
echo "
echo " _____       _           _      ______                                 
echo "/  ___|     | |         | |     |  _  \                                
echo "\ `--. _ __ | | __ _ ___| |__   | | | |__ _ _ __ ___   __ _  __ _  ___ 
echo " `--. \ '_ \| |/ _` / __| '_ \  | | | / _` | '_ ` _ \ / _` |/ _` |/ _ \
echo "/\__/ / |_) | | (_| \__ \ | | | | |/ / (_| | | | | | | (_| | (_| |  __/
echo "\____/| .__/|_|\__,_|___/_| |_| |___/ \__,_|_| |_| |_|\__,_|\__, |\___|
echo "      | |                                                    __/ |     
echo "      |_|                                                   |___/      
echo "                                                                     
echo:                                                      
echo Module generator
echo:                                                      

rem get the location of this script no mater from where we get executed
set GETROOT=%~dp0

set /p NAME=Enter the name of the new module:
IF [%NAME%] == [] goto :invalid_name

set /P GENERATE_INTERFACE=Would you like to also generate an interface module[Y/
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

set /P GENERATE_EDITOR=Would you like to also generate an editor only module[Y/N
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
echo    public %NAME%(ReadOnlyTargetRules Target^) : base(Target^)
echo    {
echo       // all options: https://docs.unrealengine.com/latest/INT/Programming
echo:
echo       // enable support for Include-What-You-Use
echo       PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
echo       bEnforceIWYU = true;
echo:
echo       // very good guide from Epic staff member:
echo       // https://answers.unrealengine.com/questions/39838/classinterface-m
echo:
echo       PrivateDependencyModuleNames.AddRange(new string[]
echo       {
echo           // ^[dependency.private^] Add modules here when you need to link
echo           // classes contained in those modules. ^(see BlackMass.build.cs 
echo           "Core",
echo           "CoreUObject",
if not [%INTERFACE_NAME%] == [] (
echo                "%INTERFACE_NAME%",
)
echo       }^);
echo:
echo       PublicIncludePathModuleNames.AddRange(new string[]
echo       {
echo           // ^[include.public^] If you're #including headers from another 
echo           // add those modules here. ^(see BlackMass.build.cs for more inf
echo       }^);
echo:
echo       PrivateIncludePathModuleNames.AddRange(new string[]
echo       {
echo           // ^[include.private^] If you're #including headers from another
echo           // add those modules here. ^(see BlackMass.build.cs for more inf
echo       }^);
echo    }
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
