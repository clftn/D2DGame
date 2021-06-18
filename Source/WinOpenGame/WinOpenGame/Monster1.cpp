#include "framework.h"
#include "Monster1.h"

void Monster1::Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	if(D2DLoadBmp != NULL)
		m_SocketImg = D2DLoadBmp(_T(".\\resources\\Monster\\Monster1.png"));
}

void Monster1::Destroy_Unit()
{
	if (m_SocketImg != NULL)
	{
		m_SocketImg->Release();
		m_SocketImg = NULL;
	}
}

Monster1 g_Mon1;