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

	//CreateRenderer("idle-R.bmp", RenderPivot::CENTER,{0, 0});
	CreateRenderer("idle-R.bmp", RenderPivot::BOT, {-100,0});//�ణ �ڷ� ��, �߽��� �߰� �Ʒ�
	//CreateRenderer("turtle-back.bmp", RenderPivot::CENTER, { -100,-100 });//HPBAR��� �׽�Ʈ
}

//�������� �� ���ư��� ������ �ȴ�
void Player::Render()
{
	//DebugRectRender();

	//ã��
	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("idle-R.bmp");

	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("�� ã��..");
	//}

	////����:��ܿ� UI��ġ �س��� UI�� �� ���̶� 0,0�ϸ� ����
	//GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());
	
}