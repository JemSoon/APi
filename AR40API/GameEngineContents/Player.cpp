#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

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
	CreateRenderer("turtle-back.bmp", RenderPivot::CENTER, { -100,-100 });
	//CreateRendererToScale("turtle-back.bmp",float4(300.0f, 20.0f), RenderPivot::CENTER, { -100,-100 });//HPBAR��� �׽�Ʈ

	if (false== GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false�� ������� �� ���� Ű �̴�
		
		//�Է�Ű�� �빮�ڷ� ���������
		GameEngineInput::GetInst()->CreateKey("Move Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Move Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Move Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Move Up", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Jump", 'C');
		GameEngineInput::GetInst()->CreateKey("Fire", 'X');
	}
}


void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{			//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{			//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::RIGHT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Up"))
	{			//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::UP);
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Down"))
	{			//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::DOWN);
	}

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
