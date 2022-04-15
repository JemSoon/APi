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

	{	//내 미래위치
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		//그 때 발바닥 위치
		float4 CheckPos = NextPos + float4(-32.0f, 0.0f);

		//int Color = MapColImage_->GetImagePixel(CheckPos1);//갈수 있냐 없냐 색 체크
		//현재 이거 쓰면 터짐 왜?

		//if (RGB(255, 0, 0) != Color)
		//{	//빨간색이 아니라면 갈수 이써
		//	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		//}

		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		
	}
}