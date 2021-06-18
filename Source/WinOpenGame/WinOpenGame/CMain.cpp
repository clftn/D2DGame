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
    srand((unsigned)time(NULL)); // ���� �Լ��� ���� �뵵

    m_hWnd = a_hWnd; // �ڵ鷯 �޾ƿ���

    // D2D�ʱ�ȭ�� ���� �κ�
    HRESULT hr = E_FAIL;

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pd2dFactory);

    RECT rc;
    GetClientRect(m_hWnd, &rc);
    D2D1_SIZE_U uSize = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
    m_pd2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hWnd, uSize, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
        &m_pd2dRenderTarget);

    //---------- Direct2D �ʱ�ȭ �κ�
    m_pd2dRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White), &m_Brush);

    //---------- ��Ʈ ����
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        _uuidof(m_pDWriteFactory),
        reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
    );

    //TextFormat : Gulim(����)�� ��Ʈũ��� 40������ ���� ���� ������ �־��ش�.
    m_pDWriteFactory->CreateTextFormat(
        _T("Gulim"), NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        40, _T(""), &m_TextFormat
    );
    
    CoInitialize(0); //Com�ʱ�ȭ
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory));

    // ��� �ʱ�ȭ �κ�
    g_BackGround.BGMgrInit(D2DLoadImg);

    // ���ΰ� �ʱ�ȭ �κ�
    g_Hero.m_hWnd = a_hWnd;
    g_Hero.Init_Unit(D2DLoadImg);

    // �Ѿ� �ʱ�ȭ �κ�
    g_Bullet_Mgr.BLMgrInit(D2DLoadImg);

    // ���� �ʱ�ȭ �κ�
    g_Boss.Init_Unit(D2DLoadImg);

    // UI �ʱ�ȭ �κ�
    g_UIMgr.UIMgrInit(m_hWnd, m_pDWriteFactory, D2DLoadImg);

    // �ð��� ���� �ʱ�ȭ
    m_LastTick = timeGetTime(); //�ʱ�ȭ
    m_LastTime = timeGetTime(); // ��ŸŸ�ӿ�
}

void CMain::MainUpdate()
{
    // ��Ÿ Ÿ�� ������ �κ�
    timeBeginPeriod(1); // ���е� ���̱� ����
    m_CurTime = timeGetTime();
    m_DeltaTime = (float)((m_CurTime - m_LastTime) * 0.001f);
    m_LastTime = m_CurTime;
    timeEndPeriod(1);
    // ��Ÿ Ÿ�� ������ �κ�

    static RECT a_Crt;
    GetClientRect(m_hWnd, &a_Crt);              // Main DC�� ���� ���� ����� ������ �Լ�
    m_ScreenHalf.x = (int)(a_Crt.right / 2);
    m_ScreenHalf.y = (int)(a_Crt.bottom / 2);   // ��ũ���� �� ����� �˾Ƶΰ�, �׸� �� ���

    if (g_GameState == GameState::GameIng)
    {   
        // ���ΰ� ������Ʈ
        g_Hero.Update_Unit(m_DeltaTime, m_ScreenHalf);

        // ī�޶��� ������ǥ ������Ʈ
        m_CamPos = g_Hero.m_CurPos; // ī�޶� �̵�
        m_CamPos.x = m_CamPos.x - (float)m_ScreenHalf.x;
        m_CamPos.y = m_CamPos.y - (float)m_ScreenHalf.y;

        LimitMoveCam();
        g_Hero.Abs_Update(m_CamPos);

        // ��� ������Ʈ   
        g_BackGround.BGMgrUpdate(m_DeltaTime, m_CamPos);

        // ���� �Ŵ��� ������Ʈ �κ�
        g_Mon_Mgr.MonMgr_Update(m_DeltaTime, m_ScreenHalf, m_CamPos, g_Hero, D2DLoadImg);

        // ������ 10�̻��̸� ��Ÿ������ ����
        if (g_Hero.m_Level >= 10)
        {
            // ���� ������Ʈ
            g_Boss.Update_Unit(m_DeltaTime, m_ScreenHalf, m_CamPos, &g_Hero);
        }

        // �Ѿ� ������Ʈ �κ�
        g_Bullet_Mgr.m_CamPos = m_CamPos;
        g_Bullet_Mgr.BLMgrUpdate(m_DeltaTime, m_LastTime, m_ScreenHalf);
    }    

    // UI ������Ʈ �κ�
    g_UIMgr.UIMgrUpdate(m_DeltaTime, m_CamPos, GameReSet);
}

void CMain::MainRender(HWND a_hWnd)
{
    if (m_pd2dRenderTarget == NULL)
        return;

    //--------- FPS ��¿� ���
    // �̺κ��� �ɼ����� �� �� �ֵ�������
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
    //--------- FPS ��¿� ���

    // �׸��� ����
    m_pd2dRenderTarget->BeginDraw();
    m_pd2dRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Blue)); //0xffffff)); // �⺻ ��漳��

    if (g_GameState == GameState::GameIng)
    {
        g_BackGround.m_hWnd = m_hWnd;
        g_BackGround.BGMgrRender(m_pd2dRenderTarget);

        // ���ΰ� �׸���
        g_Hero.Render_Unit(m_pd2dRenderTarget, m_Brush);

        // ���� �׸���
        g_Mon_Mgr.MonMgr_Render(m_pd2dRenderTarget, m_Brush);

        // ������ 10�̻��̸� ��Ÿ������ ����
        if (g_Hero.m_Level >= 10)
        {
            // ���� �׸���
            g_Boss.Render_Unit(m_pd2dRenderTarget, m_Brush);
        }

        // �Ѿ� �׷��ֱ�
        g_Bullet_Mgr.BLMgrRender(m_pd2dRenderTarget, m_Brush);

        //----- FPS ���, ���� �ɼ����� ������
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
    
    // IU �׷��ֱ�
    g_UIMgr.UIMgrRender(m_pd2dRenderTarget, m_Brush);

    // �׸��� ����
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
    // ī�޶� ���� ������ ��� �� ���� ���� �ɱ�
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

    // ĳ���� ���� ������ ��� �� ���� ���� �ɱ�
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
    // ĳ���� ���� ������ ��� �� ���� ���� �ɱ�
}

#pragma region D2D�̹��� �ε� �Լ�

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

    //����Ʈ�� �����͸� ������� �ؼ� ���� ������ ������ ������ �޸𸮸� �����ؾ� �մϴ�.
    hr = a_pRenderTarget->CreateBitmapFromWicBitmap(a_pConverter, nullptr, bitmap);

    //�����ߴ� �ڿ� ����
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
    // ����� �ʱ�ȭ
    g_Hero.HeroReset();
    g_HeroStateMove = State1;
    g_HeroStateStd = IdleLeft;

    // ���� �ʱ�ȭ
    g_Mon_Mgr.MonsterReset();

    // �Ѿ� �ʱ�ȭ
    g_Bullet_Mgr.ResetBullet();

    // ���� �ʱ�ȭ
    g_Boss.ResetBoss();

    // �������� ���� �ʱ�ȭ

}

CMain g_Main_Mgr;