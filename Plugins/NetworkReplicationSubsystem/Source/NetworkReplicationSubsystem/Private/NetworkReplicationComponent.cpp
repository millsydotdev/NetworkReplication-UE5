// Copyright © 2025 Millsy.dev. All Rights Reserved.
//
// NetworkReplicationComponent.cpp
// Implements UNetworkReplicationComponent, a Blueprint-friendly component for network replication.

#include "NetworkReplicationComponent.h"
#include "NetworkReplicationSubsystem.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Sound/SoundBase.h"
#include "Animation/AnimMontage.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UNetworkReplicationComponent::UNetworkReplicationComponent()
{
	// Enable component ticking for continuous updates
	PrimaryComponentTick.bCanEverTick = true;
	
	// Enable network replication by default for multiplayer functionality
	SetIsReplicatedByDefault(true);
}

void UNetworkReplicationComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Register this component with the network replication subsystem for centralized management
	if (UNetworkReplicationSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UNetworkReplicationSubsystem>())
	{
		Subsystem->RegisterReplicationComponent(this);
	}
}

void UNetworkReplicationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNetworkReplicationComponent::ReplicateAnimation(UAnimMontage* Montage, float PlayRate, float StartingPosition)
{
	// Validate input parameters before proceeding
	if (!Montage)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReplicateAnimation: Montage is null"));
		return;
	}

	// Determine replication method based on network authority
	if (GetOwner()->HasAuthority())
	{
		// Server: Play locally and multicast to all clients
		MulticastPlayMontage(Montage, PlayRate, StartingPosition);
	}
	else
	{
		// Client: Request server to replicate the animation
		ServerPlayMontage(Montage, PlayRate, StartingPosition);
	}
}

void UNetworkReplicationComponent::ReplicateAnimationStop(UAnimMontage* Montage)
{
	if (!Montage)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReplicateAnimationStop: Montage is null"));
		return;
	}

	if (GetOwner()->HasAuthority())
	{
		// Server: Stop locally and multicast to clients
		MulticastStopMontage(Montage);
	}
	else
	{
		// Client: Send to server
		ServerStopMontage(Montage);
	}
}

void UNetworkReplicationComponent::ReplicateSound(USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	if (!Sound)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReplicateSound: Sound is null"));
		return;
	}

	if (GetOwner()->HasAuthority())
	{
		// Server: Play locally and multicast to clients
		MulticastPlaySound(Sound, VolumeMultiplier, PitchMultiplier, StartTime);
	}
	else
	{
		// Client: Send to server
		ServerPlaySound(Sound, VolumeMultiplier, PitchMultiplier, StartTime);
	}
}

void UNetworkReplicationComponent::ReplicateSoundAtLocation(USoundBase* Sound, FVector Location, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	if (!Sound)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReplicateSoundAtLocation: Sound is null"));
		return;
	}

	if (GetOwner()->HasAuthority())
	{
		// Server: Play locally and multicast to clients
		MulticastPlaySoundAtLocation(Sound, Location, VolumeMultiplier, PitchMultiplier, StartTime);
	}
	else
	{
		// Client: Send to server
		ServerPlaySoundAtLocation(Sound, Location, VolumeMultiplier, PitchMultiplier, StartTime);
	}
}

AActor* UNetworkReplicationComponent::ReplicateActorSpawn(TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation, bool bAttachToOwner)
{
	if (!ActorClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReplicateActorSpawn: ActorClass is null"));
		return nullptr;
	}

	if (GetOwner()->HasAuthority())
	{
		// Server: Spawn locally and multicast to clients
		MulticastSpawnActor(ActorClass, Location, Rotation, bAttachToOwner);
		return nullptr; // Will be spawned via multicast
	}
	else
	{
		// Client: Send to server
		ServerSpawnActor(ActorClass, Location, Rotation, bAttachToOwner);
		return nullptr;
	}
}

