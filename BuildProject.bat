@echo off
echo Building NetworkReplication UE 5.6 Project...

REM Set the UE5 path - adjust this if your UE5 installation is elsewhere
set UE5_PATH="C:\Program Files\Epic Games\UE_5.6"
set UBT_PATH=%UE5_PATH%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe

REM Check if UE5 exists
if not exist %UBT_PATH% (
    echo Error: Unreal Engine 5.6 not found at %UE5_PATH%
    echo Please update the UE5_PATH variable in this script to match your installation.
    pause
    exit /b 1
)

REM Check if project file exists
if not exist "%~dp0NetworkReplication.uproject" (
    echo Error: NetworkReplication.uproject not found in current directory.
    echo Please run this script from the project root directory.
    pause
    exit /b 1
)

REM Generate project files first
echo Generating project files...
%UBT_PATH% -projectfiles -project="%~dp0NetworkReplication.uproject" -game -rocket -progress

if %ERRORLEVEL% neq 0 (
    echo Error: Failed to generate project files.
    pause
    exit /b 1
)

echo Project files generated successfully!

REM Build the project
echo Building NetworkReplication project...
%UBT_PATH% NetworkReplication Win64 Development -project="%~dp0NetworkReplication.uproject" -rocket -progress

if %ERRORLEVEL% equ 0 (
    echo.
    echo Build completed successfully!
    echo Your UE5.6 project is now compiled and ready.
    echo.
) else (
    echo.
    echo Error: Build failed.
    echo Check the error messages above for details.
    echo.
)

pause
