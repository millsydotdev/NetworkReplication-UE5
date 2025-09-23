# Console Commands Reference
## Network Replication Subsystem Console Commands

This document provides a comprehensive reference for all 21 console commands available in the Network Replication Subsystem plugin.

---

## **Performance Monitoring Commands**

### **Show Statistics**
```
NetworkReplication.ShowStats
```
**Description**: Displays current replication statistics including bandwidth usage, latency, and component count.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.ShowStats`

---

### **Start Profiling**
```
NetworkReplication.StartProfiling
```
**Description**: Begins performance profiling to monitor network replication performance.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.StartProfiling`

---

### **Stop Profiling**
```
NetworkReplication.StopProfiling
```
**Description**: Stops performance profiling and displays results.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.StopProfiling`

---

### **Reset Statistics**
```
NetworkReplication.ResetStats
```
**Description**: Resets all replication statistics to zero.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.ResetStats`

---

## **Network Simulation Commands**

### **Simulate Latency**
```
NetworkReplication.SimulateLatency <milliseconds>
```
**Description**: Simulates network latency for testing purposes.

**Parameters**:
- `<milliseconds>`: Latency in milliseconds (0-1000)

**Usage**: `NetworkReplication.SimulateLatency 100`

---

### **Simulate Packet Loss**
```
NetworkReplication.SimulatePacketLoss <percentage>
```
**Description**: Simulates packet loss for testing network resilience.

**Parameters**:
- `<percentage>`: Packet loss percentage (0-100)

**Usage**: `NetworkReplication.SimulatePacketLoss 5`

---

### **Simulate Bandwidth Limit**
```
NetworkReplication.SimulateBandwidth <kbps>
```
**Description**: Simulates bandwidth limitations for testing.

**Parameters**:
- `<kbps>`: Bandwidth limit in kilobits per second

**Usage**: `NetworkReplication.SimulateBandwidth 1000`

---

### **Reset Network Simulation**
```
NetworkReplication.ResetSimulation
```
**Description**: Resets all network simulation settings to normal.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.ResetSimulation`

---

## **Debug Commands**

### **Enable Debug Logging**
```
NetworkReplication.EnableDebugLogging <true/false>
```
**Description**: Enables or disables debug logging for network replication.

**Parameters**:
- `<true/false>`: Enable or disable debug logging

**Usage**: `NetworkReplication.EnableDebugLogging true`

---

### **Log Replication Event**
```
NetworkReplication.LogEvent <event_name>
```
**Description**: Logs a custom replication event for debugging.

**Parameters**:
- `<event_name>`: Name of the event to log

**Usage**: `NetworkReplication.LogEvent "PlayerJump"`

---

### **Show Network Insights**
```
NetworkReplication.ShowInsights
```
**Description**: Displays detailed network insights and analysis.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.ShowInsights`

---

### **Export Replication Data**
```
NetworkReplication.ExportData
```
**Description**: Exports replication data to a file for analysis.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.ExportData`

---

## **Component Management Commands**

### **List Active Components**
```
NetworkReplication.ListComponents
```
**Description**: Lists all active network replication components.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.ListComponents`

---

### **Get Component Count**
```
NetworkReplication.GetComponentCount
```
**Description**: Returns the number of active replication components.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.GetComponentCount`

---

### **Optimize Replication**
```
NetworkReplication.Optimize
```
**Description**: Runs optimization algorithms on active replication components.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.Optimize`

---

## **Motion Matching Commands**

### **Enable Motion Matching Debug**
```
NetworkReplication.EnableMotionMatchingDebug <true/false>
```
**Description**: Enables or disables motion matching debug visualization.

**Parameters**:
- `<true/false>`: Enable or disable motion matching debug

**Usage**: `NetworkReplication.EnableMotionMatchingDebug true`

---

### **Show Motion Matching Stats**
```
NetworkReplication.ShowMotionMatchingStats
```
**Description**: Displays motion matching replication statistics.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.ShowMotionMatchingStats`

---

### **Test Motion Matching**
```
NetworkReplication.TestMotionMatching
```
**Description**: Tests motion matching replication functionality.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.TestMotionMatching`

---

## **Performance Optimization Commands**

### **Set Replication Distance**
```
NetworkReplication.SetDistance <distance>
```
**Description**: Sets the maximum replication distance for relevancy checking.

**Parameters**:
- `<distance>`: Maximum replication distance in Unreal units

