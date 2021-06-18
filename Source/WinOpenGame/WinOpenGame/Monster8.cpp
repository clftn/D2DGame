#include "framework.h"
#include "Monster8.h"

void Monster8::Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	if (D2DLoadBmp != NULL)
		m_SocketImg = D2DLoadBmp(_T(".\\resources\\Monster\\Monster8.png"));
}

void Monster8::Destroy_Unit()
{
	if (m_SocketImg != NULL)
	{
		m_SocketImg->Release();
		m_SocketImg = NULL;
	}
}

Monster8 g_Mon8;