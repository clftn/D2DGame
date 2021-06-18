#include "framework.h"
#include "CInputPlayer.h"

void CInputPlayer::Update_Input(XMFLOAT2& a_KDirVec)
{
	if (GetFocus() == NULL)
		return;

	// 동시 키 처리
	a_KDirVec.x = 0.0f;
	a_KDirVec.y = 0.0f;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) ||
		(GetAsyncKeyState('A') & 0x8000))
	{
		a_KDirVec.x -= 1.0f;	// 왼쪽 움직임
		if (isShotting == false)
		{		
			g_HeroStateStd = WalkLeft;
		}
		else 
		{
			g_HeroStateStd = ShotLeft;
		}
		
		isKeyDown = true;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
		(GetAsyncKeyState('D') & 0x8000))
	{
		a_KDirVec.x += 1.0f;
		if (isShotting == false)
		{
			g_HeroStateStd = WalkRight;
		}
		else
		{
			g_HeroStateStd = ShotRight;
		}		
		isKeyDown = true;
	}

	if ((GetAsyncKeyState(VK_UP) & 0x8000) ||
		(GetAsyncKeyState('W') & 0x8000))
	{
		a_KDirVec.y -= 1.0f;
		if (isShotting == false)
		{
			g_HeroStateStd = WalkLeft;
		}
		else
		{
			g_HeroStateStd = ShotLeft;
		}
		isKeyDown = true;
	}

	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) ||
		(GetAsyncKeyState('S') & 0x8000))
	{
		a_KDirVec.y += 1.0f;
		if (isShotting == false)
		{
			g_HeroStateStd = WalkRight;
		}
		else
		{
			g_HeroStateStd = ShotRight;
		}
		isKeyDown = true;
	}
}

CInputPlayer g_InputPlayer;