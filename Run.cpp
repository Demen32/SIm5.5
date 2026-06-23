#include "Run.h"


Run::Run(int trys, float posX,float posY, float height, float width,int steps, Font* p_arial) {
	this->trysLeft = trys;
	this->trys = trys;
	this->pos = {posX,posY};
	this->height = height;
	this->width = width;
	this->col = BLACK;
	this->running=false;
	//this->activated=false;
	this->box = {pos.x,pos.y,width,height};
	this->stepsAllowed = steps;
	this->stepsLeft = steps;
	this->p_arial = p_arial;
	this->shortestPath = -1;
}

void Run::isClicked()
{
	if (!running) {
		if (CheckCollisionPointRec(GetMousePosition(),box)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (trysLeft > 0)
				running = true;
			else if (trysLeft == 0) {
				reset();
				running = true;
			}
				
			//activated = true;
		}
	}

}

void Run::draw()
{
	DrawCircle((box.x + box.width * 0.5f),
		(box.y + box.height * 0.5f),
		box.width *0.9,
		{ 0,0,0,255 });

	// innerer Kreis (etwas kleiner)
	DrawCircle((box.x + box.width * 0.5f),
		(box.y + box.height * 0.5f),
		box.width * 0.9 - 4.0f,
		{255,255,255,255});
	string counterSteps = to_string(stepsLeft);
	string counterStepsAllowed = to_string(stepsAllowed);
	
	//DrawText(counterStepsAllowed.c_str(), pos.x + 30, pos.y + 30, 30, BLACK);


	drawStepsCounter();

	drawShortestPath();

}

void Run::update()
{
	if (running)
		stepsLeft--;
	if (stepsLeft <= 0||deliveredPackage) {
		running = false;
		trysLeft--;
		stepsLeft = stepsAllowed;
		deliveredPackage = false;
		gotPackage = false;
	}



}

void Run::drawStepsCounter()
{

	float w = box.width / 1.0f;
	float h = box.height / 5.0f;


	float x = pos.x + (box.width - w) * 0.5f;
	float y = pos.y + (box.height - h) * 0.5f;

	DrawRectangle((int)x, (int)y, (int)w, (int)h, BLACK);

	if (deliveredPackage)
		DrawRectangle((int)x, (int)y, (int)w, (int)h, GREEN);

	float prozent = 0.0f;
	if (stepsAllowed > 0) prozent = (float)stepsLeft / (float)stepsAllowed;
	if (prozent < 0.0f) prozent = 0.0f;
	if (prozent > 1.0f) prozent = 1.0f;

	DrawRectangle((int)(x + 4), (int)(y + 4),
		(int)((w - 8) * prozent), (int)(h - 8), WHITE);

	if (prozent < 0.5)
		col = WHITE;
	else
		col = BLACK;
	if (deliveredPackage)
		drawTextExCenteredInBox("Goal Reached", h, 1, col);
	else if (running)
		drawTextExCenteredInBox(to_string(stepsLeft), h, 1, col);
	else if (trysLeft == 0)
		drawTextExCenteredInBox("Start New", h, 1, col);
	else if (!running)
		drawTextExCenteredInBox("Start Run", h, 1, col);

	// Kreise für trysLeft (Slots sind fest: trys ist immer die maximale Anzahl)
	

	int filled = trysLeft;
	if (filled < 0) filled = 0;
	if (filled > trys) filled = trys;

	float r = (float)OFFSET/10.0;          // OFFSET als Radius
	float gap = r * 0.75f;

	float totalW = 0.0f;
	if (trys > 0)
		totalW = (float)trys * (2.0f * r) + (float)(trys - 1) * gap;

	float startCx = x + (w * 0.5f) - (totalW * 0.5f) + r;
	float cy = y - h;      // oberhalb

	int i = 0;
	for (i = 0; i < trys; i++)
	{
		float cx = startCx + (float)i * ((2.0f * r) + gap);

		DrawCircleLines((int)cx, (int)cy, r, BLACK);

		if (i < filled)
			DrawCircle((int)cx, (int)cy, r, BLACK);
	}
}


void Run::drawTextExCenteredInBox(const std::string& text, float fontSize, float spacing, Color col)
{
	Vector2 size = MeasureTextEx(*p_arial, text.c_str(), fontSize, spacing);

	Vector2 p;
	p.x = pos.x + (box.width - size.x) * 0.5f;
	p.y = pos.y + (box.height - size.y) * 0.5f;


	DrawTextEx(*p_arial, text.c_str(), p, fontSize, spacing, col);
}

void Run::drawShortestPath()
{

	float w = box.width / 1.0f;
	float h = box.height / 5.0f;


	float x = pos.x + (box.width - w) * 0.5f;
	float y = pos.y + (box.height - h) * 0.5f;


	float font = h / 1.4f;
	string text = "Shortest Path Found:";
	
	Vector2 size = MeasureTextEx(*p_arial, text.c_str(),font, 1);

	Vector2 p;
	p.x = pos.x + (box.width - size.x) * 0.5f;
	p.y = pos.y + (box.height - size.y) * 0.5f+OFFSET*0.5;
	DrawTextEx(*p_arial, text.c_str(), p, font, 1, BLACK);

	if(shortestPath==-1)
		text="NONE";
	else
		text = to_string(shortestPath);
	size = MeasureTextEx(*p_arial, text.c_str(), font, 1);
	p.x = pos.x + (box.width - size.x) * 0.5f;
	p.y = pos.y + (box.height - size.y) * 0.5f + OFFSET*0.8;


	if (shortestPath == -1) 
		DrawTextEx(*p_arial, text.c_str(), p, font, 1, RED);
	else
		DrawTextEx(*p_arial, text.c_str(), p, font, 1, BLACK);


}



void Run::reset()
{
	trysLeft = trys;
	shortestPath = -1;
	deliveredPackage = false;
	gotPackage = false;
}





