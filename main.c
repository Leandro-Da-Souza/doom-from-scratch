#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Vector;

typedef struct {
    SDL_FRect rect;
    float speed;
} Player;

void move(Player *player, Vector direction, float delta) {
    player->rect.x += direction.x * player->speed * delta;
    player->rect.y += direction.y * player->speed * delta;
}

void vector_normalize(Vector *v) {
    float length = sqrtf(v->x * v->x + v->y * v->y);

    if (length > 0.0f) {
        v->x /= length;
        v->y /= length;
    }
}

float calculate_delta_time (Uint64 *last_time) {
    Uint64 current_time = SDL_GetTicks();

    float dt = (current_time - *last_time) / 1000.0f;
    *last_time = current_time;

    return dt;
}

void read_movement_input (Vector *v) {
    const bool *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_D]) {
        v->x += 1.0f;
    }

    if (keys[SDL_SCANCODE_A]) {
        v->x -= 1.0f;
    }

    if (keys[SDL_SCANCODE_W]) {
        v->y -= 1.0f;
    }

    if (keys[SDL_SCANCODE_S]) {
        v->y += 1.0f;
    }
}

int main(void) {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    Player goblin = {
        .rect = {
            .x = 100.0f,
            .y = 100.0f,
            .w = 40.0f,
            .h = 40.0f,
        },
        .speed = 200.0f
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

        float dt = calculate_delta_time(&last_time);

        Vector direction = { 0.0f, 0.0f };

        read_movement_input(&direction);

        vector_normalize(&direction);

        move(&goblin, direction, dt);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        SDL_RenderFillRect(renderer, &goblin.rect);

        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}