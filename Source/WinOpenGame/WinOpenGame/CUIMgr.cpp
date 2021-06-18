#include "framework.h"
#include "CUIMgr.h"
#include "PlayUI.h"
#include "TitleUI.h"
#include "GameOverUI.h"
#include "GameClearUI.h"
#include "GlobalValue.h"

void CUIMgr::UIMgrInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName))
{
	// 타이틀 UI 초기화
	g_TitleUI.TitleUIInit(hWnd, m_pDWriteFactory, MyLoadBitmap);

	// 플레이 UI 부분 초기화
	g_PlayUI.PlayUIInit(hWnd, m_pDWriteFactory);

	// 게임 클리어 부분 초기화
	g_gameClearUI.GameClearInit(hWnd, m_pDWriteFactory, MyLoadBitmap);

	// 게임 오버 부분 초기화
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
		// 플레이 UI업데이트 부분
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
		// 플레이 부분 랜더링
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
	// 타이틀 부분 메모리 정리
	g_TitleUI.TitleUIDestroy();

	// 플레이 부분 메모리 정리
	g_PlayUI.PlayUIDestroy();

	// 게임 클리어 부분 메모리 정리
	g_gameClearUI.GameClearDestroy();

	// 게임오버 부분 메모리 정리
	g_GameOverUI.GOUIDestroy();
}



CUIMgr g_UIMgr;