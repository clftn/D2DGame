#include "framework.h"
#include "CBullet.h"

bool CBullet::BulletUpdate(float a_DwdDeltaTime, DWORD a_DwdLastTime, float a_WpDeltaTime, Vector2D a_CamPos, VecINT2D& a_Center, void(*GenSmokePtc)(Vector2D a_StartV, DWORD a_CurTime, Vector2D a_DirVec))
{
	m_Duration = m_Duration - a_DwdDeltaTime;
	if (m_Duration < 0.0f)
	{
		m_BLActive = false;
		return false;
	}

	m_CurPos = m_CurPos + (m_DirVec * (a_DwdDeltaTime * m_MoveSpeed));		// 총알 이동처리 // 계산용
	m_RenderPos = m_RenderPos + (m_DirVec * (a_WpDeltaTime * m_MoveSpeed));	// 총알 이동처리 // 그리기용

	m_ScreenHalf.x = a_Center.x;
	m_ScreenHalf.y = a_Center.y;

	// 총알 컬링 확인
	m_Sc_HLen.x = m_ScreenHalf.x; // +40;
	m_Sc_HLen.y = m_ScreenHalf.y; // +40;

	if (m_BulletImg != NULL)
	{
		m_Obj_HLen.x = m_BulletImg->GetSize().width / 2.0f;   //가로 반 사이즈
		m_Obj_HLen.y = m_BulletImg->GetSize().height / 2.0f;  //세로 반 사이즈 
	}
	else
	{
		m_Obj_HLen.x = 50.0f;
		m_Obj_HLen.y = 50.0f;
	}

	m_InScRect = CheckAABB(a_CamPos, m_Sc_HLen, m_CurPos, m_Obj_HLen);

	return true;
}

void CBullet::BulletRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush, Vector2D a_CamPos)
{
	if (m_InScRect == false)
		return;

	static float a_iXX = 0;		// 정수로 반올림 환산(그리기는 정수 좌표이기 때문에)
	static float a_iYY = 0;

	a_iXX = (float)m_RenderPos.x - (int)a_CamPos.x;
	a_iYY = (float)m_RenderPos.y - (int)a_CamPos.y;

	a_CacX = a_iXX - m_TexImgWidth * 0.5f;
	a_CacY = a_iYY - m_TexImgHeight * 0.5f;
	a_Rotation = m_DirVec.GetAngle();
	a_Alpha = 1.0f;

	D2D1_POINT_2F center_pos = { a_iXX, a_iYY };

	if (m_UC_Type == CT_Hero)
	{		
		a_pd2dRTarget->SetTransform(D2D1::Matrix3x2F::Rotation(a_Rotation, center_pos));

		a_pBrush->SetColor(D2D1::ColorF(0x00ffff));
		a_pd2dRTarget->FillRectangle(D2D1::RectF(a_CacX, a_CacY,
			a_CacX + m_TexImgWidth, a_CacY + m_TexImgHeight), a_pBrush);
		a_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));

		a_pd2dRTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	else if (m_UC_Type == CT_Monster)
	{
		a_pBrush->SetColor(D2D1::ColorF(0x0500A5));
		a_pd2dRTarget->FillEllipse(D2D1::Ellipse(
			D2D1::Point2F(a_CacX, a_CacY), m_TexImgWidth, m_TexImgHeight), a_pBrush);

		a_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	}
	
}

bool CBullet::CheckAABB(Vector2D& AACen, Vector2D& AAHLen, Vector2D& BBCen, Vector2D& BBHLen)
{
	a_AA_Min.x = AACen.x;
	a_AA_Min.y = AACen.y;
	a_AA_Max.x = AACen.x + (AAHLen.x * 2.0f);
	a_AA_Max.y = AACen.y + (AAHLen.y * 2.0f);

	a_BB_Min.x = BBCen.x - BBHLen.x;
	a_BB_Min.y = BBCen.y - BBHLen.y;
	a_BB_Max.x = BBCen.x + BBHLen.x;
	a_BB_Max.y = BBCen.y + BBHLen.y;

	if (a_AA_Min.x <= a_BB_Max.x && a_AA_Max.x >= a_BB_Min.x &&
		a_AA_Min.y <= a_BB_Max.y && a_AA_Max.y >= a_BB_Min.y)
	{
		return true;
	}

	return false;
}
