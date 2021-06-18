#include "framework.h"
#include "CMonsters_Mgr.h"
#include "CHero.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Monster3.h"
#include "Monster4.h"
#include "Monster5.h"
#include "Monster6.h"
#include "Monster7.h"
#include "Monster8.h"
#include "Monster9.h"
#include "Monster10.h"
#include "CBullet.h"

void CMonsters_Mgr::MonMgr_Update(double a_DeltaTime, VecINT2D& a_Center, Vector2D& a_CamPos, CHero& a_Hero, ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	// �ֱ����� ���� ����
	SpawnMonster(a_DeltaTime, D2DLoadBmp);

	// ���� �浹 Ȯ�� �κ�
	for (int i = 0; i < m_MonList.size(); i++)
	{
		a_OwnMon = m_MonList[i];

		MonToHeroColl(a_Hero, *a_OwnMon);
		MonToMonColl(a_OwnMon);
	}

	// ���� ���� ������Ʈ
	for (auto& MonTemp : m_MonList)
	{
		a_OwnMon = MonTemp;
		a_OwnMon->Update_Unit(a_DeltaTime, a_Center, a_CamPos, a_Hero);
	}
}

void CMonsters_Mgr::MonMgr_Render(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush)
{
	// ���� �׸���
	for (int i = 0; i < m_MonList.size(); i++)
	{
		if (m_MonList[i]->m_InScRect == false)	// �ø�
			continue;

		m_MonList[i]->Render_Unit(a_pd2dRTarget, a_pBrush);
	}
}

void CMonsters_Mgr::MonMgr_Destroy()
{
	// ���͵� ����
	for (int i = 0; i < m_MonList.size(); i++) 
	{
		if (m_MonList[i] != NULL)
		{
			// ���� ������� �ı��Ѵ�.
			if (m_MonList[i]->MonsterKind == Mon1)
			{
				((Monster1*)m_MonList[i])->Destroy_Unit();
			}
			else if (m_MonList[i]->MonsterKind == Mon2)
			{
				((Monster2*)m_MonList[i])->Destroy_Unit();
			}
			else if (m_MonList[i]->MonsterKind == Mon3)
			{
				((Monster3*)m_MonList[i])->Destroy_Unit();
			}
			else if (m_MonList[i]->MonsterKind == Mon4)
			{
				((Monster4*)m_MonList[i])->Destroy_Unit();
			}
			else if (m_MonList[i]->MonsterKind == Mon5)
			{
				((Monster5*)m_MonList[i])->Destroy_Unit();
			}
			else if (m_MonList[i]->MonsterKind == Mon6)
			{
				((Monster6*)m_MonList[i])->Destroy_Unit();
			}
			else if (m_MonList[i]->MonsterKind == Mon7)
			{
				((Monster7*)m_MonList[i])->Destroy_Unit();
			}
			else if (m_MonList[i]->MonsterKind == Mon8)
			{
				((Monster8*)m_MonList[i])->Destroy_Unit();
			}
			else if (m_MonList[i]->MonsterKind == Mon9)
			{
				((Monster9*)m_MonList[i])->Destroy_Unit();
			}
			else if (m_MonList[i]->MonsterKind == Mon10)
			{
				((Monster10*)m_MonList[i])->Destroy_Unit();
			}
			else
			{
				m_MonList[i]->Destroy_Unit();
			}

			delete m_MonList[i];
			m_MonList[i] = NULL;
		}
	}
	m_MonList.clear();
}

