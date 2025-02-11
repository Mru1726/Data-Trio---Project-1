#include<bits/stdc++.h>
#include<conio.h> // key press kbhit
#include<windows.h>

using namespace std;

#define MAX_LENGTH 1000

//Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth, consoleHeight;

void initScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

struct Point{
    int xCoord;
    int yCoord;
    Point(){
    }
    Point(int x, int y)
    {
        xCoord = x;
        yCoord = y;
    }
};


class Snake{
    int length;
    char direction;
public:
    Point body[MAX_LENGTH];

    Snake(int x, int y)
    {
       length = 1;
       body[0] = Point(x,y);
       direction = DIR_RIGHT;
    }

    int getLength(){
        return length;
    }

    void changeDirection(char newDirection){
        if(newDirection == DIR_UP && direction != DIR_DOWN)
        {
            direction = newDirection;
        }
        else if(newDirection == DIR_DOWN && direction != DIR_UP)
        {
            direction = newDirection;
        }
        else if(newDirection == DIR_LEFT && direction != DIR_RIGHT)
        {
            direction = newDirection;
        }
        else if(newDirection == DIR_RIGHT && direction != DIR_LEFT)
        {
            direction = newDirection;
        }
    }


    bool move(Point food){
        //Move the snake's body
        for(int i= length-1;i>0;i--)  // lenght = 4
        {
            body[i] = body[i-1];
        }
        //Move the head
        switch(direction)
        {
            int val;
            case DIR_UP:
                val = body[0].yCoord;
                body[0].yCoord = val-1;
                break;
            case DIR_DOWN:
                val = body[0].yCoord;
                body[0].yCoord = val+1;
                break;
            case DIR_RIGHT:
                val = body[0].xCoord;
                body[0].xCoord = val+1;
                break;
            case DIR_LEFT:
                val = body[0].xCoord;
                body[0].xCoord = val-1;
                break;

        }

        //snake bites itself
        for(int i=1;i<length;i++)
        {
            if(body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord)
            {
                return false;
            }
        }
        //Check for collision with boundaries
        if(body[0].xCoord < 0 || body[0].xCoord >= consoleWidth || body[0].yCoord < 0 || body[0].yCoord >= consoleHeight){
            return false; //Game over
        }
        
        //snake eats food
        if(food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord)
        {
            body[length] = Point(body[length-1].xCoord, body[length-1].yCoord);
            length++;
        }

        return true;
    }
};


class Board{
    Snake *snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;
public:
    Board(){
        spawnFood();
        snake = new Snake(10,10);
        score = 0;
    }

    ~Board(){
        delete snake;
    }

    int getScore(){
        return score;
    }

    void spawnFood(){
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;
        food = Point(x, y);
    }

    void displayCurrentScore(){
        gotoxy(consoleWidth/2,0);
        cout<<"Current Score : "<< score;
    }

    void gotoxy(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    }

    void draw(){
        system("cls");
        //Draw boundaries
        for(int i=0; i<consoleWidth; i++) {
            gotoxy(i, 1); cout<< "#"; //Top boundary
            gotoxy(i, consoleHeight - 1); cout<< "#"; //Bottom boundary
        }
        for (int i=1; i<consoleHeight; i++) {
            gotoxy(0, i); cout<<"#"; //Left boundary
            gotoxy(consoleWidth - 1, i); cout<<"#"; //Right boundary
        }
        //Draw the snake
        for (int i=0; i<snake->getLength(); i++){
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout<< SNAKE_BODY;
        }
        //Draw the food
        gotoxy(food.xCoord, foor.yCoord);
        cout<< FOOD;

        displayCurrentScore();
    }

    bool update(){
       bool isAlive = snake->move(food);
       if(isAlive == false)
       {
           return false;
       }

        if(food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord)
        {
            score++;
            spawnFood();
        }
       return true;
    }

    void getInput(){
        if(kbhit())
        {
            int key = getch();
            if(key == 'w' || key == 'W')
            {
                snake->changeDirection(DIR_UP);
            }
            else if(key == 'a' || key == 'A')
            {
                snake->changeDirection(DIR_LEFT);
            }
            else if(key == 's' || key == 'S')
            {
                snake->changeDirection(DIR_DOWN);
            }
            else if(key == 'd' || key == 'D')
            {
                snake->changeDirection(DIR_RIGHT);
            }
        }
    }

};

int main(){
    srand(time(0));
    initScreen();
    Board *board = new Board();
    while(board->update())
    {
        board->getInput();
        board->draw();
        Sleep(100);
    }
    system("cls");
    cout<<"******** GAME OVER ********"<<endl;
    cout<<"Final score is :"<<board->getScore()<<endl;
    delete board;
    return 0;
}
