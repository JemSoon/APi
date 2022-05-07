#include "UPMushroom.h"
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

UPMushroom::UPMushroom()
	: Speed_(80.0f)
	, AccSpeed_(10.0f)
	, MoveDir_(float4::ZERO)
{

}

UPMushroom::~UPMushroom()
{

}

void UPMushroom::Start()
{
	SetScale({ 64,64 });

	UPMushroomCollision = CreateCollision("UPMushroom", { 64, 64 });
	UPMushroomBotCollision = CreateCollision("UPMushroomBot", { 64,2 }, { 0,33 });
	UPMushroomAnimationRender = CreateRenderer((int)ORDER::ITEM);
	UPMushroomAnimationRender->CreateAnimation("UPMushroom.bmp", "UPMushroom", 0, 0, 1.0f, false);
	UPMushroomAnimationRender->ChangeAnimation("UPMushroom");

}

void UPMushroom::Render()
{

}

void UPMushroom::Update()
{
	{	//카메라 밖에 나가면 죽인다
	/*	if (false == UPMushroomCollision->CollisionCheck("PlayerCamera"))
		{
			this->Death();
		}*/
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

void UPMushroom::FootCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 32.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void UPMushroom::LeftCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void UPMushroom::RightCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void UPMushroom::ColBotCheck()
{
	NextPos_ = (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);//미래 위치

	if (true == UPMushroomCollision->NextPosCollisionCheck("Box", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * Speed_;
		//박스 안에서 다 올라올때까진 위로 움직임
		return;//다 올라올때까진 딴 함수로 진행 못 해
	}
}

void UPMushroom::ColBotCheck2()
{
	NextPos_ = (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);//미래 위치
	if (true == UPMushroomBotCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		//박스위랑 버섯아래 충돌하면(버섯이 위로 끝까지 올라오면) 오른쪽으로 감
		MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;
		MoveDir_.y = 0.0f;
	}
}