#include <iostream>
#include <conio.h>  // For _kbhit() and _getch()
#include <cstdlib>  // For rand()
#include <windows.h>

#define WIDTH 50  // Columns
#define HEIGHT 25 // Rows

#define STOP 0
#define LEFT -1
#define RIGHT 1
#define UP -2
#define DOWN 2

using namespace std;

bool gameOver;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
int direction;

void SpawnFood() {
    bool valid;
    do {
        valid = true;
        foodX = (rand() % (WIDTH - 2)) + 1;
        foodY = (rand() % (HEIGHT - 2)) + 1;

        // Make sure food doesn't spawn on the snake's body
        if (foodX == x && foodY == y) valid = false;
        for (int i = 0; i < nTail; i++) {
            if (foodX == tailX[i] && foodY == tailY[i]) {
                valid = false;
                break;
            }
        }
    } while (!valid);
}

void Setup() {
    gameOver = false;
    direction = RIGHT;  // Start moving to the right
    x = WIDTH / 2;
    y = HEIGHT / 2;

    // Spawn food at a random location
    SpawnFood();

    score = 0;
    nTail = 0; // Reset tail length
}

void Draw() {
    system("cls"); // Clear screen

    for (int i = 0; i < WIDTH; i++) cout << "#"; // Top border
    cout << "\n";

    for (int i = 0; i < HEIGHT - 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 1) cout << "#"; // Side walls
            else if (i == y && j == x) cout << "O"; // Snake head
            else if (i == foodY && j == foodX) cout << "F"; // Food
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Snake tail
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
        }
        cout << "\n";
    }

    for (int i = 0; i < WIDTH; i++) cout << "#"; // Bottom border
    cout << "\n";

    cout << "Score: " << score << "\n";
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (direction != RIGHT) direction = LEFT; break;
            case 'd': if (direction != LEFT) direction = RIGHT; break;
            case 'w': if (direction != DOWN) direction = UP; break;
            case 's': if (direction != UP) direction = DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    if (x <= 0 || x >= WIDTH - 1 || y < 0 || y >= HEIGHT - 2) gameOver = true; // Collision with wall

    for (int i = 0; i < nTail; i++) // Collision with itself
        if (tailX[i] == x && tailY[i] == y) gameOver = true;

    if (x == foodX && y == foodY) {
        score += 10;
        nTail++;
        SpawnFood(); // Spawn food after eating
    }
}

int main() {
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }

    cout << "\nGame Over! Final Score: " << score << endl;
    return 0;
}
