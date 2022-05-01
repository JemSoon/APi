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
	BlockBotCollision = CreateCollision("BlockBot", { 64, 1 }, { 0,32 });//��� ū���������� �Ѽ����� �ɼ������� �̸��� ����
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

	{	//���� �غκа� �÷��̾�� ���κ��� �浹 ����
		if (true == BlockBotCollision->CollisionResult("PlayerHead", ColList, CollisionType::Rect, CollisionType::Rect))
		{	//�Ⱥμ���(�÷��̾� �������� ���������� MoveDir.y=0.0f;�� Fall���·� ����)
			return;
		}

		else if (true == BlockBotCollision->CollisionResult("BigPlayerHead", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			//�μ���
		}

		else if (true == BlockBotCollision->CollisionResult("WhitePlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			//�μ���
		}
	}
}
