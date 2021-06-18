#include "framework.h"
#include "CHero.h"
#include "GlobalValue.h"
#include "CInputPlayer.h"
#include "CBullet_Mgr.h"
#include "CBoss.h"

void CHero::Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	// ���ΰ� ��ǥ �ʱ�ȭ �κ�
	RECT a_Crt;
	GetClientRect(m_hWnd, &a_Crt);
	m_CurPos.x = (float)(a_Crt.right / 2);
	m_CurPos.y = (float)(a_Crt.bottom / 2);

	m_ScreenHalf.x = (float)(a_Crt.right / 2);
	m_ScreenHalf.y = (float)(a_Crt.bottom / 2);

	//�̹��� �ε�
	if (D2DLoadBmp != NULL)
	{
		m_ImgData = D2DLoadBmp(_T(".\\resources\\Hero\\Hero1.png"));
		m_SocketImg = m_ImgData;
	}

	UseAniTime = SetAniTime;
}

void CHero::Update_Unit(double a_DeltaTime, VecINT2D a_ScreenHalf)
{
	// ĳ������ �ִϸ��̼� �ο�
	UseAniTime -= a_DeltaTime;
	if (UseAniTime <= 0)
	{
		if (g_HeroStateMove == State1)
		{
			g_HeroStateMove = State2;
		}
		else if (g_HeroStateMove == State2)
		{
			g_HeroStateMove = State3;
		}
		else if (g_HeroStateMove == State3)
		{
			g_HeroStateMove = State4;
		}
		else if (g_HeroStateMove == State4)
		{
			g_HeroStateMove = State5;
		}
		else if (g_HeroStateMove == State5)
		{
			g_HeroStateMove = State1;
		}
		
		UseAniTime = SetAniTime;
	}

	// ĳ���� Ű���� �̵� ó��
	static Vector2D a_KDirVec;
	a_KDirVec.x = 0.0f;
	a_KDirVec.y = 0.0f;

	static XMFLOAT2 a_CompVec = { 0.0f, 0.0f };
	g_InputPlayer.Update_Input(a_CompVec);
	a_KDirVec = { a_CompVec.x, a_CompVec.y };

	if (a_CompVec.x != 0.0f || a_CompVec.y != 0.0f)
	{
		a_KDirVec.Normalize();
		m_CurPos = m_CurPos + (a_KDirVec * (a_DeltaTime * m_MoveSpeed));
	}
	// Ű���� �̵� ó��	

	// �Ѿ� �߻�
	static float g_MgEcTick = 0.0f;

	g_MgEcTick = g_MgEcTick - a_DeltaTime;
	if (g_MgEcTick < -10.0f)
		g_MgEcTick - 10.0f;

	if (GetFocus() != NULL)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // ���콺 ���� ��ư Ŭ��
		{
			if (g_MgEcTick <= 0.0f)
			{
				static POINT a_MPos;
				GetCursorPos(&a_MPos);
				ScreenToClient(m_hWnd, &a_MPos);

				static Vector2D a_TargetV;
				a_TargetV.x = (float)a_MPos.x + m_CamPos.x;
				a_TargetV.y = (float)a_MPos.y + m_CamPos.y;

				g_Bullet_Mgr.SpawnPistol(g_Hero.m_CurPos, a_TargetV);

				g_MgEcTick = 0.2f;

				// �Ѿ� �� �� ���ΰ� ���� ��ȭ // �������� ���º�ȭ�� MoveComponent����
				if (a_ScreenHalf.x <= a_TargetV.x)	// ���ΰ��� �������� ���� ���� ��
				{
					isShotting = true;					
					g_HeroStateStd = ShotRight;
				}
				else 
				{					
					isShotting = true;
					g_HeroStateStd = ShotLeft;
				}				
				isKeyDown = true;
			}
		}
	}
	// �Ѿ� �߻�

	// �ڵ� idle���� ��ȯ
	if (isKeyDown == true)
	{
		KeyDownTime -= a_DeltaTime;
		if (KeyDownTime <= 0)
		{			
			isShotting = false;
			isKeyDown = false;
			g_HeroStateStd = IdleLeft;
			KeyDownTime = 3.0f;
		}
	}
	// �ڵ� idle���� ��ȯ

	// ���� üũ �κ�
	if (m_Exp / m_EncExp > m_Level)
	{
		m_Level++;
		m_EncExp = 250 * m_Level;
	}
}

