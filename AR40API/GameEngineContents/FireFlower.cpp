#include "FireFlower.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

FireFlower::FireFlower()
{

}

FireFlower::~FireFlower()
{

}

void FireFlower::Start()
{
	SetScale({ 64,64 });

	FireFlowerCollision = CreateCollision("FireFlower", { 64, 64 });
	FireFlowerAnimationRender = CreateRenderer();
	FireFlowerAnimationRender->CreateAnimation("FireFlower.bmp", "FireFlower", 0, 3, 0.3f, true);
	FireFlowerAnimationRender->ChangeAnimation("FireFlower");
}

void FireFlower::Render()
{
}

void FireFlower::Update()
{
}
