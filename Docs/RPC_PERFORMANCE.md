# RPC Performance Guide
## Optimizing Custom RPCs for Maximum Performance

This guide provides advanced techniques for optimizing custom RPCs and integrating them efficiently with the Network Replication Subsystem plugin.

---

## **Performance Fundamentals**

### **RPC Types and Performance**

| RPC Type | Reliability | Performance | Use Case |
|----------|-------------|-------------|----------|
| `Server, Reliable` | ✅ Guaranteed | ⚠️ Slower | Critical game logic |
| `Server, Unreliable` | ❌ Not guaranteed | ⚡ Faster | Frequent updates |
| `NetMulticast, Reliable` | ✅ Guaranteed | ⚠️ Slower | Important events |
| `NetMulticast, Unreliable` | ❌ Not guaranteed | ⚡ Faster | Visual effects |

### **Bandwidth Considerations**

```cpp
// High bandwidth usage (avoid for frequent updates)
UFUNCTION(Server, Reliable, Category = "Performance Critical")
void ServerUpdatePlayerPosition(FVector Position, FRotator Rotation, FVector Velocity);

// Optimized for frequent updates
UFUNCTION(Server, Unreliable, Category = "Performance Critical")
void ServerUpdatePlayerPosition(FVector Position);

// Use reliable for important state changes
UFUNCTION(Server, Reliable, Category = "Performance Critical")
void ServerUpdatePlayerHealth(float NewHealth);
```

---

## **Rate Limiting and Throttling**

### **Basic Rate Limiting**

```cpp
// MyOptimizedRPCs.h
UCLASS()
class YOURGAME_API UMyOptimizedRPCs : public UActorComponent
{
    GENERATED_BODY()

public:
    UMyOptimizedRPCs();

    // Optimized update functions
    UFUNCTION(BlueprintCallable, Category = "Optimized RPCs")
    void UpdatePlayerPosition(const FVector& NewPosition);

    UFUNCTION(BlueprintCallable, Category = "Optimized RPCs")
    void UpdatePlayerRotation(const FRotator& NewRotation);

    UFUNCTION(BlueprintCallable, Category = "Optimized RPCs")
    void UpdatePlayerStats(const FPlayerStats& NewStats);

protected:
    // Rate limiting variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float PositionUpdateRate = 0.1f; // 10 times per second

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float RotationUpdateRate = 0.05f; // 20 times per second

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float StatsUpdateRate = 1.0f; // 1 time per second

    // Last update times
    float LastPositionUpdate = 0.0f;
    float LastRotationUpdate = 0.0f;
    float LastStatsUpdate = 0.0f;

    // Update counters for adaptive rate limiting
    int32 PositionUpdateCount = 0;
    int32 RotationUpdateCount = 0;
    int32 StatsUpdateCount = 0;
};
```

```cpp
// MyOptimizedRPCs.cpp
void UMyOptimizedRPCs::UpdatePlayerPosition(const FVector& NewPosition)
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    
    // Rate limiting
    if (CurrentTime - LastPositionUpdate < PositionUpdateRate)
    {
        return;
    }

    // Adaptive rate limiting based on network conditions
    if (ShouldThrottleUpdates())
    {
        PositionUpdateRate = FMath::Max(PositionUpdateRate * 1.5f, 0.5f);
        return;
    }

    // Send position update
    ServerUpdatePlayerPosition(NewPosition);
    
    LastPositionUpdate = CurrentTime;
    PositionUpdateCount++;
}

bool UMyOptimizedRPCs::ShouldThrottleUpdates()
{
    // Check network conditions
    if (UNetDriver* NetDriver = GetWorld()->GetNetDriver())
    {
        // Throttle if bandwidth is high
        if (NetDriver->GetNetStats().OutBytesPerSecond > 100000) // 100KB/s
        {
            return true;
        }
    }
    
    return false;
}
```

### **Advanced Rate Limiting**

