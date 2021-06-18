#include "GlobalValue.h"

GameState g_GameState = GameState::GameStart;
HeroStateStd g_HeroStateStd = IdleLeft;
HeroStateMove g_HeroStateMove = State1;
KindOfMonster g_MonKind = Mon1;

bool isKeyDown = false;
bool isShotting = false;