#pragma once
#include "CMonster.h"

class Monster9 : public CMonster
{
public:
	float	m_HalfColl = 40;

public:
	virtual void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	virtual void Destroy_Unit();
};

extern Monster9 g_Mon9;
