/*==============================================================
キャラクターメニュークラス
===============================================================*/

#ifndef CHARACTER_MENU
#define CHARACTER_MENU
# include <Siv3D.hpp>
#include "characterPage.h"
#include "character.h"
#include "page_switching_button.h"

class CharacterMenu
{
private:
	static const int CHARACTER_MAX = 4;
	Texture g_wallpaper;
	CharacterPage m_page;
	Character m_character[CHARACTER_MAX];
	int m_character_number = 0;
	PageSwtichingButton m_page_button_forward;
	PageSwtichingButton m_page_button_backward;

public:
	CharacterMenu();
	~CharacterMenu();
	void DrawBG();
	void DrawCharacter();
	void DrawButton();

	void PreviousPage();
	void NextPage();

	void SetMouseCursorPosition(int x, int y);
	void OnMouseClick();

private:
	void CreatePage(int character_number);
	
};
#endif // !CHARACTER_MENU

