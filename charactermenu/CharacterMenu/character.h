#ifndef CHARACTER_H
#define CHARACTER_H
#include <string.h>
#include "characterPage.h"


class Character
{
private:
	std::string m_name;
	std::string m_job;
	int m_age = 0;
	int m_level = 0;
	int m_hp = 0;
	int m_maxHP = 0;
	int m_mp = 0;
	int m_maxMP = 0;
	int m_str = 0;
	int m_int = 0;
	int m_dex = 0;
	int m_def = 0;
	int m_piety = 0;
	std::string m_portrait_filename;

public:
	Character();
	~Character();
	Character(
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
		int intell,
		int dex,
		int def,
		int piety);

	std::string GetPortraitFileName();
	std::string GetName();
	std::string GetJob();
	int GetAge();
	int GetLevel();
	int GetHp();
	int GetMaxHP();
	int GetMp();
	int GetMaxMP();
	int GetStr();
	int GetIntell();
	int GetDex();
	int GetDef();
	int GetPiety();
};


#endif CHARACTER_H
