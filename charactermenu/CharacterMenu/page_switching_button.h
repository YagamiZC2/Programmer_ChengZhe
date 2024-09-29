#ifndef PAGE_SWITCHING_BUTTON
#define PAGE_SWITCHING_BUTTON

#define BUTTON_WIDTH (64.0f)
#define BUTTON_HEIGHT (64.0f)

class PageSwtichingButton
{
public:
	enum class Direction { Forward, Backward };

private:
	Direction _diretcion = Direction:: Forward;
	float _button_X = 0;
	float _button_Y = 0;
	int _mouse_cursor_pos_x = 0;
	int _mouse_cursor_pos_y = 0; 
	const Texture _iconR{ 0xF0530_icon, 64 };
	const Texture _iconL{ 0xF0DA2_icon, 64 };

public:
	PageSwtichingButton(Direction dir, float x, float y);
	~PageSwtichingButton();

	void SetMouseCursorPosition(int x, int y);

	bool IsOverlapMouseCursor();

	void Draw();
};
#endif // !PAGE_SWITCHING_BUTTON

