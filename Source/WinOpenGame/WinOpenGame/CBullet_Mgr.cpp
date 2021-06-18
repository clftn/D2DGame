#include "framework.h"
#include "CBullet_Mgr.h"
#include "CMonsters_Mgr.h"
#include "CBoss.h"
#include "CHero.h"

void CBullet_Mgr::BLMgrInit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName))
{
	// 총알 메모리품로 미리 만들어 놓기
	CBullet* a_BLNode = NULL;
	for (int aii = 0; aii < 200; aii++)
	{
		a_BLNode = new CBullet();
		m_BullList.push_back(a_BLNode);
	}
}

void CBullet_Mgr::BLMgrUpdate(float a_DwdDeltaTime, DWORD a_DwdLastTime, VecINT2D& a_Center, float(*GetDelta)(int WpType), bool(*CheckColl)(CBullet* a_RefBull, DWORD a_CurTime), void(*GenSmokePtc)(Vector2D a_StartV, DWORD a_CurTime, Vector2D a_DirVec))
{
	// 모든 총알 이동관련 업데이트 처리
	static float a_WDelta = 0.0f;
	for (int aii = 0; aii < m_BullList.size(); aii++)
	{
		if (m_BullList[aii]->m_BLActive == false)
			continue;

		a_WDelta = a_DwdDeltaTime;
		if (GetDelta != NULL)
			a_WDelta = GetDelta(0);

		m_BullList[aii]->BulletUpdate(a_DwdDeltaTime, a_DwdLastTime, a_WDelta, m_CamPos, a_Center,GenSmokePtc);

		// 총알 몬스터 충돌 구현
		if (m_BullList[aii]->m_UC_Type == CT_Hero)
		{
			// 총알 종류에 따라 데미지를 나중에 구현하도록 하자
			g_Mon_Mgr.TakeDamageMon(m_BullList[aii], g_Hero.m_Power);

			// 보스 총알 데미지 구현
			g_Boss.DamageToBoss(m_BullList[aii], g_Hero.m_Power);
		}
		else if (m_BullList[aii]->m_UC_Type == CT_Monster)
		{
			// 주인공 총알 맞는 부분
			g_Hero.DamageToHero(m_BullList[aii], 100);
		}
	}
}

void CBullet_Mgr::BLMgrRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush)
{
	// 총알 그려주기
	for (int aii = 0; aii < m_BullList.size(); aii++)
	{
		if (m_BullList[aii]->m_BLActive == false)
			continue;

		m_BullList[aii]->BulletRender(a_pd2dRTarget, a_pBrush, m_CamPos);
	}
}

void CBullet_Mgr::BLMgrDestroy()
{
	for (int i = 0; i < m_BullList.size(); i++)
	{
		if (m_BullList[i] != NULL)
		{
			delete m_BullList[i];
			m_BullList[i];
		}
	}
	m_BullList.clear();
}

