# Hybrid Approach Guide
## Combining Plugin Functions with Custom RPCs

This guide demonstrates advanced patterns for using the Network Replication Subsystem plugin alongside custom RPCs for complex multiplayer scenarios.

---

## **Hybrid Architecture Overview**

### **Plugin Functions Handle:**
- 🎬 Visual effects (animations, particles)
- 🔊 Audio effects (sounds, music)
- 🎭 Actor spawning and destruction
- 📊 Basic variable replication
- 🏃 Motion matching data

### **Custom RPCs Handle:**
- 🎯 Game logic and state management
- 📈 Complex data structures
- 🔄 Custom networking protocols
- 🎮 Player-specific functionality
- ⚡ Performance-critical updates

---

## **Advanced Integration Patterns**

### **Pattern 1: Layered Replication**

```cpp
// MyAdvancedPlayerController.h
UCLASS()
class YOURGAME_API AMyAdvancedPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMyAdvancedPlayerController();

    // Complex game action
    UFUNCTION(BlueprintCallable, Category = "Player Actions")
    void PerformSpecialAttack(const FSpecialAttackData& AttackData);

    // Player state management
    UFUNCTION(BlueprintCallable, Category = "Player State")
    void UpdatePlayerStats(const FPlayerStats& NewStats);

protected:
    // Plugin component for effects
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network Replication")
    class UNetworkReplicationComponent* NetworkReplicationComponent;

    // Custom RPC component for game logic
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom RPCs")
    class UMyGameRPCs* GameRPCs;

    // Specialized RPC component for combat
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat RPCs")
    class UCombatRPCs* CombatRPCs;
};
```

```cpp
// MyAdvancedPlayerController.cpp
void AMyAdvancedPlayerController::PerformSpecialAttack(const FSpecialAttackData& AttackData)
{
    // Layer 1: Visual/Audio Effects (Plugin)
    if (NetworkReplicationComponent)
    {
        // Play attack animation
        NetworkReplicationComponent->ReplicateAnimation(AttackData.AttackAnimation);
        
        // Play attack sound
        NetworkReplicationComponent->ReplicateSound(AttackData.AttackSound);
        
        // Spawn attack effect
        NetworkReplicationComponent->ReplicateNiagaraEffect(
            AttackData.AttackEffect, 
            AttackData.TargetLocation, 
            AttackData.TargetRotation
        );
        
        // Spawn impact effect
        NetworkReplicationComponent->ReplicateNiagaraEffect(
            AttackData.ImpactEffect, 
            AttackData.ImpactLocation, 
            AttackData.ImpactRotation
        );
    }

    // Layer 2: Game Logic (Custom RPCs)
    if (GameRPCs)
    {
        // Update player stats
        GameRPCs->SendPlayerStats(AttackData.PlayerStats);
        
        // Update experience
        GameRPCs->SendExperienceGain(AttackData.ExperienceGained);
    }

    // Layer 3: Combat System (Specialized RPCs)
    if (CombatRPCs)
    {
        // Send damage to target
        CombatRPCs->SendDamageToTarget(AttackData.TargetID, AttackData.DamageAmount);
        
        // Update combat state
        CombatRPCs->SendCombatState(AttackData.CombatState);
        
        // Send attack result
        CombatRPCs->SendAttackResult(AttackData.AttackResult);
    }
}
```

### **Pattern 2: Event-Driven Architecture**

```cpp
// MyEventDrivenPlayer.h
UCLASS()
class YOURGAME_API AMyEventDrivenPlayer : public APawn
{
    GENERATED_BODY()

public:
    AMyEventDrivenPlayer();

    // Event handlers
    UFUNCTION()
    void OnPlayerHealthChanged(float NewHealth, float MaxHealth);

    UFUNCTION()
    void OnPlayerManaChanged(float NewMana, float MaxMana);

    UFUNCTION()
    void OnPlayerLevelUp(int32 NewLevel);

protected:
    // Plugin component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network Replication")
    class UNetworkReplicationComponent* NetworkReplicationComponent;

    // Custom RPC component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom RPCs")
    class UMyGameRPCs* GameRPCs;

    // Player stats
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player Stats")
    float Health = 100.0f;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player Stats")
    float Mana = 100.0f;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player Stats")
    int32 Level = 1;
};
```

