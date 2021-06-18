#pragma once

#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include "Vector2D.h"

class CBackGround
{
public:
	HWND m_hWnd = NULL;

private:
	ID2D1Bitmap* m_pBGBmpDesert = NULL;
	ID2D1Bitmap* m_pBGBmpForest = NULL;
	ID2D1Bitmap* m_pBGBmpCity = NULL;

	// 월드 좌표 이동 계산용 변수
	VecINT2D m_ScreenHalf = { 0, 0 };	// 화면 반 사이즈 저장용
	Vector2D m_CamPos = { 0.0f, 0.0f }; // 현재 위치

public:
	VecINT2D m_ImgSize;
	VecINT2D m_WorldHfSize;
	VecINT2D m_TileStPos;	// 타일 시작 크기
	int X_Tile = 3;			// 3 X 3 9개의 이미지로 붙여서 만든 월드 
	int Y_Tile = 3;			// 3 X 3 9개의 이미지로 붙여서 만든 월드

public:
	void BGMgrInit(ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName) = NULL);
	void BGMgrUpdate(float a_DeltaTime, Vector2D& a_CamPos);
	void BGMgrRender(ID2D1HwndRenderTarget* a_pd2dRTarget);
	void BGMgrDestroy();
};

extern CBackGround g_BackGround;