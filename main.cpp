#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "diff.h"

using namespace std;

class SnakeGame {

    string edir_str[5] = { "STOP", "LEFT", "RIGHT", "UP" ,"DOWN" };
    enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
    enum eFood { NORMAL, TOXIC, HARD, SOFT };

    string tail_effect_blured_str = ",.'/-";
    string food_toxic_effect_blured_str = ",.'/X";
    string food_hard_effect_blured_str = ",.'^%";
    string food_soft_effect_blured_str = ",.''";
    string foodStr = "@THS";
    string win_effect_blured_str = "win...";

public:
    typedef struct Pos {
        int x;
        int y;
    }Pos;

    typedef struct Food {
        int type; // is equal to enum eFood
        Pos pos;
    }Food;

    typedef struct Effect {
        int duration; //Number of frame If 0, No effect in next frame.
        int delay; //Delay of every frame
        int chance; //Presentage , Change to print the blured to the screen.
        string bluredStr;
    }Effect;

    int initialTails = 0;

    bool gameOver; 
    bool gameStart;
    bool gamePause;
    int difficult; //Level default = 0;
    int width; //Game area excluded margin
    int height; //Game area excluded margin
    int x, y; //Curent x and y of snake head
    int last_x, last_y; //Last location of snake head
    int score;
    int foodScore[4] = { 10, -5, -5, 0 };
    int foodGrownTail[4] = { 1, -1, -1, 0 }; //1: Grown, -1: Loss, 0:Nothing
    int foodChangeDirection[4] = { 0, 0 , 1 , 1 }; // 0: false , 1:true
    int dir; //is equal to eDirection
    int* foods_maximum; //Size 4
    int total_food_maximum;
    int food_generate_chance = 100; //0~100%
    int winScore;
    int winTails;
    int winCountdown = -1;
    vector<Food> foods;
    vector<Pos> tails; //<-Older ~~~~ x,y pos ~~~~~ Newer->
    Effect effect;

    SnakeGame() {
        gameOver = false;
        gameStart = false;
        gamePause = false;
        difficult = 0;
        dir = STOP;
        x = 0;
        y = 0;
        last_x = x;
        last_y = y;
        foods_maximum = new int[4];
        for (int i = 0; i < 4; i++)
            foods_maximum[i] = 1;
        total_food_maximum = 4;
        winScore = 30;
        winTails = 10;
    }

    SnakeGame(int weight, int height) {
        SnakeGame();
        this->width = weight;
        this->height = height;
    }

    void setting(int setting[10]) {
        width = setting[0];
        height = setting[1];

        foods_maximum[0] = setting[2];
        foods_maximum[1] = setting[3];
        foods_maximum[2] = setting[4];
        foods_maximum[3] = setting[5];
        total_food_maximum = setting[6];
        winScore = setting[7];
        winTails = setting[8];
        initialTails = setting[9];
    }

    void SetupForTest(int w, int h, int f1,int f2,int f3,int f4,int tail_length) {
        SnakeGame();
        width = w;
        height = h;
        x = w / 2;
        y = h / 2;
        last_x = x;
        last_y = y;
        foods_maximum = new int[4];
        foods_maximum[0] = f1;
        foods_maximum[1] = f2;
        foods_maximum[2] = f3;
        foods_maximum[3] = f4;
        total_food_maximum = 0;
        for (int i = 0; i < 4; i++)
            total_food_maximum+= foods_maximum[i];
        extendTail(tail_length);
        randomFood();
    }

