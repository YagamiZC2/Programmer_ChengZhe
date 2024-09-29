#include "page_switching_button.h"
#include "stdafx.h"

PageSwtichingButton::PageSwtichingButton(Direction dir, float x, float y)
	:_diretcion(dir),_button_X(x), _button_Y(y)
{
}

PageSwtichingButton::~PageSwtichingButton()
{
}

void PageSwtichingButton::SetMouseCursorPosition(int x, int y)
{
	_mouse_cursor_pos_x = x;
	_mouse_cursor_pos_y = y;
}

bool PageSwtichingButton::IsOverlapMouseCursor()
{
	Point mouse_cursor(_mouse_cursor_pos_x, _mouse_cursor_pos_y);
	return RectF(_button_X, _button_Y, BUTTON_WIDTH, BUTTON_HEIGHT).intersects(mouse_cursor);
}

void PageSwtichingButton::Draw()
{
	//Triangle button(_button_X, _button_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
	ColorF color = IsOverlapMouseCursor() ? ColorF(1.0f, 1.0f, 1.0f) : ColorF(0.5f, 0.5f, 0.5f);

	//button.draw(color);
	if (_diretcion == Direction::Forward)
	{
		_iconR.drawAt(_button_X, _button_Y, color);
	}
	if (_diretcion == Direction::Backward)
	{
		_iconL.drawAt(_button_X, _button_Y, color);
	}

}
