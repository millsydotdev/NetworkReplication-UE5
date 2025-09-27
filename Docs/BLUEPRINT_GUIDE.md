# Blueprint Integration Guide
## Network Replication Subsystem - Blueprint Visual Scripting

This comprehensive guide covers Blueprint integration for the Network Replication Subsystem plugin, enabling visual scripting of network replication features without traditional coding.

---

## **Blueprint Editor Overview**

### **Key Panels for Network Replication**
- **Components Panel**: Add and configure Network Replication Component
- **Event Graph**: Create network replication logic
- **My Blueprint**: Manage custom functions and events
- **Details Panel**: Configure component properties

### **Blueprint Categories**
The plugin provides organized Blueprint categories for easy navigation:
- `Network Replication|Animation` - Animation replication functions
- `Network Replication|Sound` - Sound replication functions
- `Network Replication|Motion Matching` - Motion matching functions
- `Network Replication|Debug` - Debugging and monitoring tools
- `Network Replication|Performance` - Performance optimization tools

---

## **Getting Started with Blueprints**

### **Step 1: Adding the Component**

**Method 1: Component Panel**
1. Open your Blueprint (Character, Pawn, or Actor)
2. In the Components panel, click "Add Component"
3. Search for "Network Replication Component"
4. Add it to your Blueprint

**Method 2: Class Defaults**
1. Select your Blueprint class
2. In Class Defaults, find "Network Replication Component"
3. Configure default settings

### **Step 2: Basic Configuration**

**Essential Settings:**
- **Replication Distance**: Set maximum replication range
- **Replication Frequency**: Control update rate
- **Enable Debug Logging**: Toggle debug information
- **Enable Relevancy**: Optimize network performance

---

## **Animation Replication Blueprints**

### **Basic Animation Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Animation**: Use "Replicate Animation" function
3. **Set Parameters**: Configure montage, play rate, and start time

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Replicate Animation (Montage: JumpMontage, Play Rate: 1.0, Start Time: 0.0)
```

### **Animation Event Handling**

**Blueprint Events:**
- **On Animation Replicated**: Triggered when animation is received
- **On Animation Stopped**: Triggered when animation stops
- **On Animation Completed**: Triggered when animation finishes

**Blueprint Setup:**
1. **Bind to Event**: Use "Bind Event to On Animation Replicated"
2. **Create Custom Function**: Handle the received animation
3. **Process Animation**: Apply the animation to your character

---

## **Sound Replication Blueprints**

### **Basic Sound Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Sound**: Use "Replicate Sound" function
3. **Set Parameters**: Configure sound, volume, pitch, and location

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Replicate Sound (Sound: FootstepSound, Volume: 1.0, Pitch: 1.0)
```

### **Sound at Location Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Sound At Location**: Use "Replicate Sound At Location" function
3. **Set Location**: Use "Get Actor Location" or custom vector

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Get Actor Location
    ↓
Replicate Sound At Location (Sound: ExplosionSound, Location: Actor Location, Volume: 1.0)
```

---

## **Motion Matching Blueprints**

### **Motion Matching Database Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Motion Matching Database**: Use "Replicate Motion Matching Database" function
3. **Set Database**: Reference your motion matching database

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Replicate Motion Matching Database (Database: MyMotionMatchingDatabase)
```

### **Trajectory Data Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Trajectory Data**: Use "Replicate Trajectory Data" function
3. **Set Position and Rotation**: Use "Get Actor Location" and "Get Actor Rotation"

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Get Actor Location
    ↓
Get Actor Rotation
    ↓
Replicate Trajectory Data (Position: Actor Location, Rotation: Actor Rotation)
```

### **Motion Matching Event Handling**

**Blueprint Events:**
- **On Motion Matching Replicated**: Triggered when motion matching data is received
- **On Trajectory Replicated**: Triggered when trajectory data is received
- **On Pose Search Replicated**: Triggered when pose search data is received

**Blueprint Setup:**
1. **Bind to Event**: Use "Bind Event to On Motion Matching Replicated"
2. **Create Custom Function**: Handle the received motion matching data
3. **Process Data**: Apply the motion matching data to your character

---

## **Variable Replication Blueprints**

### **String Variable Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate String Variable**: Use "Replicate String Variable" function
3. **Set Variable Name and Value**: Configure variable name and string value

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Replicate String Variable (Variable Name: "PlayerName", Variable Value: "MyPlayerName")
```

