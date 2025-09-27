# Examples and Tutorials
## Network Replication Subsystem Usage Examples

This document provides comprehensive examples and tutorials for using the Network Replication Subsystem plugin in various scenarios.

---

## **Basic Setup Examples**

### **1. Adding the Component to a Blueprint**

**Step 1: Open Your Blueprint**
- Open your character or actor Blueprint
- Navigate to the Components panel

**Step 2: Add Network Replication Component**
- Click "Add Component"
- Search for "Network Replication Component"
- Add it to your Blueprint

**Step 3: Configure Settings**
- Select the component in the Details panel
- Adjust replication settings as needed
- Enable debug logging if needed

---

### **2. Adding the Component in C++**

```cpp
// In your character class header
#include "NetworkReplicationComponent.h"

UCLASS()
class MYGAME_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacter();

protected:
    // Network replication component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network Replication", meta = (AllowPrivateAccess = "true"))
    class UNetworkReplicationComponent* NetworkReplicationComponent;
};

// In your character class implementation
AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    
    // Create network replication component
    NetworkReplicationComponent = CreateDefaultSubobject<UNetworkReplicationComponent>(TEXT("NetworkReplicationComponent"));
}
```

---

## **Animation Replication Examples**

### **Basic Animation Replication**

```cpp
// Replicate an animation montage
void AMyCharacter::PlayJumpAnimation()
{
    if (NetworkReplicationComponent && JumpMontage)
    {
        NetworkReplicationComponent->ReplicateAnimation(JumpMontage, 1.0f, 0.0f);
    }
}

// Stop an animation montage
void AMyCharacter::StopJumpAnimation()
{
    if (NetworkReplicationComponent && JumpMontage)
    {
        NetworkReplicationComponent->ReplicateAnimationStop(JumpMontage);
    }
}
```

### **Blueprint Animation Replication**

**In Blueprint:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Animation**: Use "Replicate Animation" function
3. **Set Parameters**: Configure montage, play rate, and start time
4. **Connect to Event**: Connect to appropriate events (Input, Timeline, etc.)

---

## **Sound Replication Examples**

### **Basic Sound Replication**

```cpp
// Replicate a sound effect
void AMyCharacter::PlayFootstepSound()
{
    if (NetworkReplicationComponent && FootstepSound)
    {
        NetworkReplicationComponent->ReplicateSound(FootstepSound, 1.0f, 1.0f, 0.0f);
    }
}

// Replicate a sound at a specific location
void AMyCharacter::PlayExplosionSound(FVector ExplosionLocation)
{
    if (NetworkReplicationComponent && ExplosionSound)
    {
        NetworkReplicationComponent->ReplicateSoundAtLocation(
            ExplosionSound, 
            ExplosionLocation, 
            1.0f, 
            1.0f
        );
    }
}
```

### **Blueprint Sound Replication**

**In Blueprint:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Sound**: Use "Replicate Sound" or "Replicate Sound At Location" function
3. **Set Parameters**: Configure sound, volume, pitch, and location
4. **Connect to Events**: Connect to appropriate sound events

---

## **Motion Matching Examples**

### **Motion Matching Database Replication**

```cpp
// Replicate motion matching database
void AMyCharacter::UpdateMotionMatching()
{
    if (NetworkReplicationComponent && MotionMatchingDatabase)
    {
        NetworkReplicationComponent->ReplicateMotionMatchingDatabase(MotionMatchingDatabase);
    }
}

// Replicate pose search schema
void AMyCharacter::UpdatePoseSearch()
{
    if (NetworkReplicationComponent && PoseSearchSchema)
    {
        NetworkReplicationComponent->ReplicatePoseSearchSchema(PoseSearchSchema);
    }
}

// Replicate trajectory data
void AMyCharacter::UpdateTrajectory()
{
    if (NetworkReplicationComponent)
    {
        NetworkReplicationComponent->ReplicateTrajectoryData(
            GetActorLocation(), 
            GetActorRotation()
        );
    }
}
```

### **Motion Matching Event Handling**

```cpp
// In BeginPlay
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (NetworkReplicationComponent)
    {
        // Bind to motion matching events
        NetworkReplicationComponent->OnMotionMatchingReplicated.AddDynamic(
            this, 
            &AMyCharacter::OnMotionMatchingReceived
        );
        
        NetworkReplicationComponent->OnTrajectoryReplicated.AddDynamic(
            this, 
            &AMyCharacter::OnTrajectoryReceived
        );
        
        NetworkReplicationComponent->OnPoseSearchReplicated.AddDynamic(
            this, 
            &AMyCharacter::OnPoseSearchReceived
        );
    }
}

// Event handlers
void AMyCharacter::OnMotionMatchingReceived(UObject* Database)
{
    UE_LOG(LogTemp, Log, TEXT("Motion Matching Database Received: %s"), *Database->GetName());
}

void AMyCharacter::OnTrajectoryReceived(FVector Position, FRotator Rotation)
{
    UE_LOG(LogTemp, Log, TEXT("Trajectory Received: %s, %s"), *Position.ToString(), *Rotation.ToString());
}

void AMyCharacter::OnPoseSearchReceived(UObject* Schema)
{
    UE_LOG(LogTemp, Log, TEXT("Pose Search Schema Received: %s"), *Schema->GetName());
}
```