```cpp
// MyEventDrivenPlayer.cpp
void AMyEventDrivenPlayer::OnPlayerHealthChanged(float NewHealth, float MaxHealth)
{
    // Plugin: Visual feedback
    if (NetworkReplicationComponent)
    {
        if (NewHealth < Health) // Health decreased
        {
            // Play damage animation
            NetworkReplicationComponent->ReplicateAnimation(DamageAnimation);
            
            // Play damage sound
            NetworkReplicationComponent->ReplicateSound(DamageSound);
            
            // Spawn damage effect
            NetworkReplicationComponent->ReplicateNiagaraEffect(
                DamageEffect, 
                GetActorLocation(), 
                GetActorRotation()
            );
        }
        else if (NewHealth > Health) // Health increased
        {
            // Play heal animation
            NetworkReplicationComponent->ReplicateAnimation(HealAnimation);
            
            // Play heal sound
            NetworkReplicationComponent->ReplicateSound(HealSound);
            
            // Spawn heal effect
            NetworkReplicationComponent->ReplicateNiagaraEffect(
                HealEffect, 
                GetActorLocation(), 
                GetActorRotation()
            );
        }
    }

    // Custom RPC: Game logic
    if (GameRPCs)
    {
        // Send health update to all clients
        GameRPCs->SendPlayerHealth(NewHealth, MaxHealth);
        
        // Update UI
        GameRPCs->SendUIUpdate(TEXT("Health"), FString::Printf(TEXT("%.1f/%.1f"), NewHealth, MaxHealth));
    }
}
```

### **Pattern 3: Conditional Replication**

```cpp
// MyConditionalPlayer.h
UCLASS()
class YOURGAME_API AMyConditionalPlayer : public APawn
{
    GENERATED_BODY()

public:
    AMyConditionalPlayer();

    // Conditional actions
    UFUNCTION(BlueprintCallable, Category = "Player Actions")
    void PerformAction(const FString& ActionName, const FString& ActionData);

    // Team-based actions
    UFUNCTION(BlueprintCallable, Category = "Team Actions")
    void PerformTeamAction(const FString& ActionName, int32 TeamID);

protected:
    // Plugin component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network Replication")
    class UNetworkReplicationComponent* NetworkReplicationComponent;

    // Custom RPC component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom RPCs")
    class UMyGameRPCs* GameRPCs;

    // Player properties
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
    int32 TeamID = 0;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
    bool bIsAlive = true;
};
```

```cpp
// MyConditionalPlayer.cpp
void AMyConditionalPlayer::PerformAction(const FString& ActionName, const FString& ActionData)
{
    // Plugin: Always replicate visual effects
    if (NetworkReplicationComponent)
    {
        if (ActionName == TEXT("Attack"))
        {
            NetworkReplicationComponent->ReplicateAnimation(AttackAnimation);
            NetworkReplicationComponent->ReplicateSound(AttackSound);
        }
        else if (ActionName == TEXT("Defend"))
        {
            NetworkReplicationComponent->ReplicateAnimation(DefendAnimation);
            NetworkReplicationComponent->ReplicateSound(DefendSound);
        }
    }

    // Custom RPC: Conditional game logic
    if (GameRPCs)
    {
        if (ActionName == TEXT("Attack") && bIsAlive)
        {
            // Only send attack logic if player is alive
            GameRPCs->SendAttackAction(ActionData);
        }
        else if (ActionName == TEXT("Defend"))
        {
            // Always send defend logic
            GameRPCs->SendDefendAction(ActionData);
        }
    }
}

void AMyConditionalPlayer::PerformTeamAction(const FString& ActionName, int32 TeamID)
{
    // Plugin: Replicate to all clients
    if (NetworkReplicationComponent)
    {
        NetworkReplicationComponent->ReplicateAnimation(TeamActionAnimation);
        NetworkReplicationComponent->ReplicateSound(TeamActionSound);
    }

    // Custom RPC: Only send to team members
    if (GameRPCs && this->TeamID == TeamID)
    {
        GameRPCs->SendTeamAction(ActionName, TeamID);
    }
}
```

---

## **Blueprint Integration Patterns**

### **Blueprint Event Flow**

```
Event: Player Takes Damage
├── Plugin Functions (Always)
│   ├── Replicate Animation (Damage)
│   ├── Replicate Sound (Damage)
│   └── Replicate Niagara Effect (Damage)
├── Custom RPCs (Conditional)
│   ├── Send Player Health (If Health Changed)
│   ├── Send UI Update (If Health Low)
│   └── Send Death Event (If Health <= 0)
└── Specialized RPCs (If Applicable)
    ├── Send Combat State (If In Combat)
    └── Send Team Update (If Team Member)
```

