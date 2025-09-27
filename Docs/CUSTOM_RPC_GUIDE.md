# Custom RPC Integration Guide
## Extending Network Replication with Custom RPCs

This guide shows how to integrate custom RPCs with the Network Replication Subsystem plugin for game-specific functionality.

---

## **When to Use Custom RPCs**

### **Use Plugin Functions For:**
- ✅ Animation replication (`ReplicateAnimation`)
- ✅ Sound effects (`ReplicateSound`)
- ✅ Actor spawning (`ReplicateActorSpawn`)
- ✅ Basic variable replication (`ReplicateStringVariable`)
- ✅ Niagara effects (`ReplicateNiagaraEffect`)

### **Use Custom RPCs For:**
- 🎯 Game-specific logic (scoring, player states)
- 🎯 Complex data structures
- 🎯 Custom networking protocols
- 🎯 Integration with other systems
- 🎯 Performance-critical code

---

## **Basic Custom RPC Setup**

### **1. Create Your Custom RPC Class**

```cpp
// MyGameRPCs.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Engine.h"
#include "MyGameRPCs.generated.h"

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UMyGameRPCs : public UActorComponent
{
    GENERATED_BODY()

public:
    UMyGameRPCs();

    // Custom RPC Functions
    UFUNCTION(BlueprintCallable, Category = "Custom RPCs")
    void SendPlayerScore(int32 NewScore);

    UFUNCTION(BlueprintCallable, Category = "Custom RPCs")
    void SendInventoryUpdate(const FString& ItemName, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Custom RPCs")
    void SendChatMessage(const FString& Message, const FString& PlayerName);

protected:
    // Server RPCs
    UFUNCTION(Server, Reliable, Category = "Custom RPCs")
    void ServerUpdatePlayerScore(int32 NewScore);

    UFUNCTION(Server, Reliable, Category = "Custom RPCs")
    void ServerUpdateInventory(const FString& ItemName, int32 Quantity);

    UFUNCTION(Server, Reliable, Category = "Custom RPCs")
    void ServerSendChatMessage(const FString& Message, const FString& PlayerName);

    // Multicast RPCs
    UFUNCTION(NetMulticast, Reliable, Category = "Custom RPCs")
    void MulticastUpdatePlayerScore(int32 NewScore, const FString& PlayerName);

    UFUNCTION(NetMulticast, Reliable, Category = "Custom RPCs")
    void MulticastUpdateInventory(const FString& ItemName, int32 Quantity, const FString& PlayerName);

    UFUNCTION(NetMulticast, Reliable, Category = "Custom RPCs")
    void MulticastChatMessage(const FString& Message, const FString& PlayerName);

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Custom RPCs")
    FOnPlayerScoreUpdated OnPlayerScoreUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Custom RPCs")
    FOnInventoryUpdated OnInventoryUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Custom RPCs")
    FOnChatMessageReceived OnChatMessageReceived;
};

// Delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerScoreUpdated, int32, NewScore, FString, PlayerName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInventoryUpdated, FString, ItemName, int32, Quantity, FString, PlayerName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChatMessageReceived, FString, Message, FString, PlayerName);
```

### **2. Implement Your Custom RPCs**

