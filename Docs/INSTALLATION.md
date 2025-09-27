# Network Replication Subsystem - Installation Guide
## Step-by-Step Installation Instructions

This guide will help you install the Network Replication Subsystem plugin in your Unreal Engine 5.6+ project.

---

## **Installation Methods**

### **Method 1: Manual Installation**

1. **Copy the Plugin**
   - Copy the entire `NetworkReplicationSubsystem` folder to your UE project's `Plugins` directory
   - Your project structure should look like:

     ```text
     YourProject/
     ├── YourProject.uproject
     ├── Plugins/
     │   └── NetworkReplicationSubsystem/
     │       ├── NetworkReplicationSubsystem.uplugin
     │       ├── Source/
     │       └── Docs/
     ```

2. **Enable the Plugin**
   - Open your project in Unreal Engine
   - Go to `Edit` → `Plugins`
   - Search for "Network Replication Subsystem"
   - Check the "Enabled" checkbox
   - Restart the editor

3. **Generate Project Files** (if using C++)
   - Right-click on your `.uproject` file
   - Select "Generate Visual Studio project files"
   - Build your project

### **Method 2: Git Installation**

1. **Clone the Repository**
   ```bash
   git clone https://github.com/millsydotdev/NetworkReplication-UE5.git
   ```

2. **Copy to Your Project**
   ```bash
   cp -r NetworkReplicationSubsystem/ YourProject/Plugins/
   ```

3. **Follow Method 1 steps 2-3**

---

## **System Requirements**

### **Minimum Requirements**
- **Unreal Engine**: 5.6 or later
- **Platforms**: Windows 10/11, macOS 10.15+, Linux (Ubuntu 18.04+)
- **Visual Studio**: 2022 or later (Windows)
- **Xcode**: 12.0 or later (macOS)

### **Dependencies**
- **Niagara Plugin**: Automatically enabled (included in UE 5.6+)
- **PoseSearch Plugin**: Required for motion matching features
- **Chooser Plugin**: Required for animation chooser systems
- **AnimationCore**: Core animation functionality
- **Core UE Modules**: Engine, CoreUObject (automatically included)

### **Game Animation Sample Compatibility**
- **Epic Game Animation Sample**: Fully compatible with Epic's Game Animation Sample project
- **Motion Matching**: Built-in support for pose search and trajectory replication
- **500+ Animations**: Ready to use with Epic's extensive animation library

---

## **Verification Steps**

### **Check Plugin Status**
1. Open `Edit` → `Plugins`
2. Search for "Network Replication Subsystem"
3. Verify it shows as "Enabled"

### **Test Component Availability**
1. Create a new Blueprint class
2. In Components panel, click `Add Component`
3. Search for "Network Replication Component"
4. If found, installation is successful!

### **C++ Integration Test**
```cpp
// In your C++ class
#include "NetworkReplicationComponent.h"

// Add component to your actor
UNetworkReplicationComponent* ReplicationComp = CreateDefaultSubobject<UNetworkReplicationComponent>(TEXT("ReplicationComponent"));
```

---

## **Troubleshooting**

### **Plugin Not Found**
- **Check Location**: Ensure plugin is in `YourProject/Plugins/NetworkReplicationSubsystem/`
- **Check .uplugin File**: Verify `NetworkReplicationSubsystem.uplugin` exists
- **Restart Editor**: Close and reopen Unreal Engine

### **Compilation Errors**
- **Generate Project Files**: Right-click `.uproject` → "Generate Visual Studio project files"
- **Clean Build**: Delete `Binaries` and `Intermediate` folders, then rebuild
- **Check Dependencies**: Ensure Niagara plugin is enabled

### **Component Not Available**
- **Verify Plugin Enabled**: Check in `Edit` → `Plugins`
- **Restart Editor**: Close and reopen Unreal Engine
- **Check Build**: Ensure project compiled successfully

---

## **Quick Start**

### **Basic Setup**
1. **Add Component**: Add `Network Replication Component` to your Blueprint or C++ class
2. **Configure**: Set up replication settings in the Details panel
3. **Use Functions**: Call replication functions from Blueprint or C++

### **Example Usage**
```cpp
// Replicate an animation
ReplicationComponent->ReplicateAnimation(MyMontage, 1.0f, 0.0f);

// Replicate a sound
ReplicationComponent->ReplicateSound(MySound, 1.0f, 1.0f, 0.0f);

// Spawn an actor
ReplicationComponent->ReplicateActorSpawn(MyActorClass, Location, Rotation, false);
```

---

## **Support**

### **Documentation**
- **Documentation**: Check the `Docs/` folder for comprehensive guides
- **GitHub Issues**: Report bugs at https://github.com/millsydotdev/NetworkReplication-UE5/issues
- **Discord**: Join our community server for real-time help at https://discord.gg/uyJ636Y4u8

### **Contact**
- **Email**: support@millsy.dev
- **Website**: https://millsy.dev

---

**The Network Replication Subsystem is now ready to use in your Unreal Engine project!**
