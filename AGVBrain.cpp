#include "AGVBrain.h"



Direction AGVBrain::makeMove()
{

    Direction move;
    vector<int> wayChoosingOptions;
    int chosenOption;


    int x = xTranslate(pos), y = yTranslate(pos);
    int wallX = x, wallY = y;
    cout << "pos = " << pos << endl;
    cout << "x = " << x << "y = " << y << endl;

    // Front Sensor

    if (sensorInformation[0] == true) {
        if (dir == UP) wallX = wallX + 1;
        if (dir == DOWN) wallX = wallX - 1;
        if (dir == RIGHT) wallY = wallY - 1;
        if (dir == LEFT) wallY = wallY + 1;

        int wallIndex = wallY + (wallX * cellsinarow);
        if (wallIndex >= 0 && wallIndex < brainLabyrinth.size()) {
            brainLabyrinth[wallIndex] = BLOCK;
            wallX = x, wallY = y;
        }
    }
    // Right Sensor
    if (sensorInformation[1] == true) {
        if (dir == UP) wallY = wallY - 1;
        if (dir == DOWN) wallY = wallY + 1;
        if (dir == RIGHT) wallX = wallX - 1;
        if (dir == LEFT) wallX = wallX + 1;

        int wallIndex = wallY + (wallX * cellsinarow);
        if (wallIndex >= 0 && wallIndex < brainLabyrinth.size()) {
            brainLabyrinth[wallIndex] = BLOCK;
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
            cout << "l wall: " << wallIndex << endl;
            wallX = x, wallY = y;
        }
    }



    move = (Direction)UP;
    orientation = (Direction)UP;

    if (sensorInformation[0] + sensorInformation[1] + sensorInformation[2] == 2) {
        // two walls detected, next for loop will find free space
        for (int i = 0; i <= 2; i++) {
            if (sensorInformation[i] == 0) {
                if (i == 0) { move = UP; }
                if (i == 1) { move = RIGHT; }
                if (i == 2) { move = LEFT; }
                break;
            }
        }
    }
    else {
        if (sensorInformation[0] + sensorInformation[1] + sensorInformation[2] == 1) {
            // one wall detected, robot will choose one way randomly
            for (int i = 0; i <= 2; i++) {
                if (sensorInformation[i] == 0) {
                    wayChoosingOptions.push_back(i);
                }
            }
            chosenOption = wayChoosingOptions[GetRandomValue(0, 1)];
            if (chosenOption == 0) move = UP;
            if (chosenOption == 1) move = RIGHT;
            if (chosenOption == 2) move = LEFT;
            wayChoosingOptions.clear();



        };
        if (sensorInformation[0] + sensorInformation[1] + sensorInformation[2] == 3) {
            // sensors found a dead end, go back
            move = DOWN;
        }

    }




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