#include "framework.h"
#include "GameOverUI.h"
#include "GlobalValue.h"

void GameOverUI::GOUIInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName))
{
	m_hWnd = hWnd;
	GetClientRect(m_hWnd, &m_RECT);

	// 버튼 이미지 초기화
	if (MyLoadBitmap != NULL)
	{
		m_GameOverBGImg = MyLoadBitmap(_T(".\\resources\\BackGrounds\\GameOver.png"));
		m_ButtonUpImg = MyLoadBitmap(_T(".\\resources\\UI\\GameOverBtnUp.png"));
		m_ButtonDownImg = MyLoadBitmap(_T(".\\resources\\UI\\GameOverDown.png"));

		m_ReStartBtnUpSize.x = m_ButtonUpImg->GetSize().width;
		m_ReStartBtnUpSize.y = m_ButtonUpImg->GetSize().height;

		m_ReStartBtnDownSize.x = m_ButtonDownImg->GetSize().width;
		m_ReStartBtnDownSize.y = m_ButtonDownImg->GetSize().height;

		// 버튼 위치 초기화
		m_ReStartBtnUpRenderPos.x = m_RECT.right * 0.3f;
		m_ReStartBtnUpRenderPos.y = m_RECT.bottom * 0.6f;

		m_ReStartBtnDownRenderPos.x = m_RECT.right * 0.3f;
		m_ReStartBtnDownRenderPos.y = m_RECT.bottom * 0.6f;

		// 글씨 나타내기
		_stprintf_s(ReStartStr, 256, _T("다시 하기"));

		m_pDWriteFactory->CreateTextFormat(
			_T("Gulim"), NULL,
			DWRITE_FONT_WEIGHT_DEMI_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			84, _T(""), &m_ReStartText
		);
	}
}

void GameOverUI::GOUIUpdate(void (*GameReset)())
{
	ReStartBtnClick(GameReset);
}

void GameOverUI::GOUIRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* m_Brush)
{
	// 백그라운드용
	if (m_GameOverBGImg != NULL)
	{
		a_pd2dRTarget->DrawBitmap(m_GameOverBGImg, D2D1::RectF(0.0f, 0.0f, m_RECT.right, m_RECT.bottom));
	}

	// 버튼 만들기
	if (m_ReStartBtnClicked == false)
	{
		if (m_ButtonUpImg != NULL)
		{
			a_pd2dRTarget->DrawBitmap(m_ButtonUpImg,
				D2D1::RectF(
					m_ReStartBtnUpRenderPos.x,
					m_ReStartBtnUpRenderPos.y,
					m_ReStartBtnUpRenderPos.x + m_ReStartBtnUpSize.x,
					m_ReStartBtnUpRenderPos.y + m_ReStartBtnUpSize.y));
		}

		// 버튼 글씨 쓰기
		m_Brush->SetColor(D2D1::ColorF(0xFFDE66));
		a_pd2dRTarget->DrawText(
			ReStartStr,
			_tcslen(ReStartStr),
			m_ReStartText,
			D2D1::RectF(
				m_ReStartBtnUpRenderPos.x + m_ReStartBtnUpSize.x * 0.15f,
				m_ReStartBtnUpRenderPos.y + m_ReStartBtnUpSize.y * 0.15f,
				m_ReStartBtnUpRenderPos.x + m_ReStartBtnUpSize.x,
				m_ReStartBtnUpRenderPos.y + m_ReStartBtnUpSize.y),
			m_Brush
		);
	}
	else if (m_ReStartBtnClicked == true)
	{
		a_pd2dRTarget->DrawBitmap(m_ButtonDownImg,
			D2D1::RectF(
				m_ReStartBtnDownRenderPos.x,
				m_ReStartBtnDownRenderPos.y,
				m_ReStartBtnDownRenderPos.x + m_ReStartBtnDownSize.x,
				m_ReStartBtnDownRenderPos.y + m_ReStartBtnDownSize.y));
	}
}

void GameOverUI::GOUIDestroy()
{
	// 글씨 삭제
	if (m_ReStartText != NULL)
	{
		m_ReStartText->Release();
		m_ReStartText = NULL;
	}

	if (m_ButtonUpImg != NULL)
	{
		m_ButtonUpImg->Release();
		m_ButtonUpImg = NULL;
	}

	if (m_ButtonDownImg != NULL)
	{
		m_ButtonDownImg->Release();
		m_ButtonDownImg = NULL;
	}

	if (m_GameOverBGImg != NULL)
	{
		m_GameOverBGImg->Release();
		m_GameOverBGImg = NULL;
	}
}

void GameOverUI::ReStartBtnClick(void (*GameReset)())
{
	if (GetFocus() == NULL)	// 포커스 확인
		return;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // 마우스 Down 시
	{
		GetCursorPos(&a_MouseXY);              //현재 마우스 좌표를 얻어오는 함수 
		ScreenToClient(m_hWnd, &a_MouseXY);    // 클라이언트 화면 좌표로 변경해 주는 함수

		if (m_ReStartBtnUpRenderPos.x <= a_MouseXY.x
			&& m_ReStartBtnUpRenderPos.x + m_ReStartBtnUpSize.x >= a_MouseXY.x
			&& m_ReStartBtnUpRenderPos.y <= a_MouseXY.y
			&& m_ReStartBtnUpRenderPos.y + m_ReStartBtnUpSize.y >= a_MouseXY.y) // 그림 영역을 클릭할 경우
		{
			m_ReStartBtnClicked = true;
		}
	}//if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	else // 마우스 Up 시
	{
		if (m_ReStartBtnClicked == true)
		{
			// 게임 타이틀로
			GameReset();	// 게임 초기화
			g_GameState = GameState::GameStart;
		}
		m_ReStartBtnClicked = false;
	}
}

GameOverUI g_GameOverUI;