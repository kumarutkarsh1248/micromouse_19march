#ifndef FLOOD_FILL_H
#define FLOOD_FILL_H

#include "constants.h"
#include <Arduino.h>
#include <SimpleStack.h>
#include "distance.h"



struct Cell {
public:
    volatile uint8_t i;
    volatile uint8_t j;
    volatile uint8_t distance = 0;
    volatile uint8_t config = all_clear;

    bool right_wall : 1;
    bool back_wall : 1;
    bool left_wall : 1;
    bool front_wall : 1;
    bool visited : 1;

    // Constructors
    Cell();
    Cell(volatile uint8_t i, volatile uint8_t j);
    void update();
};

/*
cellStack is defined globally which stores the cell 
where we want to perform the flood fill whenever we
call flood_fill() it first update the distance value
of that cell and add the neighboring cell to the stack
 which need flood fill
*/
void flood_fill();
/*
according to the difference configuration of the cell
the flood_fill function will call the correspoing right/
back/front/left flood fill
*/
void right_flood_fill(int i, int j);
void back_flood_fill(int i, int j);
void left_flood_fill(int i, int j);
void front_flood_fill(int i, int j);


class Bot {
public:
    int orientation = bot_front;
    int x = 0;
    int y = 0;
};

void set_boundary_wall();
void bot_update_wall();
int where_to_move(int i, int j);
bool possible_or_not(Cell initial_cell, Cell final_cell);
void found_wall(int i, int j, String wall);
void whole_flood_fill();


















// Function prototypes
// void log(String message);
// bool wallFront();
// bool wallRight();
// bool wallLeft();
// bool moveForward();
// void turnRight();
// void turnLeft();
// void setColor(int x, int y, char color);
// void setText(int x, int y, String text);

// External variable declaration
extern Cell maze[SIZE][SIZE];
extern Bot bot;
extern SimpleStack<Cell> cellStack;

#endif
