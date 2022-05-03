#include "TurtleBack.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

TurtleBack::TurtleBack():
	MoveDir_(float4::ZERO)
{

}

TurtleBack::~TurtleBack()
{

}

void TurtleBack::Start()
{
	TBCollision = CreateCollision("TBHitBox", { 64, 62 });
	TBTopLeftCollision = CreateCollision("TBHead-L", { 32, 2 }, { -16,-32 });
	TBTopRightCollision = CreateCollision("TBHead-R", { 32, 2 }, { 16,-32 });
	TBLeftCollision = CreateCollision("TBLeft", { 2, 64 }, { -32,0 });
	TBRightCollision = CreateCollision("TBRight", { 2, 64 }, { 32,0 });
	
	TBAnimationRender = CreateRenderer((int)ORDER::MONSTER);
	TBAnimationRender->CreateAnimation("turtle-back.bmp", "turtle-back", 0, 0, 0.0f, false);
	TBAnimationRender->ChangeAnimation("turtle-back");
}

void TurtleBack::Render()
{
}

void TurtleBack::Update()
{
	PlayerAttack();
	{
		//if (false == TurtleCollision->CollisionCheck("PlayerCamera"))
		//{
		//	return;
		//}
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
	}
}

void TurtleBack::FootCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 48.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::LeftCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::RightCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::PlayerAttack()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == TBTopLeftCollision->CollisionResult("PlayerFootHit", ColList, CollisionType::Rect, CollisionType::Rect)&&
		false == TBTopRightCollision->CollisionResult("PlayerFootHit", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime();
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	
	}

	//else if (false == TBTopLeftCollision->CollisionResult("PlayerFootHit", ColList, CollisionType::Rect, CollisionType::Rect) &&
	//	true == TBTopRightCollision->CollisionResult("PlayerFootHit", ColList, CollisionType::Rect, CollisionType::Rect))
	//{
	//	MoveDir_ = float4::RIGHT;
	//	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	//}
	//
	//else if (true == TBLeftCollision->CollisionResult("PlayerRight", ColList, CollisionType::Rect, CollisionType::Rect))
	//{
	//	MoveDir_ = float4::RIGHT;
	//	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	//}
	//
	//else if (true == TBRightCollision->CollisionResult("PlayerLeft", ColList, CollisionType::Rect, CollisionType::Rect))
	//{
	//	MoveDir_ = float4::LEFT;
	//	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	//}
}