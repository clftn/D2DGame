#include "framework.h"
#include "CBackGround.h"

void CBackGround::BGMgrInit(ID2D1Bitmap* (*MyLoadBitmap)(LPCWSTR fileName))
{
	if (MyLoadBitmap != NULL)
	{
		// 사막 이미지 로딩
		m_pBGBmpDesert = MyLoadBitmap(_T(".\\resources\\BackGrounds\\desert.jpg"));

		// 숲 이미지 로딩
		m_pBGBmpForest = MyLoadBitmap(_T(".\\resources\\BackGrounds\\forest.jpg"));
		
		// 도시 이미지 로딩
		m_pBGBmpCity = MyLoadBitmap(_T(".\\resources\\BackGrounds\\city.jpg"));

		// 사이즈를 맞췄으므로 계산값은 하나로 통쳐서
		if (m_pBGBmpDesert != NULL)
		{
			m_ImgSize.x = m_pBGBmpDesert->GetSize().width * 2;	// 월드 기본 사이즈 크기 지정 - 생각보다 작게 적용됨
			m_ImgSize.y = m_pBGBmpDesert->GetSize().height * 2;

			m_WorldHfSize.x = (int)(m_ImgSize.x * (X_Tile / 2.0f));
			m_WorldHfSize.y = (int)(m_ImgSize.y * (Y_Tile / 2.0f));
		}
	}
}

void CBackGround::BGMgrUpdate(float a_DeltaTime, Vector2D& a_CamPos)
{
	m_CamPos.x = a_CamPos.x;
	m_CamPos.y = a_CamPos.y;
}

void CBackGround::BGMgrRender(ID2D1HwndRenderTarget* a_pd2dRTarget)
{
	m_TileStPos.x = -m_WorldHfSize.x;
	m_TileStPos.y = -m_WorldHfSize.y;

	static int a_SetPosX = 0;
	static int a_SetPosY = 0;
	static int a_CacPosX = 0;
	static int a_CacPosY = 0;

	for (int yy = 0; yy < Y_Tile; yy++)
	{
		a_SetPosY = m_TileStPos.y + (m_ImgSize.y * yy);
		for (int xx = 0; xx < X_Tile; xx++)
		{
			a_SetPosX = m_TileStPos.x + (m_ImgSize.x * xx);

			a_CacPosX = a_SetPosX - (int)m_CamPos.x;
			a_CacPosY = a_SetPosY - (int)m_CamPos.y;

			if (xx == 0) 
			{
				a_pd2dRTarget->DrawBitmap(m_pBGBmpForest,
					D2D1::RectF(a_CacPosX, a_CacPosY,
						a_CacPosX + m_ImgSize.x, a_CacPosY + m_ImgSize.y));
			}
			else if (xx == 1)
			{
				a_pd2dRTarget->DrawBitmap(m_pBGBmpDesert,
					D2D1::RectF(a_CacPosX, a_CacPosY,
						a_CacPosX + m_ImgSize.x, a_CacPosY + m_ImgSize.y));
			}
			else 
			{
				a_pd2dRTarget->DrawBitmap(m_pBGBmpCity,
					D2D1::RectF(a_CacPosX, a_CacPosY,
						a_CacPosX + m_ImgSize.x, a_CacPosY + m_ImgSize.y));
			}			
		}
	}
}

void CBackGround::BGMgrDestroy()
{
	if (m_pBGBmpDesert != NULL)
	{
		m_pBGBmpDesert->Release();
		m_pBGBmpDesert = NULL;
	}

	if (m_pBGBmpForest != NULL)
	{
		m_pBGBmpForest->Release();
		m_pBGBmpForest = NULL;
	}

	if (m_pBGBmpCity != NULL)
	{
		m_pBGBmpCity->Release();
		m_pBGBmpCity = NULL;
	}
}

CBackGround g_BackGround;