void CBullet_Mgr::BossNormalShoot(Vector2D a_StartV, Vector2D a_TargetV)
{
	static Vector2D SpawnLocation;
	static float Ang = 0.0f;

	static Vector2D a_CacDirVec;
	a_CacDirVec = a_TargetV - a_StartV;
	a_CacDirVec.Normalize();

	SpawnLocation = a_StartV + a_CacDirVec * 40.0f;
	Ang = a_CacDirVec.GetAngle();			// 백터를 각도로 환산
	a_CacDirVec = Vector2D::GetNormalFromRotation(Ang);

	for (int aii = 0; aii < m_BullList.size(); aii++)
	{
		if (m_BullList[aii]->m_BLActive == false)
		{			
			m_BullList[aii]->m_TexImgWidth = m_BossNormalWidth;
			m_BullList[aii]->m_TexImgHeight = m_BossNormalHeight;
			m_BullList[aii]->m_Radius = 10.0f;
			m_BullList[aii]->m_MoveSpeed = 1000.0f;

			m_BullList[aii]->m_CurPos.x = SpawnLocation.x;
			m_BullList[aii]->m_CurPos.y = SpawnLocation.y;
			m_BullList[aii]->m_RenderPos.x = SpawnLocation.x;
			m_BullList[aii]->m_RenderPos.y = SpawnLocation.y;

			m_BullList[aii]->m_DirVec = a_CacDirVec;
			m_BullList[aii]->m_DirRot = Ang;
			m_BullList[aii]->m_BLActive = true;
			m_BullList[aii]->m_Duration = 2.0f;
			m_BullList[aii]->m_UC_Type = CT_Monster;

			return;
		}
	} // for (int aii = 0;aii < m_BullList.size();aii++) 

	static CBullet* a_BNode = NULL;
	a_BNode = new CBullet();	
	a_BNode->m_TexImgWidth = m_BossNormalWidth;
	a_BNode->m_TexImgHeight = m_BossNormalWidth;
	a_BNode->m_Radius = 10.0f;
	a_BNode->m_MoveSpeed = 1000.0f;

	a_BNode->m_CurPos.x = SpawnLocation.x;
	a_BNode->m_CurPos.y = SpawnLocation.y;
	a_BNode->m_RenderPos.x = SpawnLocation.x;
	a_BNode->m_RenderPos.y = SpawnLocation.y;

	a_BNode->m_DirVec = a_CacDirVec;
	a_BNode->m_DirRot = Ang;
	a_BNode->m_BLActive = true;
	a_BNode->m_Duration = 2.0f;
	a_BNode->m_UC_Type = CT_Monster;

	m_BullList.push_back(a_BNode);
}

void CBullet_Mgr::BossFeverShoot(Vector2D a_StartV, Vector2D a_TargetV)
{
	bool a_isCreate = false;
	// 12등분이 나오도록 각도정해주기
	for (m_SkillAngle = 0; m_SkillAngle < (2.0f * 3.141592f); m_SkillAngle += (3.141592f / 12))
	{
		CacStartV = a_StartV;

		a_TargetV.x = CacStartV.x + (m_SkillRadius * cos(m_SkillAngle));
		a_TargetV.y = CacStartV.y + (m_SkillRadius * sin(m_SkillAngle));

		// 총알 생성		
		static Vector2D a_CacDirVec;
		static float Ang = 0.0f;

		a_CacDirVec = a_TargetV - CacStartV;
		a_CacDirVec.Normalize();

		static Vector2D SpawnLocation;
		SpawnLocation = CacStartV + a_CacDirVec * 40.0f;
		Ang = a_CacDirVec.GetAngle();			// 백터를 각도로 환산
		a_CacDirVec = Vector2D::GetNormalFromRotation(Ang);

		for (auto CurBullet : m_BullList)
		{
			if (CurBullet->m_BLActive == false)
			{
				CurBullet->m_TexImgWidth = m_BossNormalWidth;
				CurBullet->m_TexImgHeight = m_BossNormalHeight;
				CurBullet->m_Radius = 10.0f;
				CurBullet->m_MoveSpeed = 1000.0f;
				
				CurBullet->m_CurPos.x = SpawnLocation.x;
				CurBullet->m_CurPos.y = SpawnLocation.y;
				CurBullet->m_RenderPos.x = SpawnLocation.x;
				CurBullet->m_RenderPos.y = SpawnLocation.y;
				
				CurBullet->m_DirVec = a_CacDirVec;
				CurBullet->m_DirRot = Ang;
				CurBullet->m_BLActive = true;
				CurBullet->m_Duration = 2.0f;
				CurBullet->m_UC_Type = CT_Monster;

				a_isCreate = true;
				break;
			}
		} // for (int aii = 0;aii < m_BullList.size();aii++) 

		if (a_isCreate == false)
		{
			static CBullet* a_BNode = NULL;
			a_BNode = new CBullet();
			a_BNode->m_TexImgWidth = m_BossNormalWidth;
			a_BNode->m_TexImgHeight = m_BossNormalWidth;
			a_BNode->m_Radius = 10.0f;
			a_BNode->m_MoveSpeed = 1000.0f;

			a_BNode->m_CurPos.x = a_StartV.x;
			a_BNode->m_CurPos.y = a_StartV.y;
			a_BNode->m_RenderPos.x = a_StartV.x;
			a_BNode->m_RenderPos.y = a_StartV.y;

			a_BNode->m_DirVec = a_CacDirVec;
			a_BNode->m_DirRot = Ang;
			a_BNode->m_BLActive = true;
			a_BNode->m_Duration = 2.0f;
			a_BNode->m_UC_Type = CT_Monster;

			m_BullList.push_back(a_BNode);
		}		
		// 총알 생성	
		a_isCreate = false;
	}
}

