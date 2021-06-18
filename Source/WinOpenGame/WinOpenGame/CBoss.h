#pragma once

#include "Vector2D.h"
#include <d2d1.h>
#pragma comment (lib, "d2d1.lib")

class CHero;
class CBullet;

// Boss 패턴들
enum BossState
{
	BS_SLEEP,		// inActive
	BS_NORMAL_ACT,	// Active
	BS_FEVER_ACT,		
};

class CBoss
{
public:
	BossState bossState = BS_SLEEP;

	// 몬스터 좌표 계산용 변수들
	Vector2D	m_CurPos;
	float		m_Speed = 150.0f;
	Vector2D	a_CacVec;
	Vector2D	m_DirVec;
	float		a_CacDist;
	float		a_RadiusPlus;	// 충돌 반지름
	float		m_HalfColl = 30;	

	// 절대좌표 이동 계산용 변수
	VecINT2D m_ScreenHalf;		// 화면 반 사이즈 저장용 변수
	Vector2D m_CamPos = { 0, 0 };
	Vector2D m_RenderPos;

	bool m_isActive = false;
	float m_CurHP = 1000;
	float m_MaxHP = 1000;

	// 보스 AI 관련 변수 부분
	bool isHeroView = true;							// 주인공을 인지한 여부
	int ActStep = 1;								// 공격 단계
	float m_ShootTime = 1.0f;						// 슈팅 타임
	float m_UseTime = 0.0f;							// 슈팅 타임 제어 변수
	float m_NormalActTime = 3.0f;					// 슈팅타임 시간
	float m_NormalActSpeed = 0.5f;					// 노멀 공속
	float m_NormalActSpeedUse = m_NormalActSpeed;	// 노멀 공속 사용 시간
	float m_FeverActTime = 3.0f;					// 피버타임 시간
	float m_FeverActSpeed = 0.2f;					// 피버 공속
	float m_FeverActSpeedUse = m_FeverActSpeed;		// 피버 공속 사용 시간
private:
	ID2D1Bitmap* m_SocketImg = NULL;
	ID2D1Bitmap* m_ImgData;

public:
	void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName) = NULL);
	void Update_Unit(double a_DeltaTime, VecINT2D& a_Center, Vector2D& a_CamPos, CHero* a_Hero);
	void Render_Unit(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush);
	void Destroy_Unit();

	// AI 구현도 여기에서 해야 한다.
	void Spawn(float a_XX, float a_YY);
	void BossToHero(CHero* a_Hero);
	void DamageToBoss(CBullet* a_Bullet, float Damage);
	void BossAI(float a_DeltaTime, CHero* a_Hero);
	void ResetBoss();
};

extern CBoss g_Boss;