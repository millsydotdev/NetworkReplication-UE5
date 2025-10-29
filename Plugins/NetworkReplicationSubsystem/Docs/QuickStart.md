# NetworkReplication Plugin - Quick Start Guide

Get up and running with the NetworkReplication plugin in minutes!

## Installation

### 1. Download the Plugin
- Download the `NetworkReplicationSubsystem` plugin
- Place it in your project's `Plugins/` directory

### 2. Enable the Plugin
1. Open your project in Unreal Engine 5.6
2. Go to **Edit > Plugins**
3. Search for "NetworkReplication"
4. Check the **Enabled** checkbox
5. Restart the editor when prompted

### 3. Verify Installation
- The plugin should appear in your project's **Plugins** folder
- You should see `NetworkReplicationComponent` available in the component browser

## Basic Usage

### Adding the Component

1. Select any Actor in your level
2. In the **Details** panel, click **Add Component**
3. Search for and add **NetworkReplicationComponent**

### Quick Demo - Replicate an Animation

1. **In Blueprint:**
```blueprint
// Get the NetworkReplicationComponent
Get Component by Class -> NetworkReplicationComponent

// Replicate an animation
Replicate Animation
- Montage: YourAnimMontage
- Play Rate: 1.0
- Starting Position: 0.0
```

2. **In C++:**
```cpp
// Get the component
UNetworkReplicationComponent* RepComp = GetComponentByClass<UNetworkReplicationComponent>();

// Replicate animation
RepComp->ReplicateAnimation(YourMontage, 1.0f, 0.0f);
```

### Quick Demo - Spawn Attached Actor

1. **In Blueprint:**
```blueprint
// Spawn and attach an actor
Replicate Actor Spawn Attached
- Actor Class: YourActorClass
- Attach Socket Name: None (or specific socket)
- Location Offset: (0, 0, 0)
- Rotation Offset: (0, 0, 0)
```

2. **In C++:**
```cpp
// Spawn attached actor
RepComp->ReplicateActorSpawnAttached(
    YourActorClass,
    NAME_None,
    FVector::ZeroVector,
    FRotator::ZeroRotator
);
```

## Testing Your Setup

### Enable Debug Mode
1. Select your actor with the NetworkReplicationComponent
2. In the **Details** panel, find **Network Replication | Debug**
3. Check **Debug Mode** to see replication logs

### Test in Multiplayer
1. Open **Window > Play in New Editor Window (PIE)**
2. Set **Number of Players** to 2 or more
3. Click **Play**
4. Use the replication functions and watch the console for debug output

## Common Issues

### Plugin Not Found
- Ensure the plugin is in `Plugins/NetworkReplicationSubsystem/`
- Check that the `.uplugin` file is valid
- Restart the editor after enabling

### Component Not Available
- Make sure the plugin is enabled
- Check that your project targets UE 5.6
- Verify the plugin compiled successfully

### Replication Not Working
- Ensure your actor has network replication enabled
- Check that you're testing in a multiplayer context
- Verify the component is on the server or has proper authority

## Next Steps

- Read the [Advanced Guide](Advanced.md) for detailed usage patterns
- Check the [API Reference](API_Reference.md) for all available functions
- See [Troubleshooting](Troubleshooting.md) for common issues

## Support

- Check the [Troubleshooting Guide](Troubleshooting.md)
- Review the [API Reference](API_Reference.md)
- Visit the project repository for updates and examples
