# NetworkReplication Plugin - API Reference

Complete reference for the NetworkReplicationComponent API.

## Class: UNetworkReplicationComponent

A comprehensive network replication component that handles synchronization of game state across multiplayer clients.

### Inheritance
- `UActorComponent` → `UNetworkReplicationComponent`

### Header
```cpp
#include "NetworkReplicationComponent.h"
```

## Public Functions

### Animation Replication

#### `ReplicateAnimation(UAnimMontage* Montage, float PlayRate = 1.0f, float StartingPosition = 0.0f)`
Replicates an animation montage across all clients with optional prediction.

**Parameters:**
- `Montage`: The animation montage to play
- `PlayRate`: Playback speed multiplier (default: 1.0f)
- `StartingPosition`: Starting position in seconds (default: 0.0f)

**Usage:**
```cpp
// Basic animation replication
ReplicateAnimation(MyMontage, 1.0f, 0.0f);

// With custom play rate
ReplicateAnimation(MyMontage, 1.5f, 0.0f);
```

#### `ReplicateAnimationStop(UAnimMontage* Montage)`
Stops a specific animation montage across all clients.

**Parameters:**
- `Montage`: The animation montage to stop

**Usage:**
```cpp
ReplicateAnimationStop(MyMontage);
```

### Sound Replication

#### `ReplicateSound(USoundBase* Sound, float VolumeMultiplier = 1.0f, float PitchMultiplier = 1.0f, float StartTime = 0.0f)`
Replicates a sound effect using the actor's audio component.

**Parameters:**
- `Sound`: The sound asset to play
- `VolumeMultiplier`: Volume adjustment (default: 1.0f)
- `PitchMultiplier`: Pitch adjustment (default: 1.0f)
- `StartTime`: Start time in seconds (default: 0.0f)

#### `ReplicateSoundAtLocation(USoundBase* Sound, FVector Location, float VolumeMultiplier = 1.0f, float PitchMultiplier = 1.0f, float StartTime = 0.0f)`
Replicates a sound effect at a specific world location.

**Parameters:**
- `Sound`: The sound asset to play
- `Location`: World position to play the sound
- `VolumeMultiplier`: Volume adjustment (default: 1.0f)
- `PitchMultiplier`: Pitch adjustment (default: 1.0f)
- `StartTime`: Start time in seconds (default: 0.0f)

### Actor Replication

#### `ReplicateActorSpawn(TSubclassOf<AActor> ActorClass, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator, bool bAttachToOwner = false)`
Spawns an actor at a specific location and optionally attaches it to the owner.

**Parameters:**
- `ActorClass`: The class of actor to spawn
- `Location`: World position to spawn (default: ZeroVector)
- `Rotation`: World rotation to spawn (default: ZeroRotator)
- `bAttachToOwner`: Whether to attach to the component owner (default: false)

**Returns:** `AActor*` - The spawned actor (nullptr on clients)

#### `ReplicateActorSpawnAttached(TSubclassOf<AActor> ActorClass, FName AttachSocketName = NAME_None, FVector LocationOffset = FVector::ZeroVector, FRotator RotationOffset = FRotator::ZeroRotator)`
Spawns an actor and attaches it to the owner with hot joining support.

**Parameters:**
- `ActorClass`: The class of actor to spawn
- `AttachSocketName`: Socket name for attachment (default: NAME_None)
- `LocationOffset`: Offset from owner location (default: ZeroVector)
- `RotationOffset`: Offset from owner rotation (default: ZeroRotator)

**Returns:** `AActor*` - The spawned actor (nullptr on clients)

### Niagara Effects

#### `ReplicateNiagaraEffect(UNiagaraSystem* Effect, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator, bool bAttachToOwner = false, FName AttachSocketName = NAME_None)`
Replicates a Niagara particle effect.

**Parameters:**
- `Effect`: The Niagara system to spawn
- `Location`: World position to spawn (default: ZeroVector)
- `Rotation`: World rotation to spawn (default: ZeroRotator)
- `bAttachToOwner`: Whether to attach to the component owner (default: false)
- `AttachSocketName`: Socket name for attachment (default: NAME_None)

**Returns:** `UNiagaraComponent*` - The Niagara component (nullptr on clients)

### Variable Replication

#### `ReplicateStringVariable(FName VariableName, const FString& Value)`
Replicates a string variable across all clients.

**Parameters:**
- `VariableName`: Name identifier for the variable
- `Value`: String value to replicate

#### `ReplicateFloatVariable(FName VariableName, float Value)`
Replicates a float variable across all clients.

