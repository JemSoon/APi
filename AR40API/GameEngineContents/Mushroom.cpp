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
	: Speed_(120.0f)
	, AccSpeed_(20.0f)
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
	MushroomBotCollision = CreateCollision("MushroomBot", { 64,1 }, {0,32});
	MushroomAnimationRender = CreateRenderer((int)ORDER::ITEM);
	MushroomAnimationRender->CreateAnimation("Mushroom.bmp", "Mushroom", 0, 0, 1.0f, false);
	MushroomAnimationRender->ChangeAnimation("Mushroom");

}

void Mushroom::Render()
{

}

void Mushroom::Update()
{
	{	//�ʰ� ĳ������ �浹������

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}

	{
		
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_; 
		
		ColBotCheck();

		//�� �̷���ġ
		FootCheck();//�߹ٴ� �� ���� �� üũ
		Color_ = MapColImage_->GetImagePixel(CheckPos_);
		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)//����� �ִ�
		{	//�������� �ƴ϶�� ���� �̽�
			SetMove(MoveDir_);
		}
		else//�ٴڿ� ��Ҵ�
		{
			MoveDir_.y = 0.0f;
			LeftCheck();//���� ��üũ
			Color_ = MapColImage_->GetImagePixel(CheckPos_);
			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
			{	//�������� �ƴ϶�� ���� �̽�
				MoveDir_.x = MoveDir_.x;
			}
			else
			{
				MoveDir_.x = MoveDir_.x * -1;
			}

			RightCheck();//������ ��üũ
			Color_ = MapColImage_->GetImagePixel(CheckPos_);
			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
			{	//�������� �ƴ϶�� ���� �̽�
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

void Mushroom::FootCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(0.0f, 32.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Mushroom::LeftCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Mushroom::RightCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Mushroom::ColBotCheck()
{
	NextPos_ = (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

	if (true == MushroomCollision->NextPosCollisionCheck("Box", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * Speed_;

		if (true == MushroomBotCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
		{
			//�ڽ����� �����Ʒ� �浹�ϸ�(������ ���� ������ �ö����)
			MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;
			MoveDir_.y = 0.0f;
		}
	}
}