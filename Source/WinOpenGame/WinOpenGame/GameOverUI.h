#pragma once

#include <dwrite.h> //D2D 폰트 사용을 위해서 추가 필요

#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include "Vector2D.h"

class GameOverUI
{
public:
	HWND m_hWnd;

private:
	ID2D1Bitmap* m_GameOverBGImg = NULL;		// 해당 UI 백그라운드
	ID2D1Bitmap* m_ButtonUpImg = NULL;			// 버튼 Up 이미지
	ID2D1Bitmap* m_ButtonDownImg = NULL;		// 버튼 Down 이미지

	RECT m_RECT;								// 화면 크기
	TCHAR ReStartStr[256];						// 게임 재시작 텍스트 용
	IDWriteTextFormat* m_ReStartText = NULL;	// 게임 재시작 폰트 사이즈
	Vector2D m_ReStartBtnUpSize;				// 버튼 Up 사이즈
	Vector2D m_ReStartBtnDownSize;				// 버튼 Down 사이즈
	Vector2D m_ReStartBtnUpRenderPos;
	Vector2D m_ReStartBtnDownRenderPos;
	bool m_ReStartBtnClicked = false;				// 마우스 클릭 여부
	POINT a_MouseXY;							// 마우스 클릭 좌표

public:
	void GOUIInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName));
	void GOUIUpdate(void (*GameReset)());
	void GOUIRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* m_Brush);
	void GOUIDestroy();

private:
	void ReStartBtnClick(void (*GameReset)());
};

extern GameOverUI g_GameOverUI;