**Usage**: `NetworkReplication.SetDistance 5000`

---

### **Set Replication Frequency**
```
NetworkReplication.SetFrequency <frequency>
```
**Description**: Sets the replication frequency for optimization.

**Parameters**:
- `<frequency>`: Replication frequency in Hz

**Usage**: `NetworkReplication.SetFrequency 30`

---

### **Enable Relevancy**
```
NetworkReplication.EnableRelevancy <true/false>
```
**Description**: Enables or disables relevancy checking for performance optimization.

**Parameters**:
- `<true/false>`: Enable or disable relevancy checking

**Usage**: `NetworkReplication.EnableRelevancy true`

---

### **Set Bandwidth Limit**
```
NetworkReplication.SetBandwidthLimit <kbps>
```
**Description**: Sets the bandwidth limit for replication.

**Parameters**:
- `<kbps>`: Bandwidth limit in kilobits per second

**Usage**: `NetworkReplication.SetBandwidthLimit 1000`

---

## **Advanced Debug Commands**

### **Start Network Profiling**
```
NetworkReplication.StartNetworkProfiling
```
**Description**: Begins advanced network profiling with detailed metrics.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.StartNetworkProfiling`

---

### **Stop Network Profiling**
```
NetworkReplication.StopNetworkProfiling
```
**Description**: Stops advanced network profiling and displays results.

**Usage**: Type in console or Blueprint
**Example**: `NetworkReplication.StopNetworkProfiling`

---

### **Show Component Details**
```
NetworkReplication.ShowComponentDetails <component_id>
```
**Description**: Shows detailed information about a specific replication component.

**Parameters**:
- `<component_id>`: ID of the component to inspect

**Usage**: `NetworkReplication.ShowComponentDetails 1`

---

## **Usage Examples**

### **Basic Performance Monitoring**
```
NetworkReplication.StartProfiling
NetworkReplication.ShowStats
NetworkReplication.StopProfiling
```

### **Network Condition Testing**
```
NetworkReplication.SimulateLatency 150
NetworkReplication.SimulatePacketLoss 3
NetworkReplication.SimulateBandwidth 500
```

### **Debug Motion Matching**
```
NetworkReplication.EnableMotionMatchingDebug true
NetworkReplication.ShowMotionMatchingStats
NetworkReplication.TestMotionMatching
```

### **Performance Optimization**
```
NetworkReplication.SetDistance 10000
NetworkReplication.SetFrequency 60
NetworkReplication.EnableRelevancy true
NetworkReplication.Optimize
```

---

## **Blueprint Integration**

All console commands are also available as Blueprint functions:

**Category**: `Network Replication|Console`
**Functions**: All commands listed above
**Events**: Console command execution events

### **Blueprint Usage Example**
```cpp
// In Blueprint: Call "Network Replication|Console|Show Stats" function
// In C++:
if (UNetworkReplicationSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UNetworkReplicationSubsystem>())
{
    Subsystem->ShowNetworkStats();
}
```

---

## **Troubleshooting Console Commands**

### **Command Not Found**
- Ensure the plugin is enabled
- Restart the editor after enabling the plugin
- Check that the plugin compiled successfully

### **Command Not Working**
- Verify you have the required permissions
- Check that the component is properly initialized
- Ensure network replication is enabled

### **Performance Issues**
- Use `NetworkReplication.ShowStats` to monitor performance
- Enable debug logging with `NetworkReplication.EnableDebugLogging true`
- Use profiling commands to identify bottlenecks

---

## **Best Practices**

### **Development Workflow**
1. **Start with Profiling**: Use `StartProfiling` at the beginning of development
2. **Monitor Performance**: Regularly use `ShowStats` to check performance
3. **Test Network Conditions**: Use simulation commands to test under various conditions
4. **Optimize Continuously**: Use `Optimize` command regularly

### **Debugging Workflow**
1. **Enable Debug Logging**: Use `EnableDebugLogging true` for detailed logs
2. **Use Network Insights**: Use `ShowInsights` for detailed analysis
3. **Export Data**: Use `ExportData` for external analysis
4. **Reset When Done**: Use `ResetStats` to clear old data

---

**For additional console command support, visit our [GitHub Repository](https://github.com/millsydotdev/NetworkReplication-UE5) or join our [Discord Community](https://discord.gg/uyJ636Y4u8).**
