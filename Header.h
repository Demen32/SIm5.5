#pragma once

#include<raylib.h>
#include<raymath.h>
#include<vector>
#include<iostream>
#include <string>


using namespace std;

extern int HEIGHT;
extern int WIDTH;
extern int OFFSET;
extern int FONTSIZE;

enum Direction {
	UP = 1,
	DOWN = -1,
	RIGHT = 2,  
	LEFT = -2   
};

enum Objekt {
	BLOCK = 0,
	GOAL = 3,
	SUBGOAL = 2,
	FREE = 1
};

void startRaylib();


