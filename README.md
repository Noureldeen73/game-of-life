# Game of Life with Multithreading

This program simulates the "Game of Life" cellular automaton using multithreading in C. It uses pthreads to divide the computation of generations across multiple threads, improving performance and scalability. The grid is updated in parallel, and the program prints the grid for each generation.

## Features

- **Grid Size**: The grid is 20x20.
- **Multithreading**: The program uses 4 threads to compute the next generation concurrently.
- **Generations**: The simulation runs for 32 generations.
- **Patterns**: The grid is initialized with a combination of still life (square), oscillator (blinker), and spaceship (glider) patterns.
- **Cellular Automaton Rules**: 
    - Any live cell with two or three live neighbors survives.
    - Any dead cell with exactly three live neighbors becomes alive.
    - All other live cells die, and all other dead cells remain dead.
- **Barrier Synchronization**: Pthreads barrier ensures that all threads synchronize at the right time to update the grid correctly.

## Requirements

- GCC or any C compiler with pthread support
- POSIX threads library

## How It Works

1. **Initialization**:
   - The grid is initialized with predefined patterns, including still life, blinker, and glider.
   
2. **Multithreading**:
   - The grid is divided into 4 sections, each handled by a separate thread.
   - Each thread calculates the next generation based on the current state of the grid, following the Game of Life rules.

3. **Synchronization**:
   - A barrier is used to synchronize all threads at key points in the program. The barrier ensures that all threads finish computing their part before any thread can update the grid with the newly computed values.

4. **Grid Updates**:
   - Once all threads have calculated the next generation, the barrier waits for all threads to finish before the grid is updated.
   
5. **Display**:
   - After each generation, the grid is printed to the console. Dead cells are shown as spaces, and live cells are shown as `#`. The screen is cleared before each print to show the current state.

## Compilation

To compile the program, use the following command:

```
gcc -o game_of_life game_of_life.c -pthread

## Running the Program

To run the program, simply execute the compiled binary:

```

## Code Structure

- **`print_grid()`**: Clears the screen and prints the grid.
- **`is_valid()`**: Checks if the given grid coordinates are within bounds.
- **`compute_next_gen()`**: Computes the next generation of the grid using the Game of Life rules.
- **`initialize_grid()`**: Initializes the grid to all dead cells.
- **`initialize_patterns()`**: Initializes the grid with predefined patterns (still life, blinker, glider).
- **`main()`**: Initializes the grid, creates threads, and starts the simulation.

## Example Output

```
##      
##           

       
   #  
   #  
   #  
         
         
            #  
             # 
           ###
         
         
```

## Future Improvements

- **Dynamic Grid Size**: Allow users to specify the grid size and number of generations.
- **Pattern Variations**: Add more patterns to initialize the grid.
- **Performance Optimization**: Use more threads or better synchronization mechanisms to handle larger grids more efficiently.
```
