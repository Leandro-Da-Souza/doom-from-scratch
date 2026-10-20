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

    // game loop
    bool is_game_running = true;

    while (is_game_running)
    {
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

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}