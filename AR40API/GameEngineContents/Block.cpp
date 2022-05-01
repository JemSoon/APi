#include "Block.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

Block::Block()
{

}

Block::~Block()
{

}

void Block::Start()
{
	SetScale({ 64,64 });

	BlockCollision = CreateCollision("Block", { 64, 64 });
	BlockBotCollision = CreateCollision("BlockBot", { 64, 1 }, { 0,32 });//얘는 큰마리오부터 뿌셔지는 옵션있으니 이름을 따로
	BlockTopCollision = CreateCollision("BoxTop", { 64, 1 }, { 0,-32 });
	BlockLeftCollision = CreateCollision("BoxLeft", { 1, 64 }, { -32 , 0 });
	BlockRightCollision = CreateCollision("BoxRight", { 1, 64 }, { 32 , 0 });

	BlockAnimationRender = CreateRenderer((int)ORDER::BOX);
	BlockAnimationRender->CreateAnimation("Block.bmp", "Block", 0, 0, 0.1f, false);
	BlockAnimationRender->ChangeAnimation("Block");
}

void Block::Render()
{
}

void Block::Update()
{
	PlayerCheck();
}

void Block::PlayerCheck()
{
	std::vector<GameEngineCollision*> ColList;

	{	//벽돌 밑부분과 플레이어들 윗부분의 충돌 설정
		if (true == BlockBotCollision->CollisionResult("PlayerHead", ColList, CollisionType::Rect, CollisionType::Rect))
		{	//안부서짐(플레이어 설정에선 내려가도록 MoveDir.y=0.0f;와 Fall상태로 설정)
			return;
		}

		else if (true == BlockBotCollision->CollisionResult("BigPlayerHead", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			//부셔짐
		}

		else if (true == BlockBotCollision->CollisionResult("WhitePlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			//부셔짐
		}
	}
}
