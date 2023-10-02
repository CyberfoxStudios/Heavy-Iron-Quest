#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // for getch() in Windows, or use ncurses for Unix-like systems
#include <time.h>

// Define constants for grid dimensions and game states
#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10
#define IRON 'I'
#define ENEMY 'E'
#define PLAYER 'X'
//Adjust as needed
#define TARGET_SCORE 10
#define IRON_AMT 12
#define ENEMY_AMT 8

// Function to initialize the game grid
char** initializeGrid(int width, int height);

// Function to randomly scatter iron and enemies on the grid
void scatterObjects(char** grid);

// Function to display the game grid & state
void renderGrid(char** grid, int gridScore);

// Function to move the player and update game state
void movePlayer(char** grid, int* playerX, int* playerY, int* playerScore);

// Function to check for game over conditions
int isGameOver(int score);

int main() {
    char** grid = initializeGrid(GRID_SIZE_X, GRID_SIZE_Y);
    int playerX = 0;
    int playerY = 0;
    int score = 0;

    // Seed the random number generator
    srand(time(NULL));

    scatterObjects(grid);

    renderGrid(grid, score); //testing only!
    /*while (!isGameOver(score)) {
        //system("clear");  // Use "cls" for Windows
        //renderGrid(grid, score);
        //movePlayer(grid, &playerX, &playerY, &score);
    }*/

    if (score >= TARGET_SCORE) {
        printf("Congratulations! You won Heavy Iron Quest!\n");
    } else {
        printf("Game over. You encountered an enemy.\n");
    }

    // Clean up memory
    for (int i = 0; i < GRID_SIZE_X; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}

// Function to initialize the game grid
char** initializeGrid(int width, int height) {
    // Allocate memory for the grid 
    // Note: Using sizeof(char) for easy type flexibility if needed later.
    // Since sizeof(char) is 1, could be omitted for minor efficiency.

    char** grid = (char**)malloc(width * sizeof(char*));
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE); // Handle allocation failure
    }

    for (int row = 0; row < width; row++) {
        grid[row] = (char*)malloc((height + 1) * sizeof(char)); // +1 for the null terminator
        if (grid[row] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE); // Handle allocation failure
        }
    }

    // Initialize the grid elements as blank spaces
    for (int row = 0; row < width; row++) {
        for (int column = 0; column < height; column++) {
            *(grid[row] + column) = ' ';
        }
    }

    // Player starts in the middle
    *(grid[(height - 1) / 2] + ((width - 1) / 2)) = 'P';

    return grid;
}

// Function to randomly scatter iron and enemies on the grid
void scatterObjects(char** grid)
{
    // Scatter Iron ('I') on the grid
    for(int ironLoop = 0; ironLoop < IRON_AMT; ironLoop++)
    {
        // Generate random coordinates within the grid
        int x, y;
        do {
            x = rand() % GRID_SIZE_X;
            y = rand() % GRID_SIZE_Y;
        } while (grid[y][x] != ' ');

        // Ensure the cell is empty, add iron
        grid[y][x] = IRON;
    }

    // Scatter Enemies ('E') on the grid
    for(int enemyLoop = 0; enemyLoop < ENEMY_AMT; enemyLoop++)
    {
        // Generate random coordinates within the grid
        int x, y;
        do {
            x = rand() % GRID_SIZE_X;
            y = rand() % GRID_SIZE_Y;
        } while (grid[y][x] != ' ');

        // Ensure the cell is empty, add enemy
        grid[y][x] = ENEMY;
    }
}

// Function to display the game grid & state
void renderGrid(char** grid, int gridScore) {
    printf("H E A V Y I R O N !\n"); // Title

    // Grid
    for (int row = 0; row < GRID_SIZE_X; row++) {
        for (int column = 0; column < GRID_SIZE_Y; column++) {
            printf("%c ", *(grid[row] + column * sizeof(char)));
        }
        puts(""); // End of row
    }

    printf("Score: %d out of %d\n", gridScore, TARGET_SCORE); // Score
}

// Implement movePlayer, and isGameOver functions
// ...
