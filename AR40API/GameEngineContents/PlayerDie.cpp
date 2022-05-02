#include "PlayerDie.h"
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

PlayerDie::PlayerDie()
	:MoveDir(float4::ZERO)
{

}

PlayerDie::~PlayerDie()
{

}

void PlayerDie::Start()
{
	PlayerAnimationRender=CreateRenderer((int)ORDER::PLAYER);
	PlayerAnimationRender->CreateAnimation("die.bmp", "Die", 0, 0, 0.0f, false);

	PlayerAnimationRender->ChangeAnimation("Die");

	Time = 0.0f;
	Time += GameEngineTime::GetDeltaTime();

	if (1.0 <= Time)
	{
		MoveDir += float4::UP * 20.0f;
		Time = 0.0f;
		
	}
	if (1.5 <= Time)
	{
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime(1.0) * 20.0f;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * 20.0f);
	}
	
}

void PlayerDie::Render()
{
}

void PlayerDie::Update()
{
	//if (1.5 <= Time)
	//{
	//	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime(1.0) * 20.0f;
	//	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * 20.0f);
	//}
}

