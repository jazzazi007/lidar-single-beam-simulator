#include "../include/lidar_single_beam.hpp"


int main() 
{
    std::cout<< "Starting LiDAR Single Beam Simulator"<<std::endl;
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("LiDAR Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    double angle = 0;
    const double range = 200.0;
    double i = 0;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        // Clear screen (Black)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect r;
        r.x = 150;
        r.y = 150;
        r.w = 150;
        r.h = 150;

        // Calculate Beam End Point
        int startX = 400, startY = 300;
        int endX = startX + static_cast<int>(range * cos(angle * M_PI / 180.0));
        int endY = startY + static_cast<int>(range * sin(angle * M_PI / 180.0));

        // Draw Beam (Red)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, startX, startY, endX, endY);

        SDL_RenderDrawRect(renderer, nullptr); // Draw border

         SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    // Render rect
        SDL_RenderFillRect( renderer, &r );

        // Render the rect to the screen
        SDL_RenderPresent(renderer);

        // Update Angle (Simulating 400Hz rotation)
        angle += 1.0; 
        if (angle >= 360) angle = 0;

        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Control speed
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}