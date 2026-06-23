#pragma once
#include"Header.h"

class Cam {
public:
	Camera3D myCam;
	float R;
	const float R_MIN = 10.0f;
	const float R_MAX = 400.0f;
	float pitch;
	float yaw;
	const float PITCH_LIMIT_MAX = PI / 2 - 0.01f;
	const float PITCH_LIMIT_MIN = 0.5;

	Cam();

	void update();

};