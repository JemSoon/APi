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
	//Player��ġ�� �߾����� ����
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 64,64 });
}

void Player::Render()
{
	DebugRectRender();
}