#include "AGVBrain.h"

Direction AGVBrain::makeMove()
{
    Direction move;

    move = (Direction)GetRandomValue(-2, 2);
    pos += move;
    cout << pos << ' ';
    return move;
    string hey = "hello world2";
}
