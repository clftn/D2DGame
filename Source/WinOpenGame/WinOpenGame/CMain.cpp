#include "framework.h"
#include "CMain.h"
#include "CBackGround.h"
#include "CHero.h"
#include "CBullet_Mgr.h"
#include "CMonsters_Mgr.h"
#include "CBoss.h"
#include "CUIMgr.h"

void CMain::MainInit(HWND a_hWnd , HINSTANCE hInst)
{
    srand((unsigned)time(NULL)); // 랜덤 함수를 위한 용도

    m_hWnd = a_hWnd; // 핸들러 받아오기

    // D2D초기화를 위한 부분
    HRESULT hr = E_FAIL;

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pd2dFactory);

    RECT rc;
    GetClientRect(m_hWnd, &rc);
    D2D1_SIZE_U uSize = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
    m_pd2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hWnd, uSize, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
        &m_pd2dRenderTarget);

    //---------- Direct2D 초기화 부분
    m_pd2dRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White), &m_Brush);

    //---------- 폰트 생성
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        _uuidof(m_pDWriteFactory),
        reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
    );

    //TextFormat : Gulim(굴림)와 폰트크기는 40글자의 정렬 등의 정보를 넣어준다.
    m_pDWriteFactory->CreateTextFormat(
        _T("Gulim"), NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        40, _T(""), &m_TextFormat
    );
    
    CoInitialize(0); //Com초기화
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory));

    // 배경 초기화 부분
    g_BackGround.BGMgrInit(D2DLoadImg);

    // 주인공 초기화 부분
    g_Hero.m_hWnd = a_hWnd;
    g_Hero.Init_Unit(D2DLoadImg);

    // 총알 초기화 부분
    g_Bullet_Mgr.BLMgrInit(D2DLoadImg);

    // 보스 초기화 부분
    g_Boss.Init_Unit(D2DLoadImg);

    // UI 초기화 부분
    g_UIMgr.UIMgrInit(m_hWnd, m_pDWriteFactory, D2DLoadImg);

    // 시간값 관련 초기화
    m_LastTick = timeGetTime(); //초기화
    m_LastTime = timeGetTime(); // 델타타임용
}

void CMain::MainUpdate()
{
    // 델타 타임 얻어오는 부분
    timeBeginPeriod(1); // 정밀도 높이기 전용
    m_CurTime = timeGetTime();
    m_DeltaTime = (float)((m_CurTime - m_LastTime) * 0.001f);
    m_LastTime = m_CurTime;
    timeEndPeriod(1);
    // 델타 타임 얻어오는 부분

    static RECT a_Crt;
    GetClientRect(m_hWnd, &a_Crt);              // Main DC의 가로 세로 사이즈를 얻어오는 함수
    m_ScreenHalf.x = (int)(a_Crt.right / 2);
    m_ScreenHalf.y = (int)(a_Crt.bottom / 2);   // 스크린의 반 사이즈를 알아두고, 그릴 때 사용

    if (g_GameState == GameState::GameIng)
    {   
        // 주인공 업데이트
        g_Hero.Update_Unit(m_DeltaTime, m_ScreenHalf);

        // 카메라의 월드좌표 업데이트
        m_CamPos = g_Hero.m_CurPos; // 카메라 이동
        m_CamPos.x = m_CamPos.x - (float)m_ScreenHalf.x;
        m_CamPos.y = m_CamPos.y - (float)m_ScreenHalf.y;

        LimitMoveCam();
        g_Hero.Abs_Update(m_CamPos);

        // 배경 업데이트   
        g_BackGround.BGMgrUpdate(m_DeltaTime, m_CamPos);

        // 몬스터 매니저 업데이트 부분
        g_Mon_Mgr.MonMgr_Update(m_DeltaTime, m_ScreenHalf, m_CamPos, g_Hero, D2DLoadImg);

        // 레벨이 10이상이면 나타나도록 설정
        if (g_Hero.m_Level >= 10)
        {
            // 보스 업데이트
            g_Boss.Update_Unit(m_DeltaTime, m_ScreenHalf, m_CamPos, &g_Hero);
        }

        // 총알 업데이트 부분
        g_Bullet_Mgr.m_CamPos = m_CamPos;
        g_Bullet_Mgr.BLMgrUpdate(m_DeltaTime, m_LastTime, m_ScreenHalf);
    }    

    // UI 업데이트 부분
    g_UIMgr.UIMgrUpdate(m_DeltaTime, m_CamPos, GameReSet);
}

