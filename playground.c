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

// float calculate_movement(float *direction, float speed, float dt) {}

Vector subtract_vector(Vector a, Vector b) {
    Vector subtracted = { a.x - b.x, a.y - b.y };
    return subtracted;
}

int main (void) {
    Vector start = {100.0f, 100.0f};
    Vector goblin = start;

    goblin.x -= 30;
    goblin.y += 40;

    print_vector(&goblin);

    // Where did the bastarad go to? 
    Vector displacement = subtract_vector(goblin, start);

    // How far did the bastard travel?
    float distance = magnitude(displacement);

    // which direction did the bastard go?
    Vector direction = normalize_vector(displacement, distance);

    print_vector(&direction);

    return 0;
}