#include "Header.h"
#include"Labyrinth.h"
Labyrinth::Labyrinth(int size, Shader& sh)
{

	this->sizeGameField = size;

	

	//Labyrinth klassich
	/*vector<int> raw = {
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0,
	0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0,
	0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0,
	0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0,
	0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0,
	0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
	0, 0, 1, 0, 1, 0, 0, 1, 3, 0, 1, 1, 0, 0, 0, 0,
	0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 2, 0,
	0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0,
	0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
	0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
	0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
	0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};*/

	//Schöne Fabrik
	vector<int> raw = {
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0,
	0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0,
	0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,
	0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0,
	0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0,
	0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 0,
	0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	//Test mini
	/*vector<int> raw = {
	
	0,0,0,0,
	0,1,3,0,
	0,2,1,0,
	0,0,0,0,
	
	};*/
	
	for (int v : raw) {
		this->myLabyrinth.push_back(static_cast<Objekt>(v));
	}

	for (int i = 0; i < myLabyrinth.size(); i++) {
		brainLabyrinth.push_back(FREE);
	}

	for (int i = 0; i < myLabyrinth.size(); i++) {
		if (myLabyrinth[i] == SUBGOAL)
			brainLabyrinth[i] = SUBGOAL;
		else if (myLabyrinth[i] == GOAL)
			brainLabyrinth[i] = GOAL;
	}



	this->numberOfFieldsSQR = sqrt(myLabyrinth.size());
	this->sizeQuadrant= (float)sizeGameField / numberOfFieldsSQR;

	//Shader
	Mesh m = GenMeshCube(sizeQuadrant, sizeQuadrant / 2.0f, sizeQuadrant);
	this->model = LoadModelFromMesh(m);

	Image img = GenImageColor(10,10, DARKGRAY);
	this->tex = LoadTextureFromImage(img);
	UnloadImage(img);
	this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = tex;

	this->model.materials[0].shader = sh;

	//Floor
	Image img_ground = GenImageColor(10, 10, WHITE);
	this->tex_floor = LoadTextureFromImage(img_ground);

	this->ground = LoadModelFromMesh(GenMeshPlane(sizeQuadrant, sizeQuadrant, 30, 30));
	ground.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = tex_floor;
	ground.materials[0].shader = sh;
	UnloadImage(img_ground);

	//Goal
	Image img_ball = GenImageColor(10, 10, GOLD);
	this->ball_tex = LoadTextureFromImage(img_ball);

	//this->ball = LoadModelFromMesh(GenMeshSphere(2.0f*(float)sizeQuadrant/4.0f,20,20));
	this->ball = LoadModelFromMesh(GenMeshCone(1.0f * (float)sizeQuadrant / 4.0f, 2, 20));
	ball.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = ball_tex;
	ball.materials[0].shader = sh;
	UnloadImage(img_ball);

	mainGoalViseted = false;
	subGoalViseted = false;


	//Gehirn Map
	p_brainLabyrinth = 0;
}

void Labyrinth::unload()
{
	UnloadModel(model);
	UnloadTexture(tex);
	UnloadTexture(tex_floor);
	UnloadModel(ground);

	UnloadModel(ball);
	UnloadTexture(ball_tex);
}

void Labyrinth::draw(Shader& sh)
{
	int locEmissive = GetShaderLocation(sh, "uEmissive");

	// Normale Flächen
	float off = 0.0f;


	Vector3 pos = { -sizeQuadrant / 2.0f,sizeQuadrant/4.0f,-sizeQuadrant / 2.0f };
	
	//Undurchsichtige Objekte zeichnen
	for (int i = 0; i < myLabyrinth.size(); i++) {

		pos.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (i % numberOfFieldsSQR);
		pos.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (i / numberOfFieldsSQR);

		if (myLabyrinth[i] == BLOCK && (*p_brainLabyrinth)[i] == BLOCK) {
			
				DrawModel(this->model, pos, 1, { 255,255,255,255 });
			
		}
		else if ((*p_brainLabyrinth)[i] == BLOCK&&!myLabyrinth[i] == BLOCK) {
			DrawModel(this->model, pos, 1, RED);
		}
		else if (myLabyrinth[i] == SUBGOAL) {
			if (!subGoalViseted)
				DrawModel(ball, pos, 1.0f, YELLOW);
			else
				DrawModel(ball, pos, 1.0f, GREEN);
			
		} 
		else if (myLabyrinth[i] == GOAL) {
			if(!mainGoalViseted)
			DrawModel(ball, pos, 2.5f, RED);
			else
				DrawModel(ball, pos, 2.5f, GREEN);
		}
		else if(myLabyrinth[i] == FREE){
			//DrawModel(ball, pos, 2.5f, RED);
			//DrawSpehre(pos, BLACK);
			DrawSphere({ pos.x,pos.y-0.1f,pos.z }, 0.07, {0,0,0,255});
		}
	}
	//Durchsichtige Objekte zeichnen

	if (showWayValues) {
		drawWayValues();
	}

	for (int i = 0; i < myLabyrinth.size(); i++) {

		pos.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (i % numberOfFieldsSQR);
		pos.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (i / numberOfFieldsSQR);

		if (myLabyrinth[i] == BLOCK && !(*p_brainLabyrinth)[i] == BLOCK) {



			DrawModel(this->model, pos, 1, { 255,255,255,40 });
		}
	}

	



}

void Labyrinth::drawWayValues()
{

	Vector3 pos = { -sizeQuadrant / 2.0f,0,-sizeQuadrant / 2.0f };

	for (int i = 0; i < myLabyrinth.size(); i++) {

		pos.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (i % numberOfFieldsSQR);
		pos.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (i / numberOfFieldsSQR);

		if ((*p_wayValue)[i] >= 0&& (*p_wayValue)[i]<9999) {

				DrawModel(this->ground, pos, 1, { (unsigned char)((int)255 - 8 * (*p_wayValue)[i]),0,(unsigned char)((int)0 + 8 * (*p_wayValue)[i]),100 });
		}
	}
}

