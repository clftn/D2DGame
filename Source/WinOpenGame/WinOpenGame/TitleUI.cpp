#include "framework.h"
#include "TitleUI.h"
#include "GlobalValue.h"

void TitleUI::TitleUIInit(HWND hWnd,IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName))
{
	m_hWnd = hWnd;

	GetClientRect(m_hWnd, &m_RECT);

	if (MyLoadBitmap != NULL)
	{
		m_TitleImg = MyLoadBitmap(_T(".\\resources\\BackGrounds\\StartScene.png"));
		m_ButtonUpImg = MyLoadBitmap(_T(".\\resources\\UI\\StartBtnUp.png"));
		m_ButtonDownImg = MyLoadBitmap(_T(".\\resources\\UI\\StartBtnDown.png"));

		m_StartBtnUpSize.x = m_ButtonUpImg->GetSize().width;
		m_StartBtnUpSize.y = m_ButtonUpImg->GetSize().height;

		m_StartBtnDownSize.x = m_ButtonDownImg->GetSize().width* 1.1;
		m_StartBtnDownSize.y = m_ButtonDownImg->GetSize().height * 1.1;

		// 버튼 위치 초기화
		m_StartBtnUpRenderPos.x = m_RECT.right * 0.3f;
		m_StartBtnUpRenderPos.y = m_RECT.bottom * 0.6f;

		m_StartBtnDownRenderPos.x = m_RECT.right * 0.3f;
		m_StartBtnDownRenderPos.y = m_RECT.bottom * 0.6f;
	}

	// 폰트 초기화
	_stprintf_s(TitleStr, 256, _T("나만의 RPG"));
	_stprintf_s(StartStr, 256, _T("게임 시작"));

	m_pDWriteFactory->CreateTextFormat(
		_T("Gulim"), NULL,
		DWRITE_FONT_WEIGHT_DEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		95, _T(""), &m_TitleText
	);

	m_pDWriteFactory->CreateTextFormat(
		_T("Gulim"), NULL,
		DWRITE_FONT_WEIGHT_DEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		84, _T(""), &m_StartText
	);
}

void TitleUI::TitleUIUpdate()
{
	StartBtnClick();
}

void TitleUI::TitleUIRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_Brush)
{
	// 백그라운드용
	if (m_TitleImg != NULL)
	{
		a_pd2dRTarget->DrawBitmap(m_TitleImg, D2D1::RectF(0.0f,0.0f, m_RECT.right, m_RECT.bottom));
	}

	// 타이틀 글씨 쓰기
	a_Brush->SetColor(D2D1::ColorF(0xB2EBF4));
	a_pd2dRTarget->DrawText(
		TitleStr,
		_tcslen(TitleStr),
		m_TitleText,
		D2D1::RectF(
			m_RECT.right * 0.3f,
			m_RECT.bottom * 0.1f,
			m_RECT.right * 0.7f,
			m_RECT.bottom * 0.6f),
		a_Brush
	);

	// 버튼 UI
	if (m_StartBtnClicked == false)
	{
		if (m_ButtonUpImg != NULL)
		{
			a_pd2dRTarget->DrawBitmap(m_ButtonUpImg, 
				D2D1::RectF(
					m_StartBtnUpRenderPos.x, 
					m_StartBtnUpRenderPos.y,
					m_StartBtnUpRenderPos.x + m_StartBtnUpSize.x, 
					m_StartBtnUpRenderPos.y + m_StartBtnUpSize.y));
		}

		// 버튼 글씨 쓰기
		a_Brush->SetColor(D2D1::ColorF(0x1500D7));
		a_pd2dRTarget->DrawText(
			StartStr,
			_tcslen(StartStr),
			m_StartText,
			D2D1::RectF(
				m_StartBtnUpRenderPos.x + m_StartBtnUpSize.x * 0.15f,
				m_StartBtnUpRenderPos.y + m_StartBtnUpSize.y * 0.1f,
				m_StartBtnUpRenderPos.x + m_StartBtnUpSize.x,
				m_StartBtnUpRenderPos.y + m_StartBtnUpSize.y),
			a_Brush
		);
	}
	else if (m_StartBtnClicked == true)
	{
		a_pd2dRTarget->DrawBitmap(m_ButtonDownImg,
			D2D1::RectF(
				m_StartBtnDownRenderPos.x, 
				m_StartBtnDownRenderPos.y,
				m_StartBtnDownRenderPos.x + m_StartBtnDownSize.x, 
				m_StartBtnDownRenderPos.y + m_StartBtnDownSize.y));
	}
}

void TitleUI::TitleUIDestroy()
{
	if (m_TitleText != NULL)
	{
		m_TitleText->Release();
		m_TitleText = NULL;
	}

	if (m_StartText != NULL)
	{
		m_StartText->Release();
		m_StartText = NULL;
	}

	if (m_TitleImg != NULL)
	{
		m_TitleImg->Release();
		m_TitleImg = NULL;
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
}

void TitleUI::StartBtnClick()
{
	if (GetFocus() == NULL)	// 포커스 확인
		return;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // 마우스 Down 시
	{		
		GetCursorPos(&a_MouseXY);              //현재 마우스 좌표를 얻어오는 함수 
		ScreenToClient(m_hWnd, &a_MouseXY);    // 클라이언트 화면 좌표로 변경해 주는 함수

		if (m_StartBtnUpRenderPos.x <= a_MouseXY.x 
			&& m_StartBtnUpRenderPos.x + m_StartBtnUpSize.x >= a_MouseXY.x
			&& m_StartBtnUpRenderPos.y <= a_MouseXY.y
			&& m_StartBtnUpRenderPos.y + m_StartBtnUpSize.y >= a_MouseXY.y) // 그림 영역을 클릭할 경우
		{
			m_StartBtnClicked = true;
		}
	}//if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	else // 마우스 Up 시
	{
		if (m_StartBtnClicked == true)
		{
			// 게임 시작
			g_GameState = GameState::GameIng;
		}
		m_StartBtnClicked = false;
	}
}

TitleUI g_TitleUI;