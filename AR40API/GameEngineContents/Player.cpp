#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h>//레벨을 통해서
#include "Bullet.h"//총알을 만들고 싶다

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
	//Player위치는 중앙으로 고정
	//SetPosition(GameEngineWindow::GetScale().Half());
	//선생님 왈 여기다 지정하면 안됨(스테이지 진입할때마다 다르니까)
	SetScale({ 64,64 });

	//애니메이션을 하나라도 만들면 애니메이션도 재생된다
	GameEngineRenderer* Render = CreateRenderer();
	//0~1인덱스 0.1초마다(true면 반복,false면 한번만재생)
	Render->CreateAnimation("walk-R.bmp", "Walk-R", 0, 2, 0.1f, true);
	Render->ChangeAnimation("Walk-R");


	if (false == GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false면 만들어진 적 없는 키 이다

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
		//현재 위치 + 이동하는 방향
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
	{			//현재 위치 + 이동하는 방향
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
	{			//현재 위치 + 이동하는 방향
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
		//중력
		AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;//점점 가속됨
		//if (/*땅에 닿았다면*/)
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

	/*if (2.0f < GameEngineInput::GetInst()->GetTime("Fire")) 2초간 기모으고 연사쏘기
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());

	}*/

}


//랜더러가 다 돌아가고 랜더링 된다
void Player::Render()
{
	//DebugRectRender();

	//찾기
	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("idle-R.bmp");

	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("못 찾아..");
	//}

	////주의:상단에 UI배치 해놨고 UI가 맨 앞이라 0,0하면 가림
	//GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());

}
