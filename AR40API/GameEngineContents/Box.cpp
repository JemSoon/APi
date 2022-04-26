#include "Box.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

Box::Box()
{

}

Box::~Box()
{

}

void Box::Start()
{
	SetScale({ 64,64 });

	BoxCollision = CreateCollision("Box", { 64, 64 });
	BoxAnimationRender = CreateRenderer();
	BoxAnimationRender->CreateAnimation("QBox.bmp", "Box", 0, 3, 0.3f, true);
	BoxAnimationRender->CreateAnimation("empty-Box.bmp", "EmptyBox", 0, 0, 0.1f, false);
	BoxAnimationRender->ChangeAnimation("Box");

}

void Box::Render()
{
}

void Box::Update()
{
	PlayerCheck();
}

void Box::FootCheck()
{
}

void Box::PlayerCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == BoxCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		BoxAnimationRender->ChangeAnimation("EmptyBox");
	}

	if (true == BoxCollision->CollisionResult("BigPlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		BoxAnimationRender->ChangeAnimation("EmptyBox");
	}
}