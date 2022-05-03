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


	{	//�ʰ� ĳ������ �浹������
		//(����)���� BG�� ��ǥ�� �ȸ��� ����
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}


	{
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		//�� �̷���ġ
		FootCheck();//�߹ٴ� �� ���� �� üũ
		Color_ = MapColImage_->GetImagePixel(CheckPos_);
		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)//����� �ִ�
		{	//�������� �ƴ϶�� ���� �̽�
			SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * AccSpeed_);
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

void TurtleBack::FootCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(0.0f, 48.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::LeftCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::RightCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
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