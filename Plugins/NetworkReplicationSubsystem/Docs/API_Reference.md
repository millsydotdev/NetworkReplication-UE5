# Network Replication Subsystem - API Reference
## Complete API Documentation

The Network Replication Subsystem provides Blueprint-friendly replication functions for animations, sounds, Niagara systems, and actor spawning in Unreal Engine 5.6+.

---

## **UNetworkReplicationComponent**

The main component for handling network replication.

### **Properties**

| Property | Type | Description |
|----------|------|-------------|
| `bAutoRegister` | `bool` | Automatically register with subsystem on BeginPlay |
| `ReplicationSettings` | `FNetworkReplicationSettings` | Configuration settings for replication |

### **Animation Functions**

**ReplicateAnimation**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Animation")
void ReplicateAnimation(UAnimMontage* Montage, float PlayRate = 1.0f, float StartTime = 0.0f);
```

- **Description**: Replicates an animation montage to all clients
- **Parameters**:
  - `Montage`: The animation montage to replicate
  - `PlayRate`: Playback rate multiplier
  - `StartTime`: Time to start playing from

**ReplicateAnimationStop**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Animation")
void ReplicateAnimationStop(UAnimMontage* Montage, bool bBlendOut = true);
```

- **Description**: Stops an animation montage on all clients
- **Parameters**:
  - `Montage`: The animation montage to stop
  - `bBlendOut`: Whether to blend out the animation

### **Audio Functions**

**ReplicateSound**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Audio")
void ReplicateSound(USoundBase* Sound, float Volume = 1.0f, float Pitch = 1.0f, float StartTime = 0.0f);
```

- **Description**: Replicates a sound to all clients
- **Parameters**:
  - `Sound`: The sound asset to replicate
  - `Volume`: Volume multiplier
  - `Pitch`: Pitch multiplier
  - `StartTime`: Time to start playing from

**ReplicateSoundAtLocation**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Audio")
void ReplicateSoundAtLocation(USoundBase* Sound, FVector Location, float Volume = 1.0f, float Pitch = 1.0f);
```

- **Description**: Replicates a sound at a specific world location
- **Parameters**:
  - `Sound`: The sound asset to replicate
  - `Location`: World location to play the sound
  - `Volume`: Volume multiplier
  - `Pitch`: Pitch multiplier

### **Actor Spawning Functions**

**ReplicateActorSpawn**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Spawning")
AActor* ReplicateActorSpawn(TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation, bool bAutoDestroy = false);
```

- **Description**: Spawns an actor on all clients
- **Parameters**:
  - `ActorClass`: The class of actor to spawn
  - `Location`: World location to spawn at
  - `Rotation`: World rotation to spawn with
  - `bAutoDestroy`: Whether to automatically destroy after a delay
- **Returns**: The spawned actor (on server)

**ReplicateActorDestroy**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Spawning")
void ReplicateActorDestroy(AActor* Actor);
```

- **Description**: Destroys an actor on all clients
- **Parameters**:
  - `Actor`: The actor to destroy

### **Niagara Effects Functions**

**ReplicateNiagaraEffect**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Effects")
UNiagaraComponent* ReplicateNiagaraEffect(UNiagaraSystem* System, FVector Location, FRotator Rotation);
```

- **Description**: Spawns a Niagara effect on all clients
- **Parameters**:
  - `System`: The Niagara system to spawn
  - `Location`: World location to spawn at
  - `Rotation`: World rotation to spawn with
- **Returns**: The Niagara component (on server)

### **Motion Matching Functions**

**ReplicateMotionMatchingDatabase**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Motion Matching")
void ReplicateMotionMatchingDatabase(UObject* Database);
```

- **Description**: Replicates motion matching database to all clients
- **Parameters**:
  - `Database`: The motion matching database to replicate
- **Compatibility**: Works with Epic's Game Animation Sample project

**ReplicatePoseSearchSchema**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Motion Matching")
void ReplicatePoseSearchSchema(UObject* Schema);
```

- **Description**: Replicates pose search schema to all clients
- **Parameters**:
  - `Schema`: The pose search schema to replicate
- **Compatibility**: Full PoseSearch plugin integration

**ReplicateTrajectoryData**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication|Motion Matching")
void ReplicateTrajectoryData(const FVector& Position, const FRotator& Rotation);
```

- **Description**: Replicates trajectory data for motion matching
- **Parameters**:
  - `Position`: World position for trajectory
  - `Rotation`: World rotation for trajectory
- **Use Case**: Essential for motion matching locomotion systems

### **Utility Functions**

**IsServer**

```cpp
UFUNCTION(BlueprintPure, Category = "Network Replication|Utility")
bool IsServer() const;
```

- **Description**: Returns true if running on server
- **Returns**: True if server, false if client

**IsClient**

```cpp
UFUNCTION(BlueprintPure, Category = "Network Replication|Utility")
bool IsClient() const;
```

- **Description**: Returns true if running on client
- **Returns**: True if client, false if server

**GetOwningActor**

```cpp
UFUNCTION(BlueprintPure, Category = "Network Replication|Utility")
AActor* GetOwningActor() const;
```

- **Description**: Gets the actor that owns this component
- **Returns**: The owning actor

