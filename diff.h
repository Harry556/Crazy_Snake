typedef struct Diff {

    int Beginner[10] = { 30, 25, 15, 1, 1, 1 ,15, 30, 15, 5 };
    int Intermediate[10] = { 25, 20, 7, 2, 2, 2,12, 50, 15, 5 };
    int Pro[10] = { 20, 15, 8, 2, 2, 3, 70, 15,25, 10 };
    int Master[10] = { 20, 15, 10, 3, 3, 4, 20,10, 30, 10 };
    int test[10] = { 20, 20, 3, 3, 3, 4, 1000,20, 1000, 18 };
    // Beginning to end:
    // Width of boundary, height of boundary;
    // Max. number of normal food, toxic food, hard obstacle, soft obstacle;
    // Score to win, tails length to win;
    // Initial_tails length;
}Diff;

void copyArray(int* a1, int* a2, int size);

int randomRange(int number);

int* randomArrayIndex(int length);



//Beginner.width = 45;
//Beginner.height = 45;
//Beginner.max_normal = 5;
//Beginner.max_toxic = 1;
//Beginner.max_hard = 1;
//Beginner.max_soft = 1;
//Beginner.win_score = 30;
//Beginner.win_tails = 10;
//Beginner.initial_tails = 3;

//Intermediate.width = 40;
//Intermediate.height = 40;
//Intermediate.max_normal = 4;
//Intermediate.max_toxic = 2;
//Intermediate.max_hard = 2;
//Intermediate.max_soft = 2;
//Intermediate.win_score = 50;
//Intermediate.win_tails = 15;
//Intermediate.initial_tails = 5;
//
//Pro.width = 35;
//Pro.height = 35;
//Pro.max_normal = 3;
//Pro.max_toxic = 2;
//Pro.max_hard = 2;
//Pro.max_soft = 3;
//Pro.win_score = 70;
//Pro.win_tails = 20;
//Pro.initial_tails = 8;
//
//Master.width = 30;
//Master.height = 30;
//Master.max_normal = 2;
//Master.max_toxic = 3;
//Master.max_hard = 3;
//Master.max_soft = 4;
//Master.win_score = 100;
//Master.win_tails = 25;
//Master.initial_tails = 10;
