# Conway's Game of Life in Console using C

A console-based implementation of Conway's Game of Life in C, works both on Windows and Linux.

The approach for this project as it's more like a university assignments, interesting but boring at the same time!

So I've decided to put words together as a form of User's story so that reading this also can be helpful as well.

It's a one file project just compile it and run it, that's all, read the descriptions below and in the code indeed.

---

**As a** software developer,

**I want to** create a console-based implementation of Conway's Game of Life in C,

**So that** users can observe the evolution of cellular automata based on simple rules.

## Acceptance Criteria

1. **Initialization:**
    - Users can input the dimensions of the grid (rows and columns).
    - Users can input an initial configuration of live cells or choose a random configuration.
2. **Display:**
    - The grid is displayed in the console, with live cells represented by a character (e.g., `#`) and dead cells by another character (e.g., `` or `.`).
    - The grid updates in real-time to show the evolution of the cells.
3. **Rules Implementation:**
    - Any live cell with fewer than two live neighbors dies (under-population).
    - Any live cell with two or three live neighbors lives on to the next generation.
    - Any live cell with more than three live neighbors dies (over-population).
    - Any dead cell with exactly three live neighbors becomes a live cell (reproduction).
4. **Iteration:**
    - The game progresses through generations with a user-defined delay between updates.
    - Users can pause and resume the simulation.
5. **Termination:**
    - Users can stop the simulation at any time.
    - The program gracefully exits when the simulation is terminated.

## Expected Result

- A functional implementation of Conway's Game of Life in C, running in the console.
- The game should accurately follow the defined rules and visually represent the evolution of the cellular automata.
- Users should be able to start, pause, and stop the simulation at will.

## Implementation

1. **Grid Representation:**
    - Use a 2D array to represent the grid.
    - Consider using a secondary grid to store the next generation of cells while computing the current generation.
2. **Input Handling:**
    - Use standard input functions to read the grid dimensions and initial configuration.
    - Provide an option for random initialization of the grid.
3. **Display Function:**
    - Write a function to print the grid to the console.
    - Clear the console screen between generations to create the illusion of animation:
        - For Unix-based systems (Linux, macOS): `system("clear")`
        - For Windows: `system("cls")`
4. **Game Logic:**
    - Write a function to count the live neighbors of a cell.
    - Implement the rules in a function that updates the grid for the next generation.
5. **Control Flow:**
    - Use a loop to progress through generations, with a sleep/delay function to control the speed:
        - For Unix-based systems (Linux, macOS): `usleep` or `nanosleep`
        - For Windows: `Sleep`
    - Implement pause and resume functionality by checking user input within the loop.
6. **Edge Cases:**
    - Handle edge cells properly by considering different boundary conditions (e.g., wrapping around, fixed boundaries, or extra border of dead cells).
7. **Testing:**
    - Test with various initial configurations to ensure the rules are correctly implemented.
    - Include well-known patterns like the "glider" or "blinker" to verify the game's behavior.
