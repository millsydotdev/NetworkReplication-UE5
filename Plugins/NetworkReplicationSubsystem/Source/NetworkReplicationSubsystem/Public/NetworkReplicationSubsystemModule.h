// Copyright © 2025 Millsy.dev. All Rights Reserved.
//
// NetworkReplicationSubsystemModule.h
// Declares FNetworkReplicationSubsystemModule, the main module interface for the Network Replication Subsystem plugin.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FNetworkReplicationSubsystemModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};