```cpp
// MyGameRPCs.cpp
#include "MyGameRPCs.h"
#include "Net/UnrealNetwork.h"

UMyGameRPCs::UMyGameRPCs()
{
    SetIsReplicatedByDefault(true);
}

void UMyGameRPCs::SendPlayerScore(int32 NewScore)
{
    if (GetOwner()->HasAuthority())
    {
        // Server: Update locally and multicast
        MulticastUpdatePlayerScore(NewScore, GetOwner()->GetName());
    }
    else
    {
        // Client: Send to server
        ServerUpdatePlayerScore(NewScore);
    }
}

void UMyGameRPCs::SendInventoryUpdate(const FString& ItemName, int32 Quantity)
{
    if (GetOwner()->HasAuthority())
    {
        MulticastUpdateInventory(ItemName, Quantity, GetOwner()->GetName());
    }
    else
    {
        ServerUpdateInventory(ItemName, Quantity);
    }
}

void UMyGameRPCs::SendChatMessage(const FString& Message, const FString& PlayerName)
{
    if (GetOwner()->HasAuthority())
    {
        MulticastChatMessage(Message, PlayerName);
    }
    else
    {
        ServerSendChatMessage(Message, PlayerName);
    }
}

// Server RPC Implementations
void UMyGameRPCs::ServerUpdatePlayerScore_Implementation(int32 NewScore)
{
    MulticastUpdatePlayerScore(NewScore, GetOwner()->GetName());
}

void UMyGameRPCs::ServerUpdateInventory_Implementation(const FString& ItemName, int32 Quantity)
{
    MulticastUpdateInventory(ItemName, Quantity, GetOwner()->GetName());
}

void UMyGameRPCs::ServerSendChatMessage_Implementation(const FString& Message, const FString& PlayerName)
{
    MulticastChatMessage(Message, PlayerName);
}

// Multicast RPC Implementations
void UMyGameRPCs::MulticastUpdatePlayerScore_Implementation(int32 NewScore, const FString& PlayerName)
{
    OnPlayerScoreUpdated.Broadcast(NewScore, PlayerName);
}

void UMyGameRPCs::MulticastUpdateInventory_Implementation(const FString& ItemName, int32 Quantity, const FString& PlayerName)
{
    OnInventoryUpdated.Broadcast(ItemName, Quantity, PlayerName);
}

void UMyGameRPCs::MulticastChatMessage_Implementation(const FString& Message, const FString& PlayerName)
{
    OnChatMessageReceived.Broadcast(Message, PlayerName);
}
```

---

## **Integration with Network Replication Plugin**

### **Using Both Systems Together**

```cpp
// MyPlayerController.h
UCLASS()
class YOURGAME_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMyPlayerController();

protected:
    // Plugin component for common replication
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network Replication")
    class UNetworkReplicationComponent* NetworkReplicationComponent;

    // Custom RPC component for game-specific logic
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom RPCs")
    class UMyGameRPCs* GameRPCs;

    // Example: Player takes damage
    UFUNCTION(BlueprintCallable, Category = "Player")
    void TakeDamage(float DamageAmount);

    // Example: Player picks up item
    UFUNCTION(BlueprintCallable, Category = "Player")
    void PickupItem(const FString& ItemName, int32 Quantity);
};
```

```cpp
// MyPlayerController.cpp
#include "MyPlayerController.h"
#include "NetworkReplicationComponent.h"
#include "MyGameRPCs.h"

AMyPlayerController::AMyPlayerController()
{
    // Initialize plugin component
    NetworkReplicationComponent = CreateDefaultSubobject<UNetworkReplicationComponent>(TEXT("NetworkReplicationComponent"));
    
    // Initialize custom RPC component
    GameRPCs = CreateDefaultSubobject<UMyGameRPCs>(TEXT("GameRPCs"));
}

void AMyPlayerController::TakeDamage(float DamageAmount)
{
    // Use plugin for visual/audio effects
    if (NetworkReplicationComponent)
    {
        // Play damage animation
        NetworkReplicationComponent->ReplicateAnimation(DamageAnimation);
        
        // Play damage sound
        NetworkReplicationComponent->ReplicateSound(DamageSound);
        
        // Spawn damage effect
        NetworkReplicationComponent->ReplicateNiagaraEffect(DamageEffect, GetActorLocation(), GetActorRotation());
    }

    // Use custom RPC for game logic
    if (GameRPCs)
    {
        // Update player health (game-specific)
        GameRPCs->SendPlayerScore(NewHealthValue);
    }
}

void AMyPlayerController::PickupItem(const FString& ItemName, int32 Quantity)
{
    // Use plugin for pickup effects
    if (NetworkReplicationComponent)
    {
        // Play pickup animation
        NetworkReplicationComponent->ReplicateAnimation(PickupAnimation);
        
        // Play pickup sound
        NetworkReplicationComponent->ReplicateSound(PickupSound);
        
        // Spawn pickup effect
        NetworkReplicationComponent->ReplicateNiagaraEffect(PickupEffect, GetActorLocation(), GetActorRotation());
    }

    // Use custom RPC for inventory logic
    if (GameRPCs)
    {
        // Update inventory (game-specific)
        GameRPCs->SendInventoryUpdate(ItemName, Quantity);
    }
}
```

---

## **Blueprint Integration**

### **Setting Up Custom RPCs in Blueprint**

1. **Add Components:**
   - Add `Network Replication Component` (plugin)
   - Add `My Game RPCs` (custom)

