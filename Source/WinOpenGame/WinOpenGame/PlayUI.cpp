#include "framework.h"
#include "PlayUI.h"
#include "CHero.h"

void PlayUI::PlayUIInit(HWND hWnd, IDWriteFactory* m_pDWriteFactory)
{	
	round_rect = new D2D1_ROUNDED_RECT;
	 
	// 화면 좌측 상단에 오도록 좌표 가져오기
	RECT a_Ret;
	GetClientRect(hWnd, &a_Ret);
	CharicInfoPos.x = a_Ret.right * 0.01f;
	CharicInfoPos.y = a_Ret.bottom * 0.01f;

	CharicInfoSize.x = a_Ret.right * 0.1f;
	CharicInfoSize.y = a_Ret.bottom * 0.13f;

	UserInfoPos.x = 22.0f;
	UserInfoPos.y = 15.0f;

	GuideTextPos.x = a_Ret.right * 0.7f;
	GuideTextPos.y = a_Ret.bottom * 0.01f;
	// 폰트 초기화
	m_pDWriteFactory->CreateTextFormat(
		_T("Gulim"), NULL,
		DWRITE_FONT_WEIGHT_DEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20, _T(""), &m_HeroInfoText
	);

	m_pDWriteFactory->CreateTextFormat(
		_T("Gulim"), NULL,
		DWRITE_FONT_WEIGHT_DEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20, _T(""), &m_GuideText
	);
}

void PlayUI::PlayUIUpdate(float a_DeltaTime, Vector2D& a_CamPos)
{
	// 글씨 업데이트
	_stprintf_s(strUserInfo, 256, 
		_T("HP : %.f\nATT : %d\nLevel : %d"), g_Hero.m_CurHP, g_Hero.m_Power, g_Hero.m_Level);

	_stprintf_s(strGuide, 256, _T("WSAD : 위아래좌우\n좌클릭 : 공격\n적을 공격하고 레벨 10을 올려\n보스를 죽이세요!"));
}

void PlayUI::PlayUIRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* m_Brush)
{
	// 외곽 부분
	round_rect->rect = D2D1::RectF(CharicInfoPos.x, CharicInfoPos.y, 
		CharicInfoPos.x + CharicInfoSize.x,
		CharicInfoPos.y + CharicInfoSize.y);

	round_rect->radiusX = 10.0f;
	round_rect->radiusY = 10.0f;

	m_Brush->SetColor(D2D1::ColorF(0x0054FF));
	a_pd2dRTarget->DrawRoundedRectangle(round_rect, m_Brush, 5.0f);

	m_Brush->SetColor(D2D1::ColorF(0x00D8FF, 0.3f));			// 투명도 적용
	a_pd2dRTarget->FillRoundedRectangle(round_rect, m_Brush);

	// 유저 정보 글씨 표출 부분
	m_Brush->SetColor(D2D1::ColorF(0x050099));
	TextSize = a_pd2dRTarget->GetSize();
	a_pd2dRTarget->DrawText(
		strUserInfo,
		_tcslen(strUserInfo),
		m_HeroInfoText,
		D2D1::RectF(UserInfoPos.x, UserInfoPos.y, TextSize.width, TextSize.height),
		m_Brush
	);

	// 경험치 표시 부분
	m_Brush->SetColor(D2D1::ColorF(0x050099));

	// 안내 정보 글씨 표출 부분
	m_Brush->SetColor(D2D1::ColorF(0xff0000));
	TextSize = a_pd2dRTarget->GetSize();
	a_pd2dRTarget->DrawText(
		strGuide,
		_tcslen(strGuide),
		m_GuideText,
		D2D1::RectF(GuideTextPos.x, GuideTextPos.y, TextSize.width, TextSize.height),
		m_Brush
	);
}

void PlayUI::PlayUIDestroy()
{
	if (m_HeroInfoText != NULL)
	{
		m_HeroInfoText->Release();
		m_HeroInfoText = NULL;
	}

	if (m_GuideText != NULL)
	{
		m_GuideText->Release();
		m_GuideText = NULL;
	}

	if (round_rect != NULL)
	{
		delete round_rect;
		round_rect = NULL;
	}	
}

PlayUI g_PlayUI;