#include "framework.h"
#include "CBoss.h"
#include "CHero.h"
#include "CBullet_Mgr.h"
#include "GlobalValue.h"

void CBoss::Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	//이미지 로딩
	if (D2DLoadBmp != NULL)
	{
		m_ImgData = D2DLoadBmp(_T(".\\resources\\Boss\\Boss1.png"));
		m_SocketImg = m_ImgData;
	}
}

void CBoss::Update_Unit(double a_DeltaTime, VecINT2D& a_Center, Vector2D& a_CamPos, CHero* a_Hero)
{
	m_ScreenHalf.x = a_Center.x;
	m_ScreenHalf.y = a_Center.y;

	m_CamPos.x = a_CamPos.x;
	m_CamPos.y = a_CamPos.y;

	// 보스 몬스터 스폰부분
	if (m_isActive == false && m_CurHP > 0)
	{
		Spawn(600, 600);		
	}

	if (m_isActive == true)
	{
		// 보스 몬스터 AI 부분
		BossAI(a_DeltaTime, a_Hero);

		BossToHero(a_Hero);
	}	
}

void CBoss::Render_Unit(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush)
{
	if (m_SocketImg == NULL)
		return;
	
	if (m_isActive == false)
		return;

	m_RenderPos.x = m_CurPos.x - (int)m_CamPos.x;
	m_RenderPos.y = m_CurPos.y - (int)m_CamPos.y;

	static VecINT2D img_size;
	static VecINT2D img_Half;
	img_size.x = m_SocketImg->GetSize().width;
	img_size.y = m_SocketImg->GetSize().height;
	img_Half.x = img_size.x / 2.0f;
	img_Half.y = img_size.y / 2.0f;

	// 보스 Render
	a_pd2dRTarget->DrawBitmap(m_SocketImg,
		D2D1::RectF(m_RenderPos.x - img_Half.x,
			m_RenderPos.y - img_Half.y,
			m_RenderPos.x + img_Half.x,
			m_RenderPos.y + img_Half.y)
	);
}

void CBoss::Destroy_Unit()
{
	if (m_ImgData != NULL)
	{
		m_ImgData->Release();
		m_ImgData = NULL;
	}
}

void CBoss::Spawn(float a_XX, float a_YY)
{
	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_isActive = true;

	m_CurHP = m_MaxHP;
}

void CBoss::BossToHero(CHero* a_Hero)
{
	//------- 주인공과의 충돌처리
	a_CacVec = a_Hero->m_CurPos - m_CurPos;	// 밀릴 방향
	a_CacDist = a_CacVec.Magnitude();
	a_RadiusPlus = m_HalfColl + 4 + a_Hero->m_HalfColl + 4; //(내반경 + 적반경) 변수 재활용	
	if (a_CacDist < a_RadiusPlus)
	{		
		a_CacVec.Normalize();
		a_Hero->m_CurPos = a_Hero->m_CurPos + (a_CacVec * (a_RadiusPlus - a_CacDist));
	}
}

void CBoss::DamageToBoss(CBullet* a_Bullet, float Damage)
{
	if (a_Bullet == NULL)
		return;

	// 총알과 보스 충돌 구현
	if (m_isActive == false)
		return;

	a_CacVec = m_CurPos - a_Bullet->m_CurPos;
	if (a_CacVec.Magnitude() < (m_HalfColl + a_Bullet->m_HalfColl))
	{
		m_CurHP = m_CurHP - Damage;

		//if (m_CurHP > 0.0f && isHit == false)	// 한대 맞음 AI 구현시 어그로 끌기 위해
		//{
		//	isHit = true;
		//}

		if (m_CurHP <= 0.0f)	// 몬스터 사망 처리 
		{						
			m_isActive = false;	// 몬스터 삭제 처리			
			g_GameState = GameState::GameClear; // 게임 클리어 처리
		}

		a_Bullet->m_BLActive = false;    // 총알 제거		
	}
}

void CBoss::BossAI(float a_DeltaTime, CHero* a_Hero)
{
	// 보스 총알 쏘는 부분
	if (m_isActive == true)
	{		
		if (isHeroView == true)
		{			
			if (bossState == BS_SLEEP)
			{
				m_UseTime += a_DeltaTime;
				if (m_UseTime >= m_ShootTime && ActStep  == 1)
				{
					m_UseTime = 0.0f;
					bossState = BS_NORMAL_ACT;
					ActStep = 2;
				}
				else if (m_UseTime >= m_ShootTime && ActStep == 2)
				{
					m_UseTime = 0.0f;
					bossState = BS_FEVER_ACT;
					ActStep = 1;
				}
			}			
			else if (bossState == BS_NORMAL_ACT)
			{
				m_UseTime += a_DeltaTime;
				if (m_UseTime >= m_NormalActTime)
				{
					m_UseTime = 0.0f;
					bossState = BS_SLEEP;
				}
			}
			else if (bossState == BS_FEVER_ACT)
			{
				m_UseTime += a_DeltaTime;
				if (m_UseTime >= m_FeverActTime)
				{
					m_UseTime = 0.0f;
					bossState = BS_SLEEP;
				}
			}
		}
	}

	if (bossState == BS_NORMAL_ACT) 
	{
		m_NormalActSpeedUse -= a_DeltaTime;
		if (m_NormalActSpeedUse <= 0)
		{
			m_NormalActSpeedUse = m_NormalActSpeed;
			g_Bullet_Mgr.BossNormalShoot(m_CurPos, a_Hero->m_CurPos);
		}		
	}
	else if (bossState == BS_FEVER_ACT)
	{
		m_FeverActSpeedUse -= a_DeltaTime;
		if (m_FeverActSpeedUse <= 0)
		{
			m_FeverActSpeedUse = m_FeverActSpeed;
			g_Bullet_Mgr.BossFeverShoot(m_CurPos, a_Hero->m_CurPos);
		}		
	}
	else if (bossState == BS_SLEEP)
	{
		
	}

}

void CBoss::ResetBoss()
{
	m_isActive = false;		// 액티브 상태 false
	m_CurHP = m_MaxHP;		// 피통원래대로
	isHeroView = true;		// 주인공을 인지한 여부
	ActStep = 1;			// 공격 단계
}

CBoss g_Boss;