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
}*/

#endif