void CHero::Render_Unit(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush)
{
	// ���� ��ǥ(m_CurPos) -> ������ ��ǥ(m_RenderPos)�� ȯ���ϴ� �κ�
	m_RenderPos.x = m_CurPos.x - m_CamPos.x;
	m_RenderPos.y = m_CurPos.y - m_CamPos.y;

	if (m_SocketImg == nullptr)
		return;

	// �� ����
	static D2D1_SIZE_F img_size;
	static Vector2D img_Half;
	img_size = m_SocketImg->GetSize();
	img_Half.x = img_size.width / 2.0f / 8.0f;	// ��������Ʈ ĳ���� ���� 8��
	img_Half.y = img_size.height / 2.0f / 8.0f;	// ��������Ʈ ĳ���� ���� 8��	

	a_CacMYY = (int)(img_Half.x * 0.8f);

	static float a_iXX = 0; //������ �ݿø� ȯ��(�׸���� ���� ��ǥ�̱� ������...)
	static float a_iYY = 0;
	a_iXX = m_RenderPos.x;
	a_iYY = m_RenderPos.y;

	// HP �� ����
	a_CacMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_CurHP / (float)m_MaxHP);

	a_CacMYY = (int)(img_Half.y * 0.83f);

	a_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red, FigureAlpha));
	a_pd2dRTarget->FillRectangle(D2D1::RectF(a_iXX - a_CacMXX, a_iYY - a_CacMYY,
		a_iXX - a_CacMXX + a_CurHpSize, a_iYY - (a_CacMYY + 9.0f)), a_pBrush);

	a_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White, FigureAlpha));
	a_pd2dRTarget->DrawRectangle(D2D1::RectF(a_iXX - a_CacMXX, a_iYY - a_CacMYY,
		a_iXX - a_CacMXX + a_HpBSize, a_iYY - (a_CacMYY + 9.0f)), a_pBrush);

	a_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	// HP �� ����

	// ĳ���� �׸���
	a_pd2dRTarget->DrawBitmap(m_SocketImg,
		D2D1::RectF(m_RenderPos.x - img_Half.x, m_RenderPos.y - img_Half.y,
			m_RenderPos.x + img_Half.x,	m_RenderPos.y + img_Half.y),   //  ȭ���� �׷��� ��ǥ(����� �����ذ��̴�.)
		1.0f,   // ����
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(m_SpriteWGap * g_HeroStateMove,			// ���ο��� �������� ���°�, ���ο��� ĳ������ ���°� �����ȴ�.
			m_SpriteHGap * g_HeroStateStd,
			m_SpriteWGap * g_HeroStateMove + m_CharWSize,	
			m_SpriteHGap * g_HeroStateStd + m_CharHSize)             // Image�� ��ǥ
	);
}

void CHero::Destroy_Unit()
{
	if (m_ImgData != NULL)
	{
		m_ImgData->Release();
		m_ImgData = NULL;
	}
}

void CHero::Abs_Update(Vector2D& a_CamPos)
{
	m_CamPos.x = a_CamPos.x;
	m_CamPos.y = a_CamPos.y;
}

void CHero::DamageToHero(CBullet* a_Bullet, float Damage)
{
	if (a_Bullet == NULL)
		return;

	// �Ѿ˰� ���ΰ����� �浹 ����
	a_CacVec = m_CurPos - a_Bullet->m_CurPos;
	if (a_CacVec.Magnitude() < (m_HalfColl + a_Bullet->m_HalfColl))
	{
		m_CurHP = m_CurHP - Damage;
		if (m_CurHP <= 0.0f)
		{
			m_CurHP = 0.0f;
			g_GameState = GameState::GameOver;	// ���� ���� ó��
		}

		a_Bullet->m_BLActive = false;    // �Ѿ� ����		
	}
}

void CHero::HeroReset()
{
	m_CurHP = m_MaxHP;			// ���� �ʱ�ȭ
	m_CurPos = m_ScreenHalf;	// ��ġ �ʱ�ȭ
	m_Level = 1;				// ���� �ʱ�ȭ
	m_EncExp = 250 * m_Level;
	m_Exp = 1;				    // ����ġ �ʱ�ȭ
	m_KillCount = 0;			// ų�� �ʱ�ȭ
	m_Power = 100;				// �Ŀ� �ʱ�ȭ
}

CHero g_Hero;