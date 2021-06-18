#pragma once
#include "CMonster.h"

class Monster3 : public CMonster
{
public:
	float	m_HalfColl = 45;

public:
	virtual void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	virtual void Destroy_Unit();
};

extern Monster3 g_Mon3;