```cpp
// MyAdvancedRPCs.h
UCLASS()
class YOURGAME_API UMyAdvancedRPCs : public UActorComponent
{
    GENERATED_BODY()

public:
    UMyAdvancedRPCs();

    // Adaptive update functions
    UFUNCTION(BlueprintCallable, Category = "Advanced RPCs")
    void AdaptiveUpdatePlayerPosition(const FVector& NewPosition);

    UFUNCTION(BlueprintCallable, Category = "Advanced RPCs")
    void AdaptiveUpdatePlayerRotation(const FRotator& NewRotation);

protected:
    // Adaptive rate limiting
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float BasePositionUpdateRate = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float BaseRotationUpdateRate = 0.05f;

    // Current rates (adaptive)
    float CurrentPositionUpdateRate;
    float CurrentRotationUpdateRate;

    // Network condition monitoring
    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float NetworkLatency = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float NetworkBandwidth = 0.0f;

    // Update history for trend analysis
    TArray<float> PositionUpdateHistory;
    TArray<float> RotationUpdateHistory;
};
```

```cpp
// MyAdvancedRPCs.cpp
void UMyAdvancedRPCs::AdaptiveUpdatePlayerPosition(const FVector& NewPosition)
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    
    // Adaptive rate limiting
    if (CurrentTime - LastPositionUpdate < CurrentPositionUpdateRate)
    {
        return;
    }

    // Analyze network conditions
    AnalyzeNetworkConditions();
    
    // Adjust rate based on network conditions
    AdjustUpdateRates();

    // Send position update
    ServerUpdatePlayerPosition(NewPosition);
    
    LastPositionUpdate = CurrentTime;
    
    // Track update history
    PositionUpdateHistory.Add(CurrentTime);
    if (PositionUpdateHistory.Num() > 100)
    {
        PositionUpdateHistory.RemoveAt(0);
    }
}

void UMyAdvancedRPCs::AnalyzeNetworkConditions()
{
    if (UNetDriver* NetDriver = GetWorld()->GetNetDriver())
    {
        // Get network statistics
        FNetStats NetStats = NetDriver->GetNetStats();
        
        // Update network conditions
        NetworkLatency = NetStats.AvgLatency;
        NetworkBandwidth = NetStats.OutBytesPerSecond;
    }
}

void UMyAdvancedRPCs::AdjustUpdateRates()
{
    // Adjust position update rate based on network conditions
    if (NetworkLatency > 100.0f) // High latency
    {
        CurrentPositionUpdateRate = BasePositionUpdateRate * 2.0f;
    }
    else if (NetworkBandwidth > 200000) // High bandwidth usage
    {
        CurrentPositionUpdateRate = BasePositionUpdateRate * 1.5f;
    }
    else
    {
        CurrentPositionUpdateRate = BasePositionUpdateRate;
    }

    // Adjust rotation update rate
    if (NetworkLatency > 100.0f)
    {
        CurrentRotationUpdateRate = BaseRotationUpdateRate * 2.0f;
    }
    else if (NetworkBandwidth > 200000)
    {
        CurrentRotationUpdateRate = BaseRotationUpdateRate * 1.5f;
    }
    else
    {
        CurrentRotationUpdateRate = BaseRotationUpdateRate;
    }
}
```

---

## **Data Compression and Optimization**

### **Compressed Data Structures**

```cpp
// MyCompressedRPCs.h
UCLASS()
class YOURGAME_API UMyCompressedRPCs : public UActorComponent
{
    GENERATED_BODY()

public:
    UMyCompressedRPCs();

    // Compressed update functions
    UFUNCTION(BlueprintCallable, Category = "Compressed RPCs")
    void UpdatePlayerPositionCompressed(const FVector& NewPosition);

    UFUNCTION(BlueprintCallable, Category = "Compressed RPCs")
    void UpdatePlayerRotationCompressed(const FRotator& NewRotation);

    UFUNCTION(BlueprintCallable, Category = "Compressed RPCs")
    void UpdatePlayerStatsCompressed(const FPlayerStats& NewStats);

protected:
    // Compressed data structures
    USTRUCT(BlueprintType)
    struct FCompressedPosition
    {
        GENERATED_BODY()

        UPROPERTY(BlueprintReadOnly, Category = "Compressed Data")
        int32 X, Y, Z;

        FCompressedPosition() : X(0), Y(0), Z(0) {}
        FCompressedPosition(const FVector& Vector) 
        {
            X = FMath::RoundToInt(Vector.X * 100.0f);
            Y = FMath::RoundToInt(Vector.Y * 100.0f);
            Z = FMath::RoundToInt(Vector.Z * 100.0f);
        }

        FVector ToVector() const
        {
            return FVector(X / 100.0f, Y / 100.0f, Z / 100.0f);
        }
    };

    USTRUCT(BlueprintType)
    struct FCompressedRotation
    {
        GENERATED_BODY()

        UPROPERTY(BlueprintReadOnly, Category = "Compressed Data")
        int32 Pitch, Yaw, Roll;

        FCompressedRotation() : Pitch(0), Yaw(0), Roll(0) {}
        FCompressedRotation(const FRotator& Rotator)
        {
            Pitch = FMath::RoundToInt(Rotator.Pitch);
            Yaw = FMath::RoundToInt(Rotator.Yaw);
            Roll = FMath::RoundToInt(Rotator.Roll);
        }

        FRotator ToRotator() const
        {
            return FRotator(Pitch, Yaw, Roll);
        }
    };

    // Server RPCs with compressed data
    UFUNCTION(Server, Unreliable, Category = "Compressed RPCs")
    void ServerUpdatePlayerPositionCompressed(FCompressedPosition CompressedPosition);

    UFUNCTION(Server, Unreliable, Category = "Compressed RPCs")
    void ServerUpdatePlayerRotationCompressed(FCompressedRotation CompressedRotation);

    UFUNCTION(Server, Reliable, Category = "Compressed RPCs")
    void ServerUpdatePlayerStatsCompressed(int32 Health, int32 Mana, int32 Level);
};
```

