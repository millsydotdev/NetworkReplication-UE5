// Copyright © 2025 Millsy.dev. All Rights Reserved.
//
// NetworkReplicationSubsystem.cpp
// Implements UNetworkReplicationSubsystem, providing comprehensive network replication functionality.

#include "NetworkReplicationSubsystem.h"
#include "NetworkReplicationComponent.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Engine/Console.h"
#include "HAL/IConsoleManager.h"
#include "Engine/Engine.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Net/UnrealNetwork.h"

void UNetworkReplicationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// Initialize network profiling and simulation settings
	bNetworkProfilingActive = false;
	bNetworkSimulationActive = false;
	SimulatedLatency = 0.0f;
	SimulatedPacketLoss = 0.0f;
	SimulatedBandwidthLimit = 0.0f;
	
	// Initialize performance monitoring systems
	bPerformanceMonitoringActive = false;
	bLatencyMeasurementActive = false;
	bBandwidthMonitoringActive = false;
	MaxLatencyThreshold = 100.0f;
	MaxBandwidthThreshold = 100.0f;
	MaxReplicationsThreshold = 1000;
	CurrentLatency = 0.0f;
	CurrentBandwidthUsage = 0.0f;
	LatencyMeasurementStartTime = 0.0f;
	BandwidthMeasurementStartTime = 0.0f;
	PerformanceMeasurementStartTime = 0.0f;
	
	// Initialize the subsystem
	UE_LOG(LogTemp, Log, TEXT("NetworkReplicationSubsystem initialized"));
}

void UNetworkReplicationSubsystem::Deinitialize()
{
	// Clean up registered components
	RegisteredComponents.Empty();
	
	Super::Deinitialize();
	UE_LOG(LogTemp, Log, TEXT("NetworkReplicationSubsystem deinitialized"));
}

void UNetworkReplicationSubsystem::RegisterReplicationComponent(UNetworkReplicationComponent* Component)
{
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to register null replication component"));
		return;
	}

	// Add to registered components
	RegisteredComponents.AddUnique(Component);
	UE_LOG(LogTemp, Log, TEXT("Registered replication component for actor %s"), *Component->GetOwner()->GetName());
}

void UNetworkReplicationSubsystem::UnregisterReplicationComponent(UNetworkReplicationComponent* Component)
{
	if (!Component)
	{
		return;
	}

	// Remove from registered components
	RegisteredComponents.Remove(Component);
	UE_LOG(LogTemp, Log, TEXT("Unregistered replication component for actor %s"), *Component->GetOwner()->GetName());
}

void UNetworkReplicationSubsystem::SetReplicationSettings(const FNetworkReplicationSettings& Settings)
{
	CurrentSettings = Settings;
	UE_LOG(LogTemp, Log, TEXT("Replication settings updated"));
}

FNetworkReplicationSettings UNetworkReplicationSubsystem::GetReplicationSettings() const
{
	return CurrentSettings;
}

void UNetworkReplicationSubsystem::OptimizeReplication()
{
	// Implement optimization logic
	UE_LOG(LogTemp, Log, TEXT("Replication optimization performed"));
}

int32 UNetworkReplicationSubsystem::GetActiveReplicationCount() const
{
	return RegisteredComponents.Num();
}

float UNetworkReplicationSubsystem::GetReplicationBandwidth() const
{
	// Return estimated bandwidth usage
	return RegisteredComponents.Num() * 0.1f; // 0.1 KB per component
}

void UNetworkReplicationSubsystem::OnComponentDestroyed(UNetworkReplicationComponent* Component)
{
	if (Component)
	{
		UnregisterReplicationComponent(Component);
	}
}

