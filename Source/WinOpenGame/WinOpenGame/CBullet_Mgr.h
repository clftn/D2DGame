#pragma once

#include <vector>
using namespace std;
#include "CBullet.h"

class CMonsters_Mgr;

class CBullet_Mgr
{
private:
	float m_PistolWidth = 30.0f;		// 권총 총알 사이즈
	float m_PistolHeight = 5.0f;		// 권총 총알 사이즈

	float m_BossNormalWidth = 10.0f;	// 보스 총알 사이즈
	float m_BossNormalHeight = 10.0f;	// 보스 총알 사이즈

	float m_SkillRadius = 100.0f;		// 보스 탄뿌리기 반지름
	float m_SkillAngle = 0.0f;			// 보스 스킬 각도
	Vector2D CacStartV;					// 시작점 스킬 좌표

public:
	vector<CBullet*> m_BullList;	//<--- 총알 풀 방식
	Vector2D m_CamPos = { 0.0f, 0.0f };

	// 충돌부분 관련 변수들 선언

public:
	void BLMgrInit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName) = NULL);
	void BLMgrUpdate(
		float a_DwdDeltaTime,
		DWORD a_DwdLastTime,
		VecINT2D& a_Center,
		float(*GetDelta)(int WpType) = NULL,
		bool(*CheckColl)(CBullet* a_RefBull, DWORD a_CurTime) = NULL,
		void(*GenSmokePtc)(Vector2D a_StartV, DWORD a_CurTime, Vector2D a_DirVec) = NULL
	);

	void BLMgrRender(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush);
	void BLMgrDestroy();

	void BossNormalShoot(Vector2D a_StartV, Vector2D a_TargetV);
	void BossFeverShoot(Vector2D a_StartV, Vector2D a_TargetV);

	void SpawnPistol(Vector2D a_StartV, Vector2D a_TargetV);
	void ResetBullet();
};

extern CBullet_Mgr g_Bullet_Mgr;