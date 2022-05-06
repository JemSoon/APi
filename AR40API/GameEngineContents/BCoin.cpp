#include "BCoin.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

BCoin::BCoin()
{

}

BCoin::~BCoin()
{

}

void BCoin::Start()
{
	SetScale({ 64,64 });

	BCoinCollision = CreateCollision("BCoin", { 64, 64 });
	BCoinAnimationRender = CreateRenderer((int)ORDER::ITEM);
	BCoinAnimationRender->CreateAnimation("BCoin.bmp", "BCoin", 0, 3, 0.1f, true);
	BCoinAnimationRender->ChangeAnimation("BCoin");
	MoveDir_ += float4::UP * GameEngineTime::GetDeltaTime() * 300.0f;
	
}

void BCoin::Render()
{
}

void BCoin::Update()
{
	SetMove(MoveDir_);
	Time_ = Time_ + GameEngineTime::GetDeltaTime();
	if (0.5 <= Time_)
	{
		this->Death();
	}
}
