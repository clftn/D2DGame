#pragma once

#pragma comment (lib, "d2d1.lib")  //<---Direct2D 사용하기...
#pragma comment(lib, "Dwrite.lib") //D2D의 폰트 사용을 위해서 추가 필요
#pragma comment(lib, "winmm.lib")  //timeGetTime() 함수 사용을 위하여...
#pragma comment(lib, "WindowsCodecs.lib") //Direct2D는 이미지를 로딩하는 함수가 없기 때문에
//외부 라이브러리인 WIC라는 라이브러리의 이미지로부터 이미지 데이터를 만들 수 있다.

#include <d2d1.h>                  //<---Direct2D 사용하기....
#include <d2d1helper.h>            //<---Direct2D 제공하는 각종 함수 사용을 위해...
#include <dwrite.h> //D2D 폰트 사용을 위해서 추가 필요

#include <time.h>       //timeGetTime() 함수 사용을 위하여...
#include <Mmsystem.h>   //timeGetTime() 함수 사용을 위하여...

#include <wincodec.h>

#include "Vector2D.h"

class CMain
{
private:
	HWND m_hWnd;
	ID2D1Factory* m_pd2dFactory = NULL;					// D2D 그리기 버퍼
	ID2D1HwndRenderTarget* m_pd2dRenderTarget = NULL;	// D2D 그리기 핸들러

	ID2D1SolidColorBrush* m_Brush = NULL;	// 도형그리기 용도

	IDWriteFactory* m_pDWriteFactory = NULL;	// 글씨 쓰기 용도
	IDWriteTextFormat* m_TextFormat = NULL;		// 프레임 보여주는 폰트 40 굴림

	IWICImagingFactory* m_pImageFactory = NULL;
	ID2D1Bitmap* m_pBitmap = NULL;

	// 델타타임 구하기용 변수
	float m_DeltaTime;
	DWORD m_LastTime;
	DWORD m_CurTime;

	VecINT2D m_ScreenHalf;					//화면의 반사이즈 계속 계산해준다.
	Vector2D m_CamPos = { 0.0f, 0.0f };		//카메라의 월드좌표(전체 지형 기준의 카메라의 좌표

	//--------------- FPS 출력용 변수
	DWORD           m_LastTick = 0;
	int             m_FlipCount = 0;
	int             m_OldFlipCount = 0;
	//--------------- FPS 출력용 변수

public:
	void MainInit(HWND a_hWnd, HINSTANCE hInst);
	void MainUpdate();
	void MainRender(HWND a_hWnd);
	void MainDestroy();
	
	void LimitMoveCam();

	//이미지 로딩 함수 선언
	static ID2D1Bitmap* D2DLoadImg(LPCWSTR fileName);
	static HRESULT D2DLoadBitmap(LPCWSTR fileName, ID2D1RenderTarget* a_pRenderTarget,
		IWICImagingFactory* a_pImgFactory, ID2D1Bitmap** bitmap);

	void On_MessageHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static void GameReSet();
};

extern CMain g_Main_Mgr;