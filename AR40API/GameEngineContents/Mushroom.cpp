#include "Mushroom.h"
#include "Player.h"
#include "BigPlayer.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

Mushroom::Mushroom()
	: Speed_(80.0f)
	, AccSpeed_(10.0f)
	, MoveDir_(float4::ZERO)
{

}

Mushroom::~Mushroom()
{

}

void Mushroom::Start()
{
	SetScale({ 64,64 });

	MushroomCollision = CreateCollision("Mushroom", { 64, 64 });
	MushroomBotCollision = CreateCollision("MushroomBot", { 64,3 }, {0,32});
	MushroomAnimationRender = CreateRenderer((int)ORDER::ITEM);
	MushroomAnimationRender->CreateAnimation("Mushroom.bmp", "Mushroom", 0, 0, 1.0f, false);
	MushroomAnimationRender->ChangeAnimation("Mushroom");

}

void Mushroom::Render()
{

}

void Mushroom::Update()
{
	{	//카메라 밖에 나가면 죽인다
		//if (false == MushroomCollision->CollisionCheck("PlayerCamera"))
		//{
		//	this->Death();
		//}
	}

	{	//맵과 캐릭터의 충돌설정용

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}

	{
		
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_; 
		
		ColBotCheck();
		ColBotCheck2();

		//내 미래위치
		FootCheck();//발바닥 밑 닿은 색 체크
		Color_ = MapColImage_->GetImagePixel(CheckPos_);
		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)//허공에 있다
		{	//빨간색이 아니라면 갈수 이써
			SetMove(MoveDir_);
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
		SetMove(MoveDir_);

	}
}

void Mushroom::FootCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 32.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Mushroom::LeftCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Mushroom::RightCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Mushroom::ColBotCheck()
{
	NextPos_ = (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);//미래 위치

	if (true == MushroomCollision->NextPosCollisionCheck("Box", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{	
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * Speed_;
		//박스 안에서 다 올라올때까진 위로 움직임
		return;//다 올라올때까진 딴 함수로 진행 못 해
	}
}

void Mushroom::ColBotCheck2()
{
	NextPos_ = (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);//미래 위치
	if (true == MushroomBotCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		//박스위랑 버섯아래 충돌하면(버섯이 위로 끝까지 올라오면) 오른쪽으로 감
		MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;
		MoveDir_.y = 0.0f;
	}
}