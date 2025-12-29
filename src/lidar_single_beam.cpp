#include "../include/lidar_single_beam.hpp"

LidarEnv::LidarEnv(Lidar *lidar): lidar(lidar)
{
    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow("LiDAR Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
     this->renderer= SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
     this->lidar = lidar;
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
    SDL_Rect Obj;
    Obj.x = 150;
    Obj.y = 150;
    Obj.w = 75;
    Obj.h = 75;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        // Clear screen (Black)
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);

        // Calculate Beam End Point
        int startX = 400, startY = 300;
        int endX = startX + static_cast<int>(range * cos(angle * M_PI / 180.0));
        int endY = startY + static_cast<int>(range * sin(angle * M_PI / 180.0));

        // Draw Beam (Red)
        SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(this->renderer, startX, startY, endX, endY);

        SDL_RenderDrawRect(this->renderer, nullptr); // Draw border

         SDL_SetRenderDrawColor( this->renderer, 0, 0, 255, 255 );

    // Render rect
        SDL_RenderFillRect( this->renderer, &Obj );

        // Render the rect to the screen
        SDL_RenderPresent(this->renderer);

        // Update Angle (Simulating 400Hz rotation)
        angle += 1.0; 
        if (angle >= 360) angle = 0;

        SDL_RenderPresent(this->renderer);
        SDL_Delay(1); // Control speed
    }
}