**Parameters:**
- `VariableName`: Name identifier for the variable
- `Value`: Float value to replicate

#### `ReplicateIntVariable(FName VariableName, int32 Value)`
Replicates an integer variable across all clients.

**Parameters:**
- `VariableName`: Name identifier for the variable
- `Value`: Integer value to replicate

#### `ReplicateBoolVariable(FName VariableName, bool Value)`
Replicates a boolean variable across all clients.

**Parameters:**
- `VariableName`: Name identifier for the variable
- `Value`: Boolean value to replicate

#### `ReplicateVectorVariable(FName VariableName, FVector Value)`
Replicates a vector variable across all clients.

**Parameters:**
- `VariableName`: Name identifier for the variable
- `Value`: Vector value to replicate

### Custom Events

#### `ReplicateCustomEvent(FName EventName, const FString& EventData = TEXT(""))`
Replicates a custom event with optional data.

**Parameters:**
- `EventName`: Name of the custom event
- `EventData`: Optional string data for the event (default: empty)

### Motion Matching

#### `ReplicateMotionMatchingDatabase(UObject* Database)`
Replicates motion matching database data.

**Parameters:**
- `Database`: Motion matching database object

#### `ReplicatePoseSearchSchema(UObject* Schema)`
Replicates pose search schema data.

**Parameters:**
- `Schema`: Pose search schema object

#### `ReplicateTrajectoryData(const FVector& Position, const FRotator& Rotation)`
Replicates trajectory data for motion matching.

**Parameters:**
- `Position`: Trajectory position
- `Rotation`: Trajectory rotation

### Testing Functions

#### `TestHotJoining()`
Tests hot joining functionality by simulating attachment scenarios.

**Usage:**
```cpp
// Call from console or Blueprint
TestHotJoining();
```

#### `TestHighPingPrediction()`
Tests high ping scenarios by setting network lag simulation.

**Usage:**
```cpp
// Call from console or Blueprint
TestHighPingPrediction();
```

#### `TestLowFPSScenario()`
Tests low FPS scenarios by limiting frame rate.

**Usage:**
```cpp
// Call from console or Blueprint
TestLowFPSScenario();
```

### Debug Functions

#### `EnableDebugLogging(bool bEnabled)`
Enables or disables debug logging for the component.

**Parameters:**
- `bEnabled`: Whether to enable debug logging

#### `LogReplicationEvent(const FString& EventName)`
Logs a custom replication event for debugging.

**Parameters:**
- `EventName`: Name of the event to log

#### `GetReplicationStats() const`
Returns replication statistics as a formatted string.

**Returns:** `FString` - Formatted statistics string

## Properties

### Debug Properties

#### `bool bDebugMode`
Whether debug mode is enabled for this component.

#### `int32 TotalReplications`
Total number of replications performed by this component.

#### `float LastReplicationTime`
Time of the last replication event.

### Replicated Properties

#### `FAttachmentInfo AttachmentInfo`
Replicated attachment information for hot joining support.

#### `FPredictionState PredictionState`
Replicated prediction state for client-side prediction.

#### `FAnimationPredictionData AnimationPrediction`
Replicated animation prediction data.

## Events

### Animation Events

#### `FOnAnimationReplicated OnAnimationReplicated`
Broadcast when an animation is replicated.

**Signature:** `void OnAnimationReplicated(UAnimMontage* Montage)`

### Sound Events

#### `FOnSoundReplicated OnSoundReplicated`
Broadcast when a sound is replicated.

**Signature:** `void OnSoundReplicated(USoundBase* Sound)`

### Actor Events

#### `FOnActorSpawnedReplicated OnActorSpawned`
Broadcast when an actor is spawned and replicated.

**Signature:** `void OnActorSpawnedReplicated(AActor* SpawnedActor)`

### Niagara Events

#### `FOnNiagaraEffectReplicated OnNiagaraEffectReplicated`
Broadcast when a Niagara effect is replicated.

**Signature:** `void OnNiagaraEffectReplicated(UNiagaraSystem* Effect)`

### Variable Events

#### `FOnVariableReplicated OnVariableReplicated`
Broadcast when a variable is replicated.

**Signature:** `void OnVariableReplicated(FName VariableName, FString VariableValue)`

### Custom Event Events

#### `FOnCustomEventReplicated OnCustomEventReplicated`
Broadcast when a custom event is replicated.

**Signature:** `void OnCustomEventReplicated(FName EventName, FString EventData)`

