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

	// ���� ��ǥ �̵� ���� ����
	VecINT2D m_ScreenHalf = { 0, 0 };	// ȭ�� �� ������ �����
	Vector2D m_CamPos = { 0.0f, 0.0f }; // ���� ��ġ

public:
	VecINT2D m_ImgSize;
	VecINT2D m_WorldHfSize;
	VecINT2D m_TileStPos;	// Ÿ�� ���� ũ��
	int X_Tile = 3;			// 3 X 3 9���� �̹����� �ٿ��� ���� ���� 
	int Y_Tile = 3;			// 3 X 3 9���� �̹����� �ٿ��� ���� ����

public:
	void BGMgrInit(ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName) = NULL);
	void BGMgrUpdate(float a_DeltaTime, Vector2D& a_CamPos);
	void BGMgrRender(ID2D1HwndRenderTarget* a_pd2dRTarget);
	void BGMgrDestroy();
};

extern CBackGround g_BackGround;