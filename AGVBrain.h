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

		/*find_goals();
		//init the distance array with zeros in appropiate size
		for (int i = 0; i < this->brainLabyrinth.size(); i++) {
			this->distanceArrayToCurrGoal.push_back(0);
		}
		for (int i = 0; i < this->brainLabyrinth.size(); i++) {
			this->visited.push_back(false);
		}
		cout << endl << "----------- Labyrinth -------------" << endl;
		print_vec_pos(distanceArrayToCurrGoal);
		cout << endl;
		cout << endl << "----------- BrainLabyrinth -------------" << endl;
		print_vec(this->brainLabyrinth);
		cout << endl;
		cout << endl << "----------- Pre-Visited Array ---------" << endl;
		print_vec(visited);
		cout << endl;
		calculateDistanceArray(posSubGoal, 0);
		cout << "--------- Distance Array ----------" << endl;
		print_vec(distanceArrayToCurrGoal);
		cout << endl << "----------- Post-Visited Array ---------" << endl;
		print_vec(visited);
		cout << endl;
		*/
	}


private:

	int cellsinarow = 17; //find correct length
	int yTranslate(int pos) { return pos % cellsinarow; }
	int xTranslate(int pos) { return pos / cellsinarow; }
	int translatePos(int xpos, int ypos) { return (xpos * cellsinarow + ypos); }
	Direction dir = UP;
	// global direction initialization


	/*

	//calculate the distances from each point in the lab to the current goal. Its filled with zeros in the size of the lab
	vector<int> distanceArrayToCurrGoal;

	//queue for tracking the breadth first filling
	vector<vector<int>> queue;

	//track currently visited fields
	vector<bool> visited;


<<<<<<< HEAD
	int yTranslate(int pos) { return pos % cellsinarow; }
	int xTranslate(int pos) { return pos / cellsinarow; }
	int translatePos(int xpos, int ypos) { 
			return (xpos * cellsinarow + ypos);
	}
	Direction dir = UP;
	// global direction initialization
=======
	
>>>>>>> f9d09f8a89b9478f0a46ed78c1670a9ca4da35e0

	//function to translate pos to xy
	vector<int> xyTrans(int pos) {
		vector<int> xy = { xTranslate(pos),yTranslate(pos) };
		return xy;
	}

	//pretty print a vector with objekt
	void print_vec(vector<Objekt> vec) {
		for (int i = 0; i < vec.size(); i++) {
			if (i > 0) cout << ", ";
			if (i % cellsinarow == 0) cout << endl;
			cout << vec[i];

		}
	}

	//pretty print a vector with int 
	void print_vec(vector<int> vec) {
		for (int i = 0; i < vec.size(); i++) {
			if (i > 0) cout << ", ";
			if (i % cellsinarow == 0) cout << endl;
			cout << vec[i];

		}
	}

	//pretty print a vector with int 
	void print_vec(vector<bool> vec) {
		for (int i = 0; i < vec.size(); i++) {
			if (i > 0) cout << ", ";
			if (i % cellsinarow == 0) cout << endl;
			cout << vec[i];

		}
	}

	//pretty print a vector with int 
	void print_vec_pos(vector<int> vec) {
		for (int i = 0; i < vec.size(); i++) {
			if (i > 0) cout << ", ";
			if (i % cellsinarow == 0) cout << endl;
			cout << i;

		}
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
				cout << "Index out of Bounds: Couldn't find goal or subgoal" << endl;
			}
			else if (brainLabyrinth[i] == 2) {
				subGoal[0] = xTranslate(i);
				subGoal[1] = yTranslate(i);
				posSubGoal = i;
				subGoalFound = true;
				i++;
				cout << "-----------subgoal found---------------" << endl;
				cout << "Subgoal Position at (" << subGoal[0] << "|" << subGoal[1] << ")" << endl;
				cout << "Pos at " << posSubGoal << endl;
			}
			else if (brainLabyrinth[i] == 3) {
				goal[0] = xTranslate(i);
				goal[1] = yTranslate(i);
				posGoal = i;
				goalFound = true;
				i++;
				cout << "-----------goal found---------------" << endl;
				cout << "Goal Position at (" << goal[0] << "|" << goal[1] << ")" << endl;
				cout << "Pos at " << posGoal << endl;

			}
			else {
				i++;
			}

		}
	}




	//check if pos is on field or out of bounds and if there is a wall on pos
	bool check_pos_on_Field(int x, int y) {
		cout << "check" << endl;
		if ((0 <= x) && (x < cellsinarow) && (0 <= y) && (y < cellsinarow)) {
			cout << "-------check inbound-------" << endl;
			//cout << "curr x: " << x << endl;
			//cout << "curr y: " << y << endl;
			//cout << "curr pos: " << translatePos(x, y) << endl;

			//first inbounds 
			//cout << (this->brainLabyrinth[translatePos(x, y)] == 0) << endl << translatePos(x, y) << endl;
			if (brainLabyrinth[translatePos(x, y)] == FREE) {
				cout << "-------check Walls-------" << endl;

				//second walldetection
				if (not visited[translatePos(x, y)]) {
					cout << "-------check visited-------" << endl;

					//third visited or not
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	//function to find adjacent fields from a starting pos in a vector using int pos
	vector<int> find_adj_pos(int pos) {
		cout << "curr pos: " << pos << endl;
		vector<int> result;
		int x = xTranslate(pos);
		int y = yTranslate(pos);
		cout << "curr pos trans: " << translatePos(x,y) << endl;

		//left field
		//cout << check_pos_on_Field(x - 1, y)[0] << endl;
		//cout << check_pos_on_Field(x - 1, y)[1] << endl;
		//cout << not visited[translatePos(x - 1, y)] << endl;

		if (check_pos_on_Field(x - 1, y)) {
	
			result.push_back(translatePos(x - 1, y));
			cout << result[0] << endl;
		}
		
		//right field
		if (check_pos_on_Field(x + 1, y)) {
			result.push_back(translatePos(x + 1, y));
		}
		//upper field
		if (check_pos_on_Field(x, y +1)) {
			result.push_back(translatePos(x, y + 1));
		}
		//lower field
		if (check_pos_on_Field(x, y -1)) {
			result.push_back(translatePos(x, y - 1));
		}
		return result;
	}



	//recursive algo that starts at currGoal and assigns distance values to the pos
	//first calcDist set goal to visited
	void calculateDistanceArray(int posCurrGoal, int currStep) {
		cout << "--------Start new Recursion----------" << endl;
		vector<int> adjFields = find_adj_pos(posCurrGoal);
		for (int i = 0; i < adjFields.size(); i++) {
			vector<int> newEntry = { adjFields[i],currStep + 1 };
			queue.push_back(newEntry);
		}
		cout << "Adj Fields: " << adjFields.size() << endl;
		//cout << queue[0][0] << endl;
		if (queue.size() != 0) {
			int newPos = queue[0][0];
			int newStep = queue[0][1];
			distanceArrayToCurrGoal[newPos] = newStep; 
			visited[newPos] = true;
			queue.erase(queue.begin());
			calculateDistanceArray(queue[0][0], queue[0][1]);	
		}
		else {
			return;
		}
		
	}

	vector<int> find_shortest_path(int startPos, int currGoal) {
		vector<int> path;

		return path;
	}
	*/
};