# Extending Plugin Guide
## Advanced Customization of the Network Replication Subsystem

This guide demonstrates how to extend the Network Replication Subsystem plugin with custom functionality, advanced integration patterns, and specialized networking features.

---

## **Plugin Extension Architecture**

### **Extension Levels**

1. **Component Extension** - Extend existing components
2. **Subsystem Extension** - Add custom subsystem functionality
3. **Custom Integration** - Create specialized networking systems
4. **Advanced Patterns** - Implement complex networking scenarios

---

## **Component Extension Patterns**

### **Extending NetworkReplicationComponent**

```cpp
// MyExtendedNetworkReplicationComponent.h
#pragma once

#include "CoreMinimal.h"
#include "NetworkReplicationComponent.h"
#include "MyExtendedNetworkReplicationComponent.generated.h"

/**
 * Extended Network Replication Component with custom functionality
 * Inherits all plugin functionality and adds custom features
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UMyExtendedNetworkReplicationComponent : public UNetworkReplicationComponent
{
    GENERATED_BODY()

public:
    UMyExtendedNetworkReplicationComponent();

    // Custom replication functions
    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Custom")
    void ReplicateCustomGameEvent(const FString& EventName, const FString& EventData);

    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Custom")
    void ReplicatePlayerState(const FPlayerState& PlayerState);

    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Custom")
    void ReplicateInventoryUpdate(const FInventoryData& InventoryData);

    // Advanced motion matching functions
    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Motion Matching")
    void ReplicateAdvancedTrajectory(const FAdvancedTrajectoryData& TrajectoryData);

    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Motion Matching")
    void ReplicatePoseSearchResult(const FPoseSearchResult& SearchResult);

    // Performance monitoring
    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Performance")
    void EnableAdvancedPerformanceMonitoring(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Performance")
    FString GetAdvancedPerformanceReport() const;

protected:
    // Custom RPCs
    UFUNCTION(Server, Reliable, Category = "Extended Network Replication|RPC")
    void ServerReplicateCustomGameEvent(const FString& EventName, const FString& EventData);

    UFUNCTION(Server, Reliable, Category = "Extended Network Replication|RPC")
    void ServerReplicatePlayerState(const FPlayerState& PlayerState);

    UFUNCTION(Server, Reliable, Category = "Extended Network Replication|RPC")
    void ServerReplicateInventoryUpdate(const FInventoryData& InventoryData);

    UFUNCTION(NetMulticast, Reliable, Category = "Extended Network Replication|RPC")
    void MulticastReplicateCustomGameEvent(const FString& EventName, const FString& EventData);

    UFUNCTION(NetMulticast, Reliable, Category = "Extended Network Replication|RPC")
    void MulticastReplicatePlayerState(const FPlayerState& PlayerState);

    UFUNCTION(NetMulticast, Reliable, Category = "Extended Network Replication|RPC")
    void MulticastReplicateInventoryUpdate(const FInventoryData& InventoryData);

    // Custom events
    UPROPERTY(BlueprintAssignable, Category = "Extended Network Replication|Events")
    FOnCustomGameEventReplicated OnCustomGameEventReplicated;

    UPROPERTY(BlueprintAssignable, Category = "Extended Network Replication|Events")
    FOnPlayerStateReplicated OnPlayerStateReplicated;

    UPROPERTY(BlueprintAssignable, Category = "Extended Network Replication|Events")
    FOnInventoryUpdated OnInventoryUpdated;

    // Performance monitoring
    UPROPERTY(BlueprintReadOnly, Category = "Extended Network Replication|Performance")
    bool bAdvancedPerformanceMonitoring = false;

    UPROPERTY(BlueprintReadOnly, Category = "Extended Network Replication|Performance")
    float CustomRPCBandwidth = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Extended Network Replication|Performance")
    int32 CustomRPCCount = 0;
};

// Custom data structures
USTRUCT(BlueprintType)
struct FPlayerState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    int32 Health = 100;

    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    int32 Mana = 100;

    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    int32 Level = 1;

    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    FString PlayerName = TEXT("Unknown");
};

USTRUCT(BlueprintType)
struct FInventoryData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    TArray<FString> Items;

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    TArray<int32> Quantities;

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    int32 MaxSlots = 20;
};

USTRUCT(BlueprintType)
struct FAdvancedTrajectoryData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Trajectory")
    TArray<FVector> Positions;

    UPROPERTY(BlueprintReadOnly, Category = "Trajectory")
    TArray<FRotator> Rotations;

    UPROPERTY(BlueprintReadOnly, Category = "Trajectory")
    TArray<float> Timestamps;

    UPROPERTY(BlueprintReadOnly, Category = "Trajectory")
    float Duration = 0.0f;
};

USTRUCT(BlueprintType)
struct FPoseSearchResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Pose Search")
    int32 BestPoseIndex = -1;

    UPROPERTY(BlueprintReadOnly, Category = "Pose Search")
    float SimilarityScore = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Pose Search")
    FString PoseName = TEXT("Unknown");
};

// Custom delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCustomGameEventReplicated, FString, EventName, FString, EventData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateReplicated, FPlayerState, PlayerState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, FInventoryData, InventoryData);
```

