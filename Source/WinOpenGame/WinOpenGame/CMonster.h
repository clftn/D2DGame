#pragma once

#include "Vector2D.h"
#include <d2d1.h>
#include "GlobalValue.h"

class CHero;

enum MonAIState
{
	MAI_Idle,			// 숨쉬기 상태
	MAI_Patrol,			// 패트롤 상태
	MAI_AggroTrace,		// 적으로부터 공격을 당했을 때 추적 상태
	MAI_NormalTrace,	// 일반 추적 상태
	MAI_ReturnPos,		// 추적에서 놓쳤을 때 돌아오는 상태
	MAI_Attack,			// 공격 상태
};

class CMonster
{
public:
	int m_SpawnIdx = -1;
	float m_DeltaTime = 0.0f;

	ID2D1Bitmap* m_SocketImg;
	bool m_isActive = false;
	float m_MaxHP = 400.0f;
	float m_CurHP = 400.0f;
	bool isHit = false;			// 몬스터가 맞았을 시

	// 몬스터 좌표 계산용 변수들
	Vector2D	m_CurPos;
	float		m_Speed = 150.0f;
	Vector2D	m_DirVec;
	//float		m_HalfColl = 20;

	// 절대좌표 이동 계산용 변수
	VecINT2D m_ScreenHalf;		// 화면 반 사이즈 저장용 변수
	Vector2D m_CamPos = { 0, 0 };
	Vector2D m_RenderPos;

	float m_AttackTick = 0.5f;				// 공격 속도
	float m_AttackTickUse = 0.5f;			// 공격 속도
	float m_Power = 30.0f;					// 공격력
	KindOfMonster MonsterKind = Mon1;	    // 몬스터 종류

	// 몬스터 AI 변수들
	float m_AggroRange = 300.0f;			// 공격 범위
	MonAIState MonCurState = MAI_Patrol;	// 현재 상태
	float m_PAMoveTime = 3.0f;				// 패트롤 시 움직이는 시간
	float m_PAMoveUseTime = 3.0f;			// 패트롤 움직임 사용하는 시간
	float m_PAWaitTime = 1.5f;				// 패트롤 시 잠깐 멈추는 시간
	float m_PAWaitUseTime = 1.5f;			// 패트롤 시 잠깐 멈추는 시간
	Vector2D m_CacVec;						// 움직임 계산을 위한 함수
	Vector2D m_AIDirVec;					// 움직일 방향 백터
	CHero* AggroTarget;						// 어그로까 끌릴 시 해당 타겟설정
	int isXPlusMove;						// X축으로 양의 방향으로 움직일 지 결정
	int isYPlusMove;						// Y축으로 양의 방향으로 움직일 지 결정
	int XMoveLength;						// X축으로 움직일 양 결정
	int YMoveLength;						// Y축으로 움직일 양 결정
	float AngrySpeed = 300;					// 맞았을 시 빠르게 움직이는 부분
	bool isPatrol = true;					// 패트롤 상태 OnOff
	bool isMonWait = false;					// 패트롤 이후 잠깐 멈추는 변수

	// 컬링을 위한 백터 변수들
	Vector2D m_Sc_HLen;				// 컬링을 위한 화면 반사이즈 변수
	Vector2D m_Obj_HLen;			// 컬링을 위한 그림 반사이즈 변수
	bool m_InScRect = false;		// 화면 안에 있는지 확인
	Vector2D a_AA_Min;				// AABB 충돌을 이용한 화면 컬링
	Vector2D a_AA_Max;				// AABB 충돌을 이용한 화면 컬링
	Vector2D a_BB_Min;				// AABB 충돌을 이용한 화면 컬링
	Vector2D a_BB_Max;				// AABB 충돌을 이용한 화면 컬링

public:
	virtual void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	void Update_Unit(double a_DeltaTime, VecINT2D& a_Center, Vector2D& a_CamPos, class CHero& a_Hero);
	void Render_Unit(ID2D1HwndRenderTarget* a_pd2dTarget, ID2D1SolidColorBrush* a_pBrush);
	virtual void Destroy_Unit();

	// AI 구현도 여기에서 해야 한다.
	void Spawn(float a_XX, float a_YY);
	void MonsterAI(float a_DeltaTime,class CHero& a_Hero);
	void TakeDamage(float Damage);
	void AttackHero();

	// 컬링을 위한 함수
	bool CheckAABB(Vector2D& AACen, Vector2D& AAHLen,Vector2D& BBCen, Vector2D& BBHLen);
};

