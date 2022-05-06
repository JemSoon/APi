#include "Monster.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>


Monster::Monster()
	: Speed_(50.0f)
	, AccSpeed_(50.0f)
	, MoveDir_(float4::ZERO)
{

}

Monster::~Monster()
{

}

void Monster::Start()
{
	SetScale({ 64,64 });

	MonsterCollision = CreateCollision("MonsterHitBox", { 64, 54 });
	MonsterTopCollision = CreateCollision("MonsterHead", { 64, 1 }, {0,-32});
	MonsterLeftCollision = CreateCollision("MonsterLeft", { 1, 64 }, { -32,0 });
	MonsterRightCollision = CreateCollision("MonsterRight", { 1, 64 }, { 32,0 });
	MonsterBotCollision = CreateCollision("MonsterBot", { 64, 1 }, { 0,-32 });

	MonsterAnimationRender = CreateRenderer((int)ORDER::MONSTER);
	MonsterAnimationRender->CreateAnimation("gumba-walk.bmp", "gumba-walk", 0, 1, 0.3f, true);
	MonsterAnimationRender->CreateAnimation("gumba-Bdead.bmp", "gumba-Bdead", 0, 0, 0.3f, false);
	MonsterAnimationRender->ChangeAnimation("gumba-walk");
	
	MoveDir_ = float4::LEFT;
	Speed_ = 100.0f;
}

void Monster::Render()
{

}

void Monster::Update()
{
	{
		if (false == MonsterCollision->CollisionCheck("PlayerCamera"))
		{
			return;
		}
	}


	{	//�ʰ� ĳ������ �浹������
		//(����)���� BG�� ��ǥ�� �ȸ��� ����
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}

	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	{	
		NextPos_ = (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == MonsterCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
		{
			MoveDir_.y = 0.0f;
		}

		else
		{
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
		}
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

		FallDead();
		AnotherMonsterCheck();
	}
}

void Monster::FootCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(0.0f, 32.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Monster::LeftCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Monster::RightCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Monster::AnotherMonsterCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == MonsterLeftCollision->CollisionResult("MonsterRight", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir_.x = MoveDir_.x * -1;
	}
	else if (true == MonsterRightCollision->CollisionResult("MonsterLeft", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir_.x = MoveDir_.x * -1;
	}
}

void Monster::FallDead()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == MonsterCollision->CollisionResult("Die", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		MonsterCollision->GetActor()->Death();
	}
}