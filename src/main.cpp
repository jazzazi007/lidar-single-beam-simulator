#include "../include/lidar_single_beam.hpp"

int main() 
{
    std::cout<< "Starting LiDAR Single Beam Simulator"<<std::endl;
    LidarEnv env;
    Lidar lidar(1, 10, 400);
    env.startRenderLoop(lidar);

}