### Hot Joining Events

#### `FOnAttachmentInfoReplicated OnAttachmentInfoReplicated`
Broadcast when attachment information is replicated for hot joining.

**Signature:** `void OnAttachmentInfoReplicated(FAttachmentInfo AttachmentInfo)`

### Prediction Events

#### `FOnPredictionStateReplicated OnPredictionStateReplicated`
Broadcast when prediction state is replicated.

**Signature:** `void OnPredictionStateReplicated(FPredictionState PredictionState)`

#### `FOnAnimationPredicted OnAnimationPredicted`
Broadcast when animation prediction is triggered.

**Signature:** `void OnAnimationPredicted(FAnimationPredictionData PredictionData)`

#### `FOnAnimationCorrected OnAnimationCorrected`
Broadcast when animation prediction is corrected by the server.

**Signature:** `void OnAnimationCorrected(FAnimationPredictionData CorrectionData)`

## Data Structures

### FAttachmentInfo
Structure containing attachment information for hot joining support.

```cpp
USTRUCT(BlueprintType)
struct FAttachmentInfo
{
    UPROPERTY(BlueprintReadWrite)
    TObjectPtr<UPrimitiveComponent> Component;
    
    UPROPERTY(BlueprintReadWrite)
    FName SocketName;
    
    UPROPERTY(BlueprintReadWrite)
    FTransform RelativeTransform;
    
    UPROPERTY(BlueprintReadWrite)
    TObjectPtr<AActor> Owner;
    
    UPROPERTY(BlueprintReadWrite)
    bool bKeepWorldTransform;
    
    UPROPERTY(BlueprintReadWrite)
    bool bIsActive;
};
```

### FPredictionState
Structure containing prediction state information.

```cpp
USTRUCT(BlueprintType)
struct FPredictionState
{
    UPROPERTY(BlueprintReadWrite)
    double ClientSendTime;
    
    UPROPERTY(BlueprintReadWrite)
    uint32 InputFrame;
    
    UPROPERTY(BlueprintReadWrite)
    bool bIsPredicting;
    
    UPROPERTY(BlueprintReadWrite)
    float CorrectionFactor;
};
```

### FAnimationPredictionData
Structure containing animation prediction data.

```cpp
USTRUCT(BlueprintType)
struct FAnimationPredictionData
{
    UPROPERTY(BlueprintReadWrite)
    TObjectPtr<UAnimMontage> Montage;
    
    UPROPERTY(BlueprintReadWrite)
    float PlayRate;
    
    UPROPERTY(BlueprintReadWrite)
    float StartingPosition;
    
    UPROPERTY(BlueprintReadWrite)
    double PredictionTime;
    
    UPROPERTY(BlueprintReadWrite)
    bool bIsValid;
};
```

## Usage Examples

### Basic Animation Replication
```cpp
// Get the component
UNetworkReplicationComponent* RepComp = GetComponentByClass<UNetworkReplicationComponent>();

// Replicate animation
RepComp->ReplicateAnimation(MyMontage, 1.0f, 0.0f);
```

### Spawning Attached Actor
```cpp
// Spawn actor with hot joining support
RepComp->ReplicateActorSpawnAttached(
    MyActorClass,
    TEXT("WeaponSocket"),
    FVector(0, 0, 0),
    FRotator(0, 0, 0)
);
```

### Variable Replication
```cpp
// Replicate player health
RepComp->ReplicateFloatVariable(TEXT("Health"), 85.0f);

// Replicate player name
RepComp->ReplicateStringVariable(TEXT("PlayerName"), TEXT("Player1"));
```

### Event Binding
```cpp
// Bind to animation replicated event
RepComp->OnAnimationReplicated.AddDynamic(this, &AMyActor::OnAnimationReplicated);

// Implementation
void AMyActor::OnAnimationReplicated(UAnimMontage* Montage)
{
    UE_LOG(LogTemp, Log, TEXT("Animation replicated: %s"), *Montage->GetName());
}
```

## Console Commands

### Network Testing
- `Net.PktLag <value>` - Set network packet lag in milliseconds
- `Net.PktLagVariance <value>` - Set network packet lag variance
- `stat net` - Display network statistics

### Performance Testing
- `t.MaxFPS <value>` - Set maximum frame rate
- `r.OneFrameThreadLag` - Enable one frame thread lag for testing

### Debug Commands
- `TestHotJoining` - Test hot joining functionality
- `TestHighPingPrediction` - Test high ping scenarios
- `TestLowFPSScenario` - Test low FPS scenarios