#include "framework.h"
#include "CMonster.h"
#include "CHero.h"

void CMonster::Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	
}

void CMonster::Update_Unit(double a_DeltaTime, VecINT2D& a_Center, Vector2D& a_CamPos, CHero& a_Hero)
{
	m_DeltaTime = a_DeltaTime;

	m_ScreenHalf.x = a_Center.x;
	m_ScreenHalf.y = a_Center.y;

	m_CamPos.x = a_CamPos.x;
	m_CamPos.y = a_CamPos.y;	

	// 해당 부분에서 몬스터의 움직임을 통제한다.
	MonsterAI(a_DeltaTime, a_Hero);

	// 몬스터 컬링 변수 확인
	m_Sc_HLen.x = m_ScreenHalf.x; // +40;
	m_Sc_HLen.y = m_ScreenHalf.y; // +40;

	if (m_SocketImg != NULL)
	{
		m_Obj_HLen.x = m_SocketImg->GetSize().width / 2.0f;   //가로 반 사이즈
		m_Obj_HLen.y = m_SocketImg->GetSize().height / 2.0f;  //세로 반 사이즈 
	}
	else
	{
		m_Obj_HLen.x = 50.0f;
		m_Obj_HLen.y = 50.0f;
	}

	m_InScRect = CheckAABB(m_CamPos, m_Sc_HLen, m_CurPos, m_Obj_HLen);
}

void CMonster::Render_Unit(ID2D1HwndRenderTarget* a_pd2dTarget, ID2D1SolidColorBrush* a_pBrush)
{
	if (m_SocketImg == NULL)
		return;

	if (m_InScRect == false)
		return;

	m_RenderPos.x = m_CurPos.x - (int)m_CamPos.x;
	m_RenderPos.y = m_CurPos.y - (int)m_CamPos.y;

	static VecINT2D img_size;
	static VecINT2D img_Half;
	img_size.x = m_SocketImg->GetSize().width;
	img_size.y = m_SocketImg->GetSize().height;
	img_Half.x = img_size.x / 2.0f;
	img_Half.y = img_size.y / 2.0f;

	// 캐릭터 Render
	a_pd2dTarget->DrawBitmap(m_SocketImg,
		D2D1::RectF(m_RenderPos.x - img_Half.x,
			m_RenderPos.y - img_Half.y,
			m_RenderPos.x + img_Half.x,
			m_RenderPos.y + img_Half.y)
	);
}

void CMonster::Destroy_Unit()
{

}

void CMonster::Spawn(float a_XX, float a_YY)
{
	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_isActive = true;

	m_CurHP = m_MaxHP;
}

void CMonster::MonsterAI(float a_DeltaTime, CHero& a_Hero)
{	
	
	// 순찰 상태 일 경우
	if (MonCurState == MAI_Patrol)
	{
		m_CacVec = a_Hero.m_CurPos - m_CurPos; // 주인공과의 거리
		if (m_CacVec.Magnitude() <= m_AggroRange) // 주인공과의 거리가 가까울 시 공격 모드로 변환
		{
			MonCurState = MAI_NormalTrace;
			AggroTarget = &a_Hero;
			return;
		}	

		if (isPatrol == true)	// 패트롤 방향을 결정하는 부분 - 도착해서는 잠깐 멈췄다가 움직인다.
		{
			// 몬스터의 움직일 방향 결정
			isXPlusMove = rand() % 2 + 1;
			isYPlusMove = rand() % 2 + 1;
			XMoveLength = rand() % 150 + 50;
			YMoveLength = rand() % 150 + 50;

			if (isXPlusMove == 1)
			{
				XMoveLength *= -1;
			}

			if (isYPlusMove == 1)
			{
				YMoveLength *= -1;
			}

			m_AIDirVec.x = XMoveLength;
			m_AIDirVec.y = YMoveLength;
			m_AIDirVec.Normalize();					

			isPatrol = false;
		} // if (isPatrol == true)
		else 
		{
			m_PAMoveUseTime -= a_DeltaTime;
			if (m_PAMoveUseTime <= 0)
			{				
				isMonWait = true;
				m_PAMoveUseTime = m_PAMoveTime;
			}
			else if (isMonWait == true)	// 잠깐 멈추는 타이밍
			{
				// 여기서 잠깐 대기한다.
				m_PAWaitUseTime -= a_DeltaTime;
				if (m_PAWaitUseTime <= 0)
				{
					m_PAWaitUseTime = m_PAWaitTime;
					isMonWait = false;
					isPatrol = true;
				}
			}
			else 
			{
				// 움직임 적용 부분
				m_CurPos = m_CurPos + m_AIDirVec * m_Speed * a_DeltaTime;
			}
		}
		
		if (isHit == true)	// 순찰중 맞았을 시 
		{
			MonCurState = MAI_AggroTrace;
			AggroTarget = &a_Hero;
			return;
		}
	}// if (MonCurState == MAI_Patrol)

	// 발견해서 쫒아오는 부분
	if (MonCurState == MAI_NormalTrace)
	{
		// 주인공 추적
		m_CacVec = AggroTarget->m_CurPos - m_CurPos;		
		if (m_CacVec.Magnitude() > m_AggroRange) // 거리가 멀어져서 어그로가 풀릴 때
		{
			MonCurState = MAI_Patrol;
			return;
		}
		else 
		{
			m_CacVec.Normalize();
			m_CurPos = m_CurPos + m_CacVec * m_Speed * a_DeltaTime;
		}		
	}// if (MonCurState == MAI_NormalTrace)

	if (MonCurState == MAI_AggroTrace)
	{
		// 주인공을 추적하되 빠르게 쫒아온다. // 계속 쫒아온다.
		m_CacVec = AggroTarget->m_CurPos - m_CurPos;
		m_CacVec.Normalize();
		m_CurPos = m_CurPos + m_CacVec * AngrySpeed * a_DeltaTime;
	}
}

void CMonster::TakeDamage(float Damage)
{
	m_CurHP = m_CurHP - Damage;

	if (m_CurHP > 0.0f && isHit == false)	// 한대 맞음
	{
		isHit = true;
	}

	if (m_CurHP <= 0.0f)	// 몬스터 사망 처리 
	{
		g_Hero.m_KillCount++;   // 몬스터 킬 카운트 처리
		g_Hero.m_Exp += 1000;	// 경험치 주기

		//// 아이템 스폰
		//if (RefSpawnItem != NULL)
		//	RefSpawnItem(m_CurPos, false);

		m_isActive = false;	// 몬스터 삭제 처리
	}
}

void CMonster::AttackHero()
{
	if (0.0f < m_AttackTickUse)
		m_AttackTickUse = m_AttackTickUse - m_DeltaTime;

	if (m_AttackTickUse <= 0.0f)
	{
		m_AttackTickUse = m_AttackTick;

		g_Hero.m_CurHP -= m_Power;	// 주인공 공격하기
		if (g_Hero.m_CurHP <= 0.0f)
		{
			g_Hero.m_CurHP = 0.0f;
			g_GameState = GameState::GameOver;	// 게임 오버 처리
		}
	}
}

bool CMonster::CheckAABB(Vector2D& AACen, Vector2D& AAHLen, Vector2D& BBCen, Vector2D& BBHLen)
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
