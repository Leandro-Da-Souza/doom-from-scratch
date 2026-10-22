#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Vector;

void print_vector(const Vector *v) {
    printf("(%.0f, %.0f)\n", v->x, v->y);
}

float magnitude(Vector v) {
    return sqrtf((v.x * v.x) + (v.y * v.y));
}

Vector normalize_vector(Vector v) {
    float length = magnitude(v);

    if (length > 0.0f) {
        v.x /= length;
        v.y /= length;
    }

    return v;
}

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

    float movement = magnitude(
        subtract_vector(goblin, start)
    );

    printf("Magnitude is: %.2f", movement);

    return 0;
}