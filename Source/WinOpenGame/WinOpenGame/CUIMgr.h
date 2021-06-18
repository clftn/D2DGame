#pragma once

#include <dwrite.h> //D2D 폰트 사용을 위해서 추가 필요

#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include "Vector2D.h"

class CUIMgr
{
public:
	void UIMgrInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName) = NULL);
	void UIMgrUpdate(float a_DeltaTime, Vector2D& a_CamPos, void (*GameReset)() = NULL);
	void UIMgrRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* m_Brush);
	void UIMgrDestroy();
};

extern CUIMgr g_UIMgr;