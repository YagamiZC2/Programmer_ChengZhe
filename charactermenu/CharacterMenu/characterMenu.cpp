#include <iostream>
#include "characterMenu.h"
# include <Siv3D.hpp>
CharacterMenu::CharacterMenu()
	:g_wallpaper(U"bg.png"),
	m_page_button_forward(PageSwtichingButton::Direction::Forward, 1216, 350),
	m_page_button_backward(PageSwtichingButton::Direction::Backward, 64, 350)
{	//                                                       age level hp  mhp  mp    mmp  str int dex def pie
	m_character[0] = { "character1.png", "ブレード", "ナイト", 30, 30, 150, 150, 1000, 1000, 25, 9, 12, 15, 10 };
	m_character[1] = { "character2.png", "ボー", "アーチャー", 18, 30, 130, 130, 3000, 3000, 10, 9, 25, 10, 10 };
	m_character[2] = { "character3.png", "ダガー", "盗賊",     20, 30, 130, 130, 3000, 3000, 10, 9, 25, 15, 5 };
	m_character[3] = { "character4.png", "マホー", "魔法使い", 50, 30, 100, 100, 5000, 5000, 10, 50, 10, 15, 5 };
	CreatePage(m_character_number);
}

CharacterMenu::~CharacterMenu()
{
}

void CharacterMenu::DrawBG()
{

	g_wallpaper.resized({ 1280,700 }).draw();

	Rect{ 100,200,300,300 }
		.draw(Arg::top = ColorF{ 0.5, 0.7, 0.9, 0.5 }, Arg::bottom = ColorF{ 0.5, 0.9, 0.7, 0.5 })
		.drawFrame(3,0);

	Rect{ 870,200,300,300 }
		.draw(Arg::top = ColorF{ 0.9, 0.5, 0.7, 0.5 }, Arg::bottom = ColorF{ 0.7, 0.5, 0.9, 0.5 })
		.drawFrame(3, 3, Palette::Mediumpurple);

	RoundRect({ 490,180,300,300,150 }).draw(ColorF{ 0.0, 0.0, 0.0, 0.5 });

}

void CharacterMenu::DrawCharacter()
{
	m_page.Draw();
}

void CharacterMenu::DrawButton()
{
	m_page_button_backward.Draw();
	m_page_button_forward.Draw();
}

void CharacterMenu::PreviousPage()
{
	m_character_number = (m_character_number - 1 + CHARACTER_MAX) % CHARACTER_MAX;
	CreatePage(m_character_number);
}

void CharacterMenu::NextPage()
{
	m_character_number = (m_character_number + 1) % CHARACTER_MAX;

	CreatePage(m_character_number);
}

void CharacterMenu::SetMouseCursorPosition(int x, int y)
{
	m_page_button_forward.SetMouseCursorPosition(x, y);
	m_page_button_backward.SetMouseCursorPosition(x, y);

}

void CharacterMenu::OnMouseClick()
{
	if (m_page_button_forward.IsOverlapMouseCursor())
	{
		NextPage();
	}

	if (m_page_button_backward.IsOverlapMouseCursor())
	{
		PreviousPage();
	}
}

void CharacterMenu::CreatePage(int character_number)
{
	m_page =
		CharacterPage{
		m_character[character_number].GetPortraitFileName(),
		m_character[character_number].GetName(),
		m_character[character_number].GetJob(),
		m_character[character_number].GetAge()  ,
		m_character[character_number].GetLevel(),
		m_character[character_number].GetHp()   ,
		m_character[character_number].GetMaxHP(),
		m_character[character_number].GetMp()   ,
		m_character[character_number].GetMaxMP(),
		m_character[character_number].GetStr()  ,
		m_character[character_number].GetIntell(),
		m_character[character_number].GetDex()  ,
		m_character[character_number].GetDef()  ,
		m_character[character_number].GetPiety()
	};
}