```cpp
// MyCompressedRPCs.cpp
void UMyCompressedRPCs::UpdatePlayerPositionCompressed(const FVector& NewPosition)
{
    // Compress position data
    FCompressedPosition CompressedPos(NewPosition);
    
    // Send compressed data
    ServerUpdatePlayerPositionCompressed(CompressedPos);
}

void UMyCompressedRPCs::UpdatePlayerRotationCompressed(const FRotator& NewRotation)
{
    // Compress rotation data
    FCompressedRotation CompressedRot(NewRotation);
    
    // Send compressed data
    ServerUpdatePlayerRotationCompressed(CompressedRot);
}

void UMyCompressedRPCs::UpdatePlayerStatsCompressed(const FPlayerStats& NewStats)
{
    // Compress stats data
    int32 Health = FMath::Clamp(FMath::RoundToInt(NewStats.Health), 0, 999);
    int32 Mana = FMath::Clamp(FMath::RoundToInt(NewStats.Mana), 0, 999);
    int32 Level = FMath::Clamp(NewStats.Level, 1, 99);
    
    // Send compressed data
    ServerUpdatePlayerStatsCompressed(Health, Mana, Level);
}

// Server RPC implementations
void UMyCompressedRPCs::ServerUpdatePlayerPositionCompressed_Implementation(FCompressedPosition CompressedPosition)
{
    // Decompress and update
    FVector NewPosition = CompressedPosition.ToVector();
    
    // Update player position
    if (APawn* Pawn = GetOwner<APawn>())
    {
        Pawn->SetActorLocation(NewPosition);
    }
    
    // Multicast to other clients
    MulticastUpdatePlayerPositionCompressed(CompressedPosition);
}

void UMyCompressedRPCs::ServerUpdatePlayerRotationCompressed_Implementation(FCompressedRotation CompressedRotation)
{
    // Decompress and update
    FRotator NewRotation = CompressedRotation.ToRotator();
    
    // Update player rotation
    if (APawn* Pawn = GetOwner<APawn>())
    {
        Pawn->SetActorRotation(NewRotation);
    }
    
    // Multicast to other clients
    MulticastUpdatePlayerRotationCompressed(CompressedRotation);
}
```

---

## **Batch Updates and Batching**

### **Batch Update System**

