#pragma once

#include "Vector2D.h"
#include <d2d1.h>
#pragma comment (lib, "d2d1.lib")

class CHero;
class CBullet;

// Boss ���ϵ�
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

	// ���� ��ǥ ���� ������
	Vector2D	m_CurPos;
	float		m_Speed = 150.0f;
	Vector2D	a_CacVec;
	Vector2D	m_DirVec;
	float		a_CacDist;
	float		a_RadiusPlus;	// �浹 ������
	float		m_HalfColl = 30;	

	// ������ǥ �̵� ���� ����
	VecINT2D m_ScreenHalf;		// ȭ�� �� ������ ����� ����
	Vector2D m_CamPos = { 0, 0 };
	Vector2D m_RenderPos;

	bool m_isActive = false;
	float m_CurHP = 1000;
	float m_MaxHP = 1000;

	// ���� AI ���� ���� �κ�
	bool isHeroView = true;							// ���ΰ��� ������ ����
	int ActStep = 1;								// ���� �ܰ�
	float m_ShootTime = 1.0f;						// ���� Ÿ��
	float m_UseTime = 0.0f;							// ���� Ÿ�� ���� ����
	float m_NormalActTime = 3.0f;					// ����Ÿ�� �ð�
	float m_NormalActSpeed = 0.5f;					// ��� ����
	float m_NormalActSpeedUse = m_NormalActSpeed;	// ��� ���� ��� �ð�
	float m_FeverActTime = 3.0f;					// �ǹ�Ÿ�� �ð�
	float m_FeverActSpeed = 0.2f;					// �ǹ� ����
	float m_FeverActSpeedUse = m_FeverActSpeed;		// �ǹ� ���� ��� �ð�
private:
	ID2D1Bitmap* m_SocketImg = NULL;
	ID2D1Bitmap* m_ImgData;

public:
	void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName) = NULL);
	void Update_Unit(double a_DeltaTime, VecINT2D& a_Center, Vector2D& a_CamPos, CHero* a_Hero);
	void Render_Unit(ID2D1HwndRenderTarget* a_pd2dRTarget, ID2D1SolidColorBrush* a_pBrush);
	void Destroy_Unit();

	// AI ������ ���⿡�� �ؾ� �Ѵ�.
	void Spawn(float a_XX, float a_YY);
	void BossToHero(CHero* a_Hero);
	void DamageToBoss(CBullet* a_Bullet, float Damage);
	void BossAI(float a_DeltaTime, CHero* a_Hero);
	void ResetBoss();
};

extern CBoss g_Boss;