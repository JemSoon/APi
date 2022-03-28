#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

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
	//DebugRectRender();

	//찾기
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("idle-R.bmp");

	if (nullptr == FindImage)
	{
		MsgBoxAssert("못 찾아..");
	}

	//주의:상단에 UI배치 해놨고 UI가 맨 앞이라 0,0하면 가림
	GameEngine::BackBufferImage()->BitCopy(FindImage, {200,200});

}