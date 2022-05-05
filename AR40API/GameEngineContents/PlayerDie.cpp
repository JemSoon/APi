#include "PlayerDie.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

#include "PlayLevel.h"

PlayerDie::PlayerDie()
	:MoveDir(float4::ZERO)
	,Time(0.0f)
{

}

PlayerDie::~PlayerDie()
{

}

void PlayerDie::Start()
{
	//BgmPlayer->Stop();

	GameEngineSound::SoundPlayOneShot("smb_mariodie.wav");
	PlayerAnimationRender=CreateRenderer((int)ORDER::PLAYER);
	PlayerAnimationRender->CreateAnimation("die.bmp", "Die", 0, 0, 0.0f, false);

	PlayerAnimationRender->ChangeAnimation("Die");
	
}

void PlayerDie::Render()
{
}

void PlayerDie::Update()
{
	Time =Time + GameEngineTime::GetDeltaTime();
	if (0.8 <= Time)
	{
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1.0f;
		MoveDir += float4::UP * GameEngineTime::GetDeltaTime() * 100.0f;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * 20.0f);
	}
	if (1.4 <= Time)
	{
		MoveDir.y = 0.0f;
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 20000.0f;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * 20.0f);
	}

	if (5.0 <= Time)
	{
		GetLevel()->ResetOn();
		GameEngine::GetInst().ChangeLevel("Play1");
		this->Death();
	}
}

