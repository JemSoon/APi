#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include "Bullet.h" // 총알을 만들고 싶다.



void Player::IdleUpdate()
{
	{	//맵과 캐릭터의 충돌설정용

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}


	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		ChangeState(PlayerState::Attck);
		return;
	}

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

	//내 미래위치 (Speed_는 가속력)
	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	//그 때 발바닥 위치
	float4 CheckPos1 = NextPos + float4(0.0f, 32.0f);

	int Color1 = MapColImage_->GetImagePixel(CheckPos1);//갈수 있냐 없냐 색 체크
	if (RGB(255, 0, 0) != Color1 &&
		RGB(55, 55, 55) != Color1 &&
		RGB(0, 255, 255) != Color1 &&
		RGB(0, 255, 0) != Color1)
	{	//해당색상의 충돌체가 없으면 계속 아래로
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	}

	CameraOutCheck();
}

void Player::AttackUpdate()
{
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	//if (MoveDir.y)
	//{

	//}



}

void Player::MoveUpdate()
{
	{	//맵과 캐릭터의 충돌설정용

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		ChangeState(PlayerState::Attck);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		// 가속력
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_;
	}

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

	//내 미래위치 (Speed_는 가속력)
	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	//그 때 발바닥 위치
	float4 CheckPos1 = NextPos + float4(0.0f, 32.0f);
	int Color1 = MapColImage_->GetImagePixel(CheckPos1);//갈수 있냐 없냐 색 체크
	{
		if (RGB(255, 0, 0) != Color1 &&
		RGB(55, 55, 55) != Color1 &&
		RGB(0, 255, 255) != Color1 &&
		RGB(0, 255, 0) != Color1)
		{	//허공에 떠있을때(땅에 안닿았을땐) 내려가는 힘이 가해진다
			SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		}
		else
		{	//땅에 있을땐 위로 띄워주는 힘이 가해진다(안떨어지게) 문제-플레이어가 지진난것처럼 덜덜떨림
			SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	if (0.3f <= MoveDir.Len2D())
	{
		MoveDir.Range2D(0.3f);
	}

	if (false == IsMoveKey())
	{
		MoveDir += -MoveDir * GameEngineTime::GetDeltaTime();

		if (0.005f >= MoveDir.Len2D())
		{
			MoveDir = float4::ZERO;
			return;
		}

	
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		return;
	}

	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);

	CameraOutCheck();
}


//////////////////////////////////////// State

void Player::IdleStart()
{
	// 애니메이션이 바뀐다.

	// AnimationName = "Idle_"
	//내 미래위치 (Speed_는 가속력)

}

void Player::AttackStart()
{
	// GameEngineTime::SetTimeScale(GameMonster::);

	MoveDir = float4::UP * 500.0f;
}

void Player::MoveStart()
{

}

