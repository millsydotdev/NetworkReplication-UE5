#!/bin/bash

# BuildProject.sh
# Linux build script for NetworkReplication UE5 project
# Usage: ./BuildProject.sh [Configuration] [Platform]
# Example: ./BuildProject.sh Development Linux

set -e

# Default values
CONFIGURATION=${1:-Development}
PLATFORM=${2:-Linux}
PROJECT_NAME="NetworkReplication"
UE_DIR="${UE_DIR:-$HOME/UnrealEngine-5.6}"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}Building $PROJECT_NAME for $PLATFORM ($CONFIGURATION)${NC}"
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

# Set up environment
export UE5_ROOT="$UE_DIR"
export PATH="$UE_DIR/Engine/Binaries/Linux:$PATH"

# Generate project files
echo -e "${YELLOW}Generating project files...${NC}"
"$UE_DIR/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe" -projectfiles -project="${PROJECT_NAME}.uproject" -game -rocket -progress

# Build the project
echo -e "${YELLOW}Building project...${NC}"
"$UE_DIR/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe" \
    -project="${PROJECT_NAME}.uproject" \
    -target="${PROJECT_NAME}" \
    -platform="$PLATFORM" \
    -configuration="$CONFIGURATION" \
    -rocket \
    -progress

# Build the editor target
echo -e "${YELLOW}Building editor target...${NC}"
"$UE_DIR/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe" \
    -project="${PROJECT_NAME}.uproject" \
    -target="${PROJECT_NAME}Editor" \
    -platform="$PLATFORM" \
    -configuration="$CONFIGURATION" \
    -rocket \
    -progress

echo -e "${GREEN}Build completed successfully!${NC}"
echo -e "${YELLOW}Executable location: Binaries/$PLATFORM/${PROJECT_NAME}${NC}"
