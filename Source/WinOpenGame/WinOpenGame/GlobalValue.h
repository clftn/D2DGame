#pragma once

enum class GameState 
{
	GameStart,
	GameIng,
	GameOver,
	GameClear
};

extern GameState g_GameState;

enum HeroStateStd	// ���¸� �����ϴ� ��
{
	SeeLeft = 0,		// ��������Ʈ ����
	SeeRight,
	WalkLeft,
	WalkRight,
	ShotLeft,
	ShotRight,
	IdleLeft,
	IdleRight
};

extern HeroStateStd g_HeroStateStd;

enum HeroStateMove	// �ִϸ��̼��� �����ϴ� ��
{
	State1 = 0,
	State2,
	State3,
	State4,
	State5,
};

enum KindOfMonster 
{
	Mon1 = 0,
	Mon2,
	Mon3,
	Mon4,
	Mon5,
	Mon6,
	Mon7,
	Mon8,
	Mon9,
	Mon10,
};

extern KindOfMonster g_MonKind;

extern bool isKeyDown;
extern bool isShotting;

extern HeroStateMove g_HeroStateMove;