#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	//Player위치는 중앙으로 고정
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 64,64 });
}

void Player::Render()
{
	DebugRectRender();
}