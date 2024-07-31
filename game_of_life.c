// ***************************************************************************************
//    Project: Conway's Game of Life in Console using C
//    File: game_of_life.c
//    Date: 2024-07-31
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https:www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: Read the readme file for more information
// ***************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////////////////////////
/////// CROSS-PLATFORM CONFIGURATIONS
//////////////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define CLEAR "cls"
#define wait(x) Sleep(x)
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#define CLEAR "clear"
#define wait(x) usleep(x * 1000)
#endif

//////////////////////////////////////////////////////////////////////////////////////////
/////// GAME RELATED MACROS AND TYPES
//////////////////////////////////////////////////////////////////////////////////////////
#define ALIVE '#'
#define DEAD '.'

typedef char** Grid;
#define make_grid(GRID_NAME) Grid GRID_NAME = malloc(rows * sizeof(char*))

//////////////////////////////////////////////////////////////////////////////////////////
/////// FUNCTION DECLARATIONS
//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Renders the grid on the screen
 *
 * @param grid the pointer to the 2D-Array of the grid
 * @param rows total number of rows
 * @param cols total number of columns
 */
void print_grid(Grid grid, int rows, int cols);

/**
 * @brief Updates the grid per frame (milliseconds enters by the user)
 *
 * @param grid the pointer to the 2D-Array of the grid
 * @param new_grid the pointer to the updated version of the grid
 * @param rows total number or rows
 * @param cols total number of columns
 */
void update_grid(Grid grid, Grid new_grid, int rows, int cols);

/**
 * @brief Counts the neighbors at given x and y of the grid
 *
 * @param grid the pointer to the 2D-Array of the grid
 * @param x the row of the point to be checked
 * @param y the column of the point to be checked
 * @param rows total number of rows
 * @param cols total number of columns
 */
int count_neighbors(Grid grid, int x, int y, int rows, int cols);

/**
 * @brief Initializes the allocated grid with `DEAD` cells
 *
 * @param grid the pointer to the 2D-Array of the grid
 * @param rows total number of rows
 * @param cols total number of columns
 */
void initialize_grid(Grid grid, int rows, int cols);

/**
 * @brief Copys the grid data from one to another
 *
 * @param source
 * @param destination
 * @param rows total number of rows
 * @param cols total number of columns
 */
void copy_grid(Grid source, Grid destination, int rows, int cols);

/**
 * @brief Wrapper for keyboard press event for supporting both Windows and POSIX OSes
 */
int kbhit();

//////////////////////////////////////////////////////////////////////////////////////////
/////// MAIN LOOP
//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    puts("Conway's Game of Life in C");
    puts("Implemented by Navid Dezashibi");
    puts("Version 1.0.0");
    printf("Compiled on %s - %s\n", __DATE__, __TIME__);

    int rows, cols, x, y;
    char choice;

    printf("%s", "Enter the number or rows: ");
    scanf("%d", &rows);

    printf("%s", "Enter the number of columns: ");
    scanf("%d", &cols);

    // Allocate memory for grids
    make_grid(grid);
    make_grid(new_grid);

    if (grid == NULL || new_grid == NULL)
    {
        fprintf(stderr, "Allocation for 'grid' or 'new_grid' failed, error location '%s:%d'", __FILE__, __LINE__);
        if (grid)
            free(grid);
        if (new_grid)
            free(new_grid);

        exit(EXIT_FAILURE);
    }

    // Allocate memory for each row of grid and new_grid
    for (x = 0; x < rows; ++x)
    {
        grid[x] = malloc(cols * sizeof(char));
        if (grid[x] == NULL)
        {
            fprintf(stderr, "Allocation for 'grid''s row #%d failed, error location '%s:%d'", x, __FILE__, __LINE__);
            exit(EXIT_FAILURE);
        }

        new_grid[x] = malloc(cols * sizeof(char));
        if (new_grid[x] == NULL)
        {
            fprintf(stderr, "Allocation for 'new_grid''s row #%d failed, error location '%s:%d'", x, __FILE__, __LINE__);
            exit(EXIT_FAILURE);
        }
    }

    // Let user to pre-config the grid if they want to
    puts("Do you want to input the initial configuration? (y/anything else=default)");
    printf("%s", "> ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        puts("Enter the initial configuration:");
        for (x = 0; x < rows; ++x)
        {
            for (y = 0; y < cols; ++y)
            {
            repeat:
                printf("at %d, %d -> ", x, y);
                scanf(" %c", &grid[x][y]);

                if (&grid[x][y] != DEAD || &grid[x][y] != ALIVE)
                {
                    if (strlen(grid[x][y]) == 0)
                    {
                        grid[x][y] = DEAD;
                        continue;
                    }
                }

                printf("Not a possible value, please enter '%c' for dead or '%c' for alive cells only", DEAD, ALIVE);
                goto repeat;
            }
        }
    }
    else
    {
        // randomly populate the grid with dead or alive cells
        srand(time(NULL));
        for (x = 0; x < rows; ++x)
        {
            for (y = 0; y < cols; ++y)
            {
                grid[x][y] = (rand() % 2) ? ALIVE : DEAD;
            }
        }
    }

    int delay;
    printf("%s", "Enter the delay between generations in milliseconds (100 as an example): ");
    scanf("%d", &delay);

    puts("Press Enter to start the simulation...");
    puts("You can press 'q' at anytime to end the simulation");
    getchar();
    getchar();

    while (1)
    {
        system(CLEAR); // clean the screen
        print_grid(grid, rows, cols);
        update_grid(grid, new_grid, rows, cols);
        wait(delay);

        // check for 'q' press to end the simulation
        if (kbhit())
        {
            char ch = getchar();
            if (ch == 'q' || ch == 'Q')
                break;
        }
    }

    // Cleanup memory
    for (x = 0; x < rows; ++x)
    {
        free(grid[x]);
        free(new_grid[x]);
    }

    free(grid);
    free(new_grid);

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
/////// FUNCTION IMPLEMENTATIONS
//////////////////////////////////////////////////////////////////////////////////////////