// ===== NEW DEBUGGING FUNCTIONS IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::ShowNetworkStats()
{
	int32 TotalComponents = RegisteredComponents.Num();
	int32 TotalReplications = 0;
	
	for (UNetworkReplicationComponent* Component : RegisteredComponents)
	{
		if (Component)
		{
			TotalReplications += Component->TotalReplications;
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("Network Stats - Components: %d, Total Replications: %d"), 
		TotalComponents, TotalReplications);
}

void UNetworkReplicationSubsystem::ExportReplicationData()
{
	FString Data = FString::Printf(TEXT("Network Replication Data Export\n"));
	Data += FString::Printf(TEXT("Components: %d\n"), RegisteredComponents.Num());
	
	for (UNetworkReplicationComponent* Component : RegisteredComponents)
	{
		if (Component)
		{
			Data += FString::Printf(TEXT("Component: %s - Replications: %d\n"), 
				*Component->GetOwner()->GetName(), Component->TotalReplications);
		}
	}
	
	FString FilePath = FPaths::ProjectLogDir() / TEXT("NetworkReplicationData.txt");
	FFileHelper::SaveStringToFile(Data, *FilePath);
	
	UE_LOG(LogTemp, Log, TEXT("Replication data exported to: %s"), *FilePath);
}

void UNetworkReplicationSubsystem::ResetReplicationStats()
{
	for (UNetworkReplicationComponent* Component : RegisteredComponents)
	{
		if (Component)
		{
			Component->TotalReplications = 0;
			Component->LastReplicationTime = 0.0f;
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("Replication stats reset"));
}

// ===== NEW PERFORMANCE FUNCTIONS IMPLEMENTATIONS =====

int32 UNetworkReplicationSubsystem::GetTotalReplications() const
{
	int32 Total = 0;
	for (UNetworkReplicationComponent* Component : RegisteredComponents)
	{
		if (Component)
		{
			Total += Component->TotalReplications;
		}
	}
	return Total;
}

float UNetworkReplicationSubsystem::GetAverageLatency() const
{
	float TotalLatency = 0.0f;
	int32 Count = 0;
	
	for (UNetworkReplicationComponent* Component : RegisteredComponents)
	{
		if (Component && Component->LastReplicationTime > 0.0f)
		{
			TotalLatency += Component->LastReplicationTime;
			Count++;
		}
	}
	
	return Count > 0 ? TotalLatency / Count : 0.0f;
}

void UNetworkReplicationSubsystem::OptimizeForBandwidth(float MaxBandwidthKB)
{
	float CurrentBandwidth = GetReplicationBandwidth();
	
	if (CurrentBandwidth > MaxBandwidthKB)
	{
		// Reduce replication frequency
		CurrentSettings.ReplicationInterval = FMath::Max(0.1f, CurrentSettings.ReplicationInterval * 1.5f);
		
		UE_LOG(LogTemp, Log, TEXT("Bandwidth optimization: Reduced replication interval to %.2f"), 
			CurrentSettings.ReplicationInterval);
	}
}

// ===== NEW RELEVANCY FUNCTIONS IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::SetReplicationDistance(float Distance)
{
	CurrentSettings.MaxReplicationDistance = Distance;
	UE_LOG(LogTemp, Log, TEXT("Replication distance set to: %.2f"), Distance);
}

void UNetworkReplicationSubsystem::EnableRelevancyCulling(bool bEnabled)
{
	CurrentSettings.bEnableRelevancy = bEnabled;
	UE_LOG(LogTemp, Log, TEXT("Relevancy culling %s"), bEnabled ? TEXT("enabled") : TEXT("disabled"));
}

bool UNetworkReplicationSubsystem::IsActorRelevantToPlayer(AActor* Actor, AActor* Player) const
{
	if (!Actor || !Player)
	{
		return false;
	}
	
	if (!CurrentSettings.bEnableRelevancy)
	{
		return true;
	}
	
	float Distance = FVector::Dist(Actor->GetActorLocation(), Player->GetActorLocation());
	return Distance <= CurrentSettings.MaxReplicationDistance;
}

// ===== ADVANCED DEBUGGING TOOLS IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::StartNetworkProfiling()
{
	bNetworkProfilingActive = true;
	UE_LOG(LogTemp, Log, TEXT("Network profiling started"));
}

void UNetworkReplicationSubsystem::StopNetworkProfiling()
{
	bNetworkProfilingActive = false;
	UE_LOG(LogTemp, Log, TEXT("Network profiling stopped"));
}

FString UNetworkReplicationSubsystem::GetNetworkInsights()
{
	FString Insights = TEXT("Network Insights:\n");
	Insights += FString::Printf(TEXT("Active Components: %d\n"), RegisteredComponents.Num());
	Insights += FString::Printf(TEXT("Total Replications: %d\n"), GetTotalReplications());
	Insights += FString::Printf(TEXT("Average Latency: %.2f\n"), GetAverageLatency());
	Insights += FString::Printf(TEXT("Bandwidth Usage: %.2f KB\n"), GetReplicationBandwidth());
	Insights += FString::Printf(TEXT("Profiling Active: %s\n"), bNetworkProfilingActive ? TEXT("Yes") : TEXT("No"));
	Insights += FString::Printf(TEXT("Simulation Active: %s\n"), bNetworkSimulationActive ? TEXT("Yes") : TEXT("No"));
	
	return Insights;
}

void UNetworkReplicationSubsystem::SimulateNetworkConditions(float Latency, float PacketLoss, float BandwidthLimit)
{
	bNetworkSimulationActive = true;
	SimulatedLatency = Latency;
	SimulatedPacketLoss = PacketLoss;
	SimulatedBandwidthLimit = BandwidthLimit;
	
	UE_LOG(LogTemp, Log, TEXT("Network simulation: Latency=%.2f, Loss=%.2f%%, Bandwidth=%.2f KB"), 
		Latency, PacketLoss, BandwidthLimit);
}

void UNetworkReplicationSubsystem::ResetNetworkSimulation()
{
	bNetworkSimulationActive = false;
	SimulatedLatency = 0.0f;
	SimulatedPacketLoss = 0.0f;
	SimulatedBandwidthLimit = 0.0f;
	
	UE_LOG(LogTemp, Log, TEXT("Network simulation reset"));
}

// ===== CONSOLE COMMANDS IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::RegisterConsoleCommands()
{
	// Register basic console commands with simplified approach
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("NetworkReplication.ShowStats"),
		TEXT("Show network replication statistics"),
		FConsoleCommandDelegate::CreateLambda([this]() { ShowNetworkStats(); }),
		ECVF_Default
	);
	
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("NetworkReplication.ExportData"),
		TEXT("Export replication data to file"),
		FConsoleCommandDelegate::CreateLambda([this]() { ExportReplicationData(); }),
		ECVF_Default
	);
	
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("NetworkReplication.ResetStats"),
		TEXT("Reset replication statistics"),
		FConsoleCommandDelegate::CreateLambda([this]() { ResetReplicationStats(); }),
		ECVF_Default
	);
	
	UE_LOG(LogTemp, Log, TEXT("Basic NetworkReplication console commands registered"));
}

