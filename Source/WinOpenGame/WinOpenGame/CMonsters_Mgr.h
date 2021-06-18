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
	// 메모리 풀 방식
	vector<CMonster*> m_MonList;
	vector<CMonster*>::iterator Moniter;

	Vector2D a_CacVec;
	float a_CacDist;
	float a_RadiusPlus;
	CMonster* a_OwnMon = NULL;		// 현재 비교할 몬스터
	float a_CacMargin;				// 몬스터와 주인공의 간격 계산용
	float tempHalfColl;				// 몬스터의 충돌반경 임시 변수	
	float m_SpawnTimeSTD = 3.0f;	// 스폰 시간 설정
	float m_SpawnTime = 3.0f;		// 스폰 시간 설정

	// 스폰 지역을 위한 변수들
	bool isfirst = true;			// 첫번째 몬스터 생성을 위한 변수(초반에 몬스터를 10마리씩 만들자
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
	int MaxCount = 20;				// 지역당 20 총 200마리 스폰
	int HalfMaxCount = 10;			// 10마리를 미리 스폰해놓으면
	int MonSpawnCount = 200;		// 몬스터 스폰 한계 개수
	float AreaX = 0.0f;
	float AreaY = 0.0f;
	float RadiusToMon = 0.0f;		// 콜리전을 위한 변수

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