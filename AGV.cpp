#include "AGV.h"


AGV::AGV(Color col, int numberOfFieldsSQR, int sizeGameField, float sizeQuadrant, vector<Objekt>& myLabyrinth, Shader& sh)
{
    this->col = col;
    this->numberOfFieldsSQR = numberOfFieldsSQR;
    this->sizeGameField = sizeGameField;
    this->sizeQuadrant = sizeQuadrant;

    this->pos = 1;
    this->myLabyrinth = myLabyrinth;

    this->orientation = DOWN;

    //Startposiition
    posVec = { 0,sizeQuadrant / 2.0f,0 };
    posVec.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos % numberOfFieldsSQR);
    posVec.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos / numberOfFieldsSQR);

    nowPos = posVec;
    nowPosWrong = posVec;

    this->model = LoadModelFromMesh(GenMeshSphere((float)sizeQuadrant / 3.0f, 20, 20));

    Image img = GenImageColor(10, 10, RED);
    this->tex = LoadTextureFromImage(img);
    UnloadImage(img);
    this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = tex;
    this->model.materials[0].shader = sh;


}

Direction AGV::AGVBrain()
{
    Direction direction;
    
    direction = (Direction)GetRandomValue(-2, 2);
  // cout <<"Student: "<< direction << endl;
   return direction;
 
}

vector<bool>AGV::getSensorData()
{
    vector<bool> sensoryData = { 0,0,0 };

    int indexUp = pos - numberOfFieldsSQR;
    int indexRight = pos + 1;
    int indexLeft = pos - 1;




    if (orientation == UP) {
         indexUp = pos - numberOfFieldsSQR;
         indexRight = pos + 1;
         indexLeft = pos - 1;
    }
    else if (orientation == DOWN) {
         indexUp = pos + numberOfFieldsSQR;
         indexRight = pos - 1;
         indexLeft = pos + 1;
    }
    else if (orientation == RIGHT) {
        indexUp = pos + 1;
        indexRight = pos + numberOfFieldsSQR;
        indexLeft = pos - numberOfFieldsSQR;
    }
    else if (orientation == LEFT) {
        indexUp = pos -1;
        indexRight = pos - numberOfFieldsSQR;
        indexLeft = pos + numberOfFieldsSQR;
    }

    if (indexUp >= 0 && indexUp < myLabyrinth.size())
        sensoryData[0] = (myLabyrinth[indexUp] == BLOCK);
    if (indexRight >= 0 && indexRight < myLabyrinth.size())
        sensoryData[1] = (myLabyrinth[indexRight] == BLOCK);
    if (indexLeft >= 0 && indexLeft < myLabyrinth.size())
        sensoryData[2] = (myLabyrinth[indexLeft] == BLOCK);




    return sensoryData;
}

bool AGV::makeMove(Direction dir)
{
    int posOld = pos;
    int row = pos / numberOfFieldsSQR;
    int col = pos % numberOfFieldsSQR;


    //Übersetzen von Angebener Richtung in globale Richtung über Ausrichtung
    if (orientation == DOWN)
        dir = (Direction)((int)dir* - 1);
    else if (orientation == RIGHT) {
        if((int)dir%2==0)
            dir = (Direction)((int)dir / -2);
        else
            dir = (Direction)((int)dir * 2);
    }
        
    else if (orientation == LEFT) {
        if ((int)dir % 2 == 0)
            dir = (Direction)((int)dir / 2);
        else
            dir = (Direction)((int)dir * -2);
    }

   

    switch (dir) {
    case RIGHT: // rechts
        if (col < numberOfFieldsSQR - 1&& (myLabyrinth)[pos+1]!=BLOCK) { // nicht am rechten Rand
            pos++;
            orientation = RIGHT;
            return true;
        }
        break;

    case LEFT: // links
        if (col > 0 && (myLabyrinth)[pos - 1] != BLOCK) { // nicht am linken Rand
            pos--;
            orientation = LEFT;
            return true;
        }
        break;

    case DOWN: // runter
        if (row < numberOfFieldsSQR - 1 && (myLabyrinth)[pos + numberOfFieldsSQR] != BLOCK) { // nicht in der letzten Reihe
            pos += numberOfFieldsSQR;
            orientation = DOWN;
            return true;
        }
        break;

    case UP: // hoch
        if (row > 0 && (myLabyrinth)[pos - numberOfFieldsSQR] != BLOCK) { // nicht in der ersten Reihe
            pos -= numberOfFieldsSQR;
            orientation = UP;
            return true;
        }
        break;
    }

    return false; // Bewegung nicht erlaubt

    /*if (pos<0 || pos>numberOfFieldsSQR * numberOfFieldsSQR)
        pos = posOld;

    

    return false;*/

}

void AGV::draw(Shader& sh)
{
 
   
    //Soll Position wird gesetzt
    posVec = { 0,sizeQuadrant / 2.0f,0 };
    posVec.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos % numberOfFieldsSQR);
    posVec.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos / numberOfFieldsSQR);

    
    float dt = GetFrameTime();
    float speed = 3.0f; // Einheiten pro Sekunde (anpassen)

    // nur XZ bewegen
    Vector3 target = posVec;
    target.y = nowPos.y;

    Vector3 delta = Vector3Subtract(target, nowPos);
    float dist = Vector3Length(delta);

    if (dist > 0.0001f)
    {
        float step = speed * dt;

        if (step >= dist)
        {
            nowPos = target;
        }
        else
        {
            Vector3 dir = Vector3Scale(delta, 1.0f / dist);
            nowPos = Vector3Add(nowPos, Vector3Scale(dir, step));
        }
    }


    //DrawSphere(nowPos, sizeQuadrant/2.5f, col);
    DrawModel(model, nowPos, 1.0f, RAYWHITE);
}


void AGV::drawWrong(Shader& sh, int pos)
{
    //Soll Position wird gesetzt
    Vector3 posVecW = { 0,sizeQuadrant / 2.0f,0 };
    posVecW.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos % numberOfFieldsSQR);
    posVecW.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos / numberOfFieldsSQR);


    float dt = GetFrameTime();
    float speed = 3.0f; // Einheiten pro Sekunde (anpassen)

    // nur XZ bewegen
    Vector3 target = posVecW;
    target.y = nowPosWrong.y;

    Vector3 delta = Vector3Subtract(target, nowPosWrong);
    float dist = Vector3Length(delta);

    if (dist > 0.0001f)
    {
        float step = speed * dt;

        if (step >= dist)
        {
            nowPosWrong = target;
        }
        else
        {
            Vector3 dir = Vector3Scale(delta, 1.0f / dist);
            nowPosWrong = Vector3Add(nowPosWrong, Vector3Scale(dir, step));
        }
    }


    //DrawSphere(nowPos, sizeQuadrant/2.5f, col);
    DrawModel(model, nowPosWrong, 1.0f, {255,255,255,60});
}


void AGV::unload()
{
    UnloadModel(model);
    UnloadTexture(tex);
}