```cpp
// MyExtendedNetworkReplicationComponent.cpp
#include "MyExtendedNetworkReplicationComponent.h"
#include "Net/UnrealNetwork.h"

UMyExtendedNetworkReplicationComponent::UMyExtendedNetworkReplicationComponent()
{
    // Initialize extended functionality
    bAdvancedPerformanceMonitoring = false;
    CustomRPCBandwidth = 0.0f;
    CustomRPCCount = 0;
}

void UMyExtendedNetworkReplicationComponent::ReplicateCustomGameEvent(const FString& EventName, const FString& EventData)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Replicating custom game event: %s with data: %s"), *EventName, *EventData);
    }

    if (GetOwner()->HasAuthority())
    {
        MulticastReplicateCustomGameEvent(EventName, EventData);
    }
    else
    {
        ServerReplicateCustomGameEvent(EventName, EventData);
    }

    // Update performance metrics
    CustomRPCCount++;
    TotalReplications++;
    LastReplicationTime = GetWorld()->GetTimeSeconds();
}

void UMyExtendedNetworkReplicationComponent::ReplicatePlayerState(const FPlayerState& PlayerState)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Replicating player state: Health=%d, Mana=%d, Level=%d"), 
            PlayerState.Health, PlayerState.Mana, PlayerState.Level);
    }

    if (GetOwner()->HasAuthority())
    {
        MulticastReplicatePlayerState(PlayerState);
    }
    else
    {
        ServerReplicatePlayerState(PlayerState);
    }

    CustomRPCCount++;
    TotalReplications++;
    LastReplicationTime = GetWorld()->GetTimeSeconds();
}

void UMyExtendedNetworkReplicationComponent::ReplicateInventoryUpdate(const FInventoryData& InventoryData)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Replicating inventory update: %d items"), InventoryData.Items.Num());
    }

    if (GetOwner()->HasAuthority())
    {
        MulticastReplicateInventoryUpdate(InventoryData);
    }
    else
    {
        ServerReplicateInventoryUpdate(InventoryData);
    }

    CustomRPCCount++;
    TotalReplications++;
    LastReplicationTime = GetWorld()->GetTimeSeconds();
}

// Server RPC implementations
void UMyExtendedNetworkReplicationComponent::ServerReplicateCustomGameEvent_Implementation(const FString& EventName, const FString& EventData)
{
    MulticastReplicateCustomGameEvent(EventName, EventData);
}

void UMyExtendedNetworkReplicationComponent::ServerReplicatePlayerState_Implementation(const FPlayerState& PlayerState)
{
    MulticastReplicatePlayerState(PlayerState);
}

void UMyExtendedNetworkReplicationComponent::ServerReplicateInventoryUpdate_Implementation(const FInventoryData& InventoryData)
{
    MulticastReplicateInventoryUpdate(InventoryData);
}

// Multicast RPC implementations
void UMyExtendedNetworkReplicationComponent::MulticastReplicateCustomGameEvent_Implementation(const FString& EventName, const FString& EventData)
{
    OnCustomGameEventReplicated.Broadcast(EventName, EventData);
    
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Custom game event replicated: %s with data: %s"), *EventName, *EventData);
    }
}

void UMyExtendedNetworkReplicationComponent::MulticastReplicatePlayerState_Implementation(const FPlayerState& PlayerState)
{
    OnPlayerStateReplicated.Broadcast(PlayerState);
    
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Player state replicated: Health=%d, Mana=%d, Level=%d"), 
            PlayerState.Health, PlayerState.Mana, PlayerState.Level);
    }
}

void UMyExtendedNetworkReplicationComponent::MulticastReplicateInventoryUpdate_Implementation(const FInventoryData& InventoryData)
{
    OnInventoryUpdated.Broadcast(InventoryData);
    
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Inventory updated: %d items"), InventoryData.Items.Num());
    }
}

// Performance monitoring
void UMyExtendedNetworkReplicationComponent::EnableAdvancedPerformanceMonitoring(bool bEnabled)
{
    bAdvancedPerformanceMonitoring = bEnabled;
    
    if (bEnabled)
    {
        UE_LOG(LogTemp, Log, TEXT("Advanced performance monitoring enabled"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Advanced performance monitoring disabled"));
    }
}

FString UMyExtendedNetworkReplicationComponent::GetAdvancedPerformanceReport() const
{
    return FString::Printf(TEXT("Advanced Performance Report:\nTotal Replications: %d\nCustom RPCs: %d\nCustom RPC Bandwidth: %.2f KB/s\nPlugin Functions: %d\nLast Replication: %.2f"),
        TotalReplications, CustomRPCCount, CustomRPCBandwidth, TotalReplications - CustomRPCCount, LastReplicationTime);
}
```