    //Force to put a food in empty space
    void forceRandomFood(int food_type) {
        bool condition = true;
        while (condition) {
            Pos randPos;
            randPos.x = randomRange(width);
            randPos.y = randomRange(height);

            bool isContainPos = false;
            //Check Snake Head
            if (x == randPos.x and y == randPos.y) {
                isContainPos = true;
            }

            //Check Snake tail
            for (int i = 0; i < tails.size(); i++) {
                Pos tail_pos = tails[i];
                if (tail_pos.x == randPos.x and tail_pos.y == randPos.y) {
                    isContainPos = true;
                    break;
                }
            }
            //Check Foods
            for (int i = 0; i < foods.size(); i++) {
                Pos food_pos = foods[i].pos;
                if (food_pos.x == randPos.x and food_pos.y == randPos.y) {
                    isContainPos = true;
                    break;
                }
            }
            //Location have nothing, can put a food here;
            if (!isContainPos) {
                Food newFood;
                newFood.pos = randPos;
                newFood.type = food_type;
                foods.push_back(newFood);
                condition = false;
            }
        }
    }

    void randomFood() {
        if (foods.size() >= total_food_maximum) {
            return;
        }

        int numOfType = 4;
        int* randIndexs = randomArrayIndex(numOfType);
        for (int i = 0; i < numOfType; i++) {
            int food_type = randIndexs[i]; //Same with e food type
            int food_maximum = foods_maximum[food_type];
            int food_count = 0; //Current food type
            for (int j = 0; j < foods.size(); j++) {
                if (foods[j].type == food_type) {
                    food_count++;
                }
            }

            if (food_count >= food_maximum) {
                continue;
            }

            forceRandomFood(food_type);
            break;
        }

    }


    eDirecton getDirection(int x, int y, int last_x, int last_y, int width, int height) {
        if ((x > last_x and abs(x - last_x) == 1) or (x == 0 and last_x == (width - 1)))
            return RIGHT;
        else if (x < last_x or (last_x == 0 and x == (width - 1)))
            return LEFT;
        else if ((y > last_y and abs(y - last_y) == 1) or (y == 0 and last_y == (height - 1)))
            return UP;
        else if ((y < last_y and y * last_y >= 0) or (last_y == 0 and y == (height - 1)))
            return DOWN;
        else
            return STOP;
    }

    eDirecton getFaceDirection() {
        return getDirection(x, y, last_x, last_y, width, height);
    }

    void extendTail(int length) {
        eDirecton tdir;
        int x, y;
        if (tails.size() < 2) {
            tdir = DOWN; //Default Direction is Set to DOWN
            x = this->x;
            y = this->y;
        }
        else {
            Pos p = tails[1];
            Pos last_p = tails[0]; //Last Tail Pos
            x = last_p.x, y = last_p.y;
            eDirecton tdir = getDirection(p.x, p.y, last_p.x, last_p.y, width, height);
        }


        for (int i = 0; i < length; i++) {
            if (tdir == RIGHT)
                x++;
            else if (tdir == LEFT)
                x--;
            else if (tdir == UP)
                y++;
            else if (tdir == DOWN)
                y--;
            x += width;
            y += height;
            x %= width;
            y %= height;

            Pos newPos;
            newPos.x = x;
            newPos.y = y;
            tails.insert(tails.begin(), newPos);
        }



    }

    void create_effect_conlided_with_tail() {
        //Shock Effect
        Effect shock_effect;
        shock_effect.duration = 5;
        shock_effect.delay = 100;
        shock_effect.chance = 50;
        shock_effect.bluredStr = tail_effect_blured_str;
        effect = shock_effect;
    }

    void create_effect_conlided_with_hard() {
        //Shock Effect
        Effect shock_effect;
        shock_effect.duration = 2;
        shock_effect.delay = 50;
        shock_effect.chance = 30;
        shock_effect.bluredStr = food_hard_effect_blured_str;
        effect = shock_effect;
    }

    void create_effect_conlided_with_toxic() {
        //Shock Effect
        Effect shock_effect;
        shock_effect.duration = 3;
        shock_effect.delay = 20;
        shock_effect.chance = 10;
        shock_effect.bluredStr = food_toxic_effect_blured_str;
        effect = shock_effect;
    }