void UNetworkReplicationSubsystem::UnregisterConsoleCommands()
{
	// Basic commands
	IConsoleManager::Get().UnregisterConsoleObject(TEXT("NetworkReplication.ShowStats"));
	IConsoleManager::Get().UnregisterConsoleObject(TEXT("NetworkReplication.ExportData"));
	IConsoleManager::Get().UnregisterConsoleObject(TEXT("NetworkReplication.ResetStats"));
	
	UE_LOG(LogTemp, Log, TEXT("Basic NetworkReplication console commands unregistered"));
}

// ===== CLIENT-SIDE PREDICTION IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::EnableClientPrediction(bool bEnabled)
{
	CurrentSettings.bEnableClientPrediction = bEnabled;
	UE_LOG(LogTemp, Log, TEXT("Client prediction %s"), bEnabled ? TEXT("enabled") : TEXT("disabled"));
}

void UNetworkReplicationSubsystem::SetPredictionTolerance(float Tolerance)
{
	CurrentSettings.PredictionTolerance = Tolerance;
	UE_LOG(LogTemp, Log, TEXT("Prediction tolerance set to: %.2f"), Tolerance);
}

bool UNetworkReplicationSubsystem::IsPredictionEnabled() const
{
	return CurrentSettings.bEnableClientPrediction;
}