---

## **Subsystem Extension Patterns**

### **Extending NetworkReplicationSubsystem**

```cpp
// MyExtendedNetworkReplicationSubsystem.h
#pragma once

#include "CoreMinimal.h"
#include "NetworkReplicationSubsystem.h"
#include "MyExtendedNetworkReplicationSubsystem.generated.h"

/**
 * Extended Network Replication Subsystem with custom functionality
 * Inherits all plugin functionality and adds custom features
 */
UCLASS(BlueprintType, Blueprintable)
class YOURGAME_API UMyExtendedNetworkReplicationSubsystem : public UNetworkReplicationSubsystem
{
    GENERATED_BODY()

public:
    UMyExtendedNetworkReplicationSubsystem();

    // Custom subsystem functions
    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Subsystem")
    void RegisterCustomReplicationComponent(class UMyExtendedNetworkReplicationComponent* Component);

    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Subsystem")
    void UnregisterCustomReplicationComponent(class UMyExtendedNetworkReplicationComponent* Component);

    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Subsystem")
    void BroadcastCustomGameEvent(const FString& EventName, const FString& EventData);

    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Subsystem")
    void BroadcastPlayerStateUpdate(const FPlayerState& PlayerState);

    // Advanced performance monitoring
    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Performance")
    void EnableAdvancedPerformanceMonitoring(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Extended Network Replication|Performance")
    FString GetAdvancedPerformanceReport() const;

    // Custom events
    UPROPERTY(BlueprintAssignable, Category = "Extended Network Replication|Events")
    FOnCustomGameEventBroadcast OnCustomGameEventBroadcast;

    UPROPERTY(BlueprintAssignable, Category = "Extended Network Replication|Events")
    FOnPlayerStateBroadcast OnPlayerStateBroadcast;

protected:
    // Custom component management
    UPROPERTY(BlueprintReadOnly, Category = "Extended Network Replication|Components")
    TArray<class UMyExtendedNetworkReplicationComponent*> CustomReplicationComponents;

    // Performance monitoring
    UPROPERTY(BlueprintReadOnly, Category = "Extended Network Replication|Performance")
    bool bAdvancedPerformanceMonitoring = false;

    UPROPERTY(BlueprintReadOnly, Category = "Extended Network Replication|Performance")
    float CustomRPCBandwidth = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Extended Network Replication|Performance")
    int32 CustomRPCCount = 0;

    // Custom RPCs
    UFUNCTION(NetMulticast, Reliable, Category = "Extended Network Replication|RPC")
    void MulticastBroadcastCustomGameEvent(const FString& EventName, const FString& EventData);

    UFUNCTION(NetMulticast, Reliable, Category = "Extended Network Replication|RPC")
    void MulticastBroadcastPlayerStateUpdate(const FPlayerState& PlayerState);
};

// Custom delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCustomGameEventBroadcast, FString, EventName, FString, EventData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateBroadcast, FPlayerState, PlayerState);
```

