#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_FRect player = {
        .x = 100,
        .y = 100,
        .w = 40,
        .h = 40    
    };

    win = SDL_CreateWindow(
        "DOOM from scratch",
        800,
        800,
        SDL_WINDOW_RESIZABLE
    );

    if (win == NULL) {
        fprintf(stderr, "Window error: %s \n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(
        win,
        NULL
    );

    if (renderer == NULL) {
        fprintf(stderr, "Renderer error: %s \n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    bool is_game_running = true;
    Uint64 last_time = SDL_GetTicks();
    float speed = 200.0f;

    while (is_game_running)
    {
        Uint64 current_time = SDL_GetTicks();
        float dt = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                printf("Quit event received!\n");
                is_game_running = false;
                break;
            default:
                break;
            }
        }

        player.x += speed * dt;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        SDL_RenderFillRect(renderer, &player);

        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}