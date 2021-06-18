#pragma once

#include <dwrite.h> //D2D ��Ʈ ����� ���ؼ� �߰� �ʿ�

#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include "Vector2D.h"

class PlayUI
{
public:
	Vector2D CharicInfoPos;							// ĳ���� ���� ǥ�� �簢�� ���� ��ǥ
	Vector2D CharicInfoSize;						// ĳ���� ���� ǥ�� �簢�� ũ��
	D2D1_ROUNDED_RECT* round_rect;					// ĳ���� ���� ǥ�� �簢��	

	Vector2D UserInfoPos;							// ���ΰ� �۾� ��ġ
	TCHAR strUserInfo[256];							// ���ΰ� ���� �۾� ǥ��
	D2D1_SIZE_F TextSize;							// �۾� ǥ�ø� ���� �κ�	
	IDWriteTextFormat* m_HeroInfoText = NULL;		// ���ΰ� ���� ��Ʈ
	
	Vector2D GuideTextPos;							// ���̵� �۾� ��ǥ			
	IDWriteTextFormat* m_GuideText = NULL;			// ���̵� ���� ��Ʈ
	TCHAR strGuide[256];							// ���̵� ���� �۾� ǥ��	

public:
	void PlayUIInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory);
	void PlayUIUpdate(float a_DeltaTime, Vector2D& a_CamPos);
	void PlayUIRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* m_Brush);
	void PlayUIDestroy();
};

extern PlayUI g_PlayUI;