---

## **Niagara Effects Examples**

### **Basic Niagara Effect Replication**

```cpp
// Replicate a Niagara effect
void AMyCharacter::PlayExplosionEffect(FVector ExplosionLocation)
{
    if (NetworkReplicationComponent && ExplosionEffect)
    {
        UNiagaraComponent* EffectComponent = NetworkReplicationComponent->ReplicateNiagaraEffect(
            ExplosionEffect, 
            ExplosionLocation, 
            FRotator::ZeroRotator
        );
        
        if (EffectComponent)
        {
            // Configure the effect component if needed
            EffectComponent->SetAutoDestroy(true);
        }
    }
}
```

### **Blueprint Niagara Effect Replication**

**In Blueprint:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Niagara Effect**: Use "Replicate Niagara Effect" function
3. **Set Parameters**: Configure system, location, and rotation
4. **Handle Return Value**: Use the returned Niagara Component for additional configuration

---

## **Variable Replication Examples**

### **Basic Variable Replication**

```cpp
// Replicate a string variable
void AMyCharacter::UpdatePlayerName(const FString& NewName)
{
    if (NetworkReplicationComponent)
    {
        NetworkReplicationComponent->ReplicateStringVariable(TEXT("PlayerName"), NewName);
    }
}

// Replicate a float variable
void AMyCharacter::UpdateHealth(float NewHealth)
{
    if (NetworkReplicationComponent)
    {
        NetworkReplicationComponent->ReplicateFloatVariable(TEXT("Health"), NewHealth);
    }
}

// Replicate a vector variable
void AMyCharacter::UpdateVelocity(FVector NewVelocity)
{
    if (NetworkReplicationComponent)
    {
        NetworkReplicationComponent->ReplicateVectorVariable(TEXT("Velocity"), NewVelocity);
    }
}
```

### **Variable Replication Event Handling**

```cpp
// In BeginPlay
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (NetworkReplicationComponent)
    {
        // Bind to variable replication events
        NetworkReplicationComponent->OnVariableReplicated.AddDynamic(
            this, 
            &AMyCharacter::OnVariableReceived
        );
    }
}

// Event handler
void AMyCharacter::OnVariableReceived(FName VariableName, FString VariableValue)
{
    if (VariableName == TEXT("PlayerName"))
    {
        // Handle player name update
        UE_LOG(LogTemp, Log, TEXT("Player Name Updated: %s"), *VariableValue);
    }
    else if (VariableName == TEXT("Health"))
    {
        // Handle health update
        float Health = FCString::Atof(*VariableValue);
        UE_LOG(LogTemp, Log, TEXT("Health Updated: %f"), Health);
    }
}
```

---

## **Custom Event Examples**

### **Basic Custom Event Replication**

```cpp
// Replicate a custom event
void AMyCharacter::TriggerSpecialEvent()
{
    if (NetworkReplicationComponent)
    {
        NetworkReplicationComponent->ReplicateCustomEvent(
            TEXT("SpecialEvent"), 
            TEXT("EventData")
        );
    }
}

// Replicate a custom event with data
void AMyCharacter::TriggerPlayerEvent(const FString& EventData)
{
    if (NetworkReplicationComponent)
    {
        NetworkReplicationComponent->ReplicateCustomEvent(
            TEXT("PlayerEvent"), 
            EventData
        );
    }
}
```

### **Custom Event Handling**

```cpp
// In BeginPlay
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (NetworkReplicationComponent)
    {
        // Bind to custom event replication
        NetworkReplicationComponent->OnCustomEventReplicated.AddDynamic(
            this, 
            &AMyCharacter::OnCustomEventReceived
        );
    }
}

// Event handler
void AMyCharacter::OnCustomEventReceived(FName EventName, FString EventData)
{
    if (EventName == TEXT("SpecialEvent"))
    {
        // Handle special event
        UE_LOG(LogTemp, Log, TEXT("Special Event Received: %s"), *EventData);
    }
    else if (EventName == TEXT("PlayerEvent"))
    {
        // Handle player event
        UE_LOG(LogTemp, Log, TEXT("Player Event Received: %s"), *EventData);
    }
}
```

---

## **Performance Optimization Examples**

### **Relevancy Configuration**

```cpp
// Configure relevancy settings
void AMyCharacter::ConfigureReplication()
{
    if (NetworkReplicationComponent)
    {
        // Set replication distance
        NetworkReplicationComponent->SetReplicationDistance(5000.0f);
        
        // Enable relevancy checking
        NetworkReplicationComponent->EnableRelevancyCulling(true);
    }
}
```

### **Performance Monitoring**

```cpp
// Monitor replication performance
void AMyCharacter::CheckPerformance()
{
    if (NetworkReplicationComponent)
    {
        // Get replication statistics
        FString Stats = NetworkReplicationComponent->GetReplicationStats();
        UE_LOG(LogTemp, Log, TEXT("Replication Stats: %s"), *Stats);
        
        // Enable debug logging
        NetworkReplicationComponent->EnableDebugLogging(true);
    }
}
```

