#include "AGVBrain.h"



Direction AGVBrain::makeMove()
{
    Direction move;
    vector<int> wayChoosingOptions;
    int chosenOption;
    int cellsinarow = 17;

    cout << "startpos = " << pos << " startorientation = " << orientation << endl;

    move = (Direction)UP;
    if (sensorInformation[0] + sensorInformation[1] + sensorInformation[2] == 2) {
        // two walls detected
        for (int i = 0; i <= 2; i++) {
            if (sensorInformation[i] == 0) {
                if (i == 0) { move = UP; orientation = UP; }
                if (i == 1) { move = RIGHT; orientation = RIGHT; }
                if (i == 2) { move = LEFT; orientation = LEFT; }
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
            move = DOWN;
        }

    }


    switch (move) {
    case -1:
        pos = pos - cellsinarow;
        break;
    case -2:
        pos = pos - 1;
        break;
    case 2:
        pos = pos + 1;
        break;
    case 1:
        pos = pos + cellsinarow;
        break;
    }

    cout << "pos = " << pos << " move = " << move << endl;

    cout << "x = " << xtranslate(pos) << " y = " << ytranslate(pos) << endl << "---------" << endl;

    // orientation should be included



    return move;
}