### **Float Variable Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Float Variable**: Use "Replicate Float Variable" function
3. **Set Variable Name and Value**: Configure variable name and float value

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Replicate Float Variable (Variable Name: "Health", Variable Value: 100.0)
```

### **Vector Variable Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Vector Variable**: Use "Replicate Vector Variable" function
3. **Set Variable Name and Value**: Configure variable name and vector value

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Replicate Vector Variable (Variable Name: "Velocity", Variable Value: (0, 0, 0))
```

---

## **Custom Event Blueprints**

### **Basic Custom Event Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Custom Event**: Use "Replicate Custom Event" function
3. **Set Event Name and Data**: Configure event name and data string

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Replicate Custom Event (Event Name: "SpecialEvent", Event Data: "EventData")
```

### **Custom Event Handling**

**Blueprint Events:**
- **On Custom Event Replicated**: Triggered when custom event is received
- **On Variable Replicated**: Triggered when variable is received

**Blueprint Setup:**
1. **Bind to Event**: Use "Bind Event to On Custom Event Replicated"
2. **Create Custom Function**: Handle the received custom event
3. **Process Event**: Execute appropriate logic based on event data

---

## **Niagara Effects Blueprints**

### **Basic Niagara Effect Replication**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Replicate Niagara Effect**: Use "Replicate Niagara Effect" function
3. **Set System and Location**: Configure Niagara system and spawn location

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Get Actor Location
    ↓
Replicate Niagara Effect (System: ExplosionEffect, Location: Actor Location, Rotation: (0, 0, 0))
```

### **Niagara Effect Configuration**

**Blueprint Setup:**
1. **Get Return Value**: Use the returned Niagara Component
2. **Set Auto Destroy**: Configure auto-destroy behavior
3. **Set Parameters**: Configure additional effect parameters

**Blueprint Example:**
```
Replicate Niagara Effect
    ↓
Get Return Value (Niagara Component)
    ↓
Set Auto Destroy (True)
```

---

## **Performance Optimization Blueprints**

### **Relevancy Configuration**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Set Replication Distance**: Use "Set Replication Distance" function
3. **Call Enable Relevancy Culling**: Use "Enable Relevancy Culling" function

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Set Replication Distance (5000.0)
    ↓
Enable Relevancy Culling (True)
```

### **Performance Monitoring**

**Blueprint Setup:**
1. **Get Network Replication Component**: Use "Get Network Replication Component" node
2. **Call Get Replication Stats**: Use "Get Replication Stats" function
3. **Call Enable Debug Logging**: Use "Enable Debug Logging" function

**Blueprint Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Enable Debug Logging (True)
    ↓
Get Replication Stats
    ↓
Print String (Stats)
```

---

## **Advanced Blueprint Patterns**

### **Event-Driven Architecture**

**Blueprint Setup:**
1. **Create Custom Events**: Define custom events for your game logic
2. **Bind to Network Events**: Connect network events to your custom events
3. **Process Events**: Handle events with appropriate logic

**Blueprint Example:**
```
On Motion Matching Replicated
    ↓
Custom Event: Process Motion Matching
    ↓
Custom Event: Update Character Animation
```

### **State Management**

**Blueprint Setup:**
1. **Create State Variables**: Define state variables for your character
2. **Replicate State Changes**: Use variable replication for state changes
3. **Handle State Updates**: Process received state changes

**Blueprint Example:**
```
On Variable Replicated
    ↓
Switch on Variable Name
    ├─ "Health" → Update Health Display
    ├─ "Ammo" → Update Ammo Display
    └─ "Score" → Update Score Display
```

