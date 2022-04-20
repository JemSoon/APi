#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include "Bullet.h" // 총알을 만들고 싶다.

void Player::IdleUpdate()
{
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}


	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		ChangeState(PlayerState::Attck);
		return;
	}
}

void Player::AttackUpdate()
{
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	//if (MoveDir.y)
	//{

	//}



}

void Player::MoveUpdate()
{

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		ChangeState(PlayerState::Attck);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		// 가속력
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;
	}
	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_;
	}
	if (true == GameEngineInput::GetInst()->IsPress("Move Up"))
	{
		MoveDir += float4::UP * GameEngineTime::GetDeltaTime() * Speed_;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Down"))
	{
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;
	}

	// MoveDir*= Speed_;

	if (0.3f <= MoveDir.Len2D())
	{
		MoveDir.Range2D(0.3f);
	}

	if (false == IsMoveKey())
	{
		MoveDir += -MoveDir * GameEngineTime::GetDeltaTime();

		if (0.005f >= MoveDir.Len2D())
		{
			MoveDir = float4::ZERO;
			return;
		}

		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		return;
	}



	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);


}


//////////////////////////////////////// State

void Player::IdleStart()
{
	// 애니메이션이 바뀐다.

	// AnimationName = "Idle_"
}

void Player::AttackStart()
{
	// GameEngineTime::SetTimeScale(GameMonster::);

	MoveDir = float4::UP * 500.0f;
}

void Player::MoveStart()
{

}

