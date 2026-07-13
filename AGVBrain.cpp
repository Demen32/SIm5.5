#include "AGVBrain.h"



Direction AGVBrain::makeMove()
{   
    wayValueMatrix = distanceArrayToCurrGoal;
    //cout << cellsinarow << endl;

    if (pos == 1) { pos = 1; dir = UP; moves = 0; foundSubGoal = false; foundGoal = false; versuch++; }
    
    if (versuch == 1)


    moves++;
    
    Direction move;
    
    int x = xTranslate(pos), y = yTranslate(pos);
    int wallX = x, wallY = y;
    
    // Front Sensor

    if (sensorInformation[0] == true) {
        if (dir == UP) wallX = wallX + 1;
        if (dir == DOWN) wallX = wallX - 1;
        if (dir == RIGHT) wallY = wallY - 1;
        if (dir == LEFT) wallY = wallY + 1;

        int wallIndex = wallY + (wallX * cellsinarow);
        if (wallIndex >= 0 && wallIndex < brainLabyrinth.size()) {
            brainLabyrinth[wallIndex] = BLOCK;
            //cout << "f wall: " << wallIndex << endl;
            wallX = x, wallY = y;
        }
    }
    //cout << "dir = " << dir << endl;
    // Right Sensor
    if (sensorInformation[1] == true) {
        if (dir == UP) wallY = wallY - 1;
        if (dir == DOWN) wallY = wallY + 1;
        if (dir == RIGHT) wallX = wallX - 1;
        if (dir == LEFT) wallX = wallX + 1;

        int wallIndex = wallY + (wallX * cellsinarow);
        if (wallIndex >= 0 && wallIndex < brainLabyrinth.size()) {
            brainLabyrinth[wallIndex] = BLOCK;
            //cout << "r wall: " << wallIndex << "dir = " << dir << endl;
            wallX = x, wallY = y;
        }
    }

    // Left Sensor
    if (sensorInformation[2] == true) {
        if (dir == UP) wallY = wallY + 1;
        if (dir == DOWN) wallY = wallY - 1;
        if (dir == RIGHT) wallX = wallX + 1;
        if (dir == LEFT) wallX = wallX - 1;

        int wallIndex = wallY + (wallX * cellsinarow);
        if (wallIndex >= 0 && wallIndex < brainLabyrinth.size()) {
            brainLabyrinth[wallIndex] = BLOCK;
            //cout << "l wall: " << wallIndex << endl;
            wallX = x, wallY = y;
        }
    }

    //this function delivers the next pos to move to
    int next_pos = find_shortest_path(pos);

    //mode switch for targeting next goal
    if (next_pos == posSubGoal) {
        //cout << "-------------- SUBGOAL FOUND ----------------" << endl;
        foundSubGoal = true;
    }
    //condition to terminate program
    if (next_pos == posGoal) {
        cout << "-------------- GOAL FOUND ----------------" << endl;
        foundGoal = true;
    }
      
    move = moveToNextPos(pos, next_pos, dir);
    
    orientation = move;

    //Translation of given orientation in global direction
    if (orientation == DOWN) { dir = (Direction)((int)dir * -1); }
    else if (orientation == RIGHT) {
        if ((int)dir % 2 == 0)
            dir = (Direction)((int)dir / -2);
        else
            dir = (Direction)((int)dir * 2);
    }
    else if (orientation == LEFT) {
        if ((int)dir % 2 == 0)
            dir = (Direction)((int)dir / 2);
        else
            dir = (Direction)((int)dir * -2);
    }

    // this part calculates position with direction of robot
    switch (dir) {
    case -1:
        pos = pos - cellsinarow;
        break;
    case 2:
        pos = pos - 1;
        break;
    case -2:
        pos = pos + 1;
        break;
    case 1:
        pos = pos + cellsinarow;
        break;
    }
   
    
    
    return move;
}