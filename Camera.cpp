#include"Header.h"
#include"Cam.h"

Cam::Cam() {
	this->myCam = {
		//Starpos
		{0,0,0},
		//Goal
		{0,0,0},
		//Up
		{0,1,0},
		//FoV
		25.0f,
		//
		CAMERA_PERSPECTIVE };
	this->R = 100.0f;

	this->pitch = 0.8f, yaw = 4.0f;


}

void Cam::update() {

	if (IsKeyDown(KEY_W)) pitch += 0.005f;
	if (IsKeyDown(KEY_S)) pitch -= 0.005f;
	if (IsKeyDown(KEY_D)) yaw += 0.005f;
	if (IsKeyDown(KEY_A)) yaw -= 0.005f;
	pitch = Clamp(pitch, PITCH_LIMIT_MIN, PITCH_LIMIT_MAX);

	// Smooth Zoom 
	static float targetR = 0.0f;
	if (targetR == 0.0f) targetR = R;

	float wheel = GetMouseWheelMove();
	if (wheel != 0.0f) {
		targetR *= (wheel > 0.0f) ? 0.95f : 1.05f;
		targetR = Clamp(targetR, R_MIN, R_MAX);
	}

	float t = 1.0f * GetFrameTime();   //  Smoothness (höher = schneller)
	if (t > 1.0f) t = 1.0f;
	R += (targetR - R) * t;
	R = Clamp(R, R_MIN, R_MAX);

	this->myCam.position = {
		R * cosf(pitch) * sinf(yaw),
		R * sinf(pitch),
		R * cosf(pitch) * cosf(yaw)
	};

}
