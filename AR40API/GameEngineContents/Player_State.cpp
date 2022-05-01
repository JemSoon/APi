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
		
	// 중력
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

		//===============충돌체용 중력 설정=================//
		NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos_ = NextPos_;
		//다음 미래 위치에 플레이어 발바닥 충돌이 박스탑 충돌에 닿으면 중력은 0이 된다.
		if (true == PlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
		{
			MoveDir.y = 0.0f;
			//MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

			if (true == GameEngineInput::GetInst()->IsDown("Jump"))
			{
				ChangeState(PlayerState::Jump);
			}

			if (false == IsMoveKey())
			{	//키에 손 떼놓고 있으면 감속(브레키)
				MoveDir.x *= -MoveDir.x * GameEngineTime::GetDeltaTime();
			}

			return;
		}

		//================컬러충돌용 중력 설정===================//
		else
		{
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
		}
	
	CameraOutCheck();
}

	void Player::MoveUpdate()
	{
		BreakAnimation();
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
			RGB(0, 255, 0) == Color_) && true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			MoveDir.x = 0.0f;
		}

		LeftCheck();
		//뒤가 충돌색이고 뒤키를 누르고있으면 x가 0이된다.
		if ((RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_) && true == GameEngineInput::GetInst()->IsPress("Move Left"))
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


		{
			//===============충돌체용 중력 설정=================//
			NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			CheckPos_ = NextPos_;
			//다음 미래 위치에 플레이어 발바닥 충돌이 박스탑 충돌에 닿으면 중력은 0이 된다.
			if (true == PlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
			{
				MoveDir.y = 0.0f;
				MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());//감속
				SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
				return;
			}

			else
			{	//==============컬러용 중력 설정==================//
				FootCheck();
				if (RGB(255, 0, 0) != Color_ &&
					RGB(55, 55, 55) != Color_ &&
					RGB(0, 255, 255) != Color_ &&
					RGB(0, 255, 0) != Color_)
				{	//허공에 떠있을때(땅에 안닿았을땐) 내려가는 힘이 가해진다
					SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
					ChangeState(PlayerState::Fall);
					return;
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
		}
	
	//감속
	MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());
	//근데 idle상태로 넘어가면 x가 0되서 걍 섬

	CameraOutCheck();
}

void Player::JumpUpdate()
{
	//HeadHitCheck();
	//FootHitCheck();

	
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;


	//if (true == GameEngineInput::GetInst()->IsUp("Jump"))
	//{	//점프 누른 시간에 따른 점프 길이 변화용
	//	MoveDir.y = 0.0f;
	//	ChangeState(PlayerState::Fall);
	//	return;
	//}

	// 아이들로 바꾸는게 아니에영
	
	
	//===============충돌체용 중력 설정=================//
	NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos_ = NextPos_;
	//다음 미래 위치에 플레이어 발바닥 충돌이 박스탑 충돌에 닿으면 중력은 0이 된다.
	if (true == PlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.y = 0.0f;
		MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());//감속
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);

		if (true == IsMoveKey())
		{	
			ChangeState(PlayerState::Move);
		}
		else
		{
			ChangeState(PlayerState::Idle);
		}
		return;
	}
	
	else if (true == PlayerHeadCollision->NextPosCollisionCheck("BoxBot", NextPos_, CollisionType::Rect, CollisionType::Rect)||
			 true == PlayerHeadCollision->NextPosCollisionCheck("BlockBot", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{	//박스랑 머리랑 충돌하면
		MoveDir.y = 0.0f;
		ChangeState(PlayerState::Fall);
		return;
	}

	else if (true == PlayerLeftCollision->NextPosCollisionCheck("BoxRight", NextPos_, CollisionType::Rect, CollisionType::Rect) ||
		true == PlayerRightCollision->NextPosCollisionCheck("BoxLeft", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.x = 0.0f;
	}

	//===============컬러용 중력 설정=================//
	else
	{	
		//컬러 충돌용 체크
		//머리 체크
		HeadCheck();

		if (RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_)
		{	//장애물과 부딪혔다면 바로 낙하 상태로 변경
			MoveDir.y = 0.0f;
			ChangeState(PlayerState::Fall);
			return;
		}

	}

	{	//앞 체크
		RightCheck();

		if ((RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_) && true == GameEngineInput::GetInst()->IsPress("Move Right"))
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

	}

	{	//뒤 체크
		LeftCheck();

		if ((RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_) && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{	//점프중 앞에 장애물이 있다면 x방향은 0
			MoveDir.x = 0.0f;
		}

		else if ((RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_) && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{	//앞에 장애물이 없다면
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
		}

	}

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
		{	//낙하시작할때 Fall로 되야하지않나..?
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

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos_ = NextPos_;
	//다음 미래 위치에 플레이어 발바닥 충돌이 박스탑 충돌에 닿으면 중력은 0이 된다.
	if (true == PlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.y = 0.0f;
		MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());//감속
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		
		if (true == IsMoveKey())
		{
			ChangeState(PlayerState::Move);
		}
		else
		{
			ChangeState(PlayerState::Idle);
		}
	}

	else
	{	
		//컬러용 설정
		if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			// 가속력
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::RIGHT;//총알 발사 방향 설정용
		}
		else if (true == GameEngineInput::GetInst()->IsPress("Move LEft"))
		{
			// 가속력
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::LEFT;//총알 발사 방향 설정용
		}

		RightCheck();
		//앞이 바닥or장애물이면 x가 0이된다.
		if (RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_)
		{
			MoveDir.x = 0.0f;
		}

		LeftCheck();
		//앞이 바닥or장애물이면 x가 0이된다.
		if (RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_)
		{
			MoveDir.x = 0.0f;
		}

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
			true == GameEngineInput::GetInst()->IsPress("Move Left")) && MoveDir.y == 0.0f)
		{
			//MoveDir.y += 1.0f * GameEngineTime::GetDeltaTime()*AccSpeed_;//땅에 닿아서 y가 아래로 떨어질 필요가 없으니 y=0
			ChangeState(PlayerState::Move);
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
	MoveDir += float4::UP * 35.0f;
}

void Player::FallStart()
{
	PlayerAnimationRender->ChangeAnimation("Jump-" + DirString);
}