void CMonsters_Mgr::SpawnMonster(float a_DeltaTime, ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	// ���� List�� �����, ��ġ���� ���ϴ� �κе� ������ �Ѵ�.
	// ������ ���͸� �׳� �÷�����.
	CMonster* a_Node = NULL;
    
	if (m_MonList.size() >= MonSpawnCount)	// �Ѱ�ġ�� ������ ������ �����Ѵ�.
		return;
	
	if (isfirst == true)
	{
		isfirst == false;

		// ����1 ����
		for (int i = 0; i< HalfMaxCount;i++)
		{
			a_Node = new Monster1();
			a_Node->MonsterKind = Mon1;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area1Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}

		// ����2 ����
		for (int i = 0; i < HalfMaxCount; i++)
		{
			a_Node = new Monster2();
			a_Node->MonsterKind = Mon2;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area2Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}

		// ����3 ����
		for (int i = 0; i < HalfMaxCount; i++)
		{
			a_Node = new Monster3();
			a_Node->MonsterKind = Mon3;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area3Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}

		// ����4 ����
		for (int i = 0; i < HalfMaxCount; i++)
		{
			a_Node = new Monster4();
			a_Node->MonsterKind = Mon4;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area4Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}

		// ����5 ����
		for (int i = 0; i < HalfMaxCount; i++)
		{
			a_Node = new Monster5();
			a_Node->MonsterKind = Mon5;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area5Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}

		// ����6 ����
		for (int i = 0; i < HalfMaxCount; i++)
		{
			a_Node = new Monster6();
			a_Node->MonsterKind = Mon6;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area6Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}

		// ����7 ����
		for (int i = 0; i < HalfMaxCount; i++)
		{
			a_Node = new Monster7();
			a_Node->MonsterKind = Mon7;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area7Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}

		// ����8 ����
		for (int i = 0; i < HalfMaxCount; i++)
		{
			a_Node = new Monster8();
			a_Node->MonsterKind = Mon8;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area8Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}

		// ����9 ����
		for (int i = 0; i < HalfMaxCount; i++)
		{
			a_Node = new Monster9();
			a_Node->MonsterKind = Mon9;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area9Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}

		// ����10 ����
		for (int i = 0; i < HalfMaxCount; i++)
		{
			a_Node = new Monster10();
			a_Node->MonsterKind = Mon10;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area10Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
	}

	m_SpawnTime -= a_DeltaTime;

	if (m_SpawnTime <= 0)
	{
		// ���� ��Ų��.
		if (Area1Count <= 20)
		{
			a_Node = new Monster1();
			a_Node->MonsterKind = Mon1;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area1Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
     	else if (Area2Count <= 20)
		{
			a_Node = new Monster2();
			a_Node->MonsterKind = Mon2;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area2Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
		else if (Area3Count <= 20)
		{
			a_Node = new Monster3();
			a_Node->MonsterKind = Mon3;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area3Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
		else if (Area4Count <= 20)
		{
			a_Node = new Monster4();
			a_Node->MonsterKind = Mon4;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area4Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
		else if (Area5Count <= 20)
		{
			a_Node = new Monster5();
			a_Node->MonsterKind = Mon5;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area5Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
		else if (Area6Count <= 20)
		{
			a_Node = new Monster6();
			a_Node->MonsterKind = Mon6;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area6Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
		else if (Area7Count <= 20)
		{
			a_Node = new Monster7();
			a_Node->MonsterKind = Mon7;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area7Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
		else if (Area8Count <= 20)
		{
			a_Node = new Monster8();
			a_Node->MonsterKind = Mon8;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area8Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
		else if (Area9Count <= 20)
		{
			a_Node = new Monster9();
			a_Node->MonsterKind = Mon9;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area9Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
		else if (Area10Count <= 20)
		{
			a_Node = new Monster10();
			a_Node->MonsterKind = Mon10;
			a_Node->Init_Unit(D2DLoadBmp);
			m_MonList.push_back(a_Node);
			Area10Count++;
			// ���� ��ġ
			// ���� ��ǥ�踦 �̿��ؼ� ���� ��ġ�� �����ϰ� �����Ѵ�.
			CalcSpawnArea(a_Node->MonsterKind);
			a_Node->Spawn(AreaX, AreaY);
		}
		
		m_SpawnTime = m_SpawnTimeSTD;
	}	
}

void CMonsters_Mgr::MonToHeroColl(CHero& a_Hero, CMonster& a_Monster)
{
	//------- ���ΰ����� �浹ó��
	a_CacVec = a_Monster.m_CurPos - a_Hero.m_CurPos;
	a_CacDist = a_CacVec.Magnitude();
	if (a_Monster.MonsterKind == Mon1)
	{
		a_RadiusPlus = ((Monster1*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	else if (a_Monster.MonsterKind == Mon2)
	{
		a_RadiusPlus = ((Monster2*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	else if (a_Monster.MonsterKind == Mon3)
	{
		a_RadiusPlus = ((Monster3*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	else if (a_Monster.MonsterKind == Mon4)
	{
		a_RadiusPlus = ((Monster4*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	else if (a_Monster.MonsterKind == Mon5)
	{
		a_RadiusPlus = ((Monster5*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	else if (a_Monster.MonsterKind == Mon6)
	{
		a_RadiusPlus = ((Monster6*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	else if (a_Monster.MonsterKind == Mon7)
	{
		a_RadiusPlus = ((Monster7*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	else if (a_Monster.MonsterKind == Mon8)
	{
		a_RadiusPlus = ((Monster8*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	else if (a_Monster.MonsterKind == Mon9)
	{
		a_RadiusPlus = ((Monster9*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	else if (a_Monster.MonsterKind == Mon10)
	{
		a_RadiusPlus = ((Monster10*)&a_Monster)->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��	
	}
	
	if (a_CacDist < a_RadiusPlus)
	{		
		a_CacMargin = a_RadiusPlus - a_CacDist;
		a_CacVec.Normalize();
		a_OwnMon->m_CurPos = a_OwnMon->m_CurPos + (a_CacVec * a_CacMargin);

		// ���ΰ� �����ϱ�
		a_OwnMon->AttackHero();
	}
	//------- ���ΰ����� �浹ó��
}

void CMonsters_Mgr::MonToMonColl(CMonster* thisMon)
{
	// ���ͳ��� �浹 ó��
	// ���ϰ� �ɸ��� �κ��� auto�� �̿�����
	for (auto& TempMon : m_MonList)
	{
		if (TempMon->m_isActive == false)
			continue;
	
		if (TempMon->m_InScRect == false)	// �ø�
			continue;
	
		if (thisMon == TempMon)
			continue;
	
		a_CacVec = thisMon->m_CurPos - TempMon->m_CurPos; // �з����� ����
		a_CacDist = a_CacVec.Magnitude();
		a_RadiusPlus = MonToMonCalcRadius(thisMon, TempMon);
		//a_RadiusPlus = thisMon->m_HalfColl + 10 + m_MonList[xx]->m_HalfColl + 10; // ���ݰ� + ���ݰ� ���� ��Ȱ��
		
		if (a_CacDist < a_RadiusPlus) // ��ģ ����
		{
			a_CacMargin = a_RadiusPlus - a_CacDist;
			a_CacVec.Normalize();
			thisMon->m_CurPos = thisMon->m_CurPos + (a_CacVec * a_CacMargin);
		}
	}	
}

float CMonsters_Mgr::MonToMonCalcRadius(CMonster* thisMon, CMonster* otherMon)
{	
	if (thisMon->MonsterKind == Mon1)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster1*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}		
	}
	else if (thisMon->MonsterKind == Mon2)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster2*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}
	}
	else if (thisMon->MonsterKind == Mon3)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster3*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}
	}
	else if (thisMon->MonsterKind == Mon4)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster4*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}
	}
	else if (thisMon->MonsterKind == Mon5)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster5*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}
	}
	else if (thisMon->MonsterKind == Mon6)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster6*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}
	}
	else if (thisMon->MonsterKind == Mon7)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster7*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}
	}
	else if (thisMon->MonsterKind == Mon8)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster8*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}
	}
	else if (thisMon->MonsterKind == Mon9)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster9*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}
	}
	else if (thisMon->MonsterKind == Mon10)
	{
		if (otherMon->MonsterKind == Mon1)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster1*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon2)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster2*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon3)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster3*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon4)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster4*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon5)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster5*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon6)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster6*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon7)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster7*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon8)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster8*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon9)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster9*)otherMon)->m_HalfColl + 10;
		}
		else if (otherMon->MonsterKind == Mon10)
		{
			RadiusToMon = ((Monster10*)thisMon)->m_HalfColl + 10 + ((Monster10*)otherMon)->m_HalfColl + 10;
		}
	}

	return RadiusToMon;
}

void CMonsters_Mgr::TakeDamageMon(CBullet* a_Bullet, float Damage)
{
	if (a_Bullet == NULL)
		return;	

	CMonster* a_MonNode = NULL; // ���͸� �ű�� ���� ���
	// �Ѿ��� ���Ϳ� �¾����� ������ �ش�. ���� ���� �Ѿ� ����
	for (int i = 0; i < m_MonList.size(); i++)
	{
		if (m_MonList[i]->m_isActive == false)
			continue;

		a_CacVec = m_MonList[i]->m_CurPos - a_Bullet->m_CurPos;
		// ���⼭ ���� ���� ������
		if (m_MonList[i]->MonsterKind == Mon1)
		{
			tempHalfColl = ((Monster1*)m_MonList[i])->m_HalfColl;
		}
		else if (m_MonList[i]->MonsterKind == Mon2)
		{
			tempHalfColl = ((Monster2*)m_MonList[i])->m_HalfColl;
		}
		else if (m_MonList[i]->MonsterKind == Mon3)
		{
			tempHalfColl = ((Monster3*)m_MonList[i])->m_HalfColl;
		}
		else if (m_MonList[i]->MonsterKind == Mon4)
		{
			tempHalfColl = ((Monster4*)m_MonList[i])->m_HalfColl;
		}
		else if (m_MonList[i]->MonsterKind == Mon5)
		{
			tempHalfColl = ((Monster5*)m_MonList[i])->m_HalfColl;
		}
		else if (m_MonList[i]->MonsterKind == Mon6)
		{
			tempHalfColl = ((Monster6*)m_MonList[i])->m_HalfColl;
		}
		else if (m_MonList[i]->MonsterKind == Mon7)
		{
			tempHalfColl = ((Monster7*)m_MonList[i])->m_HalfColl;
		}
		else if (m_MonList[i]->MonsterKind == Mon8)
		{
			tempHalfColl = ((Monster8*)m_MonList[i])->m_HalfColl;
		}
		else if (m_MonList[i]->MonsterKind == Mon9)
		{
			tempHalfColl = ((Monster9*)m_MonList[i])->m_HalfColl;
		}
		else if (m_MonList[i]->MonsterKind == Mon10)
		{
			tempHalfColl = ((Monster10*)m_MonList[i])->m_HalfColl;
		}
		else 
		{
			tempHalfColl = 10;
		}

		if (a_CacVec.Magnitude() < (tempHalfColl + a_Bullet->m_HalfColl))
		{
			m_MonList[i]->TakeDamage(Damage);

			a_Bullet->m_BLActive = false;    // �Ѿ� ����
			break;
		}
	}

	// ���� ���� ó��
	for (Moniter = m_MonList.begin(); Moniter != m_MonList.end();)
	{
		if ((*Moniter)->m_isActive == false)
		{
			Moniter = m_MonList.erase(Moniter);
		}
		else 
		{
			Moniter++;
		}		
	}
}

void CMonsters_Mgr::CalcSpawnArea(KindOfMonster Monkind)
{
	// ���� ������ ���� ���������� ������ ���� ������
	// �� ������ 10����	
	if (Monkind == Mon1)
	{
		AreaX = (rand() % 2000 + 2000) * -1;	// ���� : -4000 ~ -2000
		AreaY = (rand() % 1474 + 1474) * -1;	// ���� : -2456 ~ -1474
	}
	else if (Monkind == Mon2)
	{
		AreaX = (rand() % 2000 + 2000) * -1;	// ���� : -4000 ~ -2000
		AreaY = (rand() % 491 - 982) * -1;		// ���� : -491 ~ 491
	}
	else if (Monkind == Mon3)
	{
		AreaX = (rand() % 2000 + 2000) * -1;	// ���� : -4000 ~ -2000
		AreaY = (rand() % 1474 + 1474);			// ���� : 1474 ~ 2456
	}
	else if (Monkind == Mon4)
	{
		AreaX = (rand() % 720 + 720) * -1;		// ���� : -1440 ~ -720
		AreaY = (rand() % 1474 + 1474) * -1;	// ���� : -2456 ~ -1474
	}
	else if (Monkind == Mon5)
	{
		AreaX = (rand() % 720 + 720) * -1;		// ���� : -1440 ~ -720
		AreaY = (rand() % 1474 + 1474);			// ���� : 1465 ~ 2465
	}
	else if (Monkind == Mon6)
	{
		AreaX = (rand() % 720 + 720);			// ���� : 720 ~ 1440
		AreaY = (rand() % 1474 + 1474) * -1;	// ���� : -2465 ~ -1465
	}
	else if (Monkind == Mon7)
	{
		AreaX = (rand() % 720 + 720);			// ���� : 720 ~ 1440
		AreaY = (rand() % 1474 + 1474);			// ���� : 1465 ~ 2465
	}
	else if (Monkind == Mon8)
	{
		AreaX = (rand() % 2000 + 2000);			// ���� : 2000 ~ 4000
		AreaY = (rand() % 1474 + 1474) * -1;	// ���� : -2456 ~ -1474
	}
	else if (Monkind == Mon9)
	{
		AreaX = (rand() % 2000 + 2000);			// ���� : 2000 ~ 4000
		AreaY = (rand() % 491 - 982) * -1;		// ���� : -491 ~ 491
	}
	else if (Monkind == Mon10)
	{
		AreaX = (rand() % 2000 + 2000);			// ���� : 2000 ~ 4000
		AreaY = (rand() % 1474 + 1474);			// ���� : 1465 ~ 2465
	}
}

void CMonsters_Mgr::MonsterReset()
{
	MonMgr_Destroy();	// ���� �޸� ����
	isfirst = true;		// �ʹ� ���� ����
}

CMonsters_Mgr g_Mon_Mgr;