AActor* UNetworkReplicationComponent::ReplicateActorSpawnAttached(TSubclassOf<AActor> ActorClass, FName AttachSocketName, FVector LocationOffset, FRotator RotationOffset)
{
	if (!ActorClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReplicateActorSpawnAttached: ActorClass is null"));
		return nullptr;
	}

	if (GetOwner()->HasAuthority())
	{
		// Server: Spawn locally and multicast to clients
		MulticastSpawnActorAttached(ActorClass, AttachSocketName, LocationOffset, RotationOffset);
		return nullptr; // Will be spawned via multicast
	}
	else
	{
		// Client: Send to server
		ServerSpawnActorAttached(ActorClass, AttachSocketName, LocationOffset, RotationOffset);
		return nullptr;
	}
}

UNiagaraComponent* UNetworkReplicationComponent::ReplicateNiagaraEffect(UNiagaraSystem* Effect, FVector Location, FRotator Rotation, bool bAttachToOwner, FName AttachSocketName)
{
	if (!Effect)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReplicateNiagaraEffect: Effect is null"));
		return nullptr;
	}

	if (GetOwner()->HasAuthority())
	{
		// Server: Spawn locally and multicast to clients
		MulticastSpawnNiagaraEffect(Effect, Location, Rotation, bAttachToOwner, AttachSocketName);
		return nullptr; // Will be spawned via multicast
	}
	else
	{
		// Client: Send to server
		ServerSpawnNiagaraEffect(Effect, Location, Rotation, bAttachToOwner, AttachSocketName);
		return nullptr;
	}
}

// Server RPCs
void UNetworkReplicationComponent::ServerPlayMontage_Implementation(UAnimMontage* Montage, float PlayRate, float StartingPosition)
{
	MulticastPlayMontage(Montage, PlayRate, StartingPosition);
}

void UNetworkReplicationComponent::ServerStopMontage_Implementation(UAnimMontage* Montage)
{
	MulticastStopMontage(Montage);
}

void UNetworkReplicationComponent::ServerPlaySound_Implementation(USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	MulticastPlaySound(Sound, VolumeMultiplier, PitchMultiplier, StartTime);
}

void UNetworkReplicationComponent::ServerPlaySoundAtLocation_Implementation(USoundBase* Sound, FVector Location, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	MulticastPlaySoundAtLocation(Sound, Location, VolumeMultiplier, PitchMultiplier, StartTime);
}

void UNetworkReplicationComponent::ServerSpawnActor_Implementation(TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation, bool bAttachToOwner)
{
	MulticastSpawnActor(ActorClass, Location, Rotation, bAttachToOwner);
}

void UNetworkReplicationComponent::ServerSpawnActorAttached_Implementation(TSubclassOf<AActor> ActorClass, FName AttachSocketName, FVector LocationOffset, FRotator RotationOffset)
{
	MulticastSpawnActorAttached(ActorClass, AttachSocketName, LocationOffset, RotationOffset);
}

void UNetworkReplicationComponent::ServerSpawnNiagaraEffect_Implementation(UNiagaraSystem* Effect, FVector Location, FRotator Rotation, bool bAttachToOwner, FName AttachSocketName)
{
	MulticastSpawnNiagaraEffect(Effect, Location, Rotation, bAttachToOwner, AttachSocketName);
}

// Client RPCs
void UNetworkReplicationComponent::MulticastPlayMontage_Implementation(UAnimMontage* Montage, float PlayRate, float StartingPosition)
{
	if (UAnimInstance* AnimInstance = GetAnimInstance())
	{
		AnimInstance->Montage_Play(Montage, PlayRate, EMontagePlayReturnType::MontageLength, StartingPosition);
		OnAnimationReplicated.Broadcast(Montage);
	}
}

void UNetworkReplicationComponent::MulticastStopMontage_Implementation(UAnimMontage* Montage)
{
	if (UAnimInstance* AnimInstance = GetAnimInstance())
	{
		AnimInstance->Montage_Stop(0.2f, Montage);
	}
}

