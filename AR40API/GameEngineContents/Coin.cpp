#include "Coin.h"
#include "UI.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>


Coin::Coin()
{

}

Coin::~Coin()
{

}

void Coin::Start()
{
	CoinCollision = CreateCollision("Coin", { 64, 64 });

	CoinAnimationRender = CreateRenderer((int)ORDER::ITEM);
	CoinAnimationRender->CreateAnimation("coin.bmp", "Coin", 0, 2, 0.3f, true);
	CoinAnimationRender->ChangeAnimation("Coin");
}

void Coin::Render()
{
}

void Coin::Update()
{
	PlayerCheck();
}

void Coin::PlayerCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == CoinCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect)||
		true == CoinCollision->CollisionResult("BigPlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect)||
		true == CoinCollision->CollisionResult("WhitePlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		CoinCollision->GetActor()->Death();
		//코인 카운트 +1
	}
}