```cpp
// MyBatchRPCs.h
UCLASS()
class YOURGAME_API UMyBatchRPCs : public UActorComponent
{
    GENERATED_BODY()

public:
    UMyBatchRPCs();

    // Batch update functions
    UFUNCTION(BlueprintCallable, Category = "Batch RPCs")
    void AddPositionUpdate(const FVector& NewPosition);

    UFUNCTION(BlueprintCallable, Category = "Batch RPCs")
    void AddRotationUpdate(const FRotator& NewRotation);

    UFUNCTION(BlueprintCallable, Category = "Batch RPCs")
    void AddStatsUpdate(const FPlayerStats& NewStats);

    UFUNCTION(BlueprintCallable, Category = "Batch RPCs")
    void FlushBatchUpdates();

protected:
    // Batch data structures
    USTRUCT(BlueprintType)
    struct FBatchUpdateData
    {
        GENERATED_BODY()

        UPROPERTY(BlueprintReadOnly, Category = "Batch Data")
        TArray<FVector> Positions;

        UPROPERTY(BlueprintReadOnly, Category = "Batch Data")
        TArray<FRotator> Rotations;

        UPROPERTY(BlueprintReadOnly, Category = "Batch Data")
        TArray<FPlayerStats> Stats;

        UPROPERTY(BlueprintReadOnly, Category = "Batch Data")
        float Timestamp;
    };

    // Batch update settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float BatchUpdateInterval = 0.1f; // 10 times per second

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    int32 MaxBatchSize = 10;

    // Batch data
    FBatchUpdateData PendingUpdates;
    float LastBatchUpdate = 0.0f;

    // Server RPCs
    UFUNCTION(Server, Reliable, Category = "Batch RPCs")
    void ServerProcessBatchUpdates(FBatchUpdateData BatchData);

    UFUNCTION(NetMulticast, Reliable, Category = "Batch RPCs")
    void MulticastProcessBatchUpdates(FBatchUpdateData BatchData);
};
```

```cpp
// MyBatchRPCs.cpp
void UMyBatchRPCs::AddPositionUpdate(const FVector& NewPosition)
{
    // Add to batch
    PendingUpdates.Positions.Add(NewPosition);
    
    // Check if batch is full
    if (PendingUpdates.Positions.Num() >= MaxBatchSize)
    {
        FlushBatchUpdates();
    }
}

void UMyBatchRPCs::AddRotationUpdate(const FRotator& NewRotation)
{
    // Add to batch
    PendingUpdates.Rotations.Add(NewRotation);
    
    // Check if batch is full
    if (PendingUpdates.Rotations.Num() >= MaxBatchSize)
    {
        FlushBatchUpdates();
    }
}

void UMyBatchRPCs::AddStatsUpdate(const FPlayerStats& NewStats)
{
    // Add to batch
    PendingUpdates.Stats.Add(NewStats);
    
    // Check if batch is full
    if (PendingUpdates.Stats.Num() >= MaxBatchSize)
    {
        FlushBatchUpdates();
    }
}

void UMyBatchRPCs::FlushBatchUpdates()
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    
    // Check if enough time has passed
    if (CurrentTime - LastBatchUpdate < BatchUpdateInterval)
    {
        return;
    }

    // Set timestamp
    PendingUpdates.Timestamp = CurrentTime;
    
    // Send batch update
    ServerProcessBatchUpdates(PendingUpdates);
    
    // Clear batch
    PendingUpdates.Positions.Empty();
    PendingUpdates.Rotations.Empty();
    PendingUpdates.Stats.Empty();
    
    LastBatchUpdate = CurrentTime;
}

// Server RPC implementation
void UMyBatchRPCs::ServerProcessBatchUpdates_Implementation(FBatchUpdateData BatchData)
{
    // Process all updates in batch
    for (const FVector& Position : BatchData.Positions)
    {
        // Update position
        if (APawn* Pawn = GetOwner<APawn>())
        {
            Pawn->SetActorLocation(Position);
        }
    }

    for (const FRotator& Rotation : BatchData.Rotations)
    {
        // Update rotation
        if (APawn* Pawn = GetOwner<APawn>())
        {
            Pawn->SetActorRotation(Rotation);
        }
    }

    for (const FPlayerStats& Stats : BatchData.Stats)
    {
        // Update stats
        // ... update player stats
    }
    
    // Multicast to other clients
    MulticastProcessBatchUpdates(BatchData);
}
```

---

## **Network Condition Monitoring**

### **Performance Monitoring System**

