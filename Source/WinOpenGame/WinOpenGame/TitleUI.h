#pragma once

#include <dwrite.h> //D2D ��Ʈ ����� ���ؼ� �߰� �ʿ�

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

	TCHAR TitleStr[256];					 // Ÿ��Ʋ �ؽ�Ʈ
	IDWriteTextFormat* m_TitleText = NULL;   // Ÿ��Ʋ ��Ʈ ������
	TCHAR StartStr[256];					 // ��ư ���� ���� �ؽ�Ʈ
	IDWriteTextFormat* m_StartText = NULL;   // ���� ���� ��Ʈ ������

	Vector2D m_StartBtnUpSize;				 // ��ư Up ������
	Vector2D m_StartBtnDownSize;			 // ��ư Down ������
	Vector2D m_StartBtnUpRenderPos;			 
	Vector2D m_StartBtnDownRenderPos;		 
	bool m_StartBtnClicked = false;			 // ���콺 Ŭ�� ����
	POINT a_MouseXY;						 // ���콺 Ŭ�� ��ǥ
	RECT m_RECT;							 // ȭ�� ũ��

public:
	void TitleUIInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName));
	void TitleUIUpdate();
	void TitleUIRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_Brush);
	void TitleUIDestroy();

	void StartBtnClick();
};

extern TitleUI g_TitleUI;