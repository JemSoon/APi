#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h>//������ ���ؼ�
#include "Bullet.h"//�Ѿ��� ����� �ʹ�

//state���� �Լ���

void Player::IdleUpdate()
{
	float4 MoveDir = float4::ZERO;

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{

		ChangeState(PlayerState::Attack);
		//SetScale({ 32,32 });
		//
		//Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		//Ptr->SetPosition(GetPosition());
		return;
	}

}
void Player::AttackUpdate()
{

}
void Player::MoveUpdate()
{

	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		//MoveDir = float4::LEFT;

		//���� ��ġ + �̵��ϴ� ����
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 450.0f;
		}
		else
		{
			Speed_ = 150.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		//MoveDir = float4::RIGHT;

		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 1800.0f;
		}
		else
		{
			Speed_ = 150.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Up"))
	{
		//MoveDir = float4::UP;

		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 450.0f;
		}
		else
		{
			Speed_ = 150.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Down"))
	{
		//MoveDir = float4::DOWN;

		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		if (true == GameEngineInput::GetInst()->IsPress("Run"))
		{
			Speed_ = 450.0f;
		}
		else
		{
			Speed_ = 150.0f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{

		ChangeState(PlayerState::Attack);
		SetScale({ 32,32 });
		
		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());

	}
}

///////////////////////////////////////////////////State

void Player::IdleStart()
{
	//�ִϸ��̼��� �ٲ��
}
void Player::AttackStart()
{

}
void Player::MoveStart()
{

}