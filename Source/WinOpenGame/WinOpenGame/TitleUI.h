#pragma once

#include <dwrite.h> //D2D 폰트 사용을 위해서 추가 필요

#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include "Vector2D.h"

class TitleUI
{
public:
	HWND m_hWnd;

private:
	ID2D1Bitmap* m_TitleImg = NULL;
	ID2D1Bitmap* m_ButtonUpImg = NULL;
	ID2D1Bitmap* m_ButtonDownImg = NULL;

	TCHAR TitleStr[256];					 // 타이틀 텍스트
	IDWriteTextFormat* m_TitleText = NULL;   // 타이틀 폰트 사이즈
	TCHAR StartStr[256];					 // 버튼 게임 시작 텍스트
	IDWriteTextFormat* m_StartText = NULL;   // 게임 시작 폰트 사이즈

	Vector2D m_StartBtnUpSize;				 // 버튼 Up 사이즈
	Vector2D m_StartBtnDownSize;			 // 버튼 Down 사이즈
	Vector2D m_StartBtnUpRenderPos;			 
	Vector2D m_StartBtnDownRenderPos;		 
	bool m_StartBtnClicked = false;			 // 마우스 클릭 여부
	POINT a_MouseXY;						 // 마우스 클릭 좌표
	RECT m_RECT;							 // 화면 크기

public:
	void TitleUIInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName));
	void TitleUIUpdate();
	void TitleUIRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_Brush);
	void TitleUIDestroy();

	void StartBtnClick();
};

extern TitleUI g_TitleUI;