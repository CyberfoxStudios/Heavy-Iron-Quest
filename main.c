#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // for getch() in Windows, or use ncurses for Unix-like systems
#include <time.h>
#include <ctype.h>

// Define constants for grid dimensions and game states
#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10
#define IRON 'I'
#define ENEMY 'E'
#define PLAYER 'X'
#define PLAYER_START_X 4
#define PLAYER_START_Y 4
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
    int playerX = PLAYER_START_X;
    int playerY = PLAYER_START_Y;
    int score = 0;

    // Seed the random number generator
    srand(time(NULL));

    scatterObjects(grid);

    //while (!isGameOver(score)) {
    while(1){
        printf("\e[1;1H\e[2J"); //clear the screen
        renderGrid(grid, score);
        movePlayer(grid, &playerX, &playerY, &score);
    }

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
    grid[PLAYER_START_Y][PLAYER_START_X] = 'P';

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

// Function to move the player and update game state
void movePlayer(char** grid, int* playerX, int* playerY, int* playerScore) {
    //get input
    printf("Enter a direction (W/A/S/D): ");
    char moveDirection = getchar();
    while (getchar() != '\n'); // Clear input buffer
    moveDirection = tolower(moveDirection); //from ctype.h, allows upper or lower input

    //Save current pos for clearing after boundary check
    int oldX = *playerX;
    int oldY = *playerY;

    // Calculate the new position based on the input
    switch (moveDirection)
    {
        case 'w':
            (*playerY)--;
            break;
        
        case 'a':
            (*playerX)--;
            break;
        
        case 's':
            (*playerY)++;
            break;

        case 'd':
            (*playerX)++;
            break;
        
        default:
            printf("Invalid input. Please enter W, A, S, or D.\n");
            break;
    }

    // Check if the new position is within the bounds of the grid
    if(0 <= *playerX && *playerX < GRID_SIZE_X && 0 <= *playerY && *playerY < GRID_SIZE_Y)
    {
        
        // Check what's in the new position
        char foundSomething = grid[*playerY][*playerX];
            // Player collects iron
            if(foundSomething == 'I')
                (*playerScore)++;
            // Player encounters an enemy (game over)
            if(foundSomething == 'E')
            {
                printf("The enemy got you! GAME OVER\n");
                exit(0);
            }
    
        // Update the grid and player's position
        grid[oldY][oldX] = ' ';
        grid[*playerY][*playerX] = 'P';
    }
    
    // Player tried to move out of bounds
    else 
    {
        *playerX = oldX;
        *playerY = oldY;
        printf("Out of bounds. Please come back!\n");
    }
}

// Implement movePlayer, and isGameOver functions
// ...
