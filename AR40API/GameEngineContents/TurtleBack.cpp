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
	TBCollision = CreateCollision("TBHitBox", { 64, 64 });
	TBTopCollision = CreateCollision("TBHead", { 64, 2 }, { 0,-32 });
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
}

void TurtleBack::FootCheck()
{
}

void TurtleBack::LeftCheck()
{
}

void TurtleBack::RightCheck()
{
}
