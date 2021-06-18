#include "framework.h"
#include "CUIMgr.h"
#include "PlayUI.h"
#include "TitleUI.h"
#include "GameOverUI.h"
#include "GameClearUI.h"
#include "GlobalValue.h"

void CUIMgr::UIMgrInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName))
{
	// Ÿ��Ʋ UI �ʱ�ȭ
	g_TitleUI.TitleUIInit(hWnd, m_pDWriteFactory, MyLoadBitmap);

	// �÷��� UI �κ� �ʱ�ȭ
	g_PlayUI.PlayUIInit(hWnd, m_pDWriteFactory);

	// ���� Ŭ���� �κ� �ʱ�ȭ
	g_gameClearUI.GameClearInit(hWnd, m_pDWriteFactory, MyLoadBitmap);

	// ���� ���� �κ� �ʱ�ȭ
	g_GameOverUI.GOUIInit(hWnd, m_pDWriteFactory, MyLoadBitmap);
}

void CUIMgr::UIMgrUpdate(float a_DeltaTime, Vector2D& a_CamPos, void (*GameReset)())
{
	if (g_GameState == GameState::GameStart)
	{
		g_TitleUI.TitleUIUpdate();
	}
	else if (g_GameState == GameState::GameIng) 
	{
		// �÷��� UI������Ʈ �κ�
		g_PlayUI.PlayUIUpdate(a_DeltaTime, a_CamPos);
	}
	else if (g_GameState == GameState::GameClear)
	{
		g_gameClearUI.GameClearUpdate(GameReset);
	}
	else if (g_GameState == GameState::GameOver)
	{
		g_GameOverUI.GOUIUpdate(GameReset);
	}
}

void CUIMgr::UIMgrRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* m_Brush)
{
	if (g_GameState == GameState::GameStart)
	{
		g_TitleUI.TitleUIRender(a_pd2dRTarget, m_Brush);
	}
	else if (g_GameState == GameState::GameIng)
	{
		// �÷��� �κ� ������
		g_PlayUI.PlayUIRender(a_pd2dRTarget, m_Brush);
	}
	else if (g_GameState == GameState::GameClear)
	{
		g_gameClearUI.GameClearRender(a_pd2dRTarget, m_Brush);
	}
	else if (g_GameState == GameState::GameOver)
	{
		g_GameOverUI.GOUIRender(a_pd2dRTarget, m_Brush);
	}
}

void CUIMgr::UIMgrDestroy()
{
	// Ÿ��Ʋ �κ� �޸� ����
	g_TitleUI.TitleUIDestroy();

	// �÷��� �κ� �޸� ����
	g_PlayUI.PlayUIDestroy();

	// ���� Ŭ���� �κ� �޸� ����
	g_gameClearUI.GameClearDestroy();

	// ���ӿ��� �κ� �޸� ����
	g_GameOverUI.GOUIDestroy();
}



CUIMgr g_UIMgr;