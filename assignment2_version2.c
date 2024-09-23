#include <stdio.h>
#include <omp.h>

#define N 100         // Size of array
#define NUM_THREADS 10 // Number of threads

void sumChecker(int sum);

int main() {
    int A[N];
    int sum[NUM_THREADS] = {0}; // Initialize sum array

    // Fill the array with their indices
    for (int i = 0; i < N; i++) {
        A[i] = i;
    }

    // Phase 1: Each processor calculates its local sum
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        int local_sum = 0; // Local variable for reduction

        #pragma omp for
        for (int k = 0; k < N; k++) {
            local_sum += A[k];
        }

        sum[ID] = local_sum; // Store the local sum in the sum array
        printf("id: %d, sum: %d\n", ID, sum[ID]);

        // add all the local sums to sum[0]
        #pragma omp for
        for (int j = 1; j < NUM_THREADS; j++) {
            sum[0] += sum[j];
        }
    }

    printf("Global Sum (Version 2): %d\n", sum[0]);
    sumChecker(sum[0]);
    return 0;
}

// Function to check if the total sum is equal to 
// the sum of the first N natural numbers
void sumChecker(int sum)
{
    if (sum == (N * (N - 1)) / 2)
    {
        printf("\033[0;32m");
        printf("The total sum is equal to the sum of the first %d natural numbers\n", N);
        printf("\033[0m");
    }
    else
    {
        printf("\033[0;31m");
        printf("The total sum is not equal to the sum of the first %d natural numbers\n", N);
        printf("\033[0m");
    }
}
