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
	: Speed_(150.0f)
	, Gravity_(100.0f)
{

}

Monster::~Monster()
{

}

void Monster::Start()
{
	SetScale({ 64,64 });

	MonsterCollision = CreateCollision("MonsterHitBox", { 64, 64 });
	MonsterAnimationRender = CreateRenderer();
	MonsterAnimationRender->CreateAnimation("gumba-walk.bmp", "gumba-walk", 0, 1, 0.1f, true);
	MonsterAnimationRender->ChangeAnimation("gumba-walk");
}

void Monster::Render()
{

}

void Monster::Update()
{
	float4 CheckPos1;
	float4 MoveDir = float4::LEFT;

	{	//�� �̷���ġ
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		//�� �� �߹ٴ� ��ġ
		float4 CheckPos = NextPos + float4(-32.0f, 0.0f);

		//int Color = MapColImage_->GetImagePixel(CheckPos1);//���� �ֳ� ���� �� üũ
		//���� �̰� ���� ���� ��?

		//if (RGB(255, 0, 0) != Color)
		//{	//�������� �ƴ϶�� ���� �̽�
		//	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		//}

		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		
	}
}