void CMain::MainRender(HWND a_hWnd)
{
    if (m_pd2dRenderTarget == NULL)
        return;

    //--------- FPS 출력용 계산
    // 이부분은 옵션으로 뺄 수 있도록하자
    static DWORD FPSdelay = 1000;
    static DWORD thisTick;

    thisTick = timeGetTime();

    if ((thisTick - m_LastTick) >= FPSdelay)
    {
        m_LastTick = thisTick;
        m_OldFlipCount = m_FlipCount;
        m_FlipCount = 0;
    }
    else
    {
        m_FlipCount++;
    }
    static TCHAR strFPS[128];
    _stprintf_s(strFPS, 128, _T("FPS : %d"), m_OldFlipCount);
    //--------- FPS 출력용 계산

    // 그리기 시작
    m_pd2dRenderTarget->BeginDraw();
    m_pd2dRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Blue)); //0xffffff)); // 기본 배경설정

    if (g_GameState == GameState::GameIng)
    {
        g_BackGround.m_hWnd = m_hWnd;
        g_BackGround.BGMgrRender(m_pd2dRenderTarget);

        // 주인공 그리기
        g_Hero.Render_Unit(m_pd2dRenderTarget, m_Brush);

        // 몬스터 그리기
        g_Mon_Mgr.MonMgr_Render(m_pd2dRenderTarget, m_Brush);

        // 레벨이 10이상이면 나타나도록 설정
        if (g_Hero.m_Level >= 10)
        {
            // 보스 그리기
            g_Boss.Render_Unit(m_pd2dRenderTarget, m_Brush);
        }

        // 총알 그려주기
        g_Bullet_Mgr.BLMgrRender(m_pd2dRenderTarget, m_Brush);

        //----- FPS 계산, 추후 옵션으로 빼도록
        m_Brush->SetColor(D2D1::ColorF(0xff00ff));
        D2D1_SIZE_F renderTargetSize = m_pd2dRenderTarget->GetSize();
        m_pd2dRenderTarget->DrawText(
            strFPS,
            _tcslen(strFPS),
            m_TextFormat,
            D2D1::RectF(160, 0, renderTargetSize.width, renderTargetSize.height),
            m_Brush
        );
    }
    
    // IU 그려주기
    g_UIMgr.UIMgrRender(m_pd2dRenderTarget, m_Brush);

    // 그리기 종료
    m_pd2dRenderTarget->EndDraw();
}

void CMain::MainDestroy()
{
    g_UIMgr.UIMgrDestroy();

    g_Boss.Destroy_Unit();

    g_Mon_Mgr.MonMgr_Destroy();

    g_Bullet_Mgr.BLMgrDestroy();

    g_Hero.Destroy_Unit();

    if (m_pBitmap != NULL)
    {
        m_pBitmap->Release();
        m_pBitmap = NULL;
    }

    if (m_pImageFactory != NULL)
    {
        m_pImageFactory->Release();
        m_pImageFactory = NULL;
    }

    if (m_TextFormat != NULL)
    {
        m_TextFormat->Release();
        m_TextFormat = NULL;
    }

    if (m_pDWriteFactory != NULL)
    {
        m_pDWriteFactory->Release();
        m_pDWriteFactory = NULL;
    }

    if (m_Brush != NULL)
    {
        m_Brush->Release();
        m_Brush = NULL;
    }

    if (m_TextFormat != NULL)
    {
        m_TextFormat->Release();
        m_TextFormat = NULL;
    }

    if (m_pDWriteFactory != NULL)
    {
        m_pDWriteFactory->Release();
        m_pDWriteFactory = NULL;
    }

    if (m_Brush != NULL)
    {
        m_Brush->Release();
        m_Brush = NULL;
    }

    if (m_pd2dRenderTarget != nullptr)
    {
        m_pd2dRenderTarget->Release();
        m_pd2dRenderTarget = nullptr;
    }

    if (m_pd2dFactory != nullptr)
    {
        m_pd2dFactory->Release();
        m_pd2dFactory = nullptr;
    }
}

