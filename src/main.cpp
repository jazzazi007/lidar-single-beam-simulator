#include <iostream>
#include "../include/lidar_single_beam.hpp"
#include "../include/lidar_env.hpp"

int main() 
{
    std::cout << "Starting LiDAR Single Beam Simulator" << std::endl;
    
    // Initialize the sensor with datasheet specs
    // 1 beam, 10 deg FOV, 400 Hz
    Lidar lidar(1, 10, 400); 
    
    // Initialize the environment with the sensor
    LidarEnv env(&lidar);
    
    // Start the SDL2 window and physics loop
    env.startRenderLoop(&lidar);

    return 0;
}