void UNetworkReplicationComponent::MulticastPlaySound_Implementation(USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	if (UAudioComponent* AudioComponent = GetAudioComponent())
	{
		AudioComponent->SetSound(Sound);
		AudioComponent->SetVolumeMultiplier(VolumeMultiplier);
		AudioComponent->SetPitchMultiplier(PitchMultiplier);
		AudioComponent->Play(StartTime);
		OnSoundReplicated.Broadcast(Sound);
	}
	else
	{
		// Fallback to playing at actor location
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetOwner()->GetActorLocation(), VolumeMultiplier, PitchMultiplier, StartTime);
		OnSoundReplicated.Broadcast(Sound);
	}
}

void UNetworkReplicationComponent::MulticastPlaySoundAtLocation_Implementation(USoundBase* Sound, FVector Location, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location, VolumeMultiplier, PitchMultiplier, StartTime);
	OnSoundReplicated.Broadcast(Sound);
}

void UNetworkReplicationComponent::MulticastSpawnActor_Implementation(TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation, bool bAttachToOwner)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClass, Location, Rotation);
	if (SpawnedActor && bAttachToOwner)
	{
		SpawnedActor->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	}
	
	if (SpawnedActor)
	{
		OnActorSpawned.Broadcast(SpawnedActor);
	}
}

void UNetworkReplicationComponent::MulticastSpawnActorAttached_Implementation(TSubclassOf<AActor> ActorClass, FName AttachSocketName, FVector LocationOffset, FRotator RotationOffset)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	FVector SpawnLocation = GetOwner()->GetActorLocation() + LocationOffset;
	FRotator SpawnRotation = GetOwner()->GetActorRotation() + RotationOffset;

	AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClass, SpawnLocation, SpawnRotation);
	if (SpawnedActor)
	{
		if (AttachSocketName != NAME_None)
		{
			SpawnedActor->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform, AttachSocketName);
		}
		else
		{
			SpawnedActor->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
		}
		OnActorSpawned.Broadcast(SpawnedActor);
	}
}

void UNetworkReplicationComponent::MulticastSpawnNiagaraEffect_Implementation(UNiagaraSystem* Effect, FVector Location, FRotator Rotation, bool bAttachToOwner, FName AttachSocketName)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

		UNiagaraComponent* NiagaraComponent = NewObject<UNiagaraComponent>(World);
	if (NiagaraComponent)
	{
		NiagaraComponent->SetAsset(Effect);
		NiagaraComponent->SetWorldLocationAndRotation(Location, Rotation);
		
		if (bAttachToOwner)
		{
			if (AttachSocketName != NAME_None)
			{
				NiagaraComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform, AttachSocketName);
			}
			else
			{
				NiagaraComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
			}
		}
		
		NiagaraComponent->Activate();
		OnNiagaraEffectReplicated.Broadcast(Effect);
	}
}

void UNetworkReplicationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnComponentDestroyed.Broadcast(this);
	Super::EndPlay(EndPlayReason);
}

// Helper functions
UAnimInstance* UNetworkReplicationComponent::GetAnimInstance() const
{
	if (USkeletalMeshComponent* SkeletalMeshComponent = GetSkeletalMeshComponent())
	{
		return SkeletalMeshComponent->GetAnimInstance();
	}
	return nullptr;
}

USkeletalMeshComponent* UNetworkReplicationComponent::GetSkeletalMeshComponent() const
{
	return GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}

UAudioComponent* UNetworkReplicationComponent::GetAudioComponent() const
{
	return GetOwner()->FindComponentByClass<UAudioComponent>();
}

// ===== NEW VARIABLE REPLICATION IMPLEMENTATIONS =====

// Variable Replication Functions
void UNetworkReplicationComponent::ReplicateStringVariable(FName VariableName, const FString& Value)
{
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replicating String Variable: %s = %s"), *VariableName.ToString(), *Value);
	}

	if (GetOwner()->HasAuthority())
	{
		MulticastReplicateVariable(VariableName, Value, 0); // 0 = String type
	}
	else
	{
		ServerReplicateVariable(VariableName, Value, 0);
	}
	
	TotalReplications++;
	LastReplicationTime = GetWorld()->GetTimeSeconds();
}

