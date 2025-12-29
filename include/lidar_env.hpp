#ifndef LIDAR_ENV_HPP
#define LIDAR_ENV_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <limits>
#include "lidar_single_beam.hpp"


#define WIDTH 800
#define HEIGHT 600

struct Vec2 { double x, y; };
class Lidar;

class LidarEnv 
{
    public:
        LidarEnv(Lidar *lidar = nullptr);

        ~LidarEnv(){
            SDL_DestroyRenderer(this->renderer);
            SDL_DestroyWindow(this->window);
            SDL_Quit();
        };

        void startRenderLoop(Lidar *lidar);
        
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Lidar *lidar;


};

/*
float getRayDistance(Vec2 rayOrigin, Vec2 rayDir, SDL_Rect target) {
    double tMin = (target.x - rayOrigin.x) / rayDir.x;
    double tMax = (target.x + target.w - rayOrigin.x) / rayDir.x;

    if (tMin > tMax) std::swap(tMin, tMax);

    double tyMin = (target.y - rayOrigin.y) / rayDir.y;
    double tyMax = (target.y + target.h - rayOrigin.y) / rayDir.y;

    if (tyMin > tyMax) std::swap(tyMin, tyMax);

    // If intervals don't overlap, no hit
    if ((tMin > tyMax) || (tyMin >> tMax)) return -1.0f;

    if (tyMin > tMin) tMin = tyMin;
    
    // Return distance if within sensor range
    return (tMin > 0) ? static_cast<float>(tMin) : -1.0f;
}

float checkCollision(float rayX, float rayY, float dirX, float dirY, const Rect& box) {
    // Basic Ray-to-AABB intersection math
    float t1 = (box.minX - rayX) / dirX;
    float t2 = (box.maxX - rayX) / dirX;
    float t3 = (box.minY - rayY) / dirY;
    float t4 = (box.maxY - rayY) / dirY;

    float tmin = std::max(std::min(t1, t2), std::min(t3, t4));
    float tmax = std::min(std::max(t1, t2), std::max(t3, t4));

    if (tmax < 0 || tmin > tmax) return -1.0f; // No hit
    return tmin; // Distance to the hit point
}


// Inside your while(running) loop:
SDL_Rect obstacle = { 600, 250, 50, 100 }; // A "wall" or "pole"
SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green obstacle
SDL_RenderFillRect(renderer, &obstacle);

// Calculate direction vector from angle
Vec2 dir = { cos(angle * M_PI / 180.0), sin(angle * M_PI / 180.0) };
Vec2 origin = { 400.0, 300.0 };

float dist = getRayDistance(origin, dir, obstacle);

if (dist > 0 && dist < beamMaxRange) {
    // We hit something! Draw a smaller beam and a point
    int hitX = origin.x + dir.x * dist;
    int hitY = origin.y + dir.y * dist;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White point
    SDL_RenderDrawLine(renderer, origin.x, origin.y, hitX, hitY);
} else {
    // No hit, draw full range beam in dim red
}
*/

#endif