@echo off

REM Test script to verify plugin compilation using official UE5 build tools
REM Based on the pattern you provided

set VERSION=5.6
set PLUGIN_PATH="%cd%\..\Plugins\NetworkReplicationSubsystem\NetworkReplicationSubsystem.uplugin"
set RUNUAT_PATH="C:\Program Files\Epic Games\UE_%VERSION%\Engine\Build\BatchFiles\RunUAT.bat"
set PACKAGE_PATH="%TEMP%\NetworkReplicationTest_%VERSION%"

set EXTRA_PARAMS= -StrictIncludes

echo.
echo Testing Network Replication Subsystem Plugin compilation for UE%VERSION%
echo Plugin Path: %PLUGIN_PATH%
echo Package Path: %PACKAGE_PATH%
echo.

REM Check if RunUAT exists
if not exist %RUNUAT_PATH% (
    echo ERROR: RunUAT not found at %RUNUAT_PATH%
    echo Please ensure UE5.6 is installed and EPIC_LIBRARY environment variable is set
    pause
    exit /b 1
)

REM Check if plugin exists
if not exist %PLUGIN_PATH% (
    echo ERROR: Plugin not found at %PLUGIN_PATH%
    echo Current directory: %cd%
    pause
    exit /b 1
)

echo Running Unreal Automation Tool (UAT)...
echo.

%RUNUAT_PATH% BuildPlugin -Plugin=%PLUGIN_PATH% -Package=%PACKAGE_PATH% -HostPlatforms=Win64 -NoTargetPlatforms %EXTRA_PARAMS%

if %ERRORLEVEL% EQU 0 (
    echo.
    echo SUCCESS: Plugin compiled successfully!
    echo Test package created at: %PACKAGE_PATH%
) else (
    echo.
    echo ERROR: Plugin compilation failed with error code %ERRORLEVEL%
)

echo.
pause
