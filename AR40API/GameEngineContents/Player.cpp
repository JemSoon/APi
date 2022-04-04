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
	:Speed_(100.0f)
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

	////CreateRenderer("idle-R.bmp", RenderPivot::CENTER,{0, 0});
	//CreateRenderer("idle-R.bmp", RenderPivot::BOT, {-100,0});//약간 뒤로 뺌, 중심점 중간 아래
	//CreateRenderer("turtle-back.bmp", RenderPivot::CENTER, { -100,-100 });
	////CreateRendererToScale("turtle-back.bmp",float4(300.0f, 20.0f), RenderPivot::CENTER, { -100,-100 });//HPBAR대용 테스트
	
	GameEngineRenderer* Render = CreateRenderer("walk-L.bmp");
	
	Render->SetIndex(0);

	if (false== GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false면 만들어진 적 없는 키 이다
		
		//입력키는 대문자로 적어줘야함
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
	{			//현재 위치 + 이동하는 방향
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
	{			//현재 위치 + 이동하는 방향
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
