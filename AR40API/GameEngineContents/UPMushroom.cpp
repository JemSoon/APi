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
	{	//ī�޶� �ۿ� ������ ���δ�
	/*	if (false == UPMushroomCollision->CollisionCheck("PlayerCamera"))
		{
			this->Death();
		}*/
	}

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
		ColBotCheck2();

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
		SetMove(MoveDir_);

	}
}

void UPMushroom::FootCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(0.0f, 32.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void UPMushroom::LeftCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void UPMushroom::RightCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void UPMushroom::ColBotCheck()
{
	NextPos_ = (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);//�̷� ��ġ

	if (true == UPMushroomCollision->NextPosCollisionCheck("Box", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * Speed_;
		//�ڽ� �ȿ��� �� �ö�ö����� ���� ������
		return;//�� �ö�ö����� �� �Լ��� ���� �� ��
	}
}

void UPMushroom::ColBotCheck2()
{
	NextPos_ = (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);//�̷� ��ġ
	if (true == UPMushroomBotCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		//�ڽ����� �����Ʒ� �浹�ϸ�(������ ���� ������ �ö����) ���������� ��
		MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;
		MoveDir_.y = 0.0f;
	}
}