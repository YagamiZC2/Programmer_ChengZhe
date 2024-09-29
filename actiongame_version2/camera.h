#pragma once

struct CAMERA
{
	Float2	Position;
	Float2	Offset;
	float	ShakeOffset;
	int		TimeCount;
};


void InitCamera();
void UpdateCamera();
void ShakeCamera(float);

CAMERA* GetCamera();
