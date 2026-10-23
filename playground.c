#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Vector;

typedef struct {
    Vector position;
    float speed;
} Player;

typedef struct {
    int w, a, s, d;
} Keys;


void print_vector(const Vector *v) {
    printf("(%.2f, %.2f)\n", v->x, v->y);
}

float magnitude(Vector v) {
    return sqrtf((v.x * v.x) + (v.y * v.y));
}

Vector normalize_vector(Vector v, float length) {
    if (length > 0.0f) {
        v.x /= length;
        v.y /= length;
    }

    return v;
}

Vector calculate_movement(Vector direction, float speed, float dt) {
    Vector movement_vector = { 
        (direction.x * speed * dt), 
        (direction.y * speed * dt) 
    };
    return movement_vector;
}

Vector subtract_vector(Vector a, Vector b) {
    Vector subtracted = { a.x - b.x, a.y - b.y };
    return subtracted;
}

void apply_movement(Player *player, Vector movement) {
    player->position.x += movement.x;
    player->position.y += movement.y;
}

void calculate_direction(Keys k, Vector *direction) {
    direction->x = 0.0f;
    direction->y = 0.0f;

    if (k.w) {
        direction->y -= 1;
    }

    if (k.s) {
        direction->y += 1;
    }

    if (k.d) {
        direction->x += 1;
    }

    if (k.a) {
        direction->x -= 1;
    }
    
}

int main (void) {
    Player goblin = {
        .position = {100.0f, 100.0f},
        .speed = 200.0f
    };

    // simulate current keyboard event, press a and d
    Keys keyboard = {
        .w = 1,
        .a = 0,
        .s = 0,
        .d = 1
    };

    Vector direction = {0.0f, 0.0f};

    calculate_direction(keyboard, &direction);

    float dt = 0.016f;

    float length = magnitude(direction);

    Vector normalized_direction = normalize_vector(direction, length);

    for (int frame = 0; frame < 60; frame++) {
        Vector movement = calculate_movement(
                normalized_direction,
                goblin.speed,
                dt
        );

        apply_movement(&goblin, movement);
    }

    print_vector(&goblin.position);

    return 0;
}