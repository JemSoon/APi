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
	FireFlowerAnimationRender = CreateRenderer((int)ORDER::BOX);
	FireFlowerAnimationRender->CreateAnimation("FireFlower.bmp", "FireFlower", 0, 3, 0.3f, true);
	FireFlowerAnimationRender->ChangeAnimation("FireFlower");

	
}

void FireFlower::Render()
{
}

void FireFlower::Update()
{
	{	//카메라 밖에 나가면 죽인다
		if (false == FireFlowerCollision->CollisionCheck("PlayerCamera"))
		{
			this->Death();
		}
	}

	ColBotCheck();
}


void FireFlower::ColBotCheck()
{

	NextPos_ = (MoveDir_ * GameEngineTime::GetDeltaTime() * 80.0f);//미래 위치

	if (true == FireFlowerCollision->NextPosCollisionCheck("Box", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 80.0f;
		//박스 안에서 다 올라올때까진 위로 움직임
		return;//다 올라올때까진 딴 함수로 진행 못 해
	}
}