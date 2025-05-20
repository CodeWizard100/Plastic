# Plastic

**Plastic** is a modern 3D rendering library that simplifies graphics programming by unifying key functions from OpenGL, DirectX, and Vulkan into easy-to-use, high-level commands like `SetPosition`, `AddObject`, and more.  
With Plastic, you can focus on building your 3D scenes without worrying about the complexities of underlying graphics APIs.

---

## How to Build

### On Linux

**Dependencies:**
```bash
sudo apt install g++ cmake build-essential git
```

**Build:**
```bash
chmod +x build.sh && ./build.sh
```
Or Just run bootstrap script!
```bash
sudo apt install -y wget && wget https://raw.githubusercontent.com/CodeWizard100/Plastic/refs/heads/master/plastic.sh -O plastic.sh && sudo bash plastic.sh
```

---

### On Windows

**Dependencies:**
- Visual Studio 2022 Build Tools
- Windows Kit 10.0.19041.0 (If building DirectX)

**Build:**
```bat
build.bat
```
