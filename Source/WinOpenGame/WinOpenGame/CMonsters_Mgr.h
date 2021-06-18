#pragma once

#include "GlobalValue.h"
#include "Vector2D.h"
#include <vector>
using namespace std;

#include <d2d1.h>

class CMonster;
class CHero;
class CBullet;

class CMonsters_Mgr
{
private:
	// �޸� Ǯ ���
	vector<CMonster*> m_MonList;
	vector<CMonster*>::iterator Moniter;

	Vector2D a_CacVec;
	float a_CacDist;
	float a_RadiusPlus;
	CMonster* a_OwnMon = NULL;		// ���� ���� ����
	float a_CacMargin;				// ���Ϳ� ���ΰ��� ���� ����
	float tempHalfColl;				// ������ �浹�ݰ� �ӽ� ����	
	float m_SpawnTimeSTD = 3.0f;	// ���� �ð� ����
	float m_SpawnTime = 3.0f;		// ���� �ð� ����

	// ���� ������ ���� ������
	bool isfirst = true;			// ù��° ���� ������ ���� ����(�ʹݿ� ���͸� 10������ ������
	int Area1Count = 0;
	int Area2Count = 0;
	int Area3Count = 0;
	int Area4Count = 0;
	int Area5Count = 0;
	int Area6Count = 0;
	int Area7Count = 0;
	int Area8Count = 0;
	int Area9Count = 0;
	int Area10Count = 0;
	int MaxCount = 20;				// ������ 20 �� 200���� ����
	int HalfMaxCount = 10;			// 10������ �̸� �����س�����
	int MonSpawnCount = 200;		// ���� ���� �Ѱ� ����
	float AreaX = 0.0f;
	float AreaY = 0.0f;
	float RadiusToMon = 0.0f;		// �ݸ����� ���� ����

public:	
	void MonMgr_Update(double a_DeltaTime, VecINT2D& a_Center, Vector2D& a_CamPos, CHero& a_Hero, ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	void MonMgr_Render(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush);	
	void MonMgr_Destroy();

	void SpawnMonster(float a_DeltaTime, ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	void MonToHeroColl(CHero& a_Hero, CMonster& a_Monster);
	void MonToMonColl(CMonster* thisMon);
	float MonToMonCalcRadius(CMonster* thisMon, CMonster* otherMon);
	void TakeDamageMon(CBullet* a_Bullet,float Damage);
	void CalcSpawnArea(KindOfMonster Monkind);
	void MonsterReset();
};

extern CMonsters_Mgr g_Mon_Mgr;