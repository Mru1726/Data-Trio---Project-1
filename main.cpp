#include <bits/stdc++.h>

using namespace std;

const int GRID_SIZE = 20;
const char SNAKE_CHAR = 'O';
const char FOOD_CHAR = '*';
const char EMPTY_CHAR = ' ';

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
public:
    deque<pai<int, int>> body;
    Direction dir;