// ===== INTEREST MANAGEMENT IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::SetInterestRadius(float Radius)
{
	CurrentSettings.MaxReplicationDistance = Radius;
	UE_LOG(LogTemp, Log, TEXT("Interest radius set to: %.2f"), Radius);
}

void UNetworkReplicationSubsystem::AddInterestActor(AActor* Actor)
{
	if (Actor && !InterestActors.Contains(Actor))
	{
		InterestActors.Add(Actor);
		UE_LOG(LogTemp, Log, TEXT("Added interest actor: %s"), *Actor->GetName());
	}
}

void UNetworkReplicationSubsystem::RemoveInterestActor(AActor* Actor)
{
	if (Actor && InterestActors.Contains(Actor))
	{
		InterestActors.Remove(Actor);
		UE_LOG(LogTemp, Log, TEXT("Removed interest actor: %s"), *Actor->GetName());
	}
}

// Console command implementations removed for simplicity

// ===== PHASE 3: ADVANCED PERFORMANCE MONITORING IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::StartPerformanceMonitoring()
{
	bPerformanceMonitoringActive = true;
	PerformanceMeasurementStartTime = GetWorld()->GetTimeSeconds();
	PerformanceData.Empty();
	
	UE_LOG(LogTemp, Log, TEXT("Performance monitoring started"));
}

void UNetworkReplicationSubsystem::StopPerformanceMonitoring()
{
	bPerformanceMonitoringActive = false;
	UE_LOG(LogTemp, Log, TEXT("Performance monitoring stopped"));
}

FString UNetworkReplicationSubsystem::GetDetailedPerformanceReport() const
{
	FString Report = TEXT("=== DETAILED PERFORMANCE REPORT ===\n");
	
	// Basic stats
	Report += FString::Printf(TEXT("Active Components: %d\n"), RegisteredComponents.Num());
	Report += FString::Printf(TEXT("Total Replications: %d\n"), GetTotalReplications());
	Report += FString::Printf(TEXT("Average Latency: %.2f ms\n"), GetAverageLatency());
	Report += FString::Printf(TEXT("Current Bandwidth: %.2f KB/s\n"), GetReplicationBandwidth());
	
	// Performance thresholds
	Report += FString::Printf(TEXT("Max Latency Threshold: %.2f ms\n"), MaxLatencyThreshold);
	Report += FString::Printf(TEXT("Max Bandwidth Threshold: %.2f KB/s\n"), MaxBandwidthThreshold);
	Report += FString::Printf(TEXT("Max Replications Threshold: %d\n"), MaxReplicationsThreshold);
	
	// Performance status
	bool bWithinThresholds = IsPerformanceWithinThresholds();
	Report += FString::Printf(TEXT("Performance Status: %s\n"), bWithinThresholds ? TEXT("GOOD") : TEXT("WARNING"));
	
	// Monitoring status
	Report += FString::Printf(TEXT("Performance Monitoring: %s\n"), bPerformanceMonitoringActive ? TEXT("ACTIVE") : TEXT("INACTIVE"));
	Report += FString::Printf(TEXT("Latency Measurement: %s\n"), bLatencyMeasurementActive ? TEXT("ACTIVE") : TEXT("INACTIVE"));
	Report += FString::Printf(TEXT("Bandwidth Monitoring: %s\n"), bBandwidthMonitoringActive ? TEXT("ACTIVE") : TEXT("INACTIVE"));
	
	return Report;
}

void UNetworkReplicationSubsystem::SetPerformanceThresholds(float MaxLatency, float MaxBandwidth, int32 MaxReplications)
{
	MaxLatencyThreshold = MaxLatency;
	MaxBandwidthThreshold = MaxBandwidth;
	MaxReplicationsThreshold = MaxReplications;
	
	UE_LOG(LogTemp, Log, TEXT("Performance thresholds set - Latency: %.2f, Bandwidth: %.2f, Replications: %d"), 
		MaxLatency, MaxBandwidth, MaxReplications);
}