```cpp
// MyPerformanceMonitor.h
UCLASS()
class YOURGAME_API UMyPerformanceMonitor : public UActorComponent
{
    GENERATED_BODY()

public:
    UMyPerformanceMonitor();

    // Performance monitoring functions
    UFUNCTION(BlueprintCallable, Category = "Performance Monitor")
    void StartPerformanceMonitoring();

    UFUNCTION(BlueprintCallable, Category = "Performance Monitor")
    void StopPerformanceMonitoring();

    UFUNCTION(BlueprintCallable, Category = "Performance Monitor")
    FString GetPerformanceReport() const;

protected:
    // Performance metrics
    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float AverageLatency = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float AverageBandwidth = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    int32 TotalRPCsSent = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    int32 TotalRPCsReceived = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float RPCSuccessRate = 0.0f;

    // Monitoring settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float MonitoringInterval = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    bool bAutoOptimize = true;

    // Internal data
    TArray<float> LatencyHistory;
    TArray<float> BandwidthHistory;
    float LastMonitoringTime = 0.0f;
    bool bIsMonitoring = false;

    // Performance optimization
    void OptimizePerformance();
    void AdjustUpdateRates();
    void AnalyzeNetworkConditions();
};
```

```cpp
// MyPerformanceMonitor.cpp
void UMyPerformanceMonitor::StartPerformanceMonitoring()
{
    bIsMonitoring = true;
    LastMonitoringTime = GetWorld()->GetTimeSeconds();
    
    UE_LOG(LogTemp, Log, TEXT("Performance monitoring started"));
}

void UMyPerformanceMonitor::StopPerformanceMonitoring()
{
    bIsMonitoring = false;
    
    UE_LOG(LogTemp, Log, TEXT("Performance monitoring stopped"));
}

void UMyPerformanceMonitor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (!bIsMonitoring)
    {
        return;
    }

    float CurrentTime = GetWorld()->GetTimeSeconds();
    
    // Check if it's time to monitor
    if (CurrentTime - LastMonitoringTime >= MonitoringInterval)
    {
        AnalyzeNetworkConditions();
        
        if (bAutoOptimize)
        {
            OptimizePerformance();
        }
        
        LastMonitoringTime = CurrentTime;
    }
}

void UMyPerformanceMonitor::AnalyzeNetworkConditions()
{
    if (UNetDriver* NetDriver = GetWorld()->GetNetDriver())
    {
        FNetStats NetStats = NetDriver->GetNetStats();
        
        // Update metrics
        AverageLatency = NetStats.AvgLatency;
        AverageBandwidth = NetStats.OutBytesPerSecond;
        
        // Track history
        LatencyHistory.Add(AverageLatency);
        BandwidthHistory.Add(AverageBandwidth);
        
        // Keep history size manageable
        if (LatencyHistory.Num() > 100)
        {
            LatencyHistory.RemoveAt(0);
        }
        
        if (BandwidthHistory.Num() > 100)
        {
            BandwidthHistory.RemoveAt(0);
        }
    }
}

void UMyPerformanceMonitor::OptimizePerformance()
{
    // Analyze network conditions
    float AvgLatency = 0.0f;
    float AvgBandwidth = 0.0f;
    
    for (float Latency : LatencyHistory)
    {
        AvgLatency += Latency;
    }
    AvgLatency /= LatencyHistory.Num();
    
    for (float Bandwidth : BandwidthHistory)
    {
        AvgBandwidth += Bandwidth;
    }
    AvgBandwidth /= BandwidthHistory.Num();
    
    // Adjust performance based on conditions
    if (AvgLatency > 100.0f || AvgBandwidth > 200000)
    {
        // Reduce update rates
        AdjustUpdateRates();
        
        UE_LOG(LogTemp, Log, TEXT("Performance optimization: Reduced update rates due to poor network conditions"));
    }
}

FString UMyPerformanceMonitor::GetPerformanceReport() const
{
    return FString::Printf(TEXT("Performance Report:\nLatency: %.2fms\nBandwidth: %.2f KB/s\nRPCs Sent: %d\nRPCs Received: %d\nSuccess Rate: %.2f%%"),
        AverageLatency, AverageBandwidth / 1024.0f, TotalRPCsSent, TotalRPCsReceived, RPCSuccessRate);
}
```

---

## **Integration with Plugin Performance**

### **Combining Plugin and Custom RPC Performance**

```cpp
// MyOptimizedPlayerController.h
UCLASS()
class YOURGAME_API AMyOptimizedPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMyOptimizedPlayerController();

    // Optimized player actions
    UFUNCTION(BlueprintCallable, Category = "Optimized Player")
    void PerformOptimizedAction(const FString& ActionName, const FString& ActionData);

protected:
    // Plugin component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network Replication")
    class UNetworkReplicationComponent* NetworkReplicationComponent;

    // Custom RPC component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom RPCs")
    class UMyGameRPCs* GameRPCs;

    // Performance monitor
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Performance")
    class UMyPerformanceMonitor* PerformanceMonitor;

    // Performance settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    bool bUsePluginForEffects = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    bool bUseCustomRPCsForLogic = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    bool bEnablePerformanceOptimization = true;
};
```

