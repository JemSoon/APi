#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include "Bullet.h" // �Ѿ��� ����� �ʹ�.
#include "ContentsEnum.h"



void Player::IdleUpdate()
{
	{	//�ʰ� ĳ������ �浹������

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}

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

	// wndc
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	FootCheck();

	Color_ = MapColImage_->GetImagePixel(CheckPos_);//���� �ֳ� ���� �� üũ
	if (RGB(255, 0, 0) != Color_ &&
		RGB(55, 55, 55) != Color_ &&
		RGB(0, 255, 255) != Color_ &&
		RGB(0, 255, 0) != Color_)
	{	//�ش������ �浹ü�� ������ ��� �Ʒ���
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else {
		MoveDir.y = 0.0f;
	}
	//DirAnimationCheck();
	CameraOutCheck();
}

void Player::MoveUpdate()
{
	{	//�ʰ� ĳ������ �浹������

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		ChangeState(PlayerState::Attck);
		return;
	}

	{	//������
		if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			// ���ӷ�
			PlayerAnimationRender->ChangeAnimation("Walk-R");
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::RIGHT;//�Ѿ� �߻� ���� ������
		}
		//else if (true == GameEngineInput::GetInst()->IsUp("Move Right"))
		//{	//��ư ���� idle�ִϸ��̼�����
		//	PlayerAnimationRender->ChangeAnimation("idle-R");
		//	ChangeState(PlayerState::Idle);
		//	return;
		//}
	}

	{	//����
		if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			PlayerAnimationRender->ChangeAnimation("Walk-L");
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::LEFT;
		}
		//else if (true == GameEngineInput::GetInst()->IsUp("Move Left"))
		//{
		//	PlayerAnimationRender->ChangeAnimation("idle-L");
		//	ChangeState(PlayerState::Idle);
		//	return;
		//}
	}

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	FootCheck();

	{
		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)
		{	//����� ��������(���� �ȴ������) �������� ���� ��������
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
		else
		{
			MoveDir.y = 0.0f;

			NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			//�� �� �߹ٴ� ��ġ
			float4 CheckPos1 = NextPos_ + float4(0.0f, 32.0f);
			int Color1 = MapColImage_->GetImagePixel(CheckPos1);//���� �ֳ� ���� �� üũ

			if (RGB(255, 0, 0) != Color1 &&
				RGB(55, 55, 55) != Color1 &&
				RGB(0, 255, 255) != Color1 &&
				RGB(0, 255, 0) != Color1)
			{
				SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			}
			else 
			{
				MoveDir.x = 0.0f;
			}
		}
	}

	//����
	//MoveDir.

	CameraOutCheck();
}

void Player::AttackUpdate()
{
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	FootCheck();

	Color_ = MapColImage_->GetImagePixel(CheckPos_);//���� �ֳ� ���� �� üũ
	if (RGB(255, 0, 0) != Color_ &&
		RGB(55, 55, 55) != Color_ &&
		RGB(0, 255, 255) != Color_ &&
		RGB(0, 255, 0) != Color_)
	{	//�ش������ �浹ü�� ������ ��� �Ʒ���
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else 
	{
		MoveDir.y = 0.0f;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetDir(CurDir());
	}

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}


	CameraOutCheck();
}

void Player::DeadUpdate()
{
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
}


//////////////////////////////////////// State

void Player::IdleStart()
{
	// �ִϸ��̼��� �ٲ��.

	// AnimationName = "Idle_"
	//�� �̷���ġ (Speed_�� ���ӷ�)

}

void Player::MoveStart()
{

}

void Player::AttackStart()
{

}

void Player::DeadStart()
{
	// GameEngineTime::SetTimeScale(GameMonster::);

	MoveDir = float4::UP * 500.0f;
}
