#pragma once
#include"Header.h"


class Run {

private:
	
	
	
	
	
	int trys;
	

	//Interface
	Vector2 pos;
	float height;
	float width;
	Color col;
	Rectangle box;
	Font* p_arial;
	


public:
	int trysLeft;
	int stepsAllowed;
	int stepsLeft;
	bool running;
	//bool activated;

	void draw();

	Run(int trys, float posX, float posY, float height, float width, int steps, Font* p_arial);

	void isClicked();

	void update();

	void drawStepsCounter();

	void drawTextExCenteredInBox(const std::string& text, float fontSize, float spacing, Color col);

	void drawShortestPath();

	void reset();
	
	bool gotPackage;

	bool deliveredPackage;

	int shortestPath;

	

};