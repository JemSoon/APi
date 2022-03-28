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
	//Player��ġ�� �߾����� ����
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 64,64 });
}

void Player::Render()
{
	//DebugRectRender();

	//ã��
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("idle-R.bmp");

	if (nullptr == FindImage)
	{
		MsgBoxAssert("�� ã��..");
	}

	//����:��ܿ� UI��ġ �س��� UI�� �� ���̶� 0,0�ϸ� ����
	GameEngine::BackBufferImage()->BitCopy(FindImage, {200,200});

}