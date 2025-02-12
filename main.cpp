#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <windows.h> //For Sleep()

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
int obstacleX, obstacleY; // Obstacle coordinates

void SpawnFood() {
    bool valid;
    do {
        valid = true;
        foodX = (rand() % (WIDTH - 2)) + 1;
        foodY = (rand() % (HEIGHT - 2)) + 1;

        if (foodX == x && foodY == y) valid = false;
        for (int i = 0; i < nTail; i++) {
            if (foodX == tailX[i] && foodY == tailY[i]) {
                valid = false;
                break;
            }
        }
    } while (!valid);
}

void SpawnObstacle(){
    bool valid;
    do {
        valid = true;
        obstacleX = (rand() % (WIDTH-2)) + 1;
        obstacleY = (rand() % (HEIGHT - 2)) + 1;

        if (obstacleX == x && obstacleY == y) valid = false;
        if (obstacleX == foodX && obstacleY == foodY) valid = false;
        for (int i=0; i<nTail; i++){
            if (obstacleX == tailX[i] && obstacleY == tailY[i]){
                valid = false;
                break;
            }
        }
    } while (!valid);
}
void Setup() {
    gameOver = false;
    direction = RIGHT;
    x = WIDTH / 2;
    y = HEIGHT / 2;

    srand(time(0));
    SpawnFood();
    SpawnObstacle(); //Generate an obstacle initially

    score = 0;
    nTail = 2;
}

void Draw() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Get console handle
    COORD cursorPosition = {0,0};
    SetConsoleCursorPosition(hConsole, cursorPosition); //Move cursor

    for (int i = 0; i < WIDTH; i++) cout << "#";
    cout << "\n";

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 1)
                cout << "#";
            else if (i == y && j == x)
                cout << "O";
            else if (i == foodY && j == foodX)
                cout << "F";
            else if (i == obstacleY && j == obstacleX)
                cout << "B"; //obstacle displayed as B
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                        break;
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << "\n";
    }

    for (int i = 0; i < WIDTH; i++) cout << "#";
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
    int prevX = x, prevY = y;
    int prev2X, prev2Y;

    for (int i = 0; i < nTail; i++) {
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
    }

    // Wall collision fix
    if (x<=0) x = WIDTH-1; //if out of left wall, move to right wall
    else if (x>= WIDTH-1) x = 1; //if out of right wall, move to left wall

    if (y<=0) y = HEIGHT - 1; // if out of top wall, move to bottom wall
    else if (y>= HEIGHT) y = 0; //if out of bottom wall, move to top wall

    // Self-collision
    for (int i = 0; i < nTail; i++){
        if (tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }
    
    // Collision with obstacle
    if (x == obstacleX && y == obstacleY){
        gameOver = true;
    }

    // Eating food
    if (x == foodX && y == foodY) {
        score += 10;
        nTail+=2;
        SpawnFood();
        SpawnObstacle();
    }
}

int main() {
    Setup();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Adjusted speed for smoother gameplay
    }

    cout << "\nGame Over! \nFinal Score: " << score << endl;
    return 0;
}
