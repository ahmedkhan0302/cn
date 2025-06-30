#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 10
#define WINDOW 4

int main() {
    int i = 0;
    srand(time(0));

    printf("Go-Back-N Sliding Window Simulation\n");

    while (i < TOTAL) {
        int end = i + WINDOW;
        if (end > TOTAL) end = TOTAL;

        printf("\nSending frames: ");
        for (int j = i; j < end; j++)
            printf("%d ", j);

        int loss = i + rand() % (end - i);  // random loss within window
        printf("\nSimulated loss at frame %d", loss);

        printf("\nReceiver got: ");
        for (int j = i; j < loss; j++)
            printf("%d ", j);

        printf("\nACK sent till frame %d\n", loss - 1);
        i = loss;  // Go back to lost frame
    }

    return 0;
}
