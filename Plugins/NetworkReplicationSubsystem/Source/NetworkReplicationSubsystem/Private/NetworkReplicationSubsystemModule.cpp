// Copyright © 2025 Millsy.dev. All Rights Reserved.
//
// NetworkReplicationSubsystemModule.cpp
// Implements FNetworkReplicationSubsystemModule, the main module interface for the Network Replication Subsystem plugin.

#include "NetworkReplicationSubsystemModule.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FNetworkReplicationSubsystemModule"

void FNetworkReplicationSubsystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file
}

void FNetworkReplicationSubsystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNetworkReplicationSubsystemModule, NetworkReplicationSubsystem);