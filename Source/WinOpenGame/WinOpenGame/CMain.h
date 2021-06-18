#pragma once

#pragma comment (lib, "d2d1.lib")  //<---Direct2D ����ϱ�...
#pragma comment(lib, "Dwrite.lib") //D2D�� ��Ʈ ����� ���ؼ� �߰� �ʿ�
#pragma comment(lib, "winmm.lib")  //timeGetTime() �Լ� ����� ���Ͽ�...
#pragma comment(lib, "WindowsCodecs.lib") //Direct2D�� �̹����� �ε��ϴ� �Լ��� ���� ������
//�ܺ� ���̺귯���� WIC��� ���̺귯���� �̹����κ��� �̹��� �����͸� ���� �� �ִ�.

#include <d2d1.h>                  //<---Direct2D ����ϱ�....
#include <d2d1helper.h>            //<---Direct2D �����ϴ� ���� �Լ� ����� ����...
#include <dwrite.h> //D2D ��Ʈ ����� ���ؼ� �߰� �ʿ�

#include <time.h>       //timeGetTime() �Լ� ����� ���Ͽ�...
#include <Mmsystem.h>   //timeGetTime() �Լ� ����� ���Ͽ�...

#include <wincodec.h>

#include "Vector2D.h"

class CMain
{
private:
	HWND m_hWnd;
	ID2D1Factory* m_pd2dFactory = NULL;					// D2D �׸��� ����
	ID2D1HwndRenderTarget* m_pd2dRenderTarget = NULL;	// D2D �׸��� �ڵ鷯

	ID2D1SolidColorBrush* m_Brush = NULL;	// �����׸��� �뵵

	IDWriteFactory* m_pDWriteFactory = NULL;	// �۾� ���� �뵵
	IDWriteTextFormat* m_TextFormat = NULL;		// ������ �����ִ� ��Ʈ 40 ����

	IWICImagingFactory* m_pImageFactory = NULL;
	ID2D1Bitmap* m_pBitmap = NULL;

	// ��ŸŸ�� ���ϱ�� ����
	float m_DeltaTime;
	DWORD m_LastTime;
	DWORD m_CurTime;

	VecINT2D m_ScreenHalf;					//ȭ���� �ݻ����� ��� ������ش�.
	Vector2D m_CamPos = { 0.0f, 0.0f };		//ī�޶��� ������ǥ(��ü ���� ������ ī�޶��� ��ǥ

	//--------------- FPS ��¿� ����
	DWORD           m_LastTick = 0;
	int             m_FlipCount = 0;
	int             m_OldFlipCount = 0;
	//--------------- FPS ��¿� ����

public:
	void MainInit(HWND a_hWnd, HINSTANCE hInst);
	void MainUpdate();
	void MainRender(HWND a_hWnd);
	void MainDestroy();
	
	void LimitMoveCam();

	//�̹��� �ε� �Լ� ����
	static ID2D1Bitmap* D2DLoadImg(LPCWSTR fileName);
	static HRESULT D2DLoadBitmap(LPCWSTR fileName, ID2D1RenderTarget* a_pRenderTarget,
		IWICImagingFactory* a_pImgFactory, ID2D1Bitmap** bitmap);

	void On_MessageHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static void GameReSet();
};

extern CMain g_Main_Mgr;