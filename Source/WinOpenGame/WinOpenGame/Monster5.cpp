#include "framework.h"
#include "Monster5.h"

void Monster5::Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	if (D2DLoadBmp != NULL)
		m_SocketImg = D2DLoadBmp(_T(".\\resources\\Monster\\Monster5.png"));
}

void Monster5::Destroy_Unit()
{
	if (m_SocketImg != NULL)
	{
		m_SocketImg->Release();
		m_SocketImg = NULL;
	}
}

Monster5 g_Mon5;