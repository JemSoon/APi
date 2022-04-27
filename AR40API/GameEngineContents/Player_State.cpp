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

//std::string DirString;//지금 방향
//std::string PrevDirString;//방향이 바뀌었을때

void Player::IdleUpdate()
{
	{	//맵과 캐릭터의 충돌설정용

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
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
	else
	{
		MoveDir.y = 0.0f;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
	}

	if (false == IsMoveKey())
	{	//키에 손 떼놓고 있으면 감속(브레키)
		MoveDir.x *= -MoveDir.x * GameEngineTime::GetDeltaTime();
	}

	CameraOutCheck();
}

void Player::MoveUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	{	//맵과 캐릭터의 충돌설정용

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}

	RightCheck();
	//앞이 충돌색이고 앞키를 누르고있으면 x가 0이된다.
	if ((RGB(255, 0, 0) == Color_ ||
		RGB(55, 55, 55) == Color_ ||
		RGB(0, 255, 255) == Color_ ||
		RGB(0, 255, 0) == Color_)&& true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		MoveDir.x = 0.0f;
	}

	// 점프
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}


	{	//오른쪽
		if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			// 가속력
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::RIGHT;//총알 발사 방향 설정용
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Right"))
		{
			ChangeState(PlayerState::Idle);//이거넣으면 바로 멈춰버림+멈춰있는데 가속도는 유지되어있음
			return;
		}
	}

	{	//왼쪽
		if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::LEFT;
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Left"))
		{
			ChangeState(PlayerState::Idle);
			return;
		}
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

			FootCheck();

			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
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
	MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());
	//근데 idle상태로 넘어가면 x가 0되서 걍 섬

	CameraOutCheck();
}

void Player::JumpUpdate()
{
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	//if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	//{
	//	MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	//}

	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}
	// 아이들로 바꾸는게 아니에영
	
	{	//앞 체크
		RightCheck();

		if ((RGB(255,0,0) ==Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_)&& true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{	//점프중 앞에 장애물이 있다면 x방향은 0
			MoveDir.x = 0.0f;
		}

		else if ((RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_) && true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{	//앞에 장애물이 없다면
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
		}

		//else
		//{
		//	MoveDir.y = 0.0f;
		//	ChangeState(PlayerState::Idle);
		//	return;
		//}
	}


	//{	//앞아래 꼭지점 체크
	//	RightBotCheck();
	//	//바닥은 빼야함(255,0,0)
	//	if (RGB(55, 55, 55) != Color_ &&
	//		RGB(0, 255, 255) != Color_ &&
	//		RGB(0, 255, 0) != Color_)
	//	{
	//	}

	//	else if (true == GameEngineInput::GetInst()->IsPress("Move Right") ||
	//		true == GameEngineInput::GetInst()->IsPress("Move Left"))
	//	{
	//		//MoveDir.x = 0.0f;//땅에 닿아서 y가 아래로 떨어질 필요가 없으니 y=0
	//		ChangeState(PlayerState::Fall);
	//		return;
	//	}
	//	else
	//	{
	//		MoveDir.y = 0.0f;
	//		ChangeState(PlayerState::Idle);
	//		return;
	//	}
	//}

	{	//발바닥 체크
		FootCheck();

		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)
		{	//허공에 떠있다
			//허공에서 움직일때도 계속 가속되기에 그러지 못하도록 감속을 넣어준다
			MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}

		else if (true == GameEngineInput::GetInst()->IsPress("Move Right") ||
			true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			//MoveDir.y = 0.0f;//땅에 닿아서 y가 아래로 떨어질 필요가 없으니 y=0
			ChangeState(PlayerState::Fall);
			return;
		}
		else
		{
			MoveDir.y = 0.0f;
			ChangeState(PlayerState::Idle);
			return;
		}
	}

	CameraOutCheck();

}

void Player::FallUpdate()
{
	RightCheck();
	//앞이 바닥or장애물이면 x가 0이된다.
	if (RGB(255, 0, 0) == Color_ ||
		RGB(55, 55, 55) == Color_ ||
		RGB(0, 255, 255) == Color_ ||
		RGB(0, 255, 0) == Color_)
	{
		MoveDir.x = 0.0f;
	}

	//MoveDir.x = 0.0f;
	MoveDir.y += 1.0f * GameEngineTime::GetDeltaTime() * AccSpeed_;

	FootCheck();

	if (RGB(255, 0, 0) != Color_ &&
		RGB(55, 55, 55) != Color_ &&
		RGB(0, 255, 255) != Color_ &&
		RGB(0, 255, 0) != Color_)
	{	//허공에 떠있다
		//허공에서 움직일때도 계속 가속되기에 그러지 못하도록 감속을 넣어준다
		MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}

	//else if (MoveDir.y == 0.0f)
	//{
	//	ChangeState(PlayerState::Move);
	//}
	
	else if ((true == GameEngineInput::GetInst()->IsPress("Move Right") ||
		true == GameEngineInput::GetInst()->IsPress("Move Left")) && MoveDir.y==0.0f)
	{
		//MoveDir.y += 1.0f * GameEngineTime::GetDeltaTime()*AccSpeed_;//땅에 닿아서 y가 아래로 떨어질 필요가 없으니 y=0
		ChangeState(PlayerState::Move);
	}

	else
	{
		MoveDir.y = 0.0f;
		ChangeState(PlayerState::Idle);
	}

	CameraOutCheck();
}


//////////////////////////////////////// State

void Player::IdleStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	// 내방향이 왼쪽이며

	PlayerAnimationRender->ChangeAnimation("idle-" + DirString);

	// 애니메이션이 바뀐다.

	// AnimationName = "Idle_"
	//내 미래위치 (Speed_는 가속력)

	// PlayerAnimationRender->ChangeAnimation("idle-L");

}

void Player::MoveStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	PlayerAnimationRender->ChangeAnimation("Walk-" + DirString);
}

void Player::JumpStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	PlayerAnimationRender->ChangeAnimation("Jump-" + DirString);
	MoveDir += float4::UP * 40.0f;
}

void Player::FallStart()
{
	PlayerAnimationRender->ChangeAnimation("Jump-" + DirString);
}