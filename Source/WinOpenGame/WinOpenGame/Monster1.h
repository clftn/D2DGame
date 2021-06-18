#pragma once

#include "CMonster.h"

class Monster1 : public CMonster
{
public:
	float	m_HalfColl = 30;	

public:
	virtual void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	virtual void Destroy_Unit();
};

extern Monster1 g_Mon1;