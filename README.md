# Network Replication Subsystem

A comprehensive network replication plugin for Unreal Engine 5.6 that simplifies multiplayer game development with Blueprint-friendly components and advanced networking features.

## Features

- **Universal Data Replication** - Replicate any data type (strings, floats, vectors, custom objects) across the network
- **Custom Event System** - Send custom events and messages between clients and servers
- **Blueprint Integration** - Full Blueprint support with intuitive event binding
- **Hot Joining Support** - Late-joining clients receive proper game state
- **Client Prediction** - Immediate visual feedback with server validation
- **High Ping Optimization** - Smooth gameplay even with high latency
- **Low FPS Resilience** - Stable performance under low frame rates
- **Performance Monitoring** - Built-in network performance tracking and optimization
- **Debug Tools** - Comprehensive debugging and network simulation capabilities
- **Production Ready** - Optimized for real-world multiplayer games

## Installation

1. Download the plugin files
2. Copy the `NetworkReplicationSubsystem` folder to your project's `Plugins` directory
3. Open your project in Unreal Engine 5.6
4. The plugin will be automatically loaded and available

## Quick Start

### Adding the Component

1. Open any Blueprint in your project
2. Add the `NetworkReplicationComponent` from the Components panel
3. The component will appear in your Details panel with all available events

### Basic Variable Replication

```cpp
// C++ Example
NetworkComponent->ReplicateStringVariable("PlayerName", "Player1");
NetworkComponent->ReplicateFloatVariable("Health", 100.0f);
NetworkComponent->ReplicateVectorVariable("Position", FVector(100, 200, 300));
```

### Blueprint Usage

1. **Add Component**: Add `NetworkReplicationComponent` to your Blueprint
2. **Bind Events**: Use the "+" buttons to bind to replication events
3. **Replicate Data**: Call replication functions to send data across the network
4. **Receive Data**: Handle incoming data through bound events

## Available Events

- **On Variable Replicated** - Triggered when a variable is received
- **On Custom Event Replicated** - Triggered when a custom event is received
- **On Animation Replicated** - For animation synchronization
- **On Sound Replicated** - For sound effect replication
- **On Actor Spawned** - For actor spawning replication
- **On Niagara Effect Replicated** - For particle effect replication

## Console Commands

Access these commands in the Unreal Engine console for debugging and monitoring:

### Basic Commands
- `NetworkReplication.ShowStats` - Display current network statistics
- `NetworkReplication.ExportData` - Export replication data to file
- `NetworkReplication.ResetStats` - Reset all statistics

### Performance Monitoring
- `NetworkReplication.StartPerformanceMonitoring` - Begin performance tracking
- `NetworkReplication.StopPerformanceMonitoring` - Stop performance tracking
- `NetworkReplication.GetDetailedReport` - Get comprehensive performance report

### Network Simulation
- `NetworkReplication.SimulatePacketLoss [percentage]` - Simulate packet loss
- `NetworkReplication.SimulateLatency [milliseconds]` - Simulate network latency
- `NetworkReplication.ResetSimulation` - Reset all network simulations

## Configuration

### Replication Settings

The subsystem provides configurable settings for:
- **Replication Distance** - Maximum distance for replication
- **Replication Interval** - How often to replicate data
- **Bandwidth Limits** - Maximum bandwidth usage
- **Performance Thresholds** - Warning levels for performance metrics

### Performance Optimization

- **Client-Side Prediction** - Reduce perceived latency
- **Interest Management** - Only replicate relevant data
- **Bandwidth Management** - Prioritize important data
- **Adaptive Quality** - Adjust quality based on network conditions

## Examples

### Player Movement Replication

```cpp
// Replicate player position every frame
void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (NetworkComponent)
    {
        NetworkComponent->ReplicateVectorVariable("Position", GetActorLocation());
        NetworkComponent->ReplicateFloatVariable("Health", CurrentHealth);
    }
}
```

### Custom Event Handling

```cpp
// Send custom event
NetworkComponent->ReplicateCustomEvent("PlayerAction", "Jump");

// Handle received event (in Blueprint or C++)
void OnCustomEventReceived(FName EventName, const FString& EventData)
{
    if (EventName == "PlayerAction" && EventData == "Jump")
    {
        // Handle jump action
    }
}
```

## Documentation

Complete documentation is available in the `Docs` folder:

- **[Quick Start](Docs/QuickStart.md)** - Get up and running in minutes
- **[Advanced Guide](Docs/Advanced.md)** - Master advanced features and patterns
- **[API Reference](Docs/API_Reference.md)** - Complete function and class documentation
- **[Troubleshooting](Docs/Troubleshooting.md)** - Common issues and solutions

## Requirements

- **Unreal Engine 5.6** or later
- **Visual Studio 2022** (for C++ development on Windows)
- **Xcode 14+** (for C++ development on Mac)
- **GCC 9+** (for C++ development on Linux)
- **Windows 10/11** (64-bit), **macOS 12+**, or **Linux** (Ubuntu 20.04+)

## Support

For questions, issues, or feature requests:
- Check the documentation in the `Docs` folder
- Review the troubleshooting guide
- Open an issue on the project repository

## License

This project is released under the MIT License. See the LICENSE file for details.

---

**Network Replication Subsystem** - Simplifying multiplayer game development in Unreal Engine 5.6