### **Advanced Blueprint Setup**

```
Event BeginPlay
├── Get Network Replication Component
├── Get My Game RPCs
├── Get Combat RPCs
├── Bind to OnPlayerHealthChanged
├── Bind to OnPlayerManaChanged
├── Bind to OnPlayerLevelUp
└── Initialize Player State

Event OnPlayerHealthChanged
├── Network Replication Component → Replicate Animation (Health Change)
├── Network Replication Component → Replicate Sound (Health Change)
├── Network Replication Component → Replicate Niagara Effect (Health Change)
├── My Game RPCs → Send Player Health (New Health)
├── My Game RPCs → Send UI Update (Health Bar)
└── Combat RPCs → Send Combat State (If In Combat)

Event OnPlayerManaChanged
├── Network Replication Component → Replicate Animation (Mana Change)
├── Network Replication Component → Replicate Sound (Mana Change)
├── Network Replication Component → Replicate Niagara Effect (Mana Change)
├── My Game RPCs → Send Player Mana (New Mana)
└── My Game RPCs → Send UI Update (Mana Bar)

Event OnPlayerLevelUp
├── Network Replication Component → Replicate Animation (Level Up)
├── Network Replication Component → Replicate Sound (Level Up)
├── Network Replication Component → Replicate Niagara Effect (Level Up)
├── My Game RPCs → Send Player Level (New Level)
├── My Game RPCs → Send UI Update (Level Display)
└── Combat RPCs → Send Combat State (Level Up Bonus)
```

---

## **Performance Optimization**

### **Bandwidth Management**

```cpp
// MyOptimizedPlayer.h
UCLASS()
class YOURGAME_API AMyOptimizedPlayer : public APawn
{
    GENERATED_BODY()

public:
    AMyOptimizedPlayer();

    // Optimized update functions
    UFUNCTION(BlueprintCallable, Category = "Player Updates")
    void UpdatePlayerPosition(const FVector& NewPosition);

    UFUNCTION(BlueprintCallable, Category = "Player Updates")
    void UpdatePlayerRotation(const FRotator& NewRotation);

    UFUNCTION(BlueprintCallable, Category = "Player Updates")
    void UpdatePlayerStats(const FPlayerStats& NewStats);

protected:
    // Plugin component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network Replication")
    class UNetworkReplicationComponent* NetworkReplicationComponent;

    // Custom RPC component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom RPCs")
    class UMyGameRPCs* GameRPCs;

    // Performance tracking
    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float LastPositionUpdate = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float LastRotationUpdate = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float LastStatsUpdate = 0.0f;

    // Update rates
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float PositionUpdateRate = 0.1f; // 10 times per second

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float RotationUpdateRate = 0.05f; // 20 times per second

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float StatsUpdateRate = 1.0f; // 1 time per second
};
```

```cpp
// MyOptimizedPlayer.cpp
void AMyOptimizedPlayer::UpdatePlayerPosition(const FVector& NewPosition)
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    
    // Rate limiting for position updates
    if (CurrentTime - LastPositionUpdate < PositionUpdateRate)
    {
        return;
    }

    // Plugin: Use for visual effects only when needed
    if (NetworkReplicationComponent && ShouldReplicatePosition())
    {
        // Only replicate position for important events
        NetworkReplicationComponent->ReplicateVectorVariable(TEXT("Position"), NewPosition);
    }

    // Custom RPC: Use for game logic
    if (GameRPCs)
    {
        GameRPCs->SendPlayerPosition(NewPosition);
    }

    LastPositionUpdate = CurrentTime;
}

void AMyOptimizedPlayer::UpdatePlayerStats(const FPlayerStats& NewStats)
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    
    // Rate limiting for stats updates
    if (CurrentTime - LastStatsUpdate < StatsUpdateRate)
    {
        return;
    }

    // Plugin: Use for UI updates
    if (NetworkReplicationComponent)
    {
        NetworkReplicationComponent->ReplicateStringVariable(TEXT("Stats"), NewStats.ToString());
    }

    // Custom RPC: Use for game logic
    if (GameRPCs)
    {
        GameRPCs->SendPlayerStats(NewStats);
    }

    LastStatsUpdate = CurrentTime;
}
```

---

