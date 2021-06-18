#pragma once
#include "CMonster.h"

class Monster6 : public CMonster
{
public:
	float	m_HalfColl = 40;

public:
	virtual void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	virtual void Destroy_Unit();
};

extern Monster6 g_Mon6;