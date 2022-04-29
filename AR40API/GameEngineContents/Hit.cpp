#include "Hit.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

Hit::Hit()
{

}

Hit::~Hit()
{

}

void Hit::Start()
{
	GameEngineRenderer* Hit = CreateRenderer();
	Hit->CreateAnimation("Hit.bmp", "Hit", 0, 0, 0.1f, false);
	Hit->ChangeAnimation("Hit");

	//CreateCollision("PlayerAttackBox", { 32, 32 });

	Death(0.1f);//5초뒤에 총알은 사라진다(죽는다)
}

void Hit::Update()
{
}

