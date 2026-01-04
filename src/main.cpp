#include <iostream>
#include "../include/lidar_single_beam.hpp"
#include "../include/lidar_env.hpp"

int main() 
{
    std::cout << "Starting LiDAR Single Beam Simulator" << std::endl;   
    Lidar lidar(1, 10, 400); 
    std::cout << "lidar Max range: " << lidar.getBeamMaxRange() << ", Min range: " << lidar.getBeamMinRange() << ", Resolution: " << lidar.getBeamResolution() << ", Frequency: " << lidar.getFrequency() << std::endl;
    std::cout << "Starting LiDAR Env" << std::endl;
    LidarEnv env(&lidar);
    env.startRenderLoop(&lidar);

    return 0;
}