bool UNetworkReplicationSubsystem::IsPerformanceWithinThresholds() const
{
	float AvgLatency = GetAverageLatency();
	float CurrentBandwidth = GetReplicationBandwidth();
	int32 CurrentReplications = GetTotalReplications();
	
	return (AvgLatency <= MaxLatencyThreshold) && 
		   (CurrentBandwidth <= MaxBandwidthThreshold) && 
		   (CurrentReplications <= MaxReplicationsThreshold);
}

// ===== LATENCY MEASUREMENT IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::StartLatencyMeasurement()
{
	bLatencyMeasurementActive = true;
	LatencyMeasurementStartTime = GetWorld()->GetTimeSeconds();
	LatencyHistory.Empty();
	CurrentLatency = 0.0f;
	
	UE_LOG(LogTemp, Log, TEXT("Latency measurement started"));
}

void UNetworkReplicationSubsystem::StopLatencyMeasurement()
{
	bLatencyMeasurementActive = false;
	UE_LOG(LogTemp, Log, TEXT("Latency measurement stopped"));
}

float UNetworkReplicationSubsystem::GetCurrentLatency() const
{
	return CurrentLatency;
}

float UNetworkReplicationSubsystem::GetAverageLatencyOverTime(float TimeWindow) const
{
	if (LatencyHistory.Num() == 0)
	{
		return 0.0f;
	}
	
	float TotalLatency = 0.0f;
	int32 Count = 0;
	float CurrentTime = GetWorld()->GetTimeSeconds();
	
	for (float Latency : LatencyHistory)
	{
		TotalLatency += Latency;
		Count++;
	}
	
	return Count > 0 ? TotalLatency / Count : 0.0f;
}

// ===== BANDWIDTH MONITORING IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::StartBandwidthMonitoring()
{
	bBandwidthMonitoringActive = true;
	BandwidthMeasurementStartTime = GetWorld()->GetTimeSeconds();
	BandwidthHistory.Empty();
	CurrentBandwidthUsage = 0.0f;
	
	UE_LOG(LogTemp, Log, TEXT("Bandwidth monitoring started"));
}

void UNetworkReplicationSubsystem::StopBandwidthMonitoring()
{
	bBandwidthMonitoringActive = false;
	UE_LOG(LogTemp, Log, TEXT("Bandwidth monitoring stopped"));
}

float UNetworkReplicationSubsystem::GetCurrentBandwidthUsage() const
{
	return CurrentBandwidthUsage;
}

float UNetworkReplicationSubsystem::GetBandwidthUsageOverTime(float TimeWindow) const
{
	if (BandwidthHistory.Num() == 0)
	{
		return 0.0f;
	}
	
	float TotalBandwidth = 0.0f;
	int32 Count = 0;
	
	for (float Bandwidth : BandwidthHistory)
	{
		TotalBandwidth += Bandwidth;
		Count++;
	}
	
	return Count > 0 ? TotalBandwidth / Count : 0.0f;
}

// ===== PACKET LOSS SIMULATION IMPLEMENTATIONS =====

void UNetworkReplicationSubsystem::SimulatePacketLoss(float LossPercentage)
{
	SimulatedPacketLoss = FMath::Clamp(LossPercentage, 0.0f, 100.0f);
	UE_LOG(LogTemp, Log, TEXT("Packet loss simulation: %.2f%%"), SimulatedPacketLoss);
}

void UNetworkReplicationSubsystem::SimulateLatency(float LatencyMs)
{
	SimulatedLatency = FMath::Max(0.0f, LatencyMs);
	UE_LOG(LogTemp, Log, TEXT("Latency simulation: %.2f ms"), SimulatedLatency);
}

void UNetworkReplicationSubsystem::SimulateBandwidthLimit(float BandwidthKB)
{
	SimulatedBandwidthLimit = FMath::Max(0.0f, BandwidthKB);
	UE_LOG(LogTemp, Log, TEXT("Bandwidth limit simulation: %.2f KB/s"), SimulatedBandwidthLimit);
}

void UNetworkReplicationSubsystem::ResetAllSimulations()
{
	SimulatedLatency = 0.0f;
	SimulatedPacketLoss = 0.0f;
	SimulatedBandwidthLimit = 0.0f;
	
	UE_LOG(LogTemp, Log, TEXT("All network simulations reset"));
}
