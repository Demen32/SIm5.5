#pragma once
#include"Header.h"

class Labyrinth {
public:
	vector<Objekt> myLabyrinth;
	vector<Objekt>* p_brainLabyrinth;
	vector<Objekt> brainLabyrinth;
	vector<int>* p_wayValue;
	Labyrinth(int size, Shader& sh);

	int numberOfFieldsSQR;
	int sizeGameField;
	float sizeQuadrant;


	Model model;
	Model ground;
	Model ball;
	Texture2D ball_tex;
	Texture2D tex;
	Texture2D tex_floor;

	void unload();

	void draw(Shader& sh);

	bool mainGoalViseted;
	bool subGoalViseted;

	bool showWayValues;
	void drawWayValues();

};