2. **Bind Events:**
   - Bind to `OnPlayerScoreUpdated`
   - Bind to `OnInventoryUpdated`
   - Bind to `OnChatMessageReceived`

3. **Call Functions:**
   - Use plugin functions for effects
   - Use custom RPC functions for game logic

### **Example Blueprint Setup**

```
Event BeginPlay
├── Get Network Replication Component
├── Get My Game RPCs
├── Bind to OnPlayerScoreUpdated
├── Bind to OnInventoryUpdated
└── Bind to OnChatMessageReceived

Event OnPlayerTakesDamage
├── Network Replication Component → Replicate Animation (Damage)
├── Network Replication Component → Replicate Sound (Damage)
├── Network Replication Component → Replicate Niagara Effect (Damage)
└── My Game RPCs → Send Player Score (New Health)

Event OnPlayerPicksUpItem
├── Network Replication Component → Replicate Animation (Pickup)
├── Network Replication Component → Replicate Sound (Pickup)
├── Network Replication Component → Replicate Niagara Effect (Pickup)
└── My Game RPCs → Send Inventory Update (Item, Quantity)
```

---

## **Best Practices**

### **1. Authority Checking**
```cpp
void UMyGameRPCs::SendPlayerScore(int32 NewScore)
{
    // Always check authority
    if (!GetOwner()->HasAuthority())
    {
        // Client: Send to server
        ServerUpdatePlayerScore(NewScore);
    }
    else
    {
        // Server: Multicast to all clients
        MulticastUpdatePlayerScore(NewScore, GetOwner()->GetName());
    }
}
```

### **2. Parameter Validation**
```cpp
void UMyGameRPCs::ServerUpdatePlayerScore_Implementation(int32 NewScore)
{
    // Validate parameters
    if (NewScore < 0 || NewScore > 999999)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid score value: %d"), NewScore);
        return;
    }
    
    MulticastUpdatePlayerScore(NewScore, GetOwner()->GetName());
}
```

### **3. Performance Considerations**
```cpp
// Use reliable RPCs for important data
UFUNCTION(Server, Reliable, Category = "Custom RPCs")
void ServerUpdatePlayerScore(int32 NewScore);

// Use unreliable RPCs for frequent updates
UFUNCTION(Server, Unreliable, Category = "Custom RPCs")
void ServerUpdatePlayerPosition(FVector NewPosition);
```

---

## **Common Patterns**

### **1. Player State Updates**
```cpp
// Send player state changes
GameRPCs->SendPlayerScore(NewScore);
GameRPCs->SendInventoryUpdate(ItemName, Quantity);
GameRPCs->SendChatMessage(Message, PlayerName);
```

### **2. Game Events**
```cpp
// Combine plugin effects with custom logic
NetworkReplicationComponent->ReplicateAnimation(EventAnimation);
NetworkReplicationComponent->ReplicateSound(EventSound);
GameRPCs->SendGameEvent(EventName, EventData);
```

### **3. Team Communication**
```cpp
// Send team-specific messages
GameRPCs->SendTeamMessage(Message, TeamID);
GameRPCs->SendTeamScore(TeamScore, TeamID);
```

---

## **Troubleshooting**

### **Common Issues**

1. **RPCs not working:**
   - Check `SetIsReplicatedByDefault(true)`
   - Verify authority checking
   - Ensure proper network setup

2. **Performance issues:**
   - Use unreliable RPCs for frequent updates
   - Implement rate limiting
   - Monitor bandwidth usage

3. **Authority problems:**
   - Always check `HasAuthority()`
   - Use proper server/client patterns
   - Validate parameters

### **Debug Tips**

```cpp
// Add debug logging
void UMyGameRPCs::SendPlayerScore(int32 NewScore)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Sending player score: %d"), NewScore);
    }
    
    // ... rest of implementation
}
```

---

## **Next Steps**

- **[Hybrid Approach Guide](HYBRID_APPROACH.md)** - Advanced integration patterns
- **[RPC Performance Guide](RPC_PERFORMANCE.md)** - Optimization techniques
- **[Extending Plugin Guide](EXTENDING_PLUGIN.md)** - Advanced customization

---

*This guide provides the foundation for integrating custom RPCs with the Network Replication Subsystem plugin. For advanced patterns and optimization techniques, see the additional guides.*