    void create_effect_conlided_with_soft() {
        //Shock Effect
        Effect shock_effect;
        shock_effect.duration = 2;
        shock_effect.delay = 10;
        shock_effect.chance = 10;
        shock_effect.bluredStr = food_soft_effect_blured_str;
        effect = shock_effect;
    }

    void create_effect_win() {
        //Shock Effect
        Effect shock_effect;
        shock_effect.duration = winCountdown;
        shock_effect.delay = 50;
        shock_effect.chance = 30;
        shock_effect.bluredStr = win_effect_blured_str;
        effect = shock_effect;
    }


    public:
    void Draw() {
        system("cls"); //system("clear");
        stringstream sss;

        sss << "To win the game , you need to grow the tail !!" << endl;
        sss << "----------------------------------------------" << endl;
        sss << "Snake Tail Length: " << tails.size() << endl;
        sss << "Face Direction: " << edir_str[getFaceDirection()] << endl;
        sss << "Score: " << score << endl;
        sss << "Level: " << difficult << " .Attain to " << winScore << " scores and " << winTails << " tails to Win" << endl;
        //Print margin: first line or last line
        for (int i = 0; i < width + 2; i++)
            sss << "#";
        sss << endl;

        // i ~ Y, j ~ X
        for (int iy = height - 1; iy >= 0; iy--) { //Y
            for (int ix = 0; ix < width; ix++) { //X
                //Print margin: first word in every line
                if (ix == 0) { //X
                    sss << "#";
                }
                //----------------
                bool printed = false;
                //Head
                if (ix == x and iy == y) {
                    sss << "G";
                    printed = true;
                }

                if (!printed)
                    //Foods
                    for (int i = 0; i < foods.size(); i++) {
                        Pos pos = foods[i].pos;
                        int type = foods[i].type;

                        if (pos.x == ix and pos.y == iy) {
                            sss << foodStr[type];
                            printed = true;
                            break;
                        }
                    }

                if (!printed)
                    //Tails
                    for (int i = 0; i < tails.size(); i++) {
                        Pos tailPos = tails[i];

                        if (ix == tailPos.x and iy == tailPos.y) {
                            printed = true;
                            sss << "o";
                            break;
                        }
                    }

                if (!printed) {
                    //Empty or If it have Effect
                    if (effect.duration > 0) {
                        if (randomRange(100) < effect.chance) {
                            sss << effect.bluredStr[randomRange(effect.bluredStr.length())];
                        }
                        else {
                            sss << " ";
                        }
                    }
                    else
                        sss << " ";
                }

                //----------------
                //Print margin: last word in every line
                if ((ix + 1) == width) {
                    sss << "#";
                }
            }
            sss << endl;
        }

        for (int i = 0; i < width + 2; i++)
            sss << "#";
        sss << endl;

        sss << "Press x to save the game and return to menu" << endl;

        cout << sss.str();
    }
    void Input(char key) {
        if (key != 0) {
            switch (key) {
                case 'a':
                    if (getFaceDirection() != RIGHT)
                        dir = LEFT;
                    break;
                case 'd':
                    if (getFaceDirection() != LEFT)
                        dir = RIGHT;
                    break;
                case 'w':
                    if (getFaceDirection() != DOWN)
                        dir = UP;
                    break;
                case 's':
                    if (getFaceDirection() != UP)
                        dir = DOWN;
                    break;
                case 'p':
                    dir = STOP;
                    break;
                case 'x':
                    gamePause = true;
                    break;
            }
        }
    }
    