### **Conditional Replication**

**Blueprint Setup:**
1. **Check Conditions**: Use conditional nodes for replication logic
2. **Replicate Based on Conditions**: Only replicate when conditions are met
3. **Optimize Performance**: Reduce unnecessary replication

**Blueprint Example:**
```
Event Tick
    ↓
Check Distance to Player
    ↓
Branch (Is Close Enough)
    ├─ True → Replicate Animation
    └─ False → Do Nothing
```

---

## **Blueprint Best Practices**

### **Performance Optimization**

**1. Use Appropriate Replication Frequency**
- Set replication frequency based on importance
- Use lower frequency for less critical data
- Enable relevancy checking for large multiplayer games

**2. Optimize Event Handling**
- Use event-driven architecture
- Avoid unnecessary event bindings
- Clean up event bindings when appropriate

**3. Monitor Performance**
- Enable debug logging during development
- Use performance monitoring functions
- Check replication statistics regularly

### **Code Organization**

**1. Modular Design**
- Create reusable Blueprint functions
- Use custom events for communication
- Organize Blueprint nodes logically

**2. Error Handling**
- Check for null references
- Validate input parameters
- Handle network errors gracefully

**3. Documentation**
- Add comments to complex Blueprint logic
- Use descriptive node names
- Document custom functions and events

---

## **Troubleshooting Blueprint Issues**

### **Common Issues**

**1. Component Not Found**
- Ensure Network Replication Component is added
- Check component is properly configured
- Verify component is enabled

**2. Replication Not Working**
- Check network authority
- Verify replication settings
- Ensure proper event binding

**3. Performance Issues**
- Monitor replication frequency
- Enable relevancy checking
- Use appropriate replication distance

### **Debug Tools**

**1. Debug Logging**
- Enable debug logging in component settings
- Use "Print String" nodes for debugging
- Check console output for errors

**2. Performance Monitoring**
- Use "Get Replication Stats" function
- Monitor bandwidth usage
- Check replication frequency

**3. Network Simulation**
- Use console commands for testing
- Simulate network conditions
- Test under various scenarios

---

## **Blueprint Examples**

### **Complete Character Setup**

**Blueprint Structure:**
```
MyCharacter Blueprint
├─ Components
│  ├─ Skeletal Mesh Component
│  ├─ Network Replication Component
│  └─ Audio Component
├─ Events
│  ├─ BeginPlay
│  ├─ Tick
│  └─ Custom Events
├─ Functions
│  ├─ Play Animation
│  ├─ Play Sound
│  └─ Update Motion Matching
└─ Variables
    ├─ Health
    ├─ Ammo
    └─ Score
```

**Event Graph Example:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Bind Event to On Animation Replicated
    ↓
Bind Event to On Sound Replicated
    ↓
Bind Event to On Motion Matching Replicated
    ↓
Enable Debug Logging (True)
```

### **Motion Matching Integration**

**Blueprint Setup:**
```
Event BeginPlay
    ↓
Get Network Replication Component
    ↓
Replicate Motion Matching Database (MyDatabase)
    ↓
Replicate Pose Search Schema (MySchema)
    ↓
Replicate Trajectory Data (Actor Location, Actor Rotation)
```

---

## **Conclusion**

The Network Replication Subsystem provides comprehensive Blueprint integration for visual scripting of network replication features. By following this guide, you can create sophisticated multiplayer functionality without traditional coding, leveraging Unreal Engine 5.6's powerful Blueprint system.

**Key Benefits:**
- **Visual Scripting**: No coding required for basic functionality
- **Easy Integration**: Simple drag-and-drop setup
- **Powerful Features**: Access to all plugin functionality
- **Performance Optimized**: Built-in optimization tools
- **Debug Friendly**: Comprehensive debugging capabilities

**For additional Blueprint support, visit our [GitHub Repository](https://github.com/millsydotdev/NetworkReplication-UE5) or join our [Discord Community](https://discord.gg/uyJ636Y4u8).**
