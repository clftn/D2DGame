#pragma once

#include <d2d1.h>
#include "Vector2D.h"

using namespace std;

enum UClassType
{
	CT_Unit = 0,
	CT_Hero,
	CT_Monster,
};

class CBullet
{
public:
	bool m_BLActive = false;		// 총알의 액티브 상태	
	ID2D1Bitmap* m_BulletImg = NULL;

	UClassType m_UC_Type = CT_Hero;		// 누가 쏜 총알인지

	float m_TexImgWidth = 40.0f;
	float m_TexImgHeight = 10.0f;

	float m_Duration = 4.0f;		// 총알의 라이프 타임(총알을 몇초동안 날아가게 할 것인지의 시간)
	Vector2D m_CurPos;				// 총알의 현재 위치
	Vector2D m_RenderPos;			// 총알 렌더링 연출을 위한 위치 계산용 변수
	Vector2D m_DirVec;				// 총알의 날아가는 방향백터
	float m_DirRot = 0.0f;			// 총알의 날아가는 방향각도
	float m_MoveSpeed = 1700.0f;	// 총알의 이동속도
	float m_Radius = 25.0f;			// 총알 충돌 반경
	Vector2D a_CacBVec;				// 계산용 변수

	int a_CacX = 0;					// 계산용 변수
	int a_CacY = 0;					// 계산용 변수
	float a_Rotation = 0.0f;		// 총알의 돌아가는 방향
	float a_Alpha = 1.0f;			// 총알의 투명도
	float m_HalfColl = 10.0f;		// 총알의 충돌 반경

	// 컬링을 위한 백터 변수들
	Vector2D m_Sc_HLen;				// 컬링을 위한 화면 반사이즈 변수
	Vector2D m_Obj_HLen;			// 컬링을 위한 그림 반사이즈 변수
	bool m_InScRect = false;		// 화면 안에 있는지 확인
	Vector2D a_AA_Min;				// AABB 충돌을 이용한 화면 컬링
	Vector2D a_AA_Max;				// AABB 충돌을 이용한 화면 컬링
	Vector2D a_BB_Min;				// AABB 충돌을 이용한 화면 컬링
	Vector2D a_BB_Max;				// AABB 충돌을 이용한 화면 컬링
	VecINT2D m_ScreenHalf;			// 화면 반 사이즈 저장용 변수

public:
	bool BulletUpdate(
		float a_DwdDeltaTime,		// 정밀한 기준의 DeltaTime
		DWORD a_DwdLastTime,		// 정밀한 현재 시간
		float a_WpDeltaTime,		// 무기별 이동을 위한 DeltaTime
		Vector2D a_CamPos,			// 컬링을 위한 카메라 좌표
		VecINT2D& a_Center,			// 컬링 시 월드 좌표 계산용
		void(*GenSmokePtc)(Vector2D a_StartV, DWORD a_CurTime, Vector2D a_DirVec) = NULL);	// 미사일 Smoke 생성용 함수 포인터

	void BulletRender(ID2D1HwndRenderTarget* a_pd2dRTarget,
		ID2D1SolidColorBrush* a_pBrush,
		Vector2D a_CamPos = { 0,0 });

	bool CheckAABB(Vector2D& AACen, Vector2D& AAHLen, Vector2D& BBCen, Vector2D& BBHLen); // 컬링을 위한 화면 판단 여부
};