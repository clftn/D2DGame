#pragma once
#include "CMonster.h"

class Monster5 : public CMonster
{
public:
	float	m_HalfColl = 50;

public:
	virtual void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	virtual void Destroy_Unit();
};

extern Monster5 g_Mon5;