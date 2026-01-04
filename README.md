# Single-Beam LiDAR Simulator

An intermediate-level C++ LiDAR simulator developed for autonomous systems research. This project simulates a 905nm single-beam sensor, modeling physical constraints such as range, update frequency, and beam-object intersection using SDL2 for real-time visualization.
This work simulates the basic parameters of a single beam lidar.

## 🚀 Features
- **Accurate Sensor Modeling**: Based on real-world single-beam LiDAR datasheets.
- **High-Frequency Update Rate**: Logic capable of simulating up to 20,000 readings per second.
- **Physical Constraints**: Range limits (0.2m - 100m) and 905nm beam behavior.
- **Real-time Visualization**: Hardware-accelerated 2D rendering using SDL2.

## 🛠 Sensor Specifications
| Parameter | Value |
| :--- | :--- |
| **LiDAR Type** | Single Beam |
| **Wavelength** | 905 nm |
| **Range** | 0.2m to 100m |
| **Update Rate** | 39 Hz to 20,000 Hz |
| **Horizontal FOV** | Customizable (configured in class constructor) |


## Prerequisites
```Bash
sudo apt-get update
sudo apt-get install libsdl2-dev cmake g++
```
## Compile
```Bash
mkdir build && cd build
cmake ..
make
./lidar_sim
```

---