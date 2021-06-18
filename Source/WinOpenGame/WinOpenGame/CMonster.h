#pragma once

#include "Vector2D.h"
#include <d2d1.h>
#include "GlobalValue.h"

class CHero;

enum MonAIState
{
	MAI_Idle,			// ������ ����
	MAI_Patrol,			// ��Ʈ�� ����
	MAI_AggroTrace,		// �����κ��� ������ ������ �� ���� ����
	MAI_NormalTrace,	// �Ϲ� ���� ����
	MAI_ReturnPos,		// �������� ������ �� ���ƿ��� ����
	MAI_Attack,			// ���� ����
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
	bool isHit = false;			// ���Ͱ� �¾��� ��

	// ���� ��ǥ ���� ������
	Vector2D	m_CurPos;
	float		m_Speed = 150.0f;
	Vector2D	m_DirVec;
	//float		m_HalfColl = 20;

	// ������ǥ �̵� ���� ����
	VecINT2D m_ScreenHalf;		// ȭ�� �� ������ ����� ����
	Vector2D m_CamPos = { 0, 0 };
	Vector2D m_RenderPos;

	float m_AttackTick = 0.5f;				// ���� �ӵ�
	float m_AttackTickUse = 0.5f;			// ���� �ӵ�
	float m_Power = 30.0f;					// ���ݷ�
	KindOfMonster MonsterKind = Mon1;	    // ���� ����

	// ���� AI ������
	float m_AggroRange = 300.0f;			// ���� ����
	MonAIState MonCurState = MAI_Patrol;	// ���� ����
	float m_PAMoveTime = 3.0f;				// ��Ʈ�� �� �����̴� �ð�
	float m_PAMoveUseTime = 3.0f;			// ��Ʈ�� ������ ����ϴ� �ð�
	float m_PAWaitTime = 1.5f;				// ��Ʈ�� �� ��� ���ߴ� �ð�
	float m_PAWaitUseTime = 1.5f;			// ��Ʈ�� �� ��� ���ߴ� �ð�
	Vector2D m_CacVec;						// ������ ����� ���� �Լ�
	Vector2D m_AIDirVec;					// ������ ���� ����
	CHero* AggroTarget;						// ��׷α� ���� �� �ش� Ÿ�ټ���
	int isXPlusMove;						// X������ ���� �������� ������ �� ����
	int isYPlusMove;						// Y������ ���� �������� ������ �� ����
	int XMoveLength;						// X������ ������ �� ����
	int YMoveLength;						// Y������ ������ �� ����
	float AngrySpeed = 300;					// �¾��� �� ������ �����̴� �κ�
	bool isPatrol = true;					// ��Ʈ�� ���� OnOff
	bool isMonWait = false;					// ��Ʈ�� ���� ��� ���ߴ� ����

	// �ø��� ���� ���� ������
	Vector2D m_Sc_HLen;				// �ø��� ���� ȭ�� �ݻ����� ����
	Vector2D m_Obj_HLen;			// �ø��� ���� �׸� �ݻ����� ����
	bool m_InScRect = false;		// ȭ�� �ȿ� �ִ��� Ȯ��
	Vector2D a_AA_Min;				// AABB �浹�� �̿��� ȭ�� �ø�
	Vector2D a_AA_Max;				// AABB �浹�� �̿��� ȭ�� �ø�
	Vector2D a_BB_Min;				// AABB �浹�� �̿��� ȭ�� �ø�
	Vector2D a_BB_Max;				// AABB �浹�� �̿��� ȭ�� �ø�

public:
	virtual void Init_Unit(ID2D1Bitmap* (*D2DLoadBmp)(LPCWSTR FName));
	void Update_Unit(double a_DeltaTime, VecINT2D& a_Center, Vector2D& a_CamPos, class CHero& a_Hero);
	void Render_Unit(ID2D1HwndRenderTarget* a_pd2dTarget, ID2D1SolidColorBrush* a_pBrush);
	virtual void Destroy_Unit();

	// AI ������ ���⿡�� �ؾ� �Ѵ�.
	void Spawn(float a_XX, float a_YY);
	void MonsterAI(float a_DeltaTime,class CHero& a_Hero);
	void TakeDamage(float Damage);
	void AttackHero();

	// �ø��� ���� �Լ�
	bool CheckAABB(Vector2D& AACen, Vector2D& AAHLen,Vector2D& BBCen, Vector2D& BBHLen);
};

