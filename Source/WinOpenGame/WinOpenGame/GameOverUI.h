#pragma once

#include <dwrite.h> //D2D ��Ʈ ����� ���ؼ� �߰� �ʿ�

#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include "Vector2D.h"

class GameOverUI
{
public:
	HWND m_hWnd;

private:
	ID2D1Bitmap* m_GameOverBGImg = NULL;		// �ش� UI ��׶���
	ID2D1Bitmap* m_ButtonUpImg = NULL;			// ��ư Up �̹���
	ID2D1Bitmap* m_ButtonDownImg = NULL;		// ��ư Down �̹���

	RECT m_RECT;								// ȭ�� ũ��
	TCHAR ReStartStr[256];						// ���� ����� �ؽ�Ʈ ��
	IDWriteTextFormat* m_ReStartText = NULL;	// ���� ����� ��Ʈ ������
	Vector2D m_ReStartBtnUpSize;				// ��ư Up ������
	Vector2D m_ReStartBtnDownSize;				// ��ư Down ������
	Vector2D m_ReStartBtnUpRenderPos;
	Vector2D m_ReStartBtnDownRenderPos;
	bool m_ReStartBtnClicked = false;				// ���콺 Ŭ�� ����
	POINT a_MouseXY;							// ���콺 Ŭ�� ��ǥ

public:
	void GOUIInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName));
	void GOUIUpdate(void (*GameReset)());
	void GOUIRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* m_Brush);
	void GOUIDestroy();

private:
	void ReStartBtnClick(void (*GameReset)());
};

extern GameOverUI g_GameOverUI;