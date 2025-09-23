// Copyright © 2025 Millsy.dev. All Rights Reserved.
//
// NetworkReplicationComponent.h
// Declares UNetworkReplicationComponent, a Blueprint-friendly component for network replication.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Engine.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundBase.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "NetworkReplicationComponent.generated.h"

/**
 * Network replication event delegates for Blueprint binding
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationReplicated, UAnimMontage*, Montage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSoundReplicated, USoundBase*, Sound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorSpawnedReplicated, AActor*, SpawnedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNiagaraEffectReplicated, UNiagaraSystem*, Effect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComponentDestroyed, class UNetworkReplicationComponent*, Component);

/**
 * Variable and custom event replication delegates
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVariableReplicated, FName, VariableName, FString, VariableValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCustomEventReplicated, FName, EventName, FString, EventData);

/**
 * Motion matching replication delegates for pose search and trajectory data
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMotionMatchingReplicated, UObject*, Database);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTrajectoryReplicated, FVector, Position, FRotator, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPoseSearchReplicated, UObject*, Schema);


/**
 * UNetworkReplicationComponent
 * 
 * A comprehensive network replication component that handles synchronization
 * of game state across multiplayer clients. Provides Blueprint-friendly
 * functions for replicating animations, sounds, VFX, variables, and motion matching data.
 * 
 * Features:
 * - Animation montage replication
 * - Sound effect synchronization  
 * - Niagara VFX replication
 * - Custom variable replication
 * - Motion matching data synchronization
 * - Performance monitoring and debugging
 * 
 * @see UActorComponent
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORKREPLICATIONSUBSYSTEM_API UNetworkReplicationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkReplicationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Network Replication Functions - Focused on actual replication, not duplicating UE systems
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Animation", CallInEditor)
	void ReplicateAnimation(UAnimMontage* Montage, float PlayRate = 1.0f, float StartingPosition = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Animation", CallInEditor)
	void ReplicateAnimationStop(UAnimMontage* Montage);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Sound", CallInEditor)
	void ReplicateSound(USoundBase* Sound, float VolumeMultiplier = 1.0f, float PitchMultiplier = 1.0f, float StartTime = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Sound", CallInEditor)
	void ReplicateSoundAtLocation(USoundBase* Sound, FVector Location, float VolumeMultiplier = 1.0f, float PitchMultiplier = 1.0f, float StartTime = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Actor", CallInEditor)
	AActor* ReplicateActorSpawn(TSubclassOf<AActor> ActorClass, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator, bool bAttachToOwner = false);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Actor", CallInEditor)
	AActor* ReplicateActorSpawnAttached(TSubclassOf<AActor> ActorClass, FName AttachSocketName = NAME_None, FVector LocationOffset = FVector::ZeroVector, FRotator RotationOffset = FRotator::ZeroRotator);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Niagara", CallInEditor)
	UNiagaraComponent* ReplicateNiagaraEffect(UNiagaraSystem* Effect, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator, bool bAttachToOwner = false, FName AttachSocketName = NAME_None);

	// ===== NEW VARIABLE REPLICATION FUNCTIONS =====
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Variables", CallInEditor)
	void ReplicateStringVariable(FName VariableName, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Variables", CallInEditor)
	void ReplicateFloatVariable(FName VariableName, float Value);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Variables", CallInEditor)
	void ReplicateIntVariable(FName VariableName, int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Variables", CallInEditor)
	void ReplicateBoolVariable(FName VariableName, bool Value);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Variables", CallInEditor)
	void ReplicateVectorVariable(FName VariableName, FVector Value);

	// ===== CUSTOM EVENT REPLICATION =====
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Events", CallInEditor)
	void ReplicateCustomEvent(FName EventName, const FString& EventData = TEXT(""));

	// ===== MOTION MATCHING REPLICATION =====
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Motion Matching", CallInEditor)
	void ReplicateMotionMatchingDatabase(UObject* Database);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Motion Matching", CallInEditor)
	void ReplicatePoseSearchSchema(UObject* Schema);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Motion Matching", CallInEditor)
	void ReplicateTrajectoryData(const FVector& Position, const FRotator& Rotation);


	// ===== DEBUGGING FUNCTIONS =====
	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug", CallInEditor)
	void EnableDebugLogging(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug", CallInEditor)
	void LogReplicationEvent(const FString& EventName);

	UFUNCTION(BlueprintCallable, Category = "Network Replication|Debug", CallInEditor)
	FString GetReplicationStats() const;

	// Replication Events
	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Events")
	FOnAnimationReplicated OnAnimationReplicated;

	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Events")
	FOnSoundReplicated OnSoundReplicated;

	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Events")
	FOnActorSpawnedReplicated OnActorSpawned;

	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Events")
	FOnNiagaraEffectReplicated OnNiagaraEffectReplicated;

	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Events")
	FOnComponentDestroyed OnComponentDestroyed;

	// ===== NEW EVENTS =====
	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Events")
	FOnVariableReplicated OnVariableReplicated;

	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Events")
	FOnCustomEventReplicated OnCustomEventReplicated;

	// ===== MOTION MATCHING EVENTS =====
	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Motion Matching|Events")
	FOnMotionMatchingReplicated OnMotionMatchingReplicated;

	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Motion Matching|Events")
	FOnTrajectoryReplicated OnTrajectoryReplicated;

	UPROPERTY(BlueprintAssignable, Category = "Network Replication|Motion Matching|Events")
	FOnPoseSearchReplicated OnPoseSearchReplicated;


	// ===== DEBUGGING PROPERTIES =====
	UPROPERTY(BlueprintReadWrite, Category = "Network Replication|Debug")
	bool bDebugMode = false;

	UPROPERTY(BlueprintReadOnly, Category = "Network Replication|Debug")
	int32 TotalReplications = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Network Replication|Debug")
	float LastReplicationTime = 0.0f;

protected:
	// Server RPCs
	UFUNCTION(Server, Reliable, Category = "Network Replication|RPC")
	void ServerPlayMontage(UAnimMontage* Montage, float PlayRate, float StartingPosition);

	UFUNCTION(Server, Reliable, Category = "Network Replication|RPC")
	void ServerStopMontage(UAnimMontage* Montage);

	UFUNCTION(Server, Reliable, Category = "Network Replication|RPC")
	void ServerPlaySound(USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier, float StartTime);

	UFUNCTION(Server, Reliable, Category = "Network Replication|RPC")
	void ServerPlaySoundAtLocation(USoundBase* Sound, FVector Location, float VolumeMultiplier, float PitchMultiplier, float StartTime);

	UFUNCTION(Server, Reliable, Category = "Network Replication|RPC")
	void ServerSpawnActor(TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation, bool bAttachToOwner);

	UFUNCTION(Server, Reliable, Category = "Network Replication|RPC")
	void ServerSpawnActorAttached(TSubclassOf<AActor> ActorClass, FName AttachSocketName, FVector LocationOffset, FRotator RotationOffset);

	UFUNCTION(Server, Reliable, Category = "Network Replication|RPC")
	void ServerSpawnNiagaraEffect(UNiagaraSystem* Effect, FVector Location, FRotator Rotation, bool bAttachToOwner, FName AttachSocketName);

	// Client RPCs
	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|RPC")
	void MulticastPlayMontage(UAnimMontage* Montage, float PlayRate, float StartingPosition);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|RPC")
	void MulticastStopMontage(UAnimMontage* Montage);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|RPC")
	void MulticastPlaySound(USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier, float StartTime);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|RPC")
	void MulticastPlaySoundAtLocation(USoundBase* Sound, FVector Location, float VolumeMultiplier, float PitchMultiplier, float StartTime);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|RPC")
	void MulticastSpawnActor(TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation, bool bAttachToOwner);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|RPC")
	void MulticastSpawnActorAttached(TSubclassOf<AActor> ActorClass, FName AttachSocketName, FVector LocationOffset, FRotator RotationOffset);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|RPC")
	void MulticastSpawnNiagaraEffect(UNiagaraSystem* Effect, FVector Location, FRotator Rotation, bool bAttachToOwner, FName AttachSocketName);

	// ===== NEW RPCs =====
	UFUNCTION(Server, Reliable, Category = "Network Replication|RPC")
	void ServerReplicateVariable(FName VariableName, const FString& Value, int32 VariableType);

	UFUNCTION(Server, Reliable, Category = "Network Replication|RPC")
	void ServerReplicateCustomEvent(FName EventName, const FString& EventData);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|RPC")
	void MulticastReplicateVariable(FName VariableName, const FString& Value, int32 VariableType);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|RPC")
	void MulticastReplicateCustomEvent(FName EventName, const FString& EventData);

	// ===== MOTION MATCHING RPCs =====
	UFUNCTION(Server, Reliable, Category = "Network Replication|Motion Matching|RPC")
	void ServerReplicateMotionMatchingDatabase(UObject* Database);

	UFUNCTION(Server, Reliable, Category = "Network Replication|Motion Matching|RPC")
	void ServerReplicatePoseSearchSchema(UObject* Schema);

	UFUNCTION(Server, Reliable, Category = "Network Replication|Motion Matching|RPC")
	void ServerReplicateTrajectoryData(FVector Position, FRotator Rotation);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|Motion Matching|RPC")
	void MulticastReplicateMotionMatchingDatabase(UObject* Database);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|Motion Matching|RPC")
	void MulticastReplicatePoseSearchSchema(UObject* Schema);

	UFUNCTION(NetMulticast, Reliable, Category = "Network Replication|Motion Matching|RPC")
	void MulticastReplicateTrajectoryData(FVector Position, FRotator Rotation);


	// Override EndPlay to handle cleanup
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Helper functions
	class UAnimInstance* GetAnimInstance() const;
	class USkeletalMeshComponent* GetSkeletalMeshComponent() const;
	class UAudioComponent* GetAudioComponent() const;
};