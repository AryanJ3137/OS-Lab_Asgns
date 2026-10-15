#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f, i, j, k;
    int faults = 0, hits = 0;
    int time[10], counter = 0;
    int found, lru;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++) {
        found = 0;

      for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                hits++;
                time[j] = ++counter;
                break;
            }
        }

        if (!found) {
            faults++;

            // Find an empty frame
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    break;
                }
            }

            if (j == f) {
                lru = 0;

                for (k = 1; k < f; k++) {
                    if (time[k] < time[lru]) {
                        lru = k;
                    }
                }

                j = lru;
            }

            frames[j] = pages[i];
            time[j] = ++counter;
        }

        printf("%d\t", pages[i]);

        for (j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found)
            printf("\tHit\n");
        else
            printf("\tPage Fault\n");
    }

    printf("\nTotal Page Hits: %d\n", hits);
    printf("Total Page Faults: %d\n", faults);

    return 0;
}
