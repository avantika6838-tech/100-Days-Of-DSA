#include <stdio.h>
#include <stdlib.h>

// Structure for car
struct Car {
    int position;
    int speed;
};

// Comparator: sort by position descending
int compare(const void *a, const void *b) {
    return ((struct Car *)b)->position - ((struct Car *)a)->position;
}

// Function to calculate car fleets
int carFleet(int target, int position[], int speed[], int n) {
    struct Car cars[n];

    // Step 1: Combine position and speed
    for (int i = 0; i < n; i++) {
        cars[i].position = position[i];
        cars[i].speed = speed[i];
    }

    // Step 2: Sort by position descending
    qsort(cars, n, sizeof(struct Car), compare);

    int fleets = 0;
    float lastTime = 0.0;

    // Step 3: Traverse cars
    for (int i = 0; i < n; i++) {
        float time = (float)(target - cars[i].position) / cars[i].speed;

        if (time > lastTime) {
            fleets++;           // new fleet
            lastTime = time;    // update max time
        }
        // else joins existing fleet
    }

    return fleets;
}

// Driver code
int main() {
    int target = 12;
    int position[] = {10, 8, 0, 5, 3};
    int speed[] = {2, 4, 1, 1, 3};
    int n = sizeof(position) / sizeof(position[0]);

    printf("Number of car fleets = %d\n", carFleet(target, position, speed, n));

    return 0;
}
