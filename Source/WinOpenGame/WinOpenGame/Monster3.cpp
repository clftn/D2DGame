#include "framework.h"
#include "Monster3.h"

void Monster3::Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	if (D2DLoadBmp != NULL)
		m_SocketImg = D2DLoadBmp(_T(".\\resources\\Monster\\Monster3.png"));
}

void Monster3::Destroy_Unit()
{
	if (m_SocketImg != NULL)
	{
		m_SocketImg->Release();
		m_SocketImg = NULL;
	}
}

Monster3 g_Mon3;