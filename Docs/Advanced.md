# NetworkReplication Plugin - Advanced Guide

Master the advanced features and patterns of the NetworkReplication plugin.

## Architecture Overview

The NetworkReplication plugin provides a comprehensive system for replicating game state across multiplayer clients with support for:

- **Hot Joining**: Late-joining clients receive proper state
- **Client Prediction**: Immediate visual feedback with server validation
- **High Ping Support**: Optimized for high-latency scenarios
- **Low FPS Resilience**: Stable performance under low frame rates

## Core Concepts

### Authority and Replication Flow

```
Client Input → Server Validation → Multicast to All Clients
     ↓              ↓                    ↓
Local Prediction → Server Correction → State Sync
```

### Hot Joining Support

The plugin uses replicated properties with `ReplicatedUsing` to ensure late-joining clients receive the correct state:

```cpp
// Replicated properties for hot joining
UPROPERTY(ReplicatedUsing = OnRep_AttachmentInfo)
FAttachmentInfo AttachmentInfo;

UPROPERTY(ReplicatedUsing = OnRep_PredictionState)
FPredictionState PredictionState;
```

## Usage Patterns

### 1. Animation Replication with Prediction

**Basic Pattern:**
```cpp
// Client-side: Immediate visual feedback
if (!GetOwner()->HasAuthority())
{
    // Play animation immediately for responsiveness
    AnimInstance->Montage_Play(Montage, PlayRate, EMontagePlayReturnType::MontageLength, StartingPosition);
    
    // Set prediction data
    FAnimationPredictionData PredictionData;
    PredictionData.Montage = Montage;
    PredictionData.PlayRate = PlayRate;
    PredictionData.StartingPosition = StartingPosition;
    PredictionData.PredictionTime = GetWorld()->GetTimeSeconds();
    PredictionData.bIsValid = true;
    
    AnimationPrediction = PredictionData;
    OnAnimationPredicted.Broadcast(PredictionData);
}

// Request server validation
ServerPlayMontage(Montage, PlayRate, StartingPosition);
```

**Server Validation:**
```cpp
// Server validates and multicasts to all clients
void ServerPlayMontage_Implementation(UAnimMontage* Montage, float PlayRate, float StartingPosition)
{
    // Server-side validation logic here
    MulticastPlayMontage(Montage, PlayRate, StartingPosition);
}
```

### 2. Actor Attachment with Hot Joining

**Spawning with Hot Join Support:**
```cpp
void MulticastSpawnActorAttached_Implementation(TSubclassOf<AActor> ActorClass, FName AttachSocketName, FVector LocationOffset, FRotator RotationOffset)
{
    // Spawn the actor
    AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClass, SpawnLocation, SpawnRotation);
    
    if (SpawnedActor)
    {
        // Create attachment info for hot joining
        FAttachmentInfo NewAttachment;
        NewAttachment.Component = SpawnedActor->GetRootComponent();
        NewAttachment.SocketName = AttachSocketName;
        NewAttachment.Owner = GetOwner();
        NewAttachment.bKeepWorldTransform = true;
        NewAttachment.RelativeTransform = FTransform(RotationOffset, LocationOffset, FVector::OneVector);
        NewAttachment.bIsActive = true;

        // Set replicated property for hot joiners
        AttachmentInfo = NewAttachment;

        // Apply immediate attachment for current clients
        if (AttachSocketName != NAME_None)
        {
            SpawnedActor->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform, AttachSocketName);
        }
        else
        {
            SpawnedActor->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
        }
    }
}
```

**Hot Joiner Handling:**
```cpp
void OnRep_AttachmentInfo()
{
    // Apply attachment for hot joining clients
    if (AttachmentInfo.bIsActive && AttachmentInfo.Component && AttachmentInfo.Owner)
    {
        if (AttachmentInfo.SocketName != NAME_None)
        {
            AttachmentInfo.Component->AttachToComponent(
                AttachmentInfo.Owner->GetRootComponent(),
                AttachmentInfo.bKeepWorldTransform ? FAttachmentTransformRules::KeepWorldTransform : FAttachmentTransformRules::KeepRelativeTransform,
                AttachmentInfo.SocketName);
        }
        else
        {
            AttachmentInfo.Component->AttachToComponent(
                AttachmentInfo.Owner->GetRootComponent(),
                AttachmentInfo.bKeepWorldTransform ? FAttachmentTransformRules::KeepWorldTransform : FAttachmentTransformRules::KeepRelativeTransform);
        }

        // Apply relative transform if specified
        if (!AttachmentInfo.RelativeTransform.Equals(FTransform::Identity))
        {
            AttachmentInfo.Component->SetRelativeTransform(AttachmentInfo.RelativeTransform);
        }
    }

    OnAttachmentInfoReplicated.Broadcast(AttachmentInfo);
}
```

### 3. Niagara Effects with Attachment

