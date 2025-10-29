# NetworkReplication Plugin - Troubleshooting Guide

Common issues and solutions for the NetworkReplication plugin.

## Installation Issues

### Plugin Not Found

**Problem:** Plugin doesn't appear in the Plugins menu.

**Solutions:**
1. Verify the plugin is in the correct location: `Plugins/NetworkReplicationSubsystem/`
2. Check that `NetworkReplicationSubsystem.uplugin` file exists and is valid
3. Ensure the plugin is compatible with UE 5.6
4. Restart the editor after placing the plugin

**Verification:**
```bash
# Check plugin structure
ls -la Plugins/NetworkReplicationSubsystem/
# Should show: .uplugin, Source/, Config/, etc.
```

### Plugin Compilation Errors

**Problem:** Plugin fails to compile or shows errors.

**Solutions:**
1. Check that UE 5.6 is properly installed
2. Verify all required dependencies are available
3. Clean and rebuild the project
4. Check the build log in `Saved/Logs/UnrealBuildTool.log`

**Debug Steps:**
```bash
# Clean build
rm -rf Binaries/ Intermediate/ Saved/
# Regenerate project files
# Rebuild project
```

## Runtime Issues

### Component Not Available

**Problem:** NetworkReplicationComponent doesn't appear in the component browser.

**Solutions:**
1. Ensure the plugin is enabled in Project Settings > Plugins
2. Check that the plugin compiled successfully
3. Verify the project targets UE 5.6
4. Restart the editor

### Replication Not Working

**Problem:** Replication functions don't work or have no effect.

**Common Causes:**
1. **Not in multiplayer context**: Replication only works in multiplayer
2. **Missing network replication**: Actor doesn't have replication enabled
3. **Authority issues**: Calling server functions from client without authority
4. **Network not initialized**: Network subsystem not properly set up

**Solutions:**
```cpp
// 1. Check if in multiplayer
if (GetWorld()->GetNetMode() != NM_DedicatedServer && GetWorld()->GetNetMode() != NM_ListenServer)
{
    UE_LOG(LogTemp, Warning, TEXT("Not in multiplayer context"));
    return;
}

// 2. Enable actor replication
GetOwner()->SetReplicates(true);
GetOwner()->SetReplicateMovement(true);

// 3. Check authority before server operations
if (GetOwner()->HasAuthority())
{
    // Server operations
}
else
{
    // Client operations
}
```

### Hot Joining Issues

**Problem:** Late-joining clients don't receive proper state.

**Solutions:**
1. Ensure `ReplicatedUsing` properties are set correctly
2. Check that `OnRep_AttachmentInfo()` is implemented
3. Verify attachment info is set on the server
4. Test with multiple clients joining at different times

**Debug Steps:**
```cpp
// Enable debug mode
bDebugMode = true;

// Check if attachment info is being set
if (AttachmentInfo.bIsActive)
{
    UE_LOG(LogTemp, Log, TEXT("Attachment info is active"));
}
```

### High Ping Issues

**Problem:** Game feels laggy with high ping.

**Solutions:**
1. Implement client-side prediction
2. Use immediate visual feedback
3. Add server validation and correction
4. Optimize network traffic

**Testing:**
```cpp
// Simulate high ping
IConsoleManager::Get().FindConsoleVariable(TEXT("Net.PktLag"))->Set(150.0f);
IConsoleManager::Get().FindConsoleVariable(TEXT("Net.PktLagVariance"))->Set(25.0f);
```

### Low FPS Crashes

**Problem:** Game crashes or becomes unstable at low FPS.

**Solutions:**
1. Test with low FPS simulation
2. Check for null pointer access
3. Verify component cleanup
4. Monitor memory usage

**Testing:**
```cpp
// Simulate low FPS
IConsoleManager::Get().FindConsoleVariable(TEXT("t.MaxFPS"))->Set(20.0f);
IConsoleManager::Get().FindConsoleVariable(TEXT("r.OneFrameThreadLag"))->Set(1);
```

## Performance Issues

### Network Bandwidth

**Problem:** High network usage or bandwidth.

**Solutions:**
1. Reduce replication frequency
2. Use compression for replicated data
3. Implement relevance filtering
4. Batch operations when possible

**Optimization:**
```cpp
// Only replicate when necessary
if (ShouldReplicate())
{
    ReplicateAnimation(Montage, PlayRate, StartingPosition);
}
```