void UNetworkReplicationComponent::ReplicateFloatVariable(FName VariableName, float Value)
{
	FString StringValue = FString::Printf(TEXT("%.6f"), Value);
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replicating Float Variable: %s = %f"), *VariableName.ToString(), Value);
	}

	if (GetOwner()->HasAuthority())
	{
		MulticastReplicateVariable(VariableName, StringValue, 1); // 1 = Float type
	}
	else
	{
		ServerReplicateVariable(VariableName, StringValue, 1);
	}
	
	TotalReplications++;
	LastReplicationTime = GetWorld()->GetTimeSeconds();
}

void UNetworkReplicationComponent::ReplicateIntVariable(FName VariableName, int32 Value)
{
	FString StringValue = FString::Printf(TEXT("%d"), Value);
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replicating Int Variable: %s = %d"), *VariableName.ToString(), Value);
	}

	if (GetOwner()->HasAuthority())
	{
		MulticastReplicateVariable(VariableName, StringValue, 2); // 2 = Int type
	}
	else
	{
		ServerReplicateVariable(VariableName, StringValue, 2);
	}
	
	TotalReplications++;
	LastReplicationTime = GetWorld()->GetTimeSeconds();
}

void UNetworkReplicationComponent::ReplicateBoolVariable(FName VariableName, bool Value)
{
	FString StringValue = Value ? TEXT("true") : TEXT("false");
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replicating Bool Variable: %s = %s"), *VariableName.ToString(), *StringValue);
	}

	if (GetOwner()->HasAuthority())
	{
		MulticastReplicateVariable(VariableName, StringValue, 3); // 3 = Bool type
	}
	else
	{
		ServerReplicateVariable(VariableName, StringValue, 3);
	}
	
	TotalReplications++;
	LastReplicationTime = GetWorld()->GetTimeSeconds();
}

void UNetworkReplicationComponent::ReplicateVectorVariable(FName VariableName, FVector Value)
{
	FString StringValue = Value.ToString();
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replicating Vector Variable: %s = %s"), *VariableName.ToString(), *StringValue);
	}

	if (GetOwner()->HasAuthority())
	{
		MulticastReplicateVariable(VariableName, StringValue, 4); // 4 = Vector type
	}
	else
	{
		ServerReplicateVariable(VariableName, StringValue, 4);
	}
	
	TotalReplications++;
	LastReplicationTime = GetWorld()->GetTimeSeconds();
}

// Custom Event Replication
void UNetworkReplicationComponent::ReplicateCustomEvent(FName EventName, const FString& EventData)
{
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replicating Custom Event: %s with data: %s"), *EventName.ToString(), *EventData);
	}

	if (GetOwner()->HasAuthority())
	{
		MulticastReplicateCustomEvent(EventName, EventData);
	}
	else
	{
		ServerReplicateCustomEvent(EventName, EventData);
	}
	
	TotalReplications++;
	LastReplicationTime = GetWorld()->GetTimeSeconds();
}

// Debugging Functions
void UNetworkReplicationComponent::EnableDebugLogging(bool bEnabled)
{
	bDebugMode = bEnabled;
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("NetworkReplicationComponent: Debug mode enabled"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NetworkReplicationComponent: Debug mode disabled"));
	}
}

void UNetworkReplicationComponent::LogReplicationEvent(const FString& EventName)
{
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replication Event: %s"), *EventName);
	}
}

FString UNetworkReplicationComponent::GetReplicationStats() const
{
	return FString::Printf(TEXT("Total Replications: %d, Last: %.2f"), 
		TotalReplications, LastReplicationTime);
}

// Server RPC Implementations
void UNetworkReplicationComponent::ServerReplicateVariable_Implementation(FName VariableName, const FString& Value, int32 VariableType)
{
	MulticastReplicateVariable(VariableName, Value, VariableType);
}

void UNetworkReplicationComponent::ServerReplicateCustomEvent_Implementation(FName EventName, const FString& EventData)
{
	MulticastReplicateCustomEvent(EventName, EventData);
}

// Client RPC Implementations
void UNetworkReplicationComponent::MulticastReplicateVariable_Implementation(FName VariableName, const FString& Value, int32 VariableType)
{
	OnVariableReplicated.Broadcast(VariableName, Value);
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Variable Replicated: %s = %s (Type: %d)"), 
			*VariableName.ToString(), *Value, VariableType);
	}
}

