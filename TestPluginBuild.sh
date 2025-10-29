#!/bin/bash

# TestPluginBuild.sh
# Linux test script for NetworkReplicationSubsystem plugin
# Usage: ./TestPluginBuild.sh [Configuration] [Platform]
# Example: ./TestPluginBuild.sh Development Linux

set -e

# Default values
CONFIGURATION=${1:-Development}
PLATFORM=${2:-Linux}
PLUGIN_NAME="NetworkReplicationSubsystem"
PROJECT_NAME="NetworkReplication"
UE_DIR="${UE_DIR:-$HOME/UnrealEngine-5.6}"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${GREEN}Testing $PLUGIN_NAME plugin build for $PLATFORM ($CONFIGURATION)${NC}"
echo -e "${YELLOW}UE Directory: $UE_DIR${NC}"

# Check if UE directory exists
if [ ! -d "$UE_DIR" ]; then
    echo -e "${RED}Error: Unreal Engine directory not found at $UE_DIR${NC}"
    echo -e "${YELLOW}Please set UE_DIR environment variable or install UE 5.6 at ~/UnrealEngine-5.6${NC}"
    exit 1
fi

# Check if project file exists
if [ ! -f "${PROJECT_NAME}.uproject" ]; then
    echo -e "${RED}Error: Project file ${PROJECT_NAME}.uproject not found${NC}"
    exit 1
fi

# Check if plugin directory exists
if [ ! -d "Plugins/$PLUGIN_NAME" ]; then
    echo -e "${RED}Error: Plugin directory Plugins/$PLUGIN_NAME not found${NC}"
    exit 1
fi

# Set up environment
export UE5_ROOT="$UE_DIR"
export PATH="$UE_DIR/Engine/Binaries/Linux:$PATH"

# Test 1: Generate project files
echo -e "${BLUE}Test 1: Generating project files...${NC}"
"$UE_DIR/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe" -projectfiles -project="${PROJECT_NAME}.uproject" -game -rocket -progress

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Project files generated successfully${NC}"
else
    echo -e "${RED}✗ Failed to generate project files${NC}"
    exit 1
fi

# Test 2: Build plugin module
echo -e "${BLUE}Test 2: Building plugin module...${NC}"
"$UE_DIR/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe" \
    -project="${PROJECT_NAME}.uproject" \
    -target="${PLUGIN_NAME}" \
    -platform="$PLATFORM" \
    -configuration="$CONFIGURATION" \
    -rocket \
    -progress

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Plugin module built successfully${NC}"
else
    echo -e "${RED}✗ Failed to build plugin module${NC}"
    exit 1
fi

# Test 3: Build project with plugin
echo -e "${BLUE}Test 3: Building project with plugin...${NC}"
"$UE_DIR/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe" \
    -project="${PROJECT_NAME}.uproject" \
    -target="${PROJECT_NAME}" \
    -platform="$PLATFORM" \
    -configuration="$CONFIGURATION" \
    -rocket \
    -progress

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Project with plugin built successfully${NC}"
else
    echo -e "${RED}✗ Failed to build project with plugin${NC}"
    exit 1
fi

# Test 4: Verify plugin files
echo -e "${BLUE}Test 4: Verifying plugin files...${NC}"

PLUGIN_BINARIES="Binaries/$PLATFORM/lib${PLUGIN_NAME}.so"
if [ -f "$PLUGIN_BINARIES" ]; then
    echo -e "${GREEN}✓ Plugin binary found: $PLUGIN_BINARIES${NC}"
else
    echo -e "${YELLOW}⚠ Plugin binary not found: $PLUGIN_BINARIES${NC}"
fi

# Test 5: Check for compilation errors in logs
echo -e "${BLUE}Test 5: Checking for compilation errors...${NC}"
if [ -f "Saved/Logs/UnrealBuildTool.log" ]; then
    ERROR_COUNT=$(grep -c "error:" Saved/Logs/UnrealBuildTool.log || true)
    WARNING_COUNT=$(grep -c "warning:" Saved/Logs/UnrealBuildTool.log || true)
    
    if [ "$ERROR_COUNT" -eq 0 ]; then
        echo -e "${GREEN}✓ No compilation errors found${NC}"
    else
        echo -e "${RED}✗ Found $ERROR_COUNT compilation errors${NC}"
        echo -e "${YELLOW}Check Saved/Logs/UnrealBuildTool.log for details${NC}"
    fi
    
    if [ "$WARNING_COUNT" -gt 0 ]; then
        echo -e "${YELLOW}⚠ Found $WARNING_COUNT warnings${NC}"
    fi
else
    echo -e "${YELLOW}⚠ Build log not found${NC}"
fi

echo -e "${GREEN}Plugin build test completed!${NC}"
echo -e "${YELLOW}Plugin location: Plugins/$PLUGIN_NAME${NC}"
echo -e "${YELLOW}Binary location: $PLUGIN_BINARIES${NC}"
