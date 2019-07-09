#include "mbed.h"
#include "snake.cpp"

#define SPEED 0.2

DigitalOut DS(PC_10);
DigitalOut SH_CP(PC_11);
DigitalOut ST_CP(PC_12);

InterruptIn upButton(PC_2);
InterruptIn leftButton(PC_3);
InterruptIn rightButton(PC_1);
InterruptIn downButton(PC_0);

Ticker moveTicker;

bool Field[8][8] = {
 {1, 1, 1, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 };
 
unsigned int xFood , yFood;
Direction dir = UP;

snakeHead * snake = new snakeHead();
 
// Function Headers
void printField();
void turnUp();
void turnLeft();
void turnRight();
void turnDown();
void move();
void spawnFood();

int main() {    
    upButton.rise(&turnUp);
    leftButton.rise(&turnLeft);
    rightButton.rise(&turnRight);
    downButton.rise(&turnDown);
    moveTicker.attach(&move, SPEED);
    spawnFood();
    while (1) {        
        printField();
    }
}


 void printField() {
     for(unsigned int i = 0; i < 8; i++) {
            for(unsigned int j = 0; j < 16; j++) {
                SH_CP = 0;
                if (i == j) {
                    // Set active row
                    DS = 1;
                } else if (j < 8) {
                    // Deactivate other rows
                    DS = 0;
                } else {
                    // Set columns
                    DS = !Field[i][j-8];
                }
                // Load new bit into shift register
                SH_CP = 1;    
            }
            // Set output of shift register
            ST_CP = 1;
            ST_CP = 0;
            wait(0.0001);
    }
}

void turnUp() {
    if (dir == LEFT || dir == RIGHT) { dir = UP; }
}

void turnLeft() {
    if (dir == UP || dir == DOWN) { dir = LEFT; }
}

void turnRight() {
    if (dir == UP || dir == DOWN) { dir = RIGHT; }
}

void turnDown() {
    if (dir == LEFT || dir == RIGHT) { dir = DOWN; }
}

void move() {
    unsigned int xTail = snake->getTail()->getxPos();
    unsigned int yTail = snake->getTail()->getyPos();
    snake->move(dir);
    if ((snake->getxPos() == xFood) && (snake->getyPos() == yFood)) {
        // Snake has reached the food
        snakeBody * newPart = new snakeBody(xTail, yTail);
        snake->append(newPart);
        Field[xTail][yTail] = 1;
        spawnFood();
    }else if (Field[snake->getxPos()][snake->getyPos()] == 1) {
        // Snake has hit itself
        NVIC_SystemReset();
    }else {
        // Snake moved to an empty field
        Field[xTail][yTail] = 0;
        Field[snake->getxPos()][snake->getyPos()] = 1;
    }

}

void spawnFood() {
    xFood = (rand()+3) % 8;
    yFood = (rand()+3) % 8;
    while (Field[xFood][yFood] != 0) {
        xFood = rand() % 8;
        yFood = rand() % 8;
    }
    Field[xFood][yFood] = 1;
}