    void Logic() {
        if (dir == STOP)
            return;

        //last position and next postion
        bool moveToward = true;

        bool extendTail = false;

        bool isConlideWithFood = false;
        int food_type;
        //Conlide with Food
        for (int i = 0; i < foods.size(); i++) {
            Food food = foods[i];
            Pos fpos = food.pos;
            if (fpos.x == x and fpos.y == y) {
                foods.erase(foods.begin() + i);
                food_type = food.type;
                isConlideWithFood = true;
                break;
            }
        }
        if (isConlideWithFood) {
            int changeTail = foodGrownTail[food_type];
            bool changeDirection = foodChangeDirection[food_type];
            int changeScore = foodScore[food_type];

            if (changeDirection) {
                int randInt = randomRange(2);
                if (dir == RIGHT or dir == LEFT) {
                    if (randInt == 0) {
                        dir = UP;
                    }
                    else {
                        dir = DOWN;
                    }
                }
                else if (dir == UP or dir == DOWN) {
                    if (randInt == 0) {
                        dir = LEFT;
                    }
                    else {
                        dir = RIGHT;
                    }
                }
            }

            if (food_type == TOXIC)
                create_effect_conlided_with_toxic();
            else if (food_type == HARD)
                create_effect_conlided_with_hard();
            else if (food_type == SOFT)
                create_effect_conlided_with_soft();
            if (changeTail > 0) {
                extendTail = true;
            }
            else if (changeTail < 0) {
                if (tails.size() == 0 and winCountdown < 0)
                    gameOver = true;
                if (tails.size() >0)
                    tails.erase(tails.begin(), tails.begin() - changeTail);
            }
            score += changeScore;
        }

        if (!isConlideWithFood) {
            //If conlide with Tail
            bool isConlided_with_tail = false;
            //How many tail will be broken;
            int break_size;
            for (int i = 0; i < tails.size(); i++) {
                Pos p = tails[i];
                if (x == p.x and y == p.y) {
                    isConlided_with_tail = true;
                    break_size = i + 1;
                    break;
                }
            }
            if (isConlided_with_tail) {
                tails.erase(tails.begin(), tails.begin() + break_size);
                create_effect_conlided_with_tail();
            }
        }

        //vector tails <-End of tail ~~~~ x,y pos absending order~~~~~ Head->
        //Calculate tails
        //Extend Tail process
        if (extendTail) {
            Pos nextTail;
            nextTail.x = x, nextTail.y = y;
            tails.push_back(nextTail);
        }
        //Tail Calculation
        else if (tails.size() > 0) {
            Pos nextTail;
            nextTail.x = x, nextTail.y = y;
            tails.push_back(nextTail);
            tails.erase(tails.begin());
        }

        //---------------------------
        //Random food
        if (randomRange(100) < food_generate_chance)
            randomFood();

        if (moveToward) {
            last_x = x, last_y = y;
            if (dir == RIGHT)
                x++;
            else if (dir == LEFT)
                x--;
            else if (dir == UP)
                y++;
            else if (dir == DOWN)
                y--;
            x += width;
            y += height;
            x %= width;
            y %= height;
        }
        
        if (score >= winScore and tails.size() >= winTails and winCountdown < 0) {
            winCountdown = 10;
            create_effect_win();
        }

        if (winCountdown > 0) {
            winCountdown--;
        }
        else if (winCountdown == 0) {
            gameOver = true;
        }
    }

    void listener_GameStart() {
        if (!gameStart) {
            extendTail(initialTails);
        }
        gameStart = true;
    }

    void listener_GamePause() {
        gamePause = true;
    }

    void listener_GameResume() {
        gamePause = false;
    }

    void listener_GameOver() {
        gameOver = true;
    }

};

void gameMenu(SnakeGame* game);
void gamePlay(SnakeGame* game);
void gameOver(SnakeGame* game);

