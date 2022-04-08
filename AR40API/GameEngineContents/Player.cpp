#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

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
	{	//맵과 캐릭터의 충돌설정용
		//(참고)실제 BG랑 좌표가 안맞음 현재
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}

	float4 CheckPos;
	float4 MoveDir = float4::ZERO;

	{	//움직임 조작
		if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir = float4::LEFT;

			//현재 위치 + 이동하는 방향
			//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
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
			MoveDir = float4::RIGHT;

			//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
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
		{	
			MoveDir = float4::UP;

			//SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
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
		{	
			MoveDir = float4::DOWN;

			//SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
			if (true == GameEngineInput::GetInst()->IsPress("Run"))
			{
				Speed_ = 450.0f;
			}
			else
			{
				Speed_ = 150.0f;
			}
		}
	}

	{	//내 미래위치
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		//그 때 발바닥 위치
		float4 CheckPos = NextPos + float4(0.0f, 32.0f);

		int Color = MapColImage_->GetImagePixel(CheckPos);//갈수 있냐 없냐 색 체크

		if (RGB(255,0,0) != Color)
		{	//빨간색이 아니라면 갈수 이써
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}	
	}
	//플레이어가 카메라 중심에 있길 원하면 그만큼 위치를 더하거나 뺀다
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	//{	//중력 관련
	//	//내 포지션에서 (CENTER중심이라 바닥 기준이니 32아래로)
	//	int Color = MapColImage_->GetImagePixel(GetPosition() + float4(0.0f, 32.0f));


	//	//중력
	//	AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;//점점 가속됨
	//	
	//	if (RGB(255, 0, 0)==Color/*땅에 닿았다면(빨간색)*/)
	//	{
	//		AccGravity_ = 0.0f;
	//	}
	//	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);
	//}

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
	

}