```cpp
// MyOptimizedPlayerController.cpp
void AMyOptimizedPlayerController::PerformOptimizedAction(const FString& ActionName, const FString& ActionData)
{
    // Check performance conditions
    if (PerformanceMonitor && PerformanceMonitor->ShouldThrottleUpdates())
    {
        // Skip non-critical updates
        if (ActionName != TEXT("CriticalAction"))
        {
            return;
        }
    }

    // Use plugin for effects (optimized)
    if (NetworkReplicationComponent && bUsePluginForEffects)
    {
        if (ActionName == TEXT("Attack"))
        {
            // Use plugin's optimized functions
            NetworkReplicationComponent->ReplicateAnimation(AttackAnimation);
            NetworkReplicationComponent->ReplicateSound(AttackSound);
            NetworkReplicationComponent->ReplicateNiagaraEffect(AttackEffect, GetActorLocation(), GetActorRotation());
        }
    }

    // Use custom RPCs for logic (optimized)
    if (GameRPCs && bUseCustomRPCsForLogic)
    {
        // Use custom RPCs for game logic
        GameRPCs->SendActionLogic(ActionName, ActionData);
    }
}
```

---

## **Best Practices for RPC Performance**

### **1. Choose the Right RPC Type**
```cpp
// Use reliable for critical data
UFUNCTION(Server, Reliable, Category = "Critical RPCs")
void ServerUpdatePlayerHealth(float NewHealth);

// Use unreliable for frequent updates
UFUNCTION(Server, Unreliable, Category = "Frequent RPCs")
void ServerUpdatePlayerPosition(FVector NewPosition);
```

### **2. Implement Rate Limiting**
```cpp
// Rate limit frequent updates
if (CurrentTime - LastUpdate < UpdateRate)
{
    return;
}
```

### **3. Use Data Compression**
```cpp
// Compress large data structures
FCompressedData CompressedData = CompressData(LargeData);
ServerSendCompressedData(CompressedData);
```

### **4. Monitor Performance**
```cpp
// Monitor network conditions
if (NetworkLatency > Threshold)
{
    AdjustUpdateRates();
}
```

### **5. Batch Updates**
```cpp
// Batch multiple updates together
FBatchUpdateData BatchData;
BatchData.AddUpdate(Update1);
BatchData.AddUpdate(Update2);
ServerProcessBatchUpdates(BatchData);
```

---

## **Troubleshooting Performance Issues**

### **Common Performance Problems**

1. **High Bandwidth Usage:**
   - Implement rate limiting
   - Use data compression
   - Batch updates

2. **High Latency:**
   - Use unreliable RPCs for non-critical data
   - Implement adaptive rate limiting
   - Monitor network conditions

3. **RPC Failures:**
   - Check reliability settings
   - Implement retry mechanisms
   - Monitor success rates

### **Debug Performance**

```cpp
// Add performance debugging
void UMyOptimizedRPCs::UpdatePlayerPosition(const FVector& NewPosition)
{
    if (bDebugPerformance)
    {
        UE_LOG(LogTemp, Log, TEXT("Updating player position: %s"), *NewPosition.ToString());
        UE_LOG(LogTemp, Log, TEXT("Network latency: %.2fms"), NetworkLatency);
        UE_LOG(LogTemp, Log, TEXT("Bandwidth usage: %.2f KB/s"), NetworkBandwidth / 1024.0f);
    }
    
    // ... rest of implementation
}
```

---

## **Next Steps**

- **[Extending Plugin Guide](EXTENDING_PLUGIN.md)** - Advanced plugin customization
- **[Hybrid Approach Guide](HYBRID_APPROACH.md)** - Combining plugin and custom RPCs
- **[Custom RPC Guide](CUSTOM_RPC_GUIDE.md)** - Basic custom RPC setup

---

*This guide provides advanced techniques for optimizing custom RPCs and integrating them with the Network Replication Subsystem plugin. For plugin customization and advanced patterns, see the additional guides.*
