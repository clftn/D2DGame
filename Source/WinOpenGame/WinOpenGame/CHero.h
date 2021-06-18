#pragma once

#pragma comment (lib, "d2d1.lib")
#include "Vector2D.h"

#include <d2d1.h>

class CHero
{
public:
	HWND m_hWnd;	

	// 캐릭터 이동 계산용 변수
	Vector2D m_CurPos = { 0.0f, 0.0f };		//주인공의 월드좌표
	double m_MoveSpeed = 200.0f;

	// 주인공의 충돌 반경
	float m_HalfColl = 40.0f;	// 캐릭터 크기가 80
	Vector2D a_CacVec;			// 충돌 계산용

	// 주인공 HP
	float m_CurHP = 500.0f;
	float m_MaxHP = 500.0f;

	// 주인공 능력치
	int m_Level = 1;				// 레벨
	int m_Exp = 1;					// 경험치
	int m_EncExp = 250 * m_Level;	// 레벨 간격
	int m_KillCount = 0;
	int m_Power = 100;				// 주인공 파워(우선 이렇게 하고 업데이트를 하자)

	// HP 바 변수들
	//---- HP Bar Render
	float FigureAlpha = 1.0f;  //도형 투명도
	float a_CacMXX = 0.0f;
	float a_CacMYY = 0.0f;
	float a_HpBSize = 50.0f;
	float a_CurHpSize = 0.0f;

private:
	ID2D1Bitmap* m_SocketImg = NULL;
	ID2D1Bitmap* m_ImgData;

	// 스프라이트 간격	
	float m_SpriteWGap = 96.0f;
	float m_SpriteHGap = 96.0f;

	// 캐릭터 간격	
	float m_CharWSize = 95.0f;
	float m_CharHSize = 80.0f;

	// 월드좌표 이동 계산 변수
	Vector2D m_ScreenHalf;					//화면 반 사이즈 저장용 변수
	Vector2D m_CamPos = { 0.0f, 0.0f };		//현재 위치
	Vector2D m_RenderPos;					//랜더링 위치(주인공의 랜더링좌표)

	// 캐릭터의 애니메이션 시간	
	float SetAniTime = 1.0f;	// 0.5마다 변경되게 해보자
	float UseAniTime;
	float KeyDownTime = 3.0f;	// 키를 누르고 난뒤 Idle상태가 되는데 까지 걸리는 시간

public:
	void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName) = NULL);
	void Update_Unit(double a_DeltaTime, VecINT2D a_ScreenHalf);
	void Render_Unit(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush);
	void Destroy_Unit();

	void Abs_Update(Vector2D& a_CamPos);
	void DamageToHero(class CBullet* a_Bullet, float Damage);

	void HeroReset();
};

extern CHero g_Hero;