---

## **UNetworkReplicationSubsystem**

The subsystem that manages all network replication components.

### **Component Management Functions**

**GetReplicationComponent**

```cpp
UFUNCTION(BlueprintPure, Category = "Network Replication Subsystem")
UNetworkReplicationComponent* GetReplicationComponent(AActor* Actor) const;
```

- **Description**: Gets the replication component for a specific actor
- **Parameters**:
  - `Actor`: The actor to get the component from
- **Returns**: The replication component, or nullptr if not found

**RegisterReplicationComponent**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication Subsystem")
void RegisterReplicationComponent(UNetworkReplicationComponent* Component);
```

- **Description**: Registers a replication component with the subsystem
- **Parameters**:
  - `Component`: The component to register

**UnregisterReplicationComponent**

```cpp
UFUNCTION(BlueprintCallable, Category = "Network Replication Subsystem")
void UnregisterReplicationComponent(UNetworkReplicationComponent* Component);
```

- **Description**: Unregisters a replication component from the subsystem
- **Parameters**:
  - `Component`: The component to unregister

---

## **FNetworkReplicationSettings**

Configuration settings for network replication.

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `bEnableReplication` | `bool` | `true` | Whether replication is enabled |
| `ReplicationFrequency` | `float` | `60.0f` | Frequency of replication updates (Hz) |
| `MaxReplicationDistance` | `float` | `10000.0f` | Maximum distance for replication |
| `bUseRelevancy` | `bool` | `true` | Whether to use relevancy checking |
| `bCompressData` | `bool` | `false` | Whether to compress replication data |

---

## **Epic Game Animation Sample Integration**

This plugin is **fully compatible** with Epic's Game Animation Sample project, providing seamless motion matching replication for multiplayer games.

### **Game Animation Sample Setup**

1. **Download the Game Animation Sample** from Epic Games
2. **Add this plugin** to your Game Animation Sample project
3. **Enable required plugins**: PoseSearch, Chooser, AnimationCore
4. **Use motion matching functions** for network replication

### **Motion Matching Replication Example**

```cpp
// Replicate pose search schema for motion matching
ReplicationComponent->ReplicatePoseSearchSchema(MyPoseSearchSchema);

// Replicate trajectory data for locomotion
ReplicationComponent->ReplicateTrajectoryData(CharacterLocation, CharacterRotation);

// Replicate motion matching database
ReplicationComponent->ReplicateMotionMatchingDatabase(MyMotionMatchingDatabase);
```

### **Blueprint Integration**

All motion matching functions are available in Blueprint under:
- **Category**: `Network Replication|Motion Matching`
- **Events**: `OnMotionMatchingReplicated`, `OnTrajectoryReplicated`, `OnPoseSearchReplicated`

---

## **Usage Examples**

### **Adding the Component**

1. **In Blueprint Editor**:
   - Open your Blueprint
   - Click "Add Component"
   - Search for "Network Replication Component"
   - Add it to your Blueprint

2. **In C++**:
   ```cpp
   // In your class constructor
   ReplicationComponent = CreateDefaultSubobject<UNetworkReplicationComponent>(TEXT("ReplicationComponent"));
   ```

### **Animation Replication**

```cpp
// In Blueprint: Call "Replicate Animation" function
// In C++:
if (ReplicationComponent)
{
    ReplicationComponent->ReplicateAnimation(MyMontage, 1.0f, 0.0f);
}
```

### **Sound Replication**

```cpp
// In Blueprint: Call "Replicate Sound" function
// In C++:
if (ReplicationComponent)
{
    ReplicationComponent->ReplicateSound(MySound, 1.0f, 1.0f, 0.0f);
}
```

### **Actor Spawning**

```cpp
// In Blueprint: Call "Replicate Actor Spawn" function
// In C++:
if (ReplicationComponent)
{
    AActor* SpawnedActor = ReplicationComponent->ReplicateActorSpawn(
        MyActorClass,
        GetActorLocation(),
        GetActorRotation(),
        false
    );
}
```

---

## **Performance Optimization**

- **Use Relevancy**: Enable relevancy checking to only replicate to nearby clients
- **Adjust Frequency**: Lower replication frequency for less critical updates
- **Distance Culling**: Set appropriate maximum replication distance
- **Compression**: Enable data compression for bandwidth-limited scenarios

---

## **Best Practices**

- **Server Authority**: Always call replication functions from the server
- **Validation**: Validate inputs before calling replication functions
- **Error Handling**: Check for null pointers and valid assets
- **Performance Monitoring**: Use built-in performance monitoring tools

---

## **Troubleshooting**

- **Component Not Found**: Ensure the plugin is enabled and the component is added
- **Replication Not Working**: Check that the actor has replication enabled
- **Performance Issues**: Adjust replication settings and use relevancy
- **Compilation Errors**: Ensure all dependencies are included

---

## **Debugging Tools**

- **Network Profiler**: Use UE's network profiler to monitor bandwidth
- **Replication Logs**: Enable replication logging in project settings
- **Component Inspection**: Use the Details panel to inspect component settings

---

**For more examples and advanced usage, see the [Examples](Examples.md) documentation.**
