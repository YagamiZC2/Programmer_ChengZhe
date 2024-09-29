#include "characterPage.h"
# include <Siv3D.hpp>



CharacterPage::CharacterPage()
{
}

CharacterPage::CharacterPage(std::string portrait_texture_filename, std::string name, std::string job, int age, int level, int hp, int maxHP, int mp, int maxMP, int str, int intell, int dex, int def, int piety)
	:g_portrait(Unicode::Widen(portrait_texture_filename)),
	g_font(24, Typeface::Medium),
	c_name(name),
	c_age(age),
	c_job(job),
	c_level(level),
	c_hp(hp),
	c_maxHP(maxHP),
	c_mp(mp),
	c_maxMP(maxMP),
	c_str(str),
	c_int(intell),
	c_dex(dex),
	c_def(def),
	c_piety(piety)
{
}

CharacterPage::~CharacterPage()
{
}

void CharacterPage::Draw()
{
	g_portrait.resized({ 250,450 }).drawAt(640, 320);

	g_font(Unicode::Widen(c_name)).draw(24, Vec2{ 200, 220 }, ColorF{ 1.0,1.0,1.0 });
	g_font(Unicode::Widen("ジョブ：　" + c_job)).draw(24, Vec2{ 120, 260}, ColorF{1.0,1.0,1.0});
	g_font(Unicode::Widen("年齢：　"+ std::to_string(c_age) + "才")).draw(24, Vec2{ 120, 300}, ColorF{1.0,1.0,1.0});

	g_font(Unicode::Widen("Lv." + std::to_string(c_level))).draw(24, Vec2{ 900, 220 }, ColorF{ 1.0,1.0,1.0 });

	g_font(Unicode::Widen("HP：" + std::to_string(c_hp) + "/" + std::to_string(c_maxHP)))
		.draw(24, Vec2{ 900, 250}, ColorF{1.0,1.0,1.0});
	g_font(Unicode::Widen("MP：" + std::to_string(c_mp) + "/" + std::to_string(c_maxMP)))
		.draw(24, Vec2{ 900, 280 }, ColorF{ 1.0,1.0,1.0 });

	g_font(Unicode::Widen("筋力：" + std::to_string(c_str))).draw(24, Vec2{ 900, 310 }, ColorF{ 1.0,1.0,1.0 });
	g_font(Unicode::Widen("魔力：" + std::to_string(c_int))).draw(24, Vec2{ 900, 340 }, ColorF{ 1.0,1.0,1.0 });
	g_font(Unicode::Widen("素早さ：" + std::to_string(+ c_dex))).draw(24, Vec2{ 900, 370 }, ColorF{ 1.0,1.0,1.0 });
	g_font(Unicode::Widen("防御力：" + std::to_string(c_def))).draw(24, Vec2{ 900, 400 }, ColorF{ 1.0,1.0,1.0 });
	g_font(Unicode::Widen("信仰：" + std::to_string(c_piety))).draw(24, Vec2{ 900, 430 }, ColorF{ 1.0,1.0,1.0 });

}