void CMain::LimitMoveCam()
{
    // 카메라 지형 밖으로 벗어날 수 없게 제한 걸기
    static int a_LmtBdLeft = 0;
    static int a_LmtBdTop = 0;
    static int a_LmtBdRight = 0;
    static int a_LmtBdBottom = 0;

    if (g_BackGround.m_WorldHfSize.x <= 0 || g_BackGround.m_WorldHfSize.y <= 0)
        return;

    a_LmtBdLeft = -g_BackGround.m_WorldHfSize.x + 4;
    a_LmtBdTop = -g_BackGround.m_WorldHfSize.y + 4;
    a_LmtBdRight = g_BackGround.m_WorldHfSize.x - 4 - (m_ScreenHalf.x * 2);
    a_LmtBdBottom = g_BackGround.m_WorldHfSize.y - 4 - (m_ScreenHalf.y * 2);

    if (a_LmtBdRight <= a_LmtBdLeft)
    {
        m_CamPos.x -= -m_ScreenHalf.x;
    }
    else
    {
        if (m_CamPos.x < (float)a_LmtBdLeft)
            m_CamPos.x = (float)a_LmtBdLeft;

        if ((float)a_LmtBdRight < m_CamPos.x)
            m_CamPos.x = (float)a_LmtBdRight;
    }

    if (a_LmtBdBottom <= a_LmtBdTop)
    {
        m_CamPos.y -= -m_ScreenHalf.y;
    }
    else
    {
        if (m_CamPos.y < (float)a_LmtBdTop)
            m_CamPos.y = (float)a_LmtBdTop;

        if ((float)a_LmtBdBottom < m_CamPos.y)
            m_CamPos.y = (float)a_LmtBdBottom;
    }

    // 캐릭터 지형 밖으로 벗어날 수 없게 제한 걸기
    a_LmtBdLeft = -g_BackGround.m_WorldHfSize.x + 30;
    a_LmtBdTop = -g_BackGround.m_WorldHfSize.y + 40;
    a_LmtBdRight = g_BackGround.m_WorldHfSize.x - 30;
    a_LmtBdBottom = g_BackGround.m_WorldHfSize.y - 40;

    if (g_Hero.m_CurPos.x < (float)a_LmtBdLeft)
        g_Hero.m_CurPos.x = (float)a_LmtBdLeft;

    if ((float)a_LmtBdRight < g_Hero.m_CurPos.x)
        g_Hero.m_CurPos.x = (float)a_LmtBdRight;

    if (g_Hero.m_CurPos.y < (float)a_LmtBdTop)
        g_Hero.m_CurPos.y = (float)a_LmtBdTop;

    if ((float)a_LmtBdBottom < g_Hero.m_CurPos.y)
        g_Hero.m_CurPos.y = (float)a_LmtBdBottom;
    // 캐릭터 지형 밖으로 벗어날 수 없게 제한 걸기
}

#pragma region D2D이미지 로딩 함수

ID2D1Bitmap* CMain::D2DLoadImg(LPCWSTR fileName)
{
    ID2D1Bitmap* a_pBGBmp = NULL;

    if (g_Main_Mgr.m_pd2dRenderTarget == NULL)
        return NULL;

    if (g_Main_Mgr.m_pImageFactory == NULL)
        return NULL;

    D2DLoadBitmap(fileName, g_Main_Mgr.m_pd2dRenderTarget, g_Main_Mgr.m_pImageFactory, &a_pBGBmp);

    return a_pBGBmp;
}

HRESULT CMain::D2DLoadBitmap(LPCWSTR fileName, ID2D1RenderTarget* a_pRenderTarget, IWICImagingFactory* a_pImgFactory, ID2D1Bitmap** bitmap)
{
    HRESULT hr = E_FAIL;

    IWICBitmapDecoder* a_pDecoder = NULL;

    hr = a_pImgFactory->CreateDecoderFromFilename(fileName, nullptr,
        GENERIC_READ, WICDecodeMetadataCacheOnDemand, &a_pDecoder);

    if (FAILED(hr))
        return hr;

    IWICBitmapFrameDecode* a_pFrameDecoder = NULL;
    hr = a_pDecoder->GetFrame(0, &a_pFrameDecoder);

    if (FAILED(hr))
    {
        a_pDecoder->Release();
        return hr;
    }

    IWICFormatConverter* a_pConverter = NULL;
    hr = a_pImgFactory->CreateFormatConverter(&a_pConverter);

    if (FAILED(hr))
    {
        a_pDecoder->Release();
        a_pFrameDecoder->Release();
        return hr;
    }

    hr = a_pConverter->Initialize(
        a_pFrameDecoder,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr, 0.0f, WICBitmapPaletteTypeCustom
    );

    if (FAILED(hr))
    {
        a_pDecoder->Release();
        a_pFrameDecoder->Release();
        a_pConverter->Release();

        return hr;
    }

    //컨버트된 데이터를 기반으로 해서 실제 랜더링 가능한 형태의 메모리를 생성해야 합니다.
    hr = a_pRenderTarget->CreateBitmapFromWicBitmap(a_pConverter, nullptr, bitmap);

    //생성했던 자원 해제
    a_pDecoder->Release();
    a_pFrameDecoder->Release();
    a_pConverter->Release();

    return hr;
}

#pragma endregion

void CMain::On_MessageHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void CMain::GameReSet()
{
    // 히어로 초기화
    g_Hero.HeroReset();
    g_HeroStateMove = State1;
    g_HeroStateStd = IdleLeft;

    // 몬스터 초기화
    g_Mon_Mgr.MonsterReset();

    // 총알 초기화
    g_Bullet_Mgr.ResetBullet();

    // 보스 초기화
    g_Boss.ResetBoss();

    // 스테이지 정보 초기화

}

CMain g_Main_Mgr;