void gameSave(SnakeGame* game) {
    stringstream sss;
    ofstream fout;
    fout.open("gamedata.txt");

    sss << game->gameOver << " " << game->gameStart << " " << game->gamePause << " " << game->difficult << " " << game->width << " " << game->height << " ";
    sss << game->x << " " << game->y << " " << game->last_x << " " << game->last_y << " " << game->score << " ";

    for (int i = 0; i < 4; i++) {
        sss << game->foodScore[i] << " ";
    }

    for (int i = 0; i < 4; i++) {
        sss << game->foodGrownTail[i] << " ";
    }

    for (int i = 0; i < 4; i++) {
        sss << game->foodChangeDirection[i] << " ";
    }

    sss << game->dir << " ";

    for (int i = 0; i < 4; i++) {
        sss << game->foods_maximum[i] << " ";
    }

    sss << game->total_food_maximum << " ";

    sss << game->food_generate_chance << " ";

    sss << game->winScore << " " << game->winTails << " ";

    sss << game->foods.size() << " ";

    for (int i = 0; i < game->foods.size(); i++) {
        sss << game->foods[i].type << " " << game->foods[i].pos.x << " " << game->foods[i].pos.y << " ";
    }

    sss << game->tails.size() << " ";
    for (int i = 0; i < game->tails.size(); i++) {
        sss << game->tails[i].x << " " << game->tails[i].y << " ";
    }

    sss << game->effect.duration << " " << game->effect.delay << " " << game->effect.chance << " " << game->effect.bluredStr << " ";

    fout << sss.str();
    fout.close();
}

// Loading parameters
void gameLoad(SnakeGame* game) {
    char filename[80] = "gamedata.txt";
    ifstream fin;
    fin.open(filename);

    if (fin.fail()) {
        cout << "No game record!" << endl;
        exit(1);
    }

    game->foods.clear();
    game->tails.clear();


    fin >> game->gameOver >> game->gameStart >> game->gamePause >> game->difficult >> game->width >> game->height >> game->x >> game->y >> game->last_x >> game->last_y >> game->score;

    for (int i = 0; i < 4; i++) {
        fin >> game->foodScore[i];
    }

    for (int i = 0; i < 4; i++) {
        fin >> game->foodGrownTail[i];
    }

    for (int i = 0; i < 4; i++) {
        fin >> game->foodChangeDirection[i];
    }

    int last_gamedir;
    fin >> last_gamedir;
    game->dir = 0;

    for (int i = 0; i < 4; i++) {
        fin >> game->foods_maximum[i];
    }

    fin >> game->total_food_maximum;

    fin >> game->food_generate_chance;

    fin >> game->winScore >> game->winTails;

    int foods_size;
    fin >> foods_size;
    for (int i = 0; i < foods_size; i++) {
        SnakeGame::Food food_n;
        fin >> food_n.type >> food_n.pos.x >> food_n.pos.y;
        game->foods.push_back(food_n);
    }

    int tails_size;
    fin >> tails_size;
    for (int i = 0; i < tails_size; i++) {
        SnakeGame::Pos tail_n;
        fin >> tail_n.x >> tail_n.y;
        game->tails.push_back(tail_n);
    }


    fin >> game->effect.duration >> game->effect.delay >> game->effect.chance >> game->effect.bluredStr;

    fin.close();
}



string S_COLOR = "\033[1;33m";
string RST = "\x1B[0m";
//selectedLine
void printMenu(stringstream* sss,char key) {
    *sss << "Welcome to the CRAZY SNAKE! " << endl;
    *sss << "Please press key [1-5]:" << endl;
    if (key == '1')
        *sss << S_COLOR;
    *sss << "[1] Start a new game" << RST << endl;
    if (key == '2')
        *sss << S_COLOR;
    *sss << "[2] Load the game" << RST << endl;
    if (key == '3')
        *sss << S_COLOR;
    *sss << "[3] Game Rules" << RST << endl;
    if (key == '4')
        *sss << S_COLOR;
    *sss << "[4] Change difficulty" << RST << endl;
    if (key == '5')
        *sss << S_COLOR;
    *sss << "[5] Exit the game" << RST << endl;

    *sss << "Press space choose the choice." << endl;
}