```cpp
// MyExtendedNetworkReplicationSubsystem.cpp
#include "MyExtendedNetworkReplicationSubsystem.h"
#include "MyExtendedNetworkReplicationComponent.h"

UMyExtendedNetworkReplicationSubsystem::UMyExtendedNetworkReplicationSubsystem()
{
    // Initialize extended functionality
    bAdvancedPerformanceMonitoring = false;
    CustomRPCBandwidth = 0.0f;
    CustomRPCCount = 0;
}

void UMyExtendedNetworkReplicationSubsystem::RegisterCustomReplicationComponent(UMyExtendedNetworkReplicationComponent* Component)
{
    if (Component && !CustomReplicationComponents.Contains(Component))
    {
        CustomReplicationComponents.Add(Component);
        
        UE_LOG(LogTemp, Log, TEXT("Custom replication component registered: %s"), *Component->GetName());
    }
}

void UMyExtendedNetworkReplicationSubsystem::UnregisterCustomReplicationComponent(UMyExtendedNetworkReplicationComponent* Component)
{
    if (Component && CustomReplicationComponents.Contains(Component))
    {
        CustomReplicationComponents.Remove(Component);
        
        UE_LOG(LogTemp, Log, TEXT("Custom replication component unregistered: %s"), *Component->GetName());
    }
}

void UMyExtendedNetworkReplicationSubsystem::BroadcastCustomGameEvent(const FString& EventName, const FString& EventData)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Broadcasting custom game event: %s with data: %s"), *EventName, *EventData);
    }

    // Broadcast to all custom components
    for (UMyExtendedNetworkReplicationComponent* Component : CustomReplicationComponents)
    {
        if (Component)
        {
            Component->ReplicateCustomGameEvent(EventName, EventData);
        }
    }

    // Broadcast to all clients
    MulticastBroadcastCustomGameEvent(EventName, EventData);

    // Update performance metrics
    CustomRPCCount++;
}

void UMyExtendedNetworkReplicationSubsystem::BroadcastPlayerStateUpdate(const FPlayerState& PlayerState)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Broadcasting player state update: Health=%d, Mana=%d, Level=%d"), 
            PlayerState.Health, PlayerState.Mana, PlayerState.Level);
    }

    // Broadcast to all custom components
    for (UMyExtendedNetworkReplicationComponent* Component : CustomReplicationComponents)
    {
        if (Component)
        {
            Component->ReplicatePlayerState(PlayerState);
        }
    }

    // Broadcast to all clients
    MulticastBroadcastPlayerStateUpdate(PlayerState);

    CustomRPCCount++;
}

// Multicast RPC implementations
void UMyExtendedNetworkReplicationSubsystem::MulticastBroadcastCustomGameEvent_Implementation(const FString& EventName, const FString& EventData)
{
    OnCustomGameEventBroadcast.Broadcast(EventName, EventData);
    
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Custom game event broadcasted: %s with data: %s"), *EventName, *EventData);
    }
}

void UMyExtendedNetworkReplicationSubsystem::MulticastBroadcastPlayerStateUpdate_Implementation(const FPlayerState& PlayerState)
{
    OnPlayerStateBroadcast.Broadcast(PlayerState);
    
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Player state broadcasted: Health=%d, Mana=%d, Level=%d"), 
            PlayerState.Health, PlayerState.Mana, PlayerState.Level);
    }
}

// Performance monitoring
void UMyExtendedNetworkReplicationSubsystem::EnableAdvancedPerformanceMonitoring(bool bEnabled)
{
    bAdvancedPerformanceMonitoring = bEnabled;
    
    if (bEnabled)
    {
        UE_LOG(LogTemp, Log, TEXT("Advanced performance monitoring enabled for subsystem"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Advanced performance monitoring disabled for subsystem"));
    }
}

FString UMyExtendedNetworkReplicationSubsystem::GetAdvancedPerformanceReport() const
{
    return FString::Printf(TEXT("Extended Subsystem Performance Report:\nCustom Components: %d\nCustom RPCs: %d\nCustom RPC Bandwidth: %.2f KB/s\nPlugin Functions: %d"),
        CustomReplicationComponents.Num(), CustomRPCCount, CustomRPCBandwidth, GetActiveReplicationCount() - CustomRPCCount);
}
```