void CBullet_Mgr::SpawnPistol(Vector2D a_StartV, Vector2D a_TargetV)
{
	static Vector2D SpawnLocation;
	static float Ang = 0.0f;

	static Vector2D a_CacDirVec;
	a_CacDirVec = a_TargetV - a_StartV;
	a_CacDirVec.Normalize();

	SpawnLocation = a_StartV + a_CacDirVec * 40.0f;
	Ang = a_CacDirVec.GetAngle();			// 백터를 각도로 환산
	a_CacDirVec = Vector2D::GetNormalFromRotation(Ang);

	for (int aii = 0; aii < m_BullList.size(); aii++)
	{
		if (m_BullList[aii]->m_BLActive == false)
		{
			//m_BullList[aii]->WeaponType = EWeaponSlots::PISTOL;
			m_BullList[aii]->m_TexImgWidth = m_PistolWidth;
			m_BullList[aii]->m_TexImgHeight = m_PistolHeight;
			m_BullList[aii]->m_Radius = 10.0f;
			m_BullList[aii]->m_MoveSpeed = 1000.0f;

			m_BullList[aii]->m_CurPos.x = SpawnLocation.x;
			m_BullList[aii]->m_CurPos.y = SpawnLocation.y;
			m_BullList[aii]->m_RenderPos.x = SpawnLocation.x;
			m_BullList[aii]->m_RenderPos.y = SpawnLocation.y;

			m_BullList[aii]->m_DirVec = a_CacDirVec;
			m_BullList[aii]->m_DirRot = Ang;
			m_BullList[aii]->m_BLActive = true;
			m_BullList[aii]->m_Duration = 2.0f;
			m_BullList[aii]->m_UC_Type = CT_Hero;

			return;
		}
	} // for (int aii = 0;aii < m_BullList.size();aii++) 

	static CBullet* a_BNode = NULL;
	a_BNode = new CBullet();
	//a_BNode->WeaponType = EWeaponSlots::PISTOL;
	a_BNode->m_TexImgWidth = m_PistolWidth;
	a_BNode->m_TexImgHeight = m_PistolHeight;
	a_BNode->m_Radius = 10.0f;
	a_BNode->m_MoveSpeed = 1000.0f;

	a_BNode->m_CurPos.x = SpawnLocation.x;
	a_BNode->m_CurPos.y = SpawnLocation.y;
	a_BNode->m_RenderPos.x = SpawnLocation.x;
	a_BNode->m_RenderPos.y = SpawnLocation.y;

	a_BNode->m_DirVec = a_CacDirVec;
	a_BNode->m_DirRot = Ang;
	a_BNode->m_BLActive = true;
	a_BNode->m_Duration = 2.0f;
	a_BNode->m_UC_Type = CT_Hero;

	m_BullList.push_back(a_BNode);
}

void CBullet_Mgr::ResetBullet()
{
	// 총알 전체 파괴
	BLMgrDestroy();

	// 총알 메모리품로 미리 만들어 놓기
	CBullet* a_BLNode = NULL;
	for (int aii = 0; aii < 200; aii++)
	{
		a_BLNode = new CBullet();
		m_BullList.push_back(a_BLNode);
	}
}

CBullet_Mgr g_Bullet_Mgr;