#include <bits/stdc++.h>

using namespace std;

// Constants for grid size
const int GRID_SIZE = 20;
const char SNAKE_CHAR = 'O';
const char FOOD_CHAR = '*';
const char EMPTY_CHAR = ' ';

// Directions
enum Direction { UP, DOWN, LEFT, RIGHT };

// Snake class
class Snake {
public:
    deque<pair<int, int>> body; // Stores (x, y) positions of the snake
    Direction dir;

    Snake() {
        body.push_back({GRID_SIZE / 2, GRID_SIZE / 2}); // Start position
        body.push_back({GRID_SIZE / 2, (GRID_SIZE / 2) - 1});
        body.push_back({GRID_SIZE / 2, (GRID_SIZE / 2) - 2});
        dir = RIGHT;
    }

    void move(bool grow) {
        pair<int, int> head = body.front();
        switch (dir) {
            case UP: head.first--; break;
            case DOWN: head.first++; break;
            case LEFT: head.second--; break;
            case RIGHT: head.second++; break;
        }
        body.push_front(head);
        if (!grow) body.pop_back(); // Remove tail unless growing
    }

    bool checkCollision() {
        pair<int, int> head = body.front();
        if (head.first < 0 || head.first >= GRID_SIZE || head.second < 0 || head.second >= GRID_SIZE)
            return true;
        for (size_t i = 1; i < body.size(); i++)
            if (body[i] == head)
                return true;
        return false;
    }
};

// Game class
class Game {
public:
    Snake snake;
    pair<int, int> food;
    int score = 0;
    bool gameOver = false;

    Game() { generateFood(); }

    void generateFood() {
        srand(time(0));
        int x, y;
        bool valid;
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
            valid = true;
            for (auto cell : snake.body)
                if (cell.first == x && cell.second == y)
                    valid = false;
        } while (!valid);
        food = {x, y};
    }

    void update() {
        bool grow = (snake.body.front() == food);
        if (grow) {
            score++;
            generateFood();
        }
        snake.move(grow);
        if (snake.checkCollision()) {
            gameOver = true;
        }
    }

    void render() {
        system("cls"); // Clear console
        vector<vector<char>> grid(GRID_SIZE, vector<char>(GRID_SIZE, EMPTY_CHAR));

        // Draw food
        grid[food.first][food.second] = FOOD_CHAR;

        // Draw snake
        for (auto cell : snake.body) {
            grid[cell.first][cell.second] = SNAKE_CHAR;
        }

        // Display grid
        for (auto row : grid) {
            for (char cell : row) cout << cell << " ";
            cout << endl;
        }
        cout << "\nScore: " << score << endl;
    }

    void processInput() {
        if (_kbhit()) { // Check for keypress
            char ch = _getch();
            switch (ch) {
                case 'w': if (snake.dir != DOWN) snake.dir = UP; break;
                case 's': if (snake.dir != UP) snake.dir = DOWN; break;
                case 'a': if (snake.dir != RIGHT) snake.dir = LEFT; break;
                case 'd': if (snake.dir != LEFT) snake.dir = RIGHT; break;
            }
        }
    }

    void run() {
        while (!gameOver) {
            processInput();
            update();
            render();
            Sleep(100); // Adjust speed
        }

        // Game Over screen
        system("cls");
        cout << "\nGame Over! Final Score: " << score << "\n";
        cout << "Press 'r' to restart or any other key to exit.\n";
        char ch = _getch();
        if (ch == 'r') {
            *this = Game(); // Restart game
            run();
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
