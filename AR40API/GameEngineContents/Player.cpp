#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h>//������ ���ؼ�
#include "Bullet.h"//�Ѿ��� ����� �ʹ�

Player::Player()
	:Speed_(150.0f)
	,Gravity_(100.0f)
{

}

Player::~Player()
{

}

void Player::Start()
{
	//Player��ġ�� �߾����� ����
	//SetPosition(GameEngineWindow::GetScale().Half());
	//������ �� ����� �����ϸ� �ȵ�(�������� �����Ҷ����� �ٸ��ϱ�)
	SetScale({ 64,64 });

	//�ִϸ��̼��� �ϳ��� ����� �ִϸ��̼ǵ� ����ȴ�
	GameEngineRenderer* Render = CreateRenderer();
	//0~1�ε��� 0.1�ʸ���(true�� �ݺ�,false�� �ѹ������)
	Render->CreateAnimation("walk-R.bmp", "Walk-R", 0, 2, 0.1f, true);
	Render->ChangeAnimation("Walk-R");


	if (false == GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false�� ������� �� ���� Ű �̴�

		GameEngineInput::GetInst()->CreateKey("Move Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Move Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Move Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Move Up", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Jump", 'X');
		GameEngineInput::GetInst()->CreateKey("Run", 'C');
		GameEngineInput::GetInst()->CreateKey("Fire", 'Z');
	}
}


void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 450.0f;
		}
		else
		{
			Speed_ = 150.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 450.0f;
		}
		else
		{
			Speed_ = 150.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Up"))
	{			//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 450.0f;
		}
		else
		{
			Speed_ = 150.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Down"))
	{			//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 450.0f;
		}
		else
		{
			Speed_ = 150.0f;
		}
	}

	{
		//�߷�
		AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;//���� ���ӵ�
		//if (/*���� ��Ҵٸ�*/)
		//{
		//	AccGravity_ = 0.0f;
		//}
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);
	}

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());

	}

	/*if (2.0f < GameEngineInput::GetInst()->GetTime("Fire")) 2�ʰ� ������� ������
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());

	}*/

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