---

## **Game Animation Sample Integration Examples**

### **Complete Motion Matching Setup**

```cpp
// Complete motion matching character setup
UCLASS()
class GAMEANIMATIONSAMPLE_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Motion matching functions
    UFUNCTION(BlueprintCallable, Category = "Motion Matching")
    void UpdateMotionMatching();

    // Event handlers
    UFUNCTION()
    void OnMotionMatchingReceived(UObject* Database);
    
    UFUNCTION()
    void OnTrajectoryReceived(FVector Position, FRotator Rotation);

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network Replication", meta = (AllowPrivateAccess = "true"))
    class UNetworkReplicationComponent* NetworkReplicationComponent;

    // Motion matching data
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Matching", meta = (AllowPrivateAccess = "true"))
    class UObject* MotionMatchingDatabase;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Matching", meta = (AllowPrivateAccess = "true"))
    class UObject* PoseSearchSchema;
};

// Implementation
AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    
    // Create network replication component
    NetworkReplicationComponent = CreateDefaultSubobject<UNetworkReplicationComponent>(TEXT("NetworkReplicationComponent"));
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (NetworkReplicationComponent)
    {
        // Bind to motion matching events
        NetworkReplicationComponent->OnMotionMatchingReplicated.AddDynamic(this, &AMyCharacter::OnMotionMatchingReceived);
        NetworkReplicationComponent->OnTrajectoryReplicated.AddDynamic(this, &AMyCharacter::OnTrajectoryReceived);
    }
}

void AMyCharacter::UpdateMotionMatching()
{
    if (NetworkReplicationComponent)
    {
        // Replicate motion matching database
        if (MotionMatchingDatabase)
        {
            NetworkReplicationComponent->ReplicateMotionMatchingDatabase(MotionMatchingDatabase);
        }
        
        // Replicate pose search schema
        if (PoseSearchSchema)
        {
            NetworkReplicationComponent->ReplicatePoseSearchSchema(PoseSearchSchema);
        }
        
        // Replicate trajectory data
        NetworkReplicationComponent->ReplicateTrajectoryData(GetActorLocation(), GetActorRotation());
    }
}
```

---

## **Blueprint Examples**

### **Complete Blueprint Setup**

**Step 1: Add Component**
- Add "Network Replication Component" to your Blueprint

**Step 2: Configure Events**
- Bind to "On Animation Replicated" event
- Bind to "On Sound Replicated" event
- Bind to "On Motion Matching Replicated" event

**Step 3: Call Functions**
- Use "Replicate Animation" function
- Use "Replicate Sound" function
- Use "Replicate Motion Matching Database" function

**Step 4: Handle Events**
- Create event handlers for received data
- Process replicated data appropriately

---

## **Troubleshooting Examples**

### **Common Issues and Solutions**

**Issue: Replication Not Working**
```cpp
// Check if component is valid
if (NetworkReplicationComponent)
{
    // Check if owner has authority
    if (GetOwner()->HasAuthority())
    {
        // Server-side replication
        NetworkReplicationComponent->ReplicateAnimation(MyMontage, 1.0f, 0.0f);
    }
    else
    {
        // Client-side request to server
        NetworkReplicationComponent->ReplicateAnimation(MyMontage, 1.0f, 0.0f);
    }
}
```

**Issue: Performance Problems**
```cpp
// Enable performance monitoring
if (NetworkReplicationComponent)
{
    NetworkReplicationComponent->EnableDebugLogging(true);
    
    // Get performance statistics
    FString Stats = NetworkReplicationComponent->GetReplicationStats();
    UE_LOG(LogTemp, Log, TEXT("Performance Stats: %s"), *Stats);
}
```

---

## **Best Practices Examples**

### **Efficient Replication Pattern**

```cpp
// Efficient replication with validation
void AMyCharacter::ReplicatePlayerAction(const FString& ActionName, const FString& ActionData)
{
    // Validate input
    if (ActionName.IsEmpty() || !NetworkReplicationComponent)
    {
        return;
    }
    
    // Check network authority
    if (GetOwner()->HasAuthority())
    {
        // Server: Replicate immediately
        NetworkReplicationComponent->ReplicateCustomEvent(*ActionName, ActionData);
    }
    else
    {
        // Client: Request server replication
        NetworkReplicationComponent->ReplicateCustomEvent(*ActionName, ActionData);
    }
}
```

### **Performance Optimization Pattern**

```cpp
// Performance-optimized replication
void AMyCharacter::OptimizeReplication()
{
    if (NetworkReplicationComponent)
    {
        // Set appropriate replication distance
        NetworkReplicationComponent->SetReplicationDistance(5000.0f);
        
        // Enable relevancy checking
        NetworkReplicationComponent->EnableRelevancyCulling(true);
        
        // Set appropriate replication frequency
        NetworkReplicationComponent->SetReplicationFrequency(30.0f);
    }
}
```

---

**For additional examples and support, visit our [GitHub Repository](https://github.com/millsydotdev/NetworkReplication-UE5) or join our [Discord Community](https://discord.gg/uyJ636Y4u8).**
