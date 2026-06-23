#pragma once
#include"Header.h"

class AGVBrain {
public:
	//----------------DONT CHANGE-------------------//
		//Will be called to get move
	Direction makeMove();

	//Order of sensors: Up Right Left
	//Will be true if object is detected
	vector<bool> sensorInformation;

	//Main list of all elements 
	vector<Objekt> brainLabyrinth;

	//Determines if wayValueMatrix is shown
	bool showWayValues;

	//Index inside brainLabyrinth where AGV is
	int pos;

	//Direction in which the robots looks
	Direction orientation;

	//Vector for values to show as colors
	vector<int> wayValueMatrix;

	AGVBrain(vector<Objekt>& brainLabyrinth,
		int startPos,
		Direction orientation) {
		this->brainLabyrinth = brainLabyrinth;
		this->orientation = orientation;
		this->pos = startPos;
		//----------------DONT CHANGE-------------------//

		//--------------OPTIONAL CHANGE -----------------//
				//Just Zeros
		for (int i = 0; i < this->brainLabyrinth.size(); i++) {
			this->wayValueMatrix.push_back(0);
		}
		//Change to true
		this->showWayValues = false;
		//--------------OPTIONAL CHANGE -----------------//
	}


private:
};