---

## **Advanced Integration Patterns**

### **Custom Networking System**

```cpp
// MyCustomNetworkingSystem.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyCustomNetworkingSystem.generated.h"

/**
 * Custom networking system that extends plugin functionality
 * Provides specialized networking features for specific game mechanics
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UMyCustomNetworkingSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UMyCustomNetworkingSystem();

    // Custom networking functions
    UFUNCTION(BlueprintCallable, Category = "Custom Networking")
    void SendCustomMessage(const FString& Message, const FString& Recipient);

    UFUNCTION(BlueprintCallable, Category = "Custom Networking")
    void SendTeamMessage(const FString& Message, int32 TeamID);

    UFUNCTION(BlueprintCallable, Category = "Custom Networking")
    void SendGlobalMessage(const FString& Message);

    // Advanced networking features
    UFUNCTION(BlueprintCallable, Category = "Custom Networking|Advanced")
    void SendEncryptedMessage(const FString& Message, const FString& Key);

    UFUNCTION(BlueprintCallable, Category = "Custom Networking|Advanced")
    void SendCompressedData(const TArray<uint8>& Data);

    UFUNCTION(BlueprintCallable, Category = "Custom Networking|Advanced")
    void SendBatchMessages(const TArray<FString>& Messages);

protected:
    // Plugin component reference
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network Replication")
    class UNetworkReplicationComponent* NetworkReplicationComponent;

    // Custom RPCs
    UFUNCTION(Server, Reliable, Category = "Custom Networking|RPC")
    void ServerSendCustomMessage(const FString& Message, const FString& Recipient);

    UFUNCTION(Server, Reliable, Category = "Custom Networking|RPC")
    void ServerSendTeamMessage(const FString& Message, int32 TeamID);

    UFUNCTION(Server, Reliable, Category = "Custom Networking|RPC")
    void ServerSendGlobalMessage(const FString& Message);

    UFUNCTION(NetMulticast, Reliable, Category = "Custom Networking|RPC")
    void MulticastSendCustomMessage(const FString& Message, const FString& Recipient);

    UFUNCTION(NetMulticast, Reliable, Category = "Custom Networking|RPC")
    void MulticastSendTeamMessage(const FString& Message, int32 TeamID);

    UFUNCTION(NetMulticast, Reliable, Category = "Custom Networking|RPC")
    void MulticastSendGlobalMessage(const FString& Message);

    // Custom events
    UPROPERTY(BlueprintAssignable, Category = "Custom Networking|Events")
    FOnCustomMessageReceived OnCustomMessageReceived;

    UPROPERTY(BlueprintAssignable, Category = "Custom Networking|Events")
    FOnTeamMessageReceived OnTeamMessageReceived;

    UPROPERTY(BlueprintAssignable, Category = "Custom Networking|Events")
    FOnGlobalMessageReceived OnGlobalMessageReceived;
};

// Custom delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCustomMessageReceived, FString, Message, FString, Sender);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTeamMessageReceived, FString, Message, int32, TeamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGlobalMessageReceived, FString, Message);
```

