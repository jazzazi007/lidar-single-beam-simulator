#ifndef LIDAR_SINGLE_BEAM_HPP
#define LIDAR_SINGLE_BEAM_HPP

#include <algorithm>
#include "lidar_env.hpp" // Assuming this defines World and Pose


class Lidar {
public:
    // Pass specs via constructor to make the class reusable for different sensors
    Lidar(int numBeams = 1, double fov = 10.0, int frequency = 400);
    ~Lidar() = default; // std::vector handles its own memory

    // Structure to hold a single "reading"
    struct Reading {
        double angle;
        double distance;
        double intensity;
        long long timestamp_ns;
    };

    // The core "update" function
   // std::vector<Reading> generateScan(const World& world, const Pose& sensorPose);

private:
    double beamMaxRange = 100.0;
    double beamMinRange = 0.2; // Based on your earlier spec
    int numberOfBeams;
    double FOVAngle; 
    int beamFrequency; 
    std::vector<double> beamAngles; 
};

Lidar::Lidar(int numBeams, double fov, int frequency) 
    : numberOfBeams(numBeams), FOVAngle(fov), beamFrequency(frequency) {
    
    if (numberOfBeams <= 1) {
        beamAngles.push_back(0.0);
    } else {
        double angleIncrement = FOVAngle / (numberOfBeams - 1);
        double startAngle = -FOVAngle / 2.0;
        for (int i = 0; i < numberOfBeams; ++i) {
            beamAngles.push_back(startAngle + i * angleIncrement);
        }
    }
}

#endif