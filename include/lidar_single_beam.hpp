#ifndef LIDAR_SINGLE_BEAM_HPP
#define LIDAR_SINGLE_BEAM_HPP

#include "lidar_env.hpp" // Assuming this defines World and Pose
#include <vector>

#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <limits>


class Lidar {
public:
    // Pass specs via constructor to make the class reusable for different sensors
    Lidar(int numBeams = 1, double fov = 10.0, int frequency = 400);
    ~Lidar(){};

    // Structure to hold a single "reading"
    struct Reading {
        double angle;
        double distance;
        double intensity;
        long long timestamp_ns;
    };

    // The core "update" function
    std::vector<Reading> generateScan(long long currentTimeNs, double angle, double range, double intensity);
    double getBeamMaxRange() const { return beamMaxRange; }
    double getBeamMinRange() const { return beamMinRange; }
    double getBeamResolution() const { return beamResolution; }
    double getFrequency() const { return beamFrequency;}

private:
    float beamMaxRange = 100.0f;
    float beamMinRange = 0.2f; // Based on your earlier spec
    float beamResolution = 0.3f;
    int numberOfBeams;
    double FOVAngle; 
    int beamFrequency; 
    std::vector<double> beamAngles; 
};

#endif