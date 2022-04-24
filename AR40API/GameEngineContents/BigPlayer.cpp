#include "BigPlayer.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h>//레벨을 통해서
#include "Bullet.h"//총알을 만들고 싶다

BigPlayer::BigPlayer()
{

}

BigPlayer::~BigPlayer()
{

}

void BigPlayer::Start()
{
	SetScale({ 64,128 });

	//애니메이션을 하나라도 만들면 애니메이션도 재생된다
	PlayerAnimationRender = CreateRenderer();
	//0~1인덱스 0.1초마다(true면 반복,false면 한번만재생)
	PlayerAnimationRender->CreateAnimation("big-walk-R.bmp", "Walk-R", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("big-walk-L.bmp", "Walk-L", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("big-idle-R.bmp", "idle-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("big-idle-L.bmp", "idle-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("big-jump-L.bmp", "Jump-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("big-jump-R.bmp", "Jump-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("big-break-L.bmp", "Break-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("big-break-R.bmp", "Break-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->ChangeAnimation("big-idle-R");
}

void BigPlayer::Render()
{
}

void BigPlayer::Update()
{
}

