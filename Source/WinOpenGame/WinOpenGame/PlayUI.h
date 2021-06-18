#pragma once

#include <dwrite.h> //D2D 폰트 사용을 위해서 추가 필요

#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include "Vector2D.h"

class PlayUI
{
public:
	Vector2D CharicInfoPos;							// 캐릭터 정보 표출 사각형 시작 좌표
	Vector2D CharicInfoSize;						// 캐릭터 정보 표출 사각형 크기
	D2D1_ROUNDED_RECT* round_rect;					// 캐릭터 정보 표출 사각형	

	Vector2D UserInfoPos;							// 주인공 글씨 위치
	TCHAR strUserInfo[256];							// 주인공 정보 글씨 표출
	D2D1_SIZE_F TextSize;							// 글씨 표시를 위한 부분	
	IDWriteTextFormat* m_HeroInfoText = NULL;		// 주인공 정보 폰트
	
	Vector2D GuideTextPos;							// 가이드 글씨 좌표			
	IDWriteTextFormat* m_GuideText = NULL;			// 가이드 정보 폰트
	TCHAR strGuide[256];							// 가이드 정보 글씨 표출	

public:
	void PlayUIInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory);
	void PlayUIUpdate(float a_DeltaTime, Vector2D& a_CamPos);
	void PlayUIRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* m_Brush);
	void PlayUIDestroy();
};

extern PlayUI g_PlayUI;