### Memory Leaks

**Problem:** Memory usage increases over time.

**Solutions:**
1. Check component cleanup in `EndPlay`
2. Unbind delegates when components are destroyed
3. Use weak pointers where appropriate
4. Monitor with memory profiler

**Cleanup:**
```cpp
void UNetworkReplicationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Unbind all delegates
    OnAnimationReplicated.Clear();
    OnSoundReplicated.Clear();
    // ... other delegates
    
    Super::EndPlay(EndPlayReason);
}
```

## Debugging

### Enable Debug Mode

**Enable debug logging:**
```cpp
// In Blueprint or C++
bDebugMode = true;
```

**Check debug output:**
- Look for logs in the Output Log window
- Check `Saved/Logs/` directory
- Use `stat net` console command

### Common Debug Commands

```bash
# Network statistics
stat net

# Show replication info
showdebug net

# Test hot joining
TestHotJoining

# Test high ping
TestHighPingPrediction

# Test low FPS
TestLowFPSScenario
```

### Log Analysis

**Check build logs:**
```bash
# Look for errors
grep "error:" Saved/Logs/UnrealBuildTool.log

# Look for warnings
grep "warning:" Saved/Logs/UnrealBuildTool.log
```

**Check runtime logs:**
```bash
# Look for replication logs
grep "NetworkReplication" Saved/Logs/Game.log
```

## Platform-Specific Issues

### Linux Build Issues

**Problem:** Plugin doesn't build on Linux.

**Solutions:**
1. Use the provided Linux build scripts
2. Check UE 5.6 Linux installation
3. Verify all dependencies are available
4. Check file permissions

**Build Scripts:**
```bash
# Make scripts executable
chmod +x BuildProject.sh TestPluginBuild.sh

# Run build
./BuildProject.sh Development Linux

# Test plugin
./TestPluginBuild.sh Development Linux
```

### Windows Build Issues

**Problem:** Plugin doesn't build on Windows.

**Solutions:**
1. Use Visual Studio 2022
2. Check Windows SDK version
3. Verify UE 5.6 installation
4. Clean and rebuild solution

### Mac Build Issues

**Problem:** Plugin doesn't build on Mac.

**Solutions:**
1. Use Xcode 14+
2. Check macOS version compatibility
3. Verify UE 5.6 Mac installation
4. Check code signing settings

## Common Error Messages

### "Montage is null"
**Cause:** Passing null montage to replication function
**Solution:** Check montage reference before calling

### "Not in multiplayer context"
**Cause:** Calling replication functions in single-player
**Solution:** Check `GetWorld()->GetNetMode()` before replication

### "Component not found"
**Cause:** NetworkReplicationComponent not added to actor
**Solution:** Add component to actor in Blueprint or C++

### "Authority check failed"
**Cause:** Calling server functions without proper authority
**Solution:** Check `GetOwner()->HasAuthority()` before server operations

## Getting Help

### Before Asking for Help

1. **Check this guide** for common solutions
2. **Enable debug mode** and check logs
3. **Test in minimal setup** to isolate issues
4. **Check UE 5.6 compatibility**
5. **Verify plugin installation**

### Information to Include

When reporting issues, include:
- UE version (5.6.x)
- Platform (Windows/Linux/Mac)
- Plugin version
- Error messages and logs
- Steps to reproduce
- Expected vs actual behavior

### Resources

- [Quick Start Guide](QuickStart.md)
- [Advanced Guide](Advanced.md)
- [API Reference](API_Reference.md)
- Project repository and examples
- Unreal Engine documentation

## Performance Tips

### Optimization Checklist

- [ ] Disable debug mode in shipping builds
- [ ] Use authority checks before server operations
- [ ] Minimize RPC calls and batch operations
- [ ] Implement proper cleanup in EndPlay
- [ ] Test with various network conditions
- [ ] Monitor memory usage and leaks
- [ ] Use appropriate replication frequency
- [ ] Implement client-side prediction for responsiveness

### Testing Checklist

- [ ] Test in multiplayer (2+ clients)
- [ ] Test hot joining scenarios
- [ ] Test with high ping (150ms+)
- [ ] Test with low FPS (20 FPS)
- [ ] Test on different platforms
- [ ] Test with various network conditions
- [ ] Verify cleanup and memory usage
- [ ] Check for null pointer access