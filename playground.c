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

int main (void) {
    Player goblin = {
        .position = {100.0f, 100.0f},
        .speed = 200.0f
    };
    // random direction, 
    Vector direction = {3.0f, 4.0f};

    float dt = 0.5f;

    float length = magnitude(direction);

    Vector normalized_direction = normalize_vector(direction, length);

    Vector movement = calculate_movement(
        normalized_direction,
        goblin.speed,
        dt
    );

    apply_movement(&goblin, movement);

    print_vector(&goblin.position);

    return 0;
}