#include "Turtle.h"
#include "TurtleBack.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>


Turtle::Turtle()
	: Speed_(50.0f)
	, AccSpeed_(50.0f)
	, MoveDir_(float4::ZERO)
	, DirString_("L")
{

}

Turtle::~Turtle()
{

}

void Turtle::Start()
{
	SetScale({ 64,64 });

	TurtleCollision = CreateCollision("MonsterHitBox", { 64, 64 },{0,20});
	TurtleTopCollision = CreateCollision("TurtleHead", { 64, 2 }, { 0,-20 });
	TurtleLeftCollision = CreateCollision("MonsterLeft", { 2, 64 }, { -32,20 });
	TurtleRightCollision = CreateCollision("MonsterRight", { 2, 64 }, { 32,20 });

	TurtleAnimationRender = CreateRenderer((int)ORDER::MONSTER);
	TurtleAnimationRender->CreateAnimation("turtle-L.bmp", "turtle-walk-L", 0, 1, 0.3f, true);
	TurtleAnimationRender->CreateAnimation("turtle-R.bmp", "turtle-walk-R", 0, 1, 0.3f, true);

	TurtleAnimationRender->ChangeAnimation("turtle-walk-L");

	MoveDir_ = float4::LEFT;
	Speed_ = 100.0f;
}

void Turtle::Render()
{

}

void Turtle::Update()
{
	DirCheck();
	PlayerAttack();
	{
		if (false == TurtleCollision->CollisionCheck("PlayerCamera"))
		{
			return;
		}
	}


	{	//맵과 캐릭터의 충돌설정용
		//(참고)실제 BG랑 좌표가 안맞음 현재
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}


	{
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		//내 미래위치
		FootCheck();//발바닥 밑 닿은 색 체크
		Color_ = MapColImage_->GetImagePixel(CheckPos_);
		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)//허공에 있다
		{	//빨간색이 아니라면 갈수 이써
			SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * AccSpeed_);
		}
		else//바닥에 닿았다
		{
			MoveDir_.y = 0.0f;
			LeftCheck();//왼쪽 벽체크
			Color_ = MapColImage_->GetImagePixel(CheckPos_);
			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
			{	//빨간색이 아니라면 갈수 이써
				MoveDir_.x = MoveDir_.x;
			}
			else
			{
				MoveDir_.x = MoveDir_.x * -1;
			}

			RightCheck();//오른쪽 벽체크
			Color_ = MapColImage_->GetImagePixel(CheckPos_);
			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
			{	//빨간색이 아니라면 갈수 이써
				MoveDir_.x = MoveDir_.x;
			}
			else
			{
				MoveDir_.x = MoveDir_.x * -1;
			}
		}

		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

		FallDead();
		AnotherTurtleCheck();
	}
}

void Turtle::FootCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 48.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Turtle::LeftCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Turtle::RightCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Turtle::AnotherTurtleCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == TurtleLeftCollision->CollisionResult("MonsterRight", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir_.x = MoveDir_.x * -1;

	}
	else if (true == TurtleRightCollision->CollisionResult("MonsterLeft", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir_.x = MoveDir_.x * -1;
	}
}

void Turtle::DirCheck()
{
	if (MoveDir_.x < 0)
	{
		DirString_ = "L";
		TurtleAnimationRender->ChangeAnimation("turtle-walk-" + DirString_);
	}

	else if (MoveDir_.x > 0)
	{
		DirString_ = "R";
		TurtleAnimationRender->ChangeAnimation("turtle-walk-" + DirString_);
	}
}

void Turtle::PlayerAttack()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == TurtleTopCollision->CollisionResult("PlayerFootHit", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		TurtleBack* TB = GetLevel()->CreateActor<TurtleBack>();
		TB->SetPosition(GetPosition()+float4{0,16});
		TB->SetMove({ float4::ZERO });
		TurtleTopCollision->GetActor()->SetMove({ float4::ZERO });
		TurtleTopCollision->GetActor()->Off();
	}
}

void Turtle::FallDead()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == TurtleCollision->CollisionResult("Die", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		TurtleCollision->GetActor()->Death();
	}
}