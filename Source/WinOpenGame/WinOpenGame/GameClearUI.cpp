#include "framework.h"
#include "GameClearUI.h"
#include "GlobalValue.h"

void GameClearUI::GameClearInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory, ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName))
{
	m_hWnd = hWnd;
	GetClientRect(m_hWnd, &m_RECT);

	// ��ư �̹��� �ʱ�ȭ
	if (MyLoadBitmap != NULL)
	{
		m_GameClearBGImg = MyLoadBitmap(_T(".\\resources\\BackGrounds\\ClearScene.jpg"));
		m_ButtonUpImg = MyLoadBitmap(_T(".\\resources\\UI\\StageClearUpBtn.png"));
		m_ButtonDownImg = MyLoadBitmap(_T(".\\resources\\UI\\StageClearDownBtn.png"));

		m_ReStartBtnUpSize.x = m_ButtonUpImg->GetSize().width * 0.6;
		m_ReStartBtnUpSize.y = m_ButtonUpImg->GetSize().height * 0.5;

		m_ReStartBtnDownSize.x = m_ButtonDownImg->GetSize().width * 0.6;
		m_ReStartBtnDownSize.y = m_ButtonDownImg->GetSize().height * 0.5;

		// ��ư ��ġ �ʱ�ȭ
		m_ReStartBtnUpRenderPos.x = m_RECT.right * 0.35f;
		m_ReStartBtnUpRenderPos.y = m_RECT.bottom * 0.85f;

		m_ReStartBtnDownRenderPos.x = m_RECT.right * 0.35f;
		m_ReStartBtnDownRenderPos.y = m_RECT.bottom * 0.85f;

		// �۾� ��Ÿ����
		_stprintf_s(ReStartStr, 256, _T("�ٽ� �ϱ�"));

		m_pDWriteFactory->CreateTextFormat(
			_T("Gulim"), NULL,
			DWRITE_FONT_WEIGHT_DEMI_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			64, _T(""), &m_ReStartText
		);
	}
}

void GameClearUI::GameClearUpdate(void(*GameReset)())
{
	ReStartBtnClick(GameReset);
}

void GameClearUI::GameClearRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* m_Brush)
{
	// ��׶����
	if (m_GameClearBGImg != NULL)
	{
		a_pd2dRTarget->DrawBitmap(m_GameClearBGImg, D2D1::RectF(0.0f, 0.0f, m_RECT.right, m_RECT.bottom));
	}

	// ��ư �����
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

		// ��ư �۾� ����
		m_Brush->SetColor(D2D1::ColorF(0x8FCEFF));
		a_pd2dRTarget->DrawText(
			ReStartStr,
			_tcslen(ReStartStr),
			m_ReStartText,
			D2D1::RectF(
				m_ReStartBtnUpRenderPos.x + m_ReStartBtnUpSize.x * 0.11f,
				m_ReStartBtnUpRenderPos.y + m_ReStartBtnUpSize.y * 0.05f,
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

void GameClearUI::GameClearDestroy()
{
	// �۾� ����
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

	if (m_GameClearBGImg != NULL)
	{
		m_GameClearBGImg->Release();
		m_GameClearBGImg = NULL;
	}
}

void GameClearUI::ReStartBtnClick(void(*GameReset)())
{
	if (GetFocus() == NULL)	// ��Ŀ�� Ȯ��
		return;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // ���콺 Down ��
	{
		GetCursorPos(&a_MouseXY);              //���� ���콺 ��ǥ�� ������ �Լ� 
		ScreenToClient(m_hWnd, &a_MouseXY);    // Ŭ���̾�Ʈ ȭ�� ��ǥ�� ������ �ִ� �Լ�

		if (m_ReStartBtnUpRenderPos.x <= a_MouseXY.x
			&& m_ReStartBtnUpRenderPos.x + m_ReStartBtnUpSize.x >= a_MouseXY.x
			&& m_ReStartBtnUpRenderPos.y <= a_MouseXY.y
			&& m_ReStartBtnUpRenderPos.y + m_ReStartBtnUpSize.y >= a_MouseXY.y) // �׸� ������ Ŭ���� ���
		{
			m_ReStartBtnClicked = true;
		}
	}//if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	else // ���콺 Up ��
	{
		if (m_ReStartBtnClicked == true)
		{
			// ���� Ÿ��Ʋ��
			GameReset();	// ���� �ʱ�ȭ
			g_GameState = GameState::GameStart;
		}
		m_ReStartBtnClicked = false;
	}
}

GameClearUI g_gameClearUI;