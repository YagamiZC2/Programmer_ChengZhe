/*キャラクターメニューのページクラス[characterPage.h]
*/

#ifndef CHARACTERPAGE_H
#define CHARACTERPAGE_H
# include <Siv3D.hpp>
#include <string.h>
class CharacterPage
{
private:
	Texture g_portrait;
	Font g_font;

	std::string c_name;
	std::string c_job;
	int c_age= 0;

	int c_level=0;
	int c_hp=0;
	int c_maxHP=0;
	int c_mp=0;
	int c_maxMP=0;
	int c_str=0;
	int c_int=0;
	int c_dex=0;
	int c_def=0;
	int c_piety=0;
	
public:
	CharacterPage();
	CharacterPage(
		std::string portrait_texture_filename,
		std::string c_name,
		std::string c_job,
		int age,
		int level,
		int hp,
		int maxHP,
		int mp,
		int maxMP,
		int str,
		int intell ,
		int dex,
		int def,
		int piety);
	~CharacterPage();
	void Draw();
};
#endif // !CHARACTERPAGE_H
