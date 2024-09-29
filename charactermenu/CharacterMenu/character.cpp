#include "character.h"

Character::Character()
{
}

Character::~Character()
{
}

Character::Character(std::string portrait_texture_filename, std::string name, std::string job, int age, int level, int hp, int maxHP, int mp, int maxMP, int str, int intell, int dex, int def, int piety)
	:
	m_portrait_filename(portrait_texture_filename),
	m_name(name),
	m_age(age),
	m_job(job),
	m_level(level),
	m_hp(hp),
	m_maxHP(maxHP),
	m_mp(mp),
	m_maxMP(maxMP),
	m_str(str),
	m_int(intell),
	m_dex(dex),
	m_def(def),
	m_piety(piety)
{
}

std::string Character::GetPortraitFileName()
{
	return m_portrait_filename;
}

std::string Character::GetName()
{
	return m_name;
}

std::string Character::GetJob()
{
	return m_job;
}

int Character::GetAge()
{
	return m_age;
}

int Character::GetLevel()
{
	return m_level;
}

int Character::GetHp()
{
	return m_hp;
}

int Character::GetMaxHP()
{
	return m_maxHP;
}

int Character::GetMp()
{
	return m_mp;
}

int Character::GetMaxMP()
{
	return m_maxMP;
}

int Character::GetStr()
{
	return m_str;
}

int Character::GetIntell()
{
	return m_int;
}

int Character::GetDex()
{
	return m_dex;
}

int Character::GetDef()
{
	return m_def;
}

int Character::GetPiety()
{
	return m_piety;
}
