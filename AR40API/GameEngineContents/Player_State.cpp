#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include "Bullet.h" // 총알을 만들고 싶다.
#include "ContentsEnum.h"



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

	// wndc
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	FootCheck();

	Color_ = MapColImage_->GetImagePixel(CheckPos_);//갈수 있냐 없냐 색 체크
	if (RGB(255, 0, 0) != Color_ &&
		RGB(55, 55, 55) != Color_ &&
		RGB(0, 255, 255) != Color_ &&
		RGB(0, 255, 0) != Color_)
	{	//해당색상의 충돌체가 없으면 계속 아래로
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else {
		MoveDir.y = 0.0f;
	}
	//DirAnimationCheck();
	CameraOutCheck();
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

	{	//오른쪽
		if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			// 가속력
			PlayerAnimationRender->ChangeAnimation("Walk-R");
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::RIGHT;//총알 발사 방향 설정용
		}
		//else if (true == GameEngineInput::GetInst()->IsUp("Move Right"))
		//{	//버튼 떼면 idle애니메이션으로
		//	PlayerAnimationRender->ChangeAnimation("idle-R");
		//	ChangeState(PlayerState::Idle);
		//	return;
		//}
	}

	{	//왼쪽
		if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			PlayerAnimationRender->ChangeAnimation("Walk-L");
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::LEFT;
		}
		//else if (true == GameEngineInput::GetInst()->IsUp("Move Left"))
		//{
		//	PlayerAnimationRender->ChangeAnimation("idle-L");
		//	ChangeState(PlayerState::Idle);
		//	return;
		//}
	}

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	FootCheck();

	{
		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)
		{	//허공에 떠있을때(땅에 안닿았을땐) 내려가는 힘이 가해진다
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
		else
		{
			MoveDir.y = 0.0f;

			NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			//그 때 발바닥 위치
			float4 CheckPos1 = NextPos_ + float4(0.0f, 32.0f);
			int Color1 = MapColImage_->GetImagePixel(CheckPos1);//갈수 있냐 없냐 색 체크

			if (RGB(255, 0, 0) != Color1 &&
				RGB(55, 55, 55) != Color1 &&
				RGB(0, 255, 255) != Color1 &&
				RGB(0, 255, 0) != Color1)
			{
				SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			}
			else 
			{
				MoveDir.x = 0.0f;
			}
		}
	}

	//감속
	//MoveDir.

	CameraOutCheck();
}

void Player::AttackUpdate()
{
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	FootCheck();

	Color_ = MapColImage_->GetImagePixel(CheckPos_);//갈수 있냐 없냐 색 체크
	if (RGB(255, 0, 0) != Color_ &&
		RGB(55, 55, 55) != Color_ &&
		RGB(0, 255, 255) != Color_ &&
		RGB(0, 255, 0) != Color_)
	{	//해당색상의 충돌체가 없으면 계속 아래로
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else 
	{
		MoveDir.y = 0.0f;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetDir(CurDir());
	}

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}


	CameraOutCheck();
}

void Player::DeadUpdate()
{
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
}


//////////////////////////////////////// State

void Player::IdleStart()
{
	// 애니메이션이 바뀐다.

	// AnimationName = "Idle_"
	//내 미래위치 (Speed_는 가속력)

}

void Player::MoveStart()
{

}

void Player::AttackStart()
{

}

void Player::DeadStart()
{
	// GameEngineTime::SetTimeScale(GameMonster::);

	MoveDir = float4::UP * 500.0f;
}
