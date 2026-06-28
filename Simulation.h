#pragma once
#include"Header.h"
#include"Cam.h"
#include"Labyrinth.h"
#include"AGV.h"
#include"Run.h"
#include"AGVBrain.h"



class Simulation {
public:
	Simulation() : sh(LoadShader("Assets/min_light.vs", "Assets/min_light.fs"))
		, labyrinth(30, sh)
		, brain(labyrinth.brainLabyrinth,1,DOWN)
		, mouse(PINK, labyrinth.numberOfFieldsSQR, labyrinth.sizeGameField,
			labyrinth.sizeQuadrant, labyrinth.myLabyrinth, sh)
		, myRun(3, OFFSET, HEIGHT/2.0-150, HEIGHT/8,HEIGHT/8, labyrinth.myLabyrinth.size() / 4.0, &arial)
	{



		//Shader
		// Uniform-Locations
		locLightPos = GetShaderLocation(sh, "uLightPos");
		locViewPos = GetShaderLocation(sh, "uViewPos");
		// Startposition des Lichts
		lightPos = { -3.0f, 20.5f, -3.0f };

		//Zeit Kontrolle
		interval = 0.0f;
		lastCall = 0.0;

		//Laden von Assets
		tu_logo = LoadTexture("Assets/TU_Logo.png");
		iit_logo = LoadTexture("Assets/IIT_Logo.png");
		arial = LoadFontEx("Assets/arial.ttf", 150, 0, 0);

		//Einstellungen des Fensters
		SetTextureFilter(arial.texture, TEXTURE_FILTER_BILINEAR);
		SetTargetFPS(60);


		//Labyrinth bekommt Gehirn Map, startet mit Free
		labyrinth.p_brainLabyrinth = &brain.brainLabyrinth;
		labyrinth.p_wayValue = &brain.wayValueMatrix;
		labyrinth.showWayValues = brain.showWayValues;
	
	}


	void end() {

		CloseWindow();

		UnloadFont(arial);
		UnloadTexture(tu_logo);
		UnloadTexture(iit_logo);
		UnloadShader(sh);
	}

	void update() {


		updateShaderAndCam();
		bool noRunRunning = true;
		
			if (myRun.running)
				noRunRunning = false;
		
			if (!myRun.running&&noRunRunning)
				myRun.isClicked();
		
		
		//AGV macht schritt
		
			if (myRun.stepsLeft == myRun.stepsAllowed) {
				mouse.pos = 1;
				mouse.orientation = DOWN;

				brain.pos = 1;
				brain.orientation = DOWN;

				if (myRun.trysLeft == 3) {
					brain.brainLabyrinth = labyrinth.brainLabyrinth;
				}
			}

			if (myRun.running) {
				
				//Zeitsteuerung
				float t = GetTime();

				//Brain gets new sensor Data
				brain.sensorInformation = mouse.getSensorData();

				if (t - lastCall >= interval&& (mouse.nowPos.x== mouse.posVec.x) && (mouse.nowPos.z == mouse.posVec.z)) {
					
					//Zug wird gemacht
					while (!mouse.makeMove(brain.makeMove())) {
						
					}
					
					//cout << "\n------------------------\n\n";
					cout << "Real pos: " << mouse.pos<<endl;
					cout << "Brain pos: " << brain.pos<<endl<<endl;


						if (myRun.running) {
							

							if (labyrinth.myLabyrinth[mouse.pos] == SUBGOAL) {
								myRun.gotPackage = true;
								
									
							}
							if (labyrinth.myLabyrinth[mouse.pos] == GOAL && myRun.gotPackage) {
								myRun.deliveredPackage = true;
								if(myRun.shortestPath==-1||myRun.shortestPath>= myRun.stepsAllowed - myRun.stepsLeft)
									myRun.shortestPath = myRun.stepsAllowed - myRun.stepsLeft;
								
							}

							labyrinth.subGoalViseted = myRun.gotPackage;
							labyrinth.mainGoalViseted = myRun.deliveredPackage;

							myRun.update();
							
						}
					
					lastCall = t;
				}
			}
		

	}

	void draw() {
		BeginDrawing();


		BeginMode3D(myCamera.myCam);
		//DrawGrid(4, 10);

		ClearBackground(WHITE);
		
		mouse.draw(sh);
		labyrinth.draw(sh);
		//Falsche Position zeichnen
		if (brain.pos != mouse.pos)
			mouse.drawWrong(sh, brain.pos);

		EndMode3D();
		
		//Logo und Titel
		DrawTextEx(arial, "EII Projektaufgabe - Version 0.9", { (float)WIDTH-MeasureTextEx(arial,"EII Projektaufgabe - Version 1.0",FONTSIZE /2.0f,1).x-10,(float)HEIGHT - MeasureTextEx(arial,"EII Projektaufgabe - Version 0.9",FONTSIZE / 2.0f,1).y-10 }, FONTSIZE / 2.0f, 1, BLACK);
		DrawTextEx(arial, "AGV Simulator", { (float)tu_logo.width + iit_logo.width + 30,(float)tu_logo.height / 2 - 20 }, FONTSIZE, 5, BLACK);
		DrawTexture(tu_logo, 0, 0, WHITE);
		DrawTexture(iit_logo, tu_logo.width, 30, WHITE);
		

		//Runs
		
			myRun.draw();
	

		//drawBrainInformation();

		EndDrawing();
	}

	void checkifReachedGoal(){

		
		if (labyrinth.myLabyrinth[mouse.pos] == SUBGOAL);

	}

	void run() {
		while (!WindowShouldClose()) {



			update();

			draw();


		}

		end();
	}


	void updateShaderAndCam() {
		//Kamera
		myCamera.update();

		//SHADER
		SetShaderValue(sh, locLightPos, &lightPos, SHADER_UNIFORM_VEC3);
		SetShaderValue(sh, locViewPos, &myCamera.myCam.position, SHADER_UNIFORM_VEC3);
		locRangeScale = GetShaderLocation(sh, "uRangeScale");

		SetShaderValue(sh, locRangeScale, &rangeScale, SHADER_UNIFORM_FLOAT);
	}

private:
	Shader sh;
	int locLightPos;
	int locViewPos;
	Vector3 lightPos;
	float rangeScale = 0.1f; //  Reichweite vom Licht
	int locRangeScale;

	float interval = 0.5f;
	float lastCall = 0.0;

	const int HEIGHT = ::HEIGHT;
	const int WIDTH = ::WIDTH;
	const int OFFSET = ::OFFSET;
	const int FONTSIZE = ::FONTSIZE;

	Texture2D  tu_logo;
	Texture2D  iit_logo;
	Font arial;

	Cam myCamera;

	//Objekte der Simulation
	Labyrinth labyrinth;
	AGV mouse;
	Run myRun;
	AGVBrain brain;

	vector<Objekt> map;


	void drawBrainInformation() {

		Vector2 pos = { WIDTH - 3.5 * OFFSET ,OFFSET / 2.0f };

		DrawRectangle(pos.x, pos.y , 3 * OFFSET, 4 * OFFSET, DARKGRAY);
		DrawRectangle(pos.x+3, pos.y+3, 3 * OFFSET-6, 4 * OFFSET-6, WHITE);

		printArialText("Sensor Data: ", { pos.x + 10,pos.y + 10 }, 1.1);


	}

	void printArialText(string text, Vector2 pos, float size) {

		DrawTextEx(arial, text.c_str(), pos, (FONTSIZE / 2.0f)* size, 3, BLACK);

	}


};