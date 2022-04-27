#include "BigPlayer.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include "Bullet.h" // 총알을 만들고 싶다.
#include "ContentsEnum.h"

void BigPlayer::IdleUpdate()
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
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	if (true == IsMoveKey())
	{
		ChangeState(BigPlayerState::Move);
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
		ChangeState(BigPlayerState::Jump);
	}

	if (false == IsMoveKey())
	{	//키에 손 떼놓고 있으면 감속(브레키)
		MoveDir.x *= -MoveDir.x * GameEngineTime::GetDeltaTime();
	}

	CameraOutCheck();
}

void BigPlayer::MoveUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	{	//맵과 캐릭터의 충돌설정용

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}

	// 점프
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(BigPlayerState::Jump);
		return;
	}


	{	//오른쪽
		if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			// 가속력
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			BigPlayerDir_ = float4::RIGHT;//총알 발사 방향 설정용
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Right"))
		{
			ChangeState(BigPlayerState::Idle);//이거넣으면 바로 멈춰버림+멈춰있는데 가속도는 유지되어있음
			return;
		}
	}

	{	//왼쪽
		if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			BigPlayerDir_ = float4::LEFT;
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Left"))
		{
			ChangeState(BigPlayerState::Idle);
			return;
		}
	}

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
	
	{	//앞 체크
		RightCheck();

		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)
		{
		}

		else if (true == GameEngineInput::GetInst()->IsPress("Move Right") ||
			true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir.x = 0.0f;//땅에 닿아서 y가 아래로 떨어질 필요가 없으니 y=0
			ChangeState(BigPlayerState::Move);
		}
		else
		{
			MoveDir.y = 0.0f;
			ChangeState(BigPlayerState::Idle);
		}
	}


	{	//앞아래 꼭지점 체크
		RightBotCheck();

		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)
		{
		}

		else if (true == GameEngineInput::GetInst()->IsPress("Move Right") ||
			true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir.x = 0.0f;//땅에 닿아서 y가 아래로 떨어질 필요가 없으니 y=0
			ChangeState(BigPlayerState::Move);
		}
		else
		{
			MoveDir.y = 0.0f;
			ChangeState(BigPlayerState::Idle);
		}
	}

	

	{
		FootCheck();

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

void BigPlayer::JumpUpdate()
{
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}
	// 아이들로 바꾸는게 아니에영


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
		MoveDir.y = 0.0f;//땅에 닿아서 y가 아래로 떨어질 필요가 없으니 y=0
		ChangeState(BigPlayerState::Move);
	}
	else
	{
		MoveDir.y = 0.0f;
		ChangeState(BigPlayerState::Idle);
	}

	CameraOutCheck();

}




//////////////////////////////////////// State

void BigPlayer::IdleStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	// 내방향이 왼쪽이며

	BigPlayerAnimationRender->ChangeAnimation("Bidle-" + BigDirString);

	// 애니메이션이 바뀐다.

	// AnimationName = "Idle_"
	//내 미래위치 (Speed_는 가속력)

	// PlayerAnimationRender->ChangeAnimation("idle-L");

}

void BigPlayer::MoveStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	BigPlayerAnimationRender->ChangeAnimation("BWalk-" + BigDirString);
}

void BigPlayer::JumpStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	BigPlayerAnimationRender->ChangeAnimation("BJump-" + BigDirString);
	MoveDir += float4::UP * 40.0f;
}
