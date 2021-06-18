#pragma once

#pragma comment (lib, "d2d1.lib")
#include "Vector2D.h"

#include <d2d1.h>

class CHero
{
public:
	HWND m_hWnd;	

	// ĳ���� �̵� ���� ����
	Vector2D m_CurPos = { 0.0f, 0.0f };		//���ΰ��� ������ǥ
	double m_MoveSpeed = 200.0f;

	// ���ΰ��� �浹 �ݰ�
	float m_HalfColl = 40.0f;	// ĳ���� ũ�Ⱑ 80
	Vector2D a_CacVec;			// �浹 ����

	// ���ΰ� HP
	float m_CurHP = 500.0f;
	float m_MaxHP = 500.0f;

	// ���ΰ� �ɷ�ġ
	int m_Level = 1;				// ����
	int m_Exp = 1;					// ����ġ
	int m_EncExp = 250 * m_Level;	// ���� ����
	int m_KillCount = 0;
	int m_Power = 100;				// ���ΰ� �Ŀ�(�켱 �̷��� �ϰ� ������Ʈ�� ����)

	// HP �� ������
	//---- HP Bar Render
	float FigureAlpha = 1.0f;  //���� ����
	float a_CacMXX = 0.0f;
	float a_CacMYY = 0.0f;
	float a_HpBSize = 50.0f;
	float a_CurHpSize = 0.0f;

private:
	ID2D1Bitmap* m_SocketImg = NULL;
	ID2D1Bitmap* m_ImgData;

	// ��������Ʈ ����	
	float m_SpriteWGap = 96.0f;
	float m_SpriteHGap = 96.0f;

	// ĳ���� ����	
	float m_CharWSize = 95.0f;
	float m_CharHSize = 80.0f;

	// ������ǥ �̵� ��� ����
	Vector2D m_ScreenHalf;					//ȭ�� �� ������ ����� ����
	Vector2D m_CamPos = { 0.0f, 0.0f };		//���� ��ġ
	Vector2D m_RenderPos;					//������ ��ġ(���ΰ��� ��������ǥ)

	// ĳ������ �ִϸ��̼� �ð�	
	float SetAniTime = 1.0f;	// 0.5���� ����ǰ� �غ���
	float UseAniTime;
	float KeyDownTime = 3.0f;	// Ű�� ������ ���� Idle���°� �Ǵµ� ���� �ɸ��� �ð�

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