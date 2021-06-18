#include "framework.h"
#include "Monster2.h"

void Monster2::Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	if (D2DLoadBmp != NULL)
		m_SocketImg = D2DLoadBmp(_T(".\\resources\\Monster\\Monster2.png"));
}

void Monster2::Destroy_Unit()
{
	if (m_SocketImg != NULL)
	{
		m_SocketImg->Release();
		m_SocketImg = NULL;
	}
}

Monster2 g_Mon2;