```cpp
// MyCustomNetworkingSystem.cpp
#include "MyCustomNetworkingSystem.h"
#include "NetworkReplicationComponent.h"

UMyCustomNetworkingSystem::UMyCustomNetworkingSystem()
{
    // Initialize custom networking system
    SetIsReplicatedByDefault(true);
}

void UMyCustomNetworkingSystem::BeginPlay()
{
    Super::BeginPlay();
    
    // Get plugin component
    NetworkReplicationComponent = GetOwner()->FindComponentByClass<UNetworkReplicationComponent>();
    
    if (!NetworkReplicationComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("NetworkReplicationComponent not found on %s"), *GetOwner()->GetName());
    }
}

void UMyCustomNetworkingSystem::SendCustomMessage(const FString& Message, const FString& Recipient)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Sending custom message to %s: %s"), *Recipient, *Message);
    }

    if (GetOwner()->HasAuthority())
    {
        MulticastSendCustomMessage(Message, Recipient);
    }
    else
    {
        ServerSendCustomMessage(Message, Recipient);
    }
}

void UMyCustomNetworkingSystem::SendTeamMessage(const FString& Message, int32 TeamID)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Sending team message to team %d: %s"), TeamID, *Message);
    }

    if (GetOwner()->HasAuthority())
    {
        MulticastSendTeamMessage(Message, TeamID);
    }
    else
    {
        ServerSendTeamMessage(Message, TeamID);
    }
}

void UMyCustomNetworkingSystem::SendGlobalMessage(const FString& Message)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Sending global message: %s"), *Message);
    }

    if (GetOwner()->HasAuthority())
    {
        MulticastSendGlobalMessage(Message);
    }
    else
    {
        ServerSendGlobalMessage(Message);
    }
}

// Server RPC implementations
void UMyCustomNetworkingSystem::ServerSendCustomMessage_Implementation(const FString& Message, const FString& Recipient)
{
    MulticastSendCustomMessage(Message, Recipient);
}

void UMyCustomNetworkingSystem::ServerSendTeamMessage_Implementation(const FString& Message, int32 TeamID)
{
    MulticastSendTeamMessage(Message, TeamID);
}

void UMyCustomNetworkingSystem::ServerSendGlobalMessage_Implementation(const FString& Message)
{
    MulticastSendGlobalMessage(Message);
}

// Multicast RPC implementations
void UMyCustomNetworkingSystem::MulticastSendCustomMessage_Implementation(const FString& Message, const FString& Recipient)
{
    OnCustomMessageReceived.Broadcast(Message, Recipient);
    
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Custom message received: %s from %s"), *Message, *Recipient);
    }
}

void UMyCustomNetworkingSystem::MulticastSendTeamMessage_Implementation(const FString& Message, int32 TeamID)
{
    OnTeamMessageReceived.Broadcast(Message, TeamID);
    
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Team message received: %s for team %d"), *Message, TeamID);
    }
}

void UMyCustomNetworkingSystem::MulticastSendGlobalMessage_Implementation(const FString& Message)
{
    OnGlobalMessageReceived.Broadcast(Message);
    
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Global message received: %s"), *Message);
    }
}
```

---

## **Blueprint Integration**

### **Extended Component Setup**

```
Event BeginPlay
├── Get Network Replication Component (Plugin)
├── Get My Extended Network Replication Component (Custom)
├── Get My Custom Networking System (Custom)
├── Bind to OnCustomGameEventReplicated
├── Bind to OnPlayerStateReplicated
├── Bind to OnInventoryUpdated
├── Bind to OnCustomMessageReceived
├── Bind to OnTeamMessageReceived
└── Bind to OnGlobalMessageReceived

Event OnPlayerPerformsAction
├── Network Replication Component → Replicate Animation (Action)
├── Network Replication Component → Replicate Sound (Action)
├── Network Replication Component → Replicate Niagara Effect (Action)
├── My Extended Network Replication Component → Replicate Custom Game Event (Action)
├── My Extended Network Replication Component → Replicate Player State (New State)
├── My Extended Network Replication Component → Replicate Inventory Update (Inventory)
└── My Custom Networking System → Send Custom Message (Action Details)
```

