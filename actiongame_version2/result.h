#pragma once
void InitResult();
void UninitResult();
void UpdateResult();
void DrawResult();

typedef enum RESULT_STATE {
	RESULT_STATE_HP0,
	RESULT_STATE_CLEAR,
	RESULT_STATE_PLUS,
};