void UNetworkReplicationComponent::MulticastReplicateCustomEvent_Implementation(FName EventName, const FString& EventData)
{
	OnCustomEventReplicated.Broadcast(EventName, EventData);
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Custom Event Replicated: %s with data: %s"), 
			*EventName.ToString(), *EventData);
	}
}

// ===== MOTION MATCHING IMPLEMENTATIONS =====

/**
 * Replicates motion matching database data across the network
 * Compatible with Epic's Game Animation Sample motion matching system
 */
void UNetworkReplicationComponent::ReplicateMotionMatchingDatabase(UObject* Database)
{
	// Validate input parameters
	if (!Database)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReplicateMotionMatchingDatabase: Database is null"));
		return;
	}

	// Log replication for debugging when debug mode is enabled
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replicating Motion Matching Database: %s"), *Database->GetName());
	}

	// Determine replication method based on network authority
	if (GetOwner()->HasAuthority())
	{
		// Server: Directly multicast to all clients
		MulticastReplicateMotionMatchingDatabase(Database);
	}
	else
	{
		// Client: Request server to replicate
		ServerReplicateMotionMatchingDatabase(Database);
	}
	
	// Update replication statistics for monitoring
	TotalReplications++;
	LastReplicationTime = GetWorld()->GetTimeSeconds();
}

void UNetworkReplicationComponent::ReplicatePoseSearchSchema(UObject* Schema)
{
	if (!Schema)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReplicatePoseSearchSchema: Schema is null"));
		return;
	}

	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replicating Pose Search Schema: %s"), *Schema->GetName());
	}

	if (GetOwner()->HasAuthority())
	{
		MulticastReplicatePoseSearchSchema(Schema);
	}
	else
	{
		ServerReplicatePoseSearchSchema(Schema);
	}
	
	TotalReplications++;
	LastReplicationTime = GetWorld()->GetTimeSeconds();
}

void UNetworkReplicationComponent::ReplicateTrajectoryData(const FVector& Position, const FRotator& Rotation)
{
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Replicating Trajectory Data: Position=%s, Rotation=%s"), 
			*Position.ToString(), *Rotation.ToString());
	}

	if (GetOwner()->HasAuthority())
	{
		MulticastReplicateTrajectoryData(Position, Rotation);
	}
	else
	{
		ServerReplicateTrajectoryData(Position, Rotation);
	}
	
	TotalReplications++;
	LastReplicationTime = GetWorld()->GetTimeSeconds();
}

// Motion Matching Server RPC Implementations
void UNetworkReplicationComponent::ServerReplicateMotionMatchingDatabase_Implementation(UObject* Database)
{
	MulticastReplicateMotionMatchingDatabase(Database);
}

void UNetworkReplicationComponent::ServerReplicatePoseSearchSchema_Implementation(UObject* Schema)
{
	MulticastReplicatePoseSearchSchema(Schema);
}

void UNetworkReplicationComponent::ServerReplicateTrajectoryData_Implementation(FVector Position, FRotator Rotation)
{
	MulticastReplicateTrajectoryData(Position, Rotation);
}

// Motion Matching Client RPC Implementations
void UNetworkReplicationComponent::MulticastReplicateMotionMatchingDatabase_Implementation(UObject* Database)
{
	OnMotionMatchingReplicated.Broadcast(Database);
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Motion Matching Database Replicated: %s"), *Database->GetName());
	}
}

void UNetworkReplicationComponent::MulticastReplicatePoseSearchSchema_Implementation(UObject* Schema)
{
	OnPoseSearchReplicated.Broadcast(Schema);
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Pose Search Schema Replicated: %s"), *Schema->GetName());
	}
}

void UNetworkReplicationComponent::MulticastReplicateTrajectoryData_Implementation(FVector Position, FRotator Rotation)
{
	OnTrajectoryReplicated.Broadcast(Position, Rotation);
	
	if (bDebugMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Trajectory Data Replicated: Position=%s, Rotation=%s"), 
			*Position.ToString(), *Rotation.ToString());
	}
}
