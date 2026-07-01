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
		find_goals();

	}


private:

	int cellsinarow = 17;

	int yTranslate(int pos) { return pos % cellsinarow; }
	int xTranslate(int pos) { return pos / cellsinarow; }
	int translatePos(int xpos, int ypos) { return (xpos * cellsinarow + ypos); }
	Direction dir = UP;
	// global direction initialization

	//function to translate pos to xy
	vector<int> xyTrans(int pos) {
		vector<int> xy = { xTranslate(pos),yTranslate(pos) };
		return xy;
	}

	//check if pos is on field or out of bounds and if there is a wall on pos
	bool check_pos_on_Field(int x, int y) {
		if ((0 < x < cellsinarow) && (0 < y < cellsinarow) && (brainLabyrinth[translatePos(x,y)] != 0)) {
			return true;
		}
		else {
			return false;
		}
	}

	//function to find adjacent fields from a starting pos
	vector<int> find_adj_pos(int pos) {
		vector<int> result;
		vector<int> xyPos = xyTrans(pos);
		if (check_pos_on_Field(xyPos[0] - 1, xyPos[1])) {
			result.push_back(translatePos(xyPos[0] - 1, xyPos[1]));
		}
		//add other adjacent fields
	}

	int goal[2];
	int subGoal[2];
	int posGoal;
	int posSubGoal;

	//find xy of sub-goal and goal
	void find_goals() {
		bool goalFound = false;
		bool subGoalFound = false;
		
		int i = 0;
		while (not goalFound || not subGoalFound) {
			if (i > brainLabyrinth.size()) {
				cout << "Index out of Bounds: Couldn't find goal or subgoal"<<endl;
			}
			else if (brainLabyrinth[i] == 2) {
				subGoal[0] = xTranslate(i);
				subGoal[1] = yTranslate(i);
				posSubGoal = i;
				subGoalFound = true;
				i++;
				cout << "-----------subgoal found---------------"<< endl;
				cout << "Subgoal Position at (" << subGoal[0] << "|" << subGoal[1]<<")" << endl;

			}
			else if (brainLabyrinth[i] == 3) {
				goal[0] = xTranslate(i);
				goal[1] = yTranslate(i);
				posGoal = i;
				goalFound = true;
				i++;
				cout << "-----------goal found---------------" << endl;
				cout << "Goal Position at (" << goal[0] << "|" << goal[1]<<")" << endl;

			}
			else {
				i++;
			}

		}
	}
	//calculate the distances from each point in the lab to the current goal
	vector<int> distanceArrayToCurrGoal;
	//recursive algo that starts at currGoal and assigns distance values to the pos
	void distanceToCurrGoal(int currGoal) {
		vector<int> queue;


		
	}

	vector<int> find_shortest_path(int startPos, int currGoal) {
		vector<int> path;

		return path;
	}
};