void printRules(stringstream* sss, char key) {
    *sss << "Player should use the arrow keys on the keyboard to control the movement of the snake.\n" << endl;
    
    *sss << "During the game, the player can press [p], [x], [e]:" << endl;
    *sss << "[p] Pause the game" << endl;
    *sss << "[x] Save the game then quit" << endl;
    *sss << "[e] Back to the main page\n" << endl;
    
    *sss << "The following types of foods and obstacles will be appeared:" << endl;
    *sss << "* Normal Food @" << endl;
    *sss << "  > Add score by 10" << endl;
    *sss << "  > Increase one unit length of the snake" << endl;
    *sss << "* Toxic Food T" << endl;
    *sss << "  > Reduce score by 5" << endl;
    *sss << "  > Decrease one unit length of the snake" << endl;
    *sss << "* Hard Obstacle H" << endl;
    *sss << "  > Random bound to one of the perpendicular direction" << endl;
    *sss << "  > Decrease one unit length of the snake" << endl;
    *sss << "  > Reduce score by 5" << endl;
    *sss << "* Soft Obstacle S" << endl;
    *sss << "  > Random bound to one of the perpendicular direction\n" << endl;
    
    *sss << "If the player attain the enought score or length tail, then win the game." << endl;
    *sss << "The player can continue to play to break the records if the player won the game.\n" << endl;
    
    if (key == 'e')
        *sss << S_COLOR;
    *sss << "Press [e] back to the main page" << RST << endl;
    
}

void printDiff(stringstream* sss,char key) {
    Diff diff;
    *sss << "Different level have difficult size of game area , food generation rate:\n" << endl;
    *sss << "Please press [A-D] to choose difficulty:\n" << endl;
    if (key == 'a' or key == '1')
        *sss << S_COLOR;
    *sss << "[A] Beginner" << RST << endl;
    *sss << "  > Winning score: " << diff.Beginner[7] << endl << "  > Winning tails length: " << diff.Beginner[8] << endl;
    if (key == 'b' or key == '2')
        *sss << S_COLOR;
    *sss << "[B] Intermediate" << RST << endl;
    *sss << "  > Winning score: " << diff.Intermediate[7] << endl << "  > Winning tails length: " << diff.Intermediate[8] << endl;
    if (key == 'c' or key == '3')
        *sss << S_COLOR;
    *sss << "[C] Advance" << RST << endl;
    *sss << "  > Winning score: " << diff.Pro[7] << endl << "  > Winning tails length: " << diff.Pro[8] << endl;
    if (key == 'd' or key == '4')
        *sss << S_COLOR;
    *sss << "[D] Master" << RST << endl;
    *sss << "  > Winning score: " << diff.Master[7] << endl << "  > Winning tails length: " << diff.Master[8] << endl;
    if (key == 'e')
        *sss << S_COLOR;
    *sss << "Press [e] back to the main page" << RST << endl;
}




void transition_animation() {
    stringstream sss;
    Sleep(1000 / 2);
    sss.str("");
    sss << "################" << endl;
    sss << "#  HHHHHHHHH   #" << endl;
    sss << "#          H   #" << endl;
    sss << "#  HHHHHHHHH   #" << endl;
    sss << "#          H   #" << endl;
    sss << "#  HHHHHHHHH   #" << endl;
    sss << "################" << endl;
    cout << sss.str();
    Sleep(1000 / 2);
    system("cls"); //system("clear");
    sss.str("");
    sss << "################" << endl;
    sss << "#  HHHHHHHHH   #" << endl;
    sss << "#          H   #" << endl;
    sss << "#  HHHHHHHHH   #" << endl;
    sss << "#  H           #" << endl;
    sss << "#  HHHHHHHHH   #" << endl;
    sss << "################" << endl;
    cout << sss.str();
    Sleep(1000 / 2);
    system("cls"); //system("clear");
    sss.str("");
    sss << "################" << endl;
    sss << "#     HH       #" << endl;
    sss << "#    H H       #" << endl;
    sss << "#      H       #" << endl;
    sss << "#      H       #" << endl;
    sss << "#   HHHHHHH    #" << endl;
    sss << "################" << endl;
    cout << sss.str();
    Sleep(1000 / 2);
}

void gameend_animation(bool win) {
    stringstream sss;
    Sleep(1000 / 2);
    for( int i = 0 ; i < 10 ; i++){
        system("cls"); //system("clear");
        sss.str("");
        sss << "################" << "################" << "################" << "################" << endl;
        sss << "#  HHHHHHHHH   #" << "#     HHH      #" << "#   HHH HHH    #" << "#  HHHHHHHHH   #" << endl;
        sss << "#  H           #" << "#    H   H     #" << "#  H   H   H   #" << "#  H           #" << endl;
        sss << "#  H   HHHHH   #" << "#   HHHHHHH    #" << "#  H   H   H   #" << "#  HHHHHHHHH   #" << endl;
        sss << "#  H   H   H   #" << "#  H       H   #" << "#  H   H   H   #" << "#  H           #" << endl;
        sss << "#  HHHHHHHHH   #" << "#  H       H   #" << "#  H   H   H   #" << "#  HHHHHHHHH   #" << endl;
        sss << "################" << "################" << "################" << "################" << endl;
        if(i%2 == 0)
        if (win) {
            sss << "################################################################" << endl;
            sss << "#    H        H     HHHHHHH     H        H         HH   HH     #" << endl;
            sss << "#    H   H   H        H         HH      H          HH   HH     #" << endl;
            sss << "#    H  H H  H        H         H HH   H           HH   HH     #" << endl;
            sss << "#    H H  H H         H        H    HHH                        #" << endl;
            sss << "#     H    H      HHHHHHH     H       H            HH   HH     #" << endl;
            sss << "################################################################" << endl;
        }
        else {
            sss << "################################################################" << endl;
            sss << "#  H          HHHHHHHHH   HHHHHHHHH   HHHHHHHHH    HHHHHHH     #" << endl;
            sss << "#  H          H       H   HH          H           H       H    #" << endl;
            sss << "#  H          H       H   HHHHHHHHH   HHHHHHHHH   HHHHHHHH     #" << endl;
            sss << "#  H          H       H           H   H           H    HH      #" << endl;
            sss << "#  HHHHHHHH   HHHHHHHHH   HHHHHHHHH   HHHHHHHHH   H      HH    #" << endl;
            sss << "################################################################" << endl;
        }
        cout << sss.str();
        Sleep(1000 / 5);
    }
}

void setDifficult(SnakeGame* game,int difficult) {
    Diff diff;
    game->difficult = difficult;
    if (difficult == 0) {
        game->setting(diff.Beginner);
    }
    else if (difficult == 1) {
        game->setting(diff.Intermediate);
    }
    else if (difficult == 2) {
        game->setting(diff.Pro);
    }
    else if (difficult == 3) {
        game->setting(diff.Master);
    }
    else if (difficult == 4) {
        game->setting(diff.test);
    }
}

