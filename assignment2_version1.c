#include <stdio.h>
#include <omp.h>

#define N 100         // Size of array
#define NUM_THREADS 10 // Number of processors (1 <= NUM_THREADS <= 12)

void sumChecker(int sum);

int main()
{
    int A[N];
    int Sum[NUM_THREADS] = {0}; // Initialize sum array

    // Initialize array A with their respective indices
    for (int i = 0; i < N; i++)
    {
        A[i] = i;
    }

    // Phase 1: Each processor calculates its local sum
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num(); // Get the thread ID
        int local_sum = 0;              // Local sum for each thread

        // Determine the subarray each thread works on
        int chunk_size = N / NUM_THREADS;
        int start = tid * chunk_size;
        int end = start + chunk_size;

        // Calculate local sum
        for (int i = start; i < end; i++)
        {
            local_sum += A[i];
        }

        // Store local sum in Sum[tid]
        Sum[tid] = local_sum;
    }

    int temp_sum = 0;
    // Phase 2 (Version 1): Processor 0 adds all local sums
    printf("Version 1: Processor 0 collects all sums\n");
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp single
        {
            // store sum[0] in a global variable
            temp_sum = Sum[0];
            for (int i = 1; i < NUM_THREADS; i++)
            {
                Sum[0] += Sum[i];
            }
        }
    }

    printf("Global Sum (Version 1): %d\n", Sum[0]);
    sumChecker(Sum[0]);
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
