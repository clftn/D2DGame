#pragma once

#include "CMonster.h" 

class Monster2 : public CMonster
{
public:
	float	m_HalfColl = 8;

public:
	virtual void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	virtual void Destroy_Unit();
};

extern Monster2 g_Mon2;