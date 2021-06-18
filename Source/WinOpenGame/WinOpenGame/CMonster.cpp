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

	// �ش� �κп��� ������ �������� �����Ѵ�.
	MonsterAI(a_DeltaTime, a_Hero);

	// ���� �ø� ���� Ȯ��
	m_Sc_HLen.x = m_ScreenHalf.x; // +40;
	m_Sc_HLen.y = m_ScreenHalf.y; // +40;

	if (m_SocketImg != NULL)
	{
		m_Obj_HLen.x = m_SocketImg->GetSize().width / 2.0f;   //���� �� ������
		m_Obj_HLen.y = m_SocketImg->GetSize().height / 2.0f;  //���� �� ������ 
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

	// ĳ���� Render
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
	
	// ���� ���� �� ���
	if (MonCurState == MAI_Patrol)
	{
		m_CacVec = a_Hero.m_CurPos - m_CurPos; // ���ΰ����� �Ÿ�
		if (m_CacVec.Magnitude() <= m_AggroRange) // ���ΰ����� �Ÿ��� ����� �� ���� ���� ��ȯ
		{
			MonCurState = MAI_NormalTrace;
			AggroTarget = &a_Hero;
			return;
		}	

		if (isPatrol == true)	// ��Ʈ�� ������ �����ϴ� �κ� - �����ؼ��� ��� ����ٰ� �����δ�.
		{
			// ������ ������ ���� ����
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
			else if (isMonWait == true)	// ��� ���ߴ� Ÿ�̹�
			{
				// ���⼭ ��� ����Ѵ�.
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
				// ������ ���� �κ�
				m_CurPos = m_CurPos + m_AIDirVec * m_Speed * a_DeltaTime;
			}
		}
		
		if (isHit == true)	// ������ �¾��� �� 
		{
			MonCurState = MAI_AggroTrace;
			AggroTarget = &a_Hero;
			return;
		}
	}// if (MonCurState == MAI_Patrol)

	// �߰��ؼ� �i�ƿ��� �κ�
	if (MonCurState == MAI_NormalTrace)
	{
		// ���ΰ� ����
		m_CacVec = AggroTarget->m_CurPos - m_CurPos;		
		if (m_CacVec.Magnitude() > m_AggroRange) // �Ÿ��� �־����� ��׷ΰ� Ǯ�� ��
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
		// ���ΰ��� �����ϵ� ������ �i�ƿ´�. // ��� �i�ƿ´�.
		m_CacVec = AggroTarget->m_CurPos - m_CurPos;
		m_CacVec.Normalize();
		m_CurPos = m_CurPos + m_CacVec * AngrySpeed * a_DeltaTime;
	}
}

void CMonster::TakeDamage(float Damage)
{
	m_CurHP = m_CurHP - Damage;

	if (m_CurHP > 0.0f && isHit == false)	// �Ѵ� ����
	{
		isHit = true;
	}

	if (m_CurHP <= 0.0f)	// ���� ��� ó�� 
	{
		g_Hero.m_KillCount++;   // ���� ų ī��Ʈ ó��
		g_Hero.m_Exp += 1000;	// ����ġ �ֱ�

		//// ������ ����
		//if (RefSpawnItem != NULL)
		//	RefSpawnItem(m_CurPos, false);

		m_isActive = false;	// ���� ���� ó��
	}
}

void CMonster::AttackHero()
{
	if (0.0f < m_AttackTickUse)
		m_AttackTickUse = m_AttackTickUse - m_DeltaTime;

	if (m_AttackTickUse <= 0.0f)
	{
		m_AttackTickUse = m_AttackTick;

		g_Hero.m_CurHP -= m_Power;	// ���ΰ� �����ϱ�
		if (g_Hero.m_CurHP <= 0.0f)
		{
			g_Hero.m_CurHP = 0.0f;
			g_GameState = GameState::GameOver;	// ���� ���� ó��
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
