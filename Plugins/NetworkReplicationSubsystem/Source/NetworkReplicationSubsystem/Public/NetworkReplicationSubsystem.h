// Copyright © 2025 Millsy.dev. All Rights Reserved.
//
// NetworkReplicationSubsystem.h
// Declares UNetworkReplicationSubsystem, a comprehensive network replication subsystem for Unreal Engine 5.6+.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "HAL/IConsoleManager.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Engine/Console.h"
#include "Net/UnrealNetwork.h"
#include "NetworkReplicationSubsystem.generated.h"

class UNetworkReplicationComponent;

USTRUCT(BlueprintType)
struct FNetworkReplicationSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Replication")
	float ReplicationInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Replication")
	float MaxReplicationDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Replication")
	bool bEnableCompression;

	// ===== NEW OPTIMIZATION SETTINGS =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Replication|Optimization")
	bool bEnableClientPrediction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Replication|Optimization")
	bool bEnableInterestManagement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Replication|Optimization")
	float PredictionTolerance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Replication|Optimization")
	int32 MaxReplicationFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Replication|Optimization")
	bool bEnableRelevancy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Replication|Optimization")
	float BandwidthLimitKB;

	FNetworkReplicationSettings()
		: ReplicationInterval(0.05f)
		, MaxReplicationDistance(15000.0f)
		, bEnableCompression(true)
		, bEnableClientPrediction(true)
		, bEnableInterestManagement(true)
		, PredictionTolerance(0.1f)
		, MaxReplicationFrequency(60)
		, bEnableRelevancy(true)
		, BandwidthLimitKB(100.0f)
	{}
};

UCLASS(BlueprintType, Blueprintable)
class NETWORKREPLICATIONSUBSYSTEM_API UNetworkReplicationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Management")
	void RegisterReplicationComponent(UNetworkReplicationComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Management")
	void UnregisterReplicationComponent(UNetworkReplicationComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Optimization")
	void SetReplicationSettings(const FNetworkReplicationSettings& Settings);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Optimization")
	FNetworkReplicationSettings GetReplicationSettings() const;

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Optimization")
	void OptimizeReplication();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Monitoring")
	int32 GetActiveReplicationCount() const;

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Monitoring")
	float GetReplicationBandwidth() const;

	/** Debugging and monitoring functions */
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug")
	void ShowNetworkStats();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug")
	void ExportReplicationData();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug")
	void ResetReplicationStats();

	/** Performance monitoring and optimization functions */
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance")
	int32 GetTotalReplications() const;

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance")
	float GetAverageLatency() const;

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance")
	void OptimizeForBandwidth(float MaxBandwidthKB);

	/** Relevancy and culling functions */
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Optimization")
	void SetReplicationDistance(float Distance);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Optimization")
	void EnableRelevancyCulling(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Optimization")
	bool IsActorRelevantToPlayer(AActor* Actor, AActor* Player) const;

	/** Advanced debugging and profiling tools */
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug|Advanced")
	void StartNetworkProfiling();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug|Advanced")
	void StopNetworkProfiling();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug|Advanced")
	FString GetNetworkInsights();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug|Advanced")
	void SimulateNetworkConditions(float Latency, float PacketLoss, float BandwidthLimit);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug|Advanced")
	void ResetNetworkSimulation();

	/** Console command management */
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Console")
	void RegisterConsoleCommands();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Console")
	void UnregisterConsoleCommands();

	/** Client-side prediction system */
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Prediction")
	void EnableClientPrediction(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Prediction")
	void SetPredictionTolerance(float Tolerance);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Prediction")
	bool IsPredictionEnabled() const;

	/** Interest management system */
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Interest")
	void SetInterestRadius(float Radius);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Interest")
	void AddInterestActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Interest")
	void RemoveInterestActor(AActor* Actor);

	// ===== PHASE 3: ADVANCED PERFORMANCE MONITORING =====
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Advanced")
	void StartPerformanceMonitoring();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Advanced")
	void StopPerformanceMonitoring();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Advanced")
	FString GetDetailedPerformanceReport() const;

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Advanced")
	void SetPerformanceThresholds(float MaxLatency, float MaxBandwidth, int32 MaxReplications);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Advanced")
	bool IsPerformanceWithinThresholds() const;

	// ===== LATENCY MEASUREMENT =====
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Latency")
	void StartLatencyMeasurement();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Latency")
	void StopLatencyMeasurement();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Latency")
	float GetCurrentLatency() const;

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Latency")
	float GetAverageLatencyOverTime(float TimeWindow) const;

	// ===== BANDWIDTH MONITORING =====
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Bandwidth")
	void StartBandwidthMonitoring();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Bandwidth")
	void StopBandwidthMonitoring();

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Bandwidth")
	float GetCurrentBandwidthUsage() const;

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Bandwidth")
	float GetBandwidthUsageOverTime(float TimeWindow) const;

	// ===== PACKET LOSS SIMULATION =====
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Simulation")
	void SimulatePacketLoss(float LossPercentage);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Simulation")
	void SimulateLatency(float LatencyMs);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Simulation")
	void SimulateBandwidthLimit(float BandwidthKB);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Performance|Simulation")
	void ResetAllSimulations();


	// Console command implementations removed for simplicity

private:
	UPROPERTY()
	TArray<UNetworkReplicationComponent*> RegisteredComponents;

	/** Motion matching components */

	FNetworkReplicationSettings CurrentSettings;

	/** Interest management system data */
	UPROPERTY()
	TArray<AActor*> InterestActors;

	/** Network profiling and simulation state */
	bool bNetworkProfilingActive;
	bool bNetworkSimulationActive;
	float SimulatedLatency;
	float SimulatedPacketLoss;
	float SimulatedBandwidthLimit;

	/** Console command management */
	FDelegateHandle ConsoleCommandHandle;

	/** Performance monitoring system state */
	bool bPerformanceMonitoringActive;
	bool bLatencyMeasurementActive;
	bool bBandwidthMonitoringActive;
	
	/** Performance monitoring thresholds */
	float MaxLatencyThreshold;
	float MaxBandwidthThreshold;
	int32 MaxReplicationsThreshold;
	
	/** Latency measurement data */
	TArray<float> LatencyHistory;
	float CurrentLatency;
	float LatencyMeasurementStartTime;
	
	/** Bandwidth monitoring data */
	TArray<float> BandwidthHistory;
	float CurrentBandwidthUsage;
	float BandwidthMeasurementStartTime;
	
	/** Performance data collection */
	TArray<float> PerformanceData;
	float PerformanceMeasurementStartTime;

	void OnComponentDestroyed(UNetworkReplicationComponent* Component);
};