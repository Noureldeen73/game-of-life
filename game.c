#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GRID_SIZE 20
#define NUM_THREADS 4
#define GENERATIONS 32

int grid[GRID_SIZE][GRID_SIZE];
int next_gen[GRID_SIZE][GRID_SIZE];
pthread_barrier_t barrier;

typedef struct
{
    int start;
    int end;
} thread_args;

void print_grid()
{
    system("clear");
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] == 1)
            {
                printf("# ");
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
    usleep(500000);
}

__uint8_t is_valid(int i, int j)
{
    if (i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE)
    {
        return 'T';
    }
    return 'F';
}
// Function to compute next generation of Game of Life
void *compute_next_gen(void *arg)
{
    thread_args *args = (thread_args *)arg;
    int start = args->start;
    int end = args->end;
    int xval[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int yval[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < GENERATIONS; i++)
    {
        for (int i = start; i < end; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                int alive = 0;
                for (int k = 0; k < 8; k++)
                {
                    int ni = i + xval[k];
                    int nj = j + yval[k];
                    if (is_valid(ni, nj) == 'T' && grid[ni][nj] == 1)
                    {
                        alive++;
                    }
                }
                if (grid[i][j] == 0)
                {
                    if (alive == 3)
                    {
                        next_gen[i][j] = 1;
                    }
                }
                if (grid[i][j] == 1)
                {
                    if (alive == 2 || alive == 3)
                    {
                        next_gen[i][j] = 1;
                    }
                    else
                    {
                        next_gen[i][j] = 0;
                    }
                }
            }
        }
        pthread_barrier_wait(&barrier);
        for (int i = start; i < end; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                grid[i][j] = next_gen[i][j];
            }
        }
        pthread_barrier_wait(&barrier);
        if (start == 0)
            print_grid();
    }
}

void initialize_grid(int grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = 0; // Set every cell to 0 (dead)
        }
    }
}
void initialize_patterns(int grid[GRID_SIZE][GRID_SIZE])
{

    initialize_grid(grid);

    // Initialize Still Life (Square) at top-left
    grid[1][1] = 1;
    grid[1][2] = 1;
    grid[2][1] = 1;
    grid[2][2] = 1;

    // Initialize Oscillator (Blinker) in the middle
    grid[5][6] = 1;
    grid[6][6] = 1;
    grid[7][6] = 1;

    // Initialize Spaceship (Glider) in the bottom-right
    grid[10][10] = 1;
    grid[11][11] = 1;
    grid[12][9] = 1;
    grid[12][10] = 1;
    grid[12][11] = 1;
}

int main()
{
    initialize_patterns(grid);
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    pthread_t threads[NUM_THREADS];
    thread_args args[NUM_THREADS];

    for (int i = 0, t = 0; i < GRID_SIZE; t++, i += 5)
    {
        args[t].start = i;
        args[t].end = i + 5;
        pthread_create(&threads[t], NULL, compute_next_gen, &args[t]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_barrier_destroy(&barrier);
    return 0;
}