### **Advanced Blueprint Patterns**

```
Event: Player Joins Team
├── Plugin Functions (Visual/Audio)
│   ├── Network Replication Component → Replicate Animation (Join Team)
│   ├── Network Replication Component → Replicate Sound (Join Team)
│   └── Network Replication Component → Replicate Niagara Effect (Join Team)
├── Extended Plugin Functions (Game Logic)
│   ├── My Extended Network Replication Component → Replicate Player State (Team Info)
│   └── My Extended Network Replication Component → Replicate Custom Game Event (Team Join)
└── Custom Networking (Communication)
    ├── My Custom Networking System → Send Team Message (Welcome Message)
    └── My Custom Networking System → Send Global Message (Player Joined Team)
```

---

## **Best Practices for Plugin Extension**

### **1. Inheritance Hierarchy**
```cpp
// Extend plugin components
class UMyExtendedNetworkReplicationComponent : public UNetworkReplicationComponent

// Extend plugin subsystems
class UMyExtendedNetworkReplicationSubsystem : public UNetworkReplicationSubsystem

// Create custom systems
class UMyCustomNetworkingSystem : public UActorComponent
```

### **2. Event Binding**
```cpp
// Bind to plugin events
NetworkReplicationComponent->OnAnimationReplicated.AddDynamic(this, &AMyPlayer::OnAnimationReplicated);

// Bind to custom events
MyExtendedNetworkReplicationComponent->OnCustomGameEventReplicated.AddDynamic(this, &AMyPlayer::OnCustomGameEventReplicated);
```

### **3. Performance Monitoring**
```cpp
// Monitor plugin performance
FString PluginStats = NetworkReplicationComponent->GetReplicationStats();

// Monitor custom performance
FString CustomStats = MyExtendedNetworkReplicationComponent->GetAdvancedPerformanceReport();
```

### **4. Error Handling**
```cpp
// Validate plugin components
if (!NetworkReplicationComponent)
{
    UE_LOG(LogTemp, Error, TEXT("NetworkReplicationComponent not found"));
    return;
}

// Validate custom components
if (!MyExtendedNetworkReplicationComponent)
{
    UE_LOG(LogTemp, Error, TEXT("MyExtendedNetworkReplicationComponent not found"));
    return;
}
```

---

## **Troubleshooting Plugin Extensions**

### **Common Issues**

1. **Component Not Found:**
   - Check component initialization
   - Verify component attachment
   - Ensure proper Blueprint setup

2. **RPC Failures:**
   - Check authority settings
   - Verify RPC parameters
   - Monitor network conditions

3. **Performance Issues:**
   - Monitor bandwidth usage
   - Implement rate limiting
   - Use performance profiling

### **Debug Tips**

```cpp
// Add debug logging
void UMyExtendedNetworkReplicationComponent::ReplicateCustomGameEvent(const FString& EventName, const FString& EventData)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Replicating custom game event: %s with data: %s"), *EventName, *EventData);
        UE_LOG(LogTemp, Log, TEXT("Component: %s, Owner: %s"), *GetName(), *GetOwner()->GetName());
    }
    
    // ... rest of implementation
}
```

---

## **Next Steps**

- **[RPC Performance Guide](RPC_PERFORMANCE.md)** - Advanced optimization techniques
- **[Hybrid Approach Guide](HYBRID_APPROACH.md)** - Combining plugin and custom RPCs
- **[Custom RPC Guide](CUSTOM_RPC_GUIDE.md)** - Basic custom RPC setup

---

*This guide demonstrates advanced techniques for extending the Network Replication Subsystem plugin with custom functionality. For performance optimization and integration patterns, see the additional guides.*
