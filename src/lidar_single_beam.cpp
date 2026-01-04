#include "../include/lidar_single_beam.hpp"
#include "../include/lidar_env.hpp"

LidarEnv::LidarEnv(Lidar *lidar): lidar(lidar)
{
    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow("LiDAR Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
     this->renderer= SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
     this->lidar = lidar;
}

std::vector<Lidar::Reading> Lidar::generateScan(long long currentTimeNs, double angle, double range, double intensity)
{
    std::vector<Lidar::Reading> data;
    Lidar::Reading reading;
    reading.timestamp_ns = currentTimeNs;
    reading.angle = angle;
    reading.distance = range;
    reading.intensity = intensity;
    data.push_back(reading);
    return data;
}

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
static float getRayDistance(Vec2 rayOrigin, Vec2 rayDir, SDL_Rect target, float resolution, bool errflag) {
    double tMin = (target.x - rayOrigin.x) / rayDir.x;
    double tMax = (target.x + target.w - rayOrigin.x) / rayDir.x;

    
    if (tMin > tMax) std::swap(tMin, tMax);
    
    double tyMin = (target.y - rayOrigin.y) / rayDir.y;
    double tyMax = (target.y + target.h - rayOrigin.y) / rayDir.y;
    
    if (tyMin > tyMax) std::swap(tyMin, tyMax);
    
    // If intervals don't overlap, no hit
    if ((tMin > tyMax) || (tyMin > tMax)) return -1.0f;
    
    if (tyMin > tMin) tMin = tyMin;
    
    if (errflag)
        tMin += resolution;
    else
        tMin -= resolution;
    return (tMin > 0) ? static_cast<float>(tMin) : -1.0f;
}

void LidarEnv::startRenderLoop(Lidar *lidar) 
{
    bool running = true;
    double angle = 0;
    const float range = lidar->getBeamMaxRange();
    const float intensity = 1.0f;
    const double timestamp_ns = 0;
    const float frequency = lidar->getFrequency();
    const float resolution = lidar->getBeamResolution();
    bool errorFlag = false;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);       

        SDL_Rect obstacle = { 400, 250, 50, 100 }; // A "wall" or "pole"
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green obstacle
        SDL_RenderFillRect(renderer, &obstacle);

        // Calculate direction vector from angle
        Vec2 dir = { cos(angle * M_PI / 180.0), sin(angle * M_PI / 180.0) };
        Vec2 origin = { 500.0, 300.0 };

        float dist = getRayDistance(origin, dir, obstacle, resolution, errorFlag);
        errorFlag = !errorFlag; // Toggle error for next beam
        int endX = origin.x + static_cast<int>(range * cos(angle * M_PI / 180.0));
        int endY = origin.y + static_cast<int>(range * sin(angle * M_PI / 180.0));
        
        if (dist > 0 && dist < range) {
            // We hit something! Draw a smaller beam and a point
            int hitX = origin.x + dir.x * dist;
            int hitY = origin.y + dir.y * dist;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White point
            SDL_RenderDrawLine(renderer, origin.x, origin.y, hitX, hitY);
            std::cout << "Distance: " << dist << std::endl;
        }
        else
        {
            SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(this->renderer, origin.x, origin.y, endX, endY);
        } 

        SDL_RenderDrawRect(this->renderer, nullptr); // Draw border
        SDL_RenderPresent(this->renderer);

        // Update Angle (Simulating 400Hz rotation)
        angle += 1.0; 
        if (angle >= 360) angle = 0;

        SDL_RenderPresent(this->renderer);
        SDL_Delay((1/frequency) * 1000); // Control speed
    }
}