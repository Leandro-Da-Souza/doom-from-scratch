#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Vector;

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

int main (void) {
    float speed = 200.0f;
    // Delta time (dt): seconds elapsed between two frames.
    // Multiplying speed (pixels/second) by dt gives us
    // how many pixels to move during that frame.
    // Fixed at 0.5 seconds here for testing; measured in a real game.
    float dt = 0.5f;
    Vector start = {100.0f, 100.0f};
    Vector goblin = start;

    goblin.x -= 30;
    goblin.y += 40;

    print_vector(&goblin);

    // Where did the bastarad go to? 
    Vector displacement = subtract_vector(goblin, start);

    // How far did the bastard travel?
    float distance = magnitude(displacement);

    // Which direction did the bastard go?
    Vector direction = normalize_vector(displacement, distance);

    // Get the bastards movement.
    Vector movement = calculate_movement(
        direction,
        speed,
        dt
    );

    print_vector(&movement);

    return 0;
}