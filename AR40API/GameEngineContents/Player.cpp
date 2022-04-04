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
	:Speed_(100.0f)
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

	////CreateRenderer("idle-R.bmp", RenderPivot::CENTER,{0, 0});
	//CreateRenderer("idle-R.bmp", RenderPivot::BOT, {-100,0});//�ణ �ڷ� ��, �߽��� �߰� �Ʒ�
	//CreateRenderer("turtle-back.bmp", RenderPivot::CENTER, { -100,-100 });
	////CreateRendererToScale("turtle-back.bmp",float4(300.0f, 20.0f), RenderPivot::CENTER, { -100,-100 });//HPBAR��� �׽�Ʈ
	
	GameEngineRenderer* Render = CreateRenderer("walk-L.bmp");
	
	Render->SetIndex(0);

	if (false== GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false�� ������� �� ���� Ű �̴�
		
		//�Է�Ű�� �빮�ڷ� ���������
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
		if(true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_=300.0f;
		}
		else
		{
			Speed_ = 100.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{	
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 300.0f;
		}
		else
		{
			Speed_ = 100.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Up"))
	{			//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 300.0f;
		}
		else
		{
			Speed_ = 100.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Down"))
	{			//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 300.0f;
		}
		else
		{
			Speed_ = 100.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());

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