**Replicating VFX:**
```cpp
UNiagaraComponent* ReplicateNiagaraEffect(UNiagaraSystem* Effect, FVector Location, FRotator Rotation, bool bAttachToOwner, FName AttachSocketName)
{
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
```

## Testing and Debugging

### Hot Joining Tests

```cpp
void TestHotJoining()
{
    // Simulate spawning an attached actor for hot joining test
    if (GetOwner()->HasAuthority())
    {
        FAttachmentInfo TestAttachment;
        TestAttachment.bIsActive = true;
        TestAttachment.Owner = GetOwner();
        TestAttachment.SocketName = NAME_None;
        TestAttachment.bKeepWorldTransform = true;
        TestAttachment.RelativeTransform = FTransform::Identity;

        // Set the replicated property to trigger OnRep for hot joiners
        AttachmentInfo = TestAttachment;
    }
}
```

### High Ping Simulation

```cpp
void TestHighPingPrediction()
{
    // Set up high ping simulation via console commands
    if (IConsoleVariable* NetPktLag = IConsoleManager::Get().FindConsoleVariable(TEXT("Net.PktLag")))
    {
        NetPktLag->Set(150.0f); // 150ms lag
    }

    if (IConsoleVariable* NetPktLagVariance = IConsoleManager::Get().FindConsoleVariable(TEXT("Net.PktLagVariance")))
    {
        NetPktLagVariance->Set(25.0f); // 25ms variance
    }
}
```

### Low FPS Testing

```cpp
void TestLowFPSScenario()
{
    // Set low FPS via console commands
    if (IConsoleVariable* MaxFPS = IConsoleManager::Get().FindConsoleVariable(TEXT("t.MaxFPS")))
    {
        MaxFPS->Set(20.0f); // 20 FPS
    }

    if (IConsoleVariable* OneFrameThreadLag = IConsoleManager::Get().FindConsoleVariable(TEXT("r.OneFrameThreadLag")))
    {
        OneFrameThreadLag->Set(1); // Enable one frame thread lag
    }
}
```

## Performance Considerations

### Network Optimization

1. **Use Authority Checks**: Always check `GetOwner()->HasAuthority()` before server-only operations
2. **Minimize RPC Calls**: Batch operations when possible
3. **Optimize Replication**: Use `ReplicatedUsing` only when necessary
4. **Debug Mode**: Disable in shipping builds

### Memory Management

1. **Component Cleanup**: The component handles cleanup in `EndPlay`
2. **Delegate Binding**: Unbind delegates when components are destroyed
3. **Replicated Properties**: Keep them lightweight and necessary

## Best Practices

### 1. Authority Patterns

```cpp
// Always check authority before server operations
if (GetOwner()->HasAuthority())
{
    // Server-only logic
    MulticastOperation();
}
else
{
    // Client request to server
    ServerOperation();
}
```

### 2. Error Handling

```cpp
// Validate inputs before replication
if (!Montage)
{
    UE_LOG(LogTemp, Warning, TEXT("ReplicateAnimation: Montage is null"));
    return;
}
```

### 3. Debug Logging

```cpp
// Use debug mode for logging
if (bDebugMode)
{
    UE_LOG(LogTemp, Log, TEXT("Replicating Animation: %s"), *Montage->GetName());
}
```

## Integration with Other Systems

### Motion Matching

The plugin includes support for Epic's Game Animation Sample motion matching:

```cpp
// Replicate motion matching database
ReplicateMotionMatchingDatabase(MotionMatchingDatabase);

// Replicate pose search schema
ReplicatePoseSearchSchema(PoseSearchSchema);

// Replicate trajectory data
ReplicateTrajectoryData(Position, Rotation);
```

### Custom Variables

Replicate custom game state:

```cpp
// String variables
ReplicateStringVariable(FName("PlayerName"), TEXT("Player1"));

// Numeric variables
ReplicateFloatVariable(FName("Health"), 100.0f);
ReplicateIntVariable(FName("Score"), 1500);
ReplicateBoolVariable(FName("IsAlive"), true);

// Vector variables
ReplicateVectorVariable(FName("LastPosition"), FVector(100, 200, 300));
```

## Troubleshooting

### Common Issues

1. **Hot Joining Not Working**: Ensure `ReplicatedUsing` properties are set correctly
2. **Prediction Feels Laggy**: Check client-side prediction implementation
3. **High Ping Issues**: Verify server validation and correction logic
4. **Low FPS Crashes**: Test with performance monitoring enabled

### Debug Tools

1. **Enable Debug Mode**: Set `bDebugMode = true` on the component
2. **Console Commands**: Use `Net.PktLag` and `t.MaxFPS` for testing
3. **Log Files**: Check `Saved/Logs/` for detailed information
4. **Network Stats**: Use `stat net` console command

## Next Steps

- Review the [API Reference](API_Reference.md) for complete function documentation
- Check [Troubleshooting](Troubleshooting.md) for specific issues
- Explore the plugin source code for advanced customization