void gameMenu(SnakeGame* game) {
    bool condition = true;
    int page = 0;
    char key = 0;
    bool isPressingSpace = false;
    stringstream* sss;
    sss = new stringstream();
    int sperframe_menu = 60;
    int default_duration = 10;
    int notice_duration = 0;
    int difficult = 0;
    string notice_msg = "";
    while (condition) {
        system("cls"); //system("clear");

        sss->str("");
        if (_kbhit()) {
            int input = (int)_getch();
            if (input == 32) {
                isPressingSpace = true;
            }
            else {
                key = (char)input;
                isPressingSpace = false;
            }
        }
        if (isPressingSpace) {
            if (page == 0) {
                if (key == '1') {
                    page = 1;
                }
                else if (key == '2') {
                    page = 2;
                }
                else if (key == '3') {
                    page = 3;
                }
                else if (key == '4') {
                    page = 4;
                }
                else if (key == '5') {
                    page = 5;
                }
            }
            else if (page == 3) {
                if (key == 'e') {
                    page = 0;
                }
            }
            else if (page == 4) {
                if (key == 'a' or key == '1') {
                    difficult = 0;
                    notice_msg = "Set difficult to level 1 - Beginner";
                    notice_duration = default_duration;
                    setDifficult(game, difficult);
                }
                else if (key == 'b' or key == '2') {
                    difficult = 1;
                    notice_msg = "Set difficult to level 2 - Intermediate";
                    notice_duration = default_duration;
                    setDifficult(game, difficult);
                }
                else if (key == 'c' or key == '3') {
                    difficult = 2;
                    notice_msg = "Set difficult to level 3 - Advance";
                    notice_duration = default_duration;
                    setDifficult(game, difficult);
                }
                else if (key == 'd' or key == '4') {
                    difficult = 3;
                    notice_msg = "Set difficult to level 4 - Master";
                    notice_duration = default_duration;
                    setDifficult(game, difficult);
                }
                else if (key == 't' or key == '5') {
                    difficult = 4;
                    notice_msg = "Set difficult to level 5 - Just for testing the program";
                    notice_duration = default_duration;
                    setDifficult(game, difficult);
                }
                else if (key == 'e') {
                    page = 0;
                }
            }
            isPressingSpace = false;
        }

        if (page == 0) {
            printMenu(sss, key);
        }
        else if (page == 1) {
            condition = false;
            game = new SnakeGame();
            setDifficult(game,difficult);

            gamePlay(game);
            gameSave(game);
            return;
        }
        else if (page == 2) {
            page = 0;
            printMenu(sss, key);
            ifstream ifile;
            ifile.open("gamedata.txt");
            if(ifile) {
                gameLoad(game);
                setDifficult(game, game->difficult);
                game->dir = 0;
                gamePlay(game);
                condition = false;
                return;
            }else{
                notice_msg = "Not find a game data, can't resume it";
                notice_duration = default_duration;
                isPressingSpace = false;
            }
            
        }
        else if (page == 3) {
            printRules(sss, key);
        }
        else if (page == 4) {
            printDiff(sss, key);
        }
        else if (page == 5) {
            transition_animation();
            exit(0);
            return;
        }

        if (notice_duration-- > 0) {
            *sss << endl << "-------Notice-------" << endl;
            *sss << notice_msg << endl;
            *sss << "--------------------" << endl;
        }

        cout << sss->str();

        Sleep(1000 / sperframe_menu);
    }

    
}

void gameEnd(SnakeGame* game,bool win) {
    gameend_animation(win);
}

void gamePlay(SnakeGame* game) {
    //Tansition Animate before game
    transition_animation();

    int sperframe = 1000;

    if (game->gameStart)
        game->listener_GameResume();
    else
        game->listener_GameStart();
    game->Draw();
    
    game->gameStart = true;
    bool win = false; //Win or lose
    while (!game->gameOver and game->gameStart) {

        if (_kbhit())
            game->Input(_getch());

        game->Logic();
        game->Draw();
        if (game->gamePause) {
            game->listener_GamePause();
            gameSave(game);
            gameMenu(game);
            return;
        }
        //Delay
        Sleep(1000 / sperframe);
        if (game->effect.duration > 0) {
            game->effect.duration--;
            Sleep(game->effect.delay);
        }

        if (game->score < 0 or game->tails.size() == 0) {
            win = false;
            break;
        }

        if (game->winCountdown == 0) {
            win = true;
            break;
        }
    }
    game->listener_GameOver();
    gameEnd(game,win);
    Sleep(2000);
    delete game;
    game = new SnakeGame();
    gameMenu(game);
}

int main(){
    SnakeGame* game = new SnakeGame();
    gameMenu(game);
    return 0;
}

