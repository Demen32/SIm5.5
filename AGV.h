#pragma once
#include"Header.h"

class AGV {
public:
	vector<Objekt> myLabyrinth;
	Color col;
	int pos;

	Direction orientation;

	Vector3 posOnScreen;
	Vector3 posVec;
	Vector3 nowPos;
	Vector3 nowPosWrong;
	AGV(Color col, int numberOfFieldsSQR, int sizeGameField, float sizeQuadrant, vector<Objekt>& myLabyrinth, Shader& sh);

	Direction AGVBrain();

	int numberOfFieldsSQR;
	int sizeGameField;
	float sizeQuadrant;
	vector<bool> getSensorData();
	bool makeMove(Direction direction);

	Model model;
	Texture2D tex;

	void draw(Shader& sh);

	void drawWrong(Shader& sh, int pos);

	void unload();

	
};