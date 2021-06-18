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
	bool m_BLActive = false;		// �Ѿ��� ��Ƽ�� ����	
	ID2D1Bitmap* m_BulletImg = NULL;

	UClassType m_UC_Type = CT_Hero;		// ���� �� �Ѿ�����

	float m_TexImgWidth = 40.0f;
	float m_TexImgHeight = 10.0f;

	float m_Duration = 4.0f;		// �Ѿ��� ������ Ÿ��(�Ѿ��� ���ʵ��� ���ư��� �� �������� �ð�)
	Vector2D m_CurPos;				// �Ѿ��� ���� ��ġ
	Vector2D m_RenderPos;			// �Ѿ� ������ ������ ���� ��ġ ���� ����
	Vector2D m_DirVec;				// �Ѿ��� ���ư��� �������
	float m_DirRot = 0.0f;			// �Ѿ��� ���ư��� ���Ⱒ��
	float m_MoveSpeed = 1700.0f;	// �Ѿ��� �̵��ӵ�
	float m_Radius = 25.0f;			// �Ѿ� �浹 �ݰ�
	Vector2D a_CacBVec;				// ���� ����

	int a_CacX = 0;					// ���� ����
	int a_CacY = 0;					// ���� ����
	float a_Rotation = 0.0f;		// �Ѿ��� ���ư��� ����
	float a_Alpha = 1.0f;			// �Ѿ��� ����
	float m_HalfColl = 10.0f;		// �Ѿ��� �浹 �ݰ�

	// �ø��� ���� ���� ������
	Vector2D m_Sc_HLen;				// �ø��� ���� ȭ�� �ݻ����� ����
	Vector2D m_Obj_HLen;			// �ø��� ���� �׸� �ݻ����� ����
	bool m_InScRect = false;		// ȭ�� �ȿ� �ִ��� Ȯ��
	Vector2D a_AA_Min;				// AABB �浹�� �̿��� ȭ�� �ø�
	Vector2D a_AA_Max;				// AABB �浹�� �̿��� ȭ�� �ø�
	Vector2D a_BB_Min;				// AABB �浹�� �̿��� ȭ�� �ø�
	Vector2D a_BB_Max;				// AABB �浹�� �̿��� ȭ�� �ø�
	VecINT2D m_ScreenHalf;			// ȭ�� �� ������ ����� ����

public:
	bool BulletUpdate(
		float a_DwdDeltaTime,		// ������ ������ DeltaTime
		DWORD a_DwdLastTime,		// ������ ���� �ð�
		float a_WpDeltaTime,		// ���⺰ �̵��� ���� DeltaTime
		Vector2D a_CamPos,			// �ø��� ���� ī�޶� ��ǥ
		VecINT2D& a_Center,			// �ø� �� ���� ��ǥ ����
		void(*GenSmokePtc)(Vector2D a_StartV, DWORD a_CurTime, Vector2D a_DirVec) = NULL);	// �̻��� Smoke ������ �Լ� ������

	void BulletRender(ID2D1HwndRenderTarget* a_pd2dRTarget,
		ID2D1SolidColorBrush* a_pBrush,
		Vector2D a_CamPos = { 0,0 });

	bool CheckAABB(Vector2D& AACen, Vector2D& AAHLen, Vector2D& BBCen, Vector2D& BBHLen); // �ø��� ���� ȭ�� �Ǵ� ����
};