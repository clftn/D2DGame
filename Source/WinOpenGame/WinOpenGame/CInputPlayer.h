#pragma once

#include "GlobalValue.h"
#include <DirectXMath.h>
using namespace DirectX;

class CInputPlayer
{
public:
	void Update_Input(XMFLOAT2& a_KDirVec);
};

extern CInputPlayer g_InputPlayer;