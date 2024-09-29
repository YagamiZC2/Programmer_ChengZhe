# include <Siv3D.hpp> // Siv3D v0.6.14
#include "characterMenu.h"
#include "CharacterPage.h"
#include "page_switching_button.h"

void Main()
{
	Window::Resize(1280, 700);
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.0, 0.0, 0.0 });
	CharacterMenu character;
	
	const Font fontMedium{ 36, Typeface::Medium };

	while (System::Update())
	{
		character.SetMouseCursorPosition(Cursor::Pos().x, Cursor::Pos().y);

		// 
		// 左キーが押されていたら | If left key is pressed
		/*if (KeyLeft.down())
		{
			character.PreviousPage();
		}*/

		// 右キーが押されていたら | If right key is pressed
		//if (KeyRight.down())
		//{
		//	character.NextPage();
		//}
		if (MouseL.down())
		{
			character.OnMouseClick();
		}
		character.DrawBG();
		character.DrawCharacter();

		character.DrawButton();

	}
}