## **Advanced Blueprint Patterns**

### **Event-Driven Blueprint Setup**

```
Event BeginPlay
├── Get Network Replication Component
├── Get My Game RPCs
├── Get Combat RPCs
├── Bind to OnPlayerHealthChanged
├── Bind to OnPlayerManaChanged
├── Bind to OnPlayerLevelUp
├── Bind to OnCombatStateChanged
└── Initialize Player State

Event OnPlayerHealthChanged
├── Branch: Health < Previous Health
│   ├── Network Replication Component → Replicate Animation (Damage)
│   ├── Network Replication Component → Replicate Sound (Damage)
│   └── Network Replication Component → Replicate Niagara Effect (Damage)
├── Branch: Health > Previous Health
│   ├── Network Replication Component → Replicate Animation (Heal)
│   ├── Network Replication Component → Replicate Sound (Heal)
│   └── Network Replication Component → Replicate Niagara Effect (Heal)
├── My Game RPCs → Send Player Health (New Health)
├── My Game RPCs → Send UI Update (Health Bar)
├── Branch: Health <= 0
│   ├── My Game RPCs → Send Death Event
│   └── Combat RPCs → Send Combat State (Dead)
└── Branch: Health > 0
    └── Combat RPCs → Send Combat State (Alive)
```

### **Conditional Replication Blueprint**

```
Event: Player Performs Action
├── Branch: Action Type == "Attack"
│   ├── Network Replication Component → Replicate Animation (Attack)
│   ├── Network Replication Component → Replicate Sound (Attack)
│   ├── Network Replication Component → Replicate Niagara Effect (Attack)
│   ├── My Game RPCs → Send Attack Action (Action Data)
│   └── Combat RPCs → Send Combat State (Attacking)
├── Branch: Action Type == "Defend"
│   ├── Network Replication Component → Replicate Animation (Defend)
│   ├── Network Replication Component → Replicate Sound (Defend)
│   ├── Network Replication Component → Replicate Niagara Effect (Defend)
│   ├── My Game RPCs → Send Defend Action (Action Data)
│   └── Combat RPCs → Send Combat State (Defending)
└── Branch: Action Type == "Special"
    ├── Network Replication Component → Replicate Animation (Special)
    ├── Network Replication Component → Replicate Sound (Special)
    ├── Network Replication Component → Replicate Niagara Effect (Special)
    ├── My Game RPCs → Send Special Action (Action Data)
    └── Combat RPCs → Send Combat State (Special)
```

---

## **Best Practices for Hybrid Approach**

### **1. Clear Separation of Concerns**
- **Plugin Functions**: Visual/audio effects, basic replication
- **Custom RPCs**: Game logic, state management, complex data

### **2. Performance Optimization**
- Use rate limiting for frequent updates
- Implement conditional replication
- Monitor bandwidth usage

### **3. Event-Driven Architecture**
- Bind to events for automatic updates
- Use delegates for loose coupling
- Implement proper cleanup

### **4. Error Handling**
- Validate parameters before sending
- Implement fallback mechanisms
- Add debug logging

### **5. Testing and Debugging**
- Use network simulation
- Monitor RPC performance
- Test with multiple clients

---

## **Troubleshooting Hybrid Approach**

### **Common Issues**

1. **RPC Conflicts:**
   - Ensure proper component initialization
   - Check for duplicate RPC names
   - Verify authority checking

2. **Performance Problems:**
   - Implement rate limiting
   - Use conditional replication
   - Monitor bandwidth usage

3. **Event Binding Issues:**
   - Check event binding order
   - Verify delegate types
   - Ensure proper cleanup

### **Debug Tips**

```cpp
// Add debug logging
void AMyAdvancedPlayerController::PerformSpecialAttack(const FSpecialAttackData& AttackData)
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Log, TEXT("Performing special attack: %s"), *AttackData.AttackName);
    }
    
    // ... rest of implementation
}
```

---

## **Next Steps**

- **[RPC Performance Guide](RPC_PERFORMANCE.md)** - Advanced optimization techniques
- **[Extending Plugin Guide](EXTENDING_PLUGIN.md)** - Custom plugin extensions
- **[Custom RPC Guide](CUSTOM_RPC_GUIDE.md)** - Basic custom RPC setup

---

*This guide demonstrates advanced patterns for combining the Network Replication Subsystem plugin with custom RPCs. For performance optimization and advanced customization, see the additional guides.*
