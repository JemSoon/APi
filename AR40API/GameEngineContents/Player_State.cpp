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

//std::string DirString;//���� ����
//std::string PrevDirString;//������ �ٲ������

void Player::IdleUpdate()
{
	{	//�ʰ� ĳ������ �浹������

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
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
	else
	{
		MoveDir.y = 0.0f;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
	}

	if (false == IsMoveKey())
	{	//Ű�� �� ������ ������ ����(�극Ű)
		MoveDir.x *= -MoveDir.x * GameEngineTime::GetDeltaTime();
	}

	CameraOutCheck();
}

void Player::MoveUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	{	//�ʰ� ĳ������ �浹������

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}

	RightCheck();
	//���� �浹���̰� ��Ű�� ������������ x�� 0�̵ȴ�.
	if ((RGB(255, 0, 0) == Color_ ||
		RGB(55, 55, 55) == Color_ ||
		RGB(0, 255, 255) == Color_ ||
		RGB(0, 255, 0) == Color_)&& true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		MoveDir.x = 0.0f;
	}

	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}


	{	//������
		if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			// ���ӷ�
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::RIGHT;//�Ѿ� �߻� ���� ������
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Right"))
		{
			ChangeState(PlayerState::Idle);//�̰ų����� �ٷ� �������+�����ִµ� ���ӵ��� �����Ǿ�����
			return;
		}
	}

	{	//����
		if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			PlayerDir_ = float4::LEFT;
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Left"))
		{
			ChangeState(PlayerState::Idle);
			return;
		}
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

			FootCheck();

			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
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
	MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());
	//�ٵ� idle���·� �Ѿ�� x�� 0�Ǽ� �� ��

	CameraOutCheck();
}

void Player::JumpUpdate()
{
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	//if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	//{
	//	MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	//}

	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}
	// ���̵�� �ٲٴ°� �ƴϿ���
	
	{	//�� üũ
		RightCheck();

		if ((RGB(255,0,0) ==Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_)&& true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{	//������ �տ� ��ֹ��� �ִٸ� x������ 0
			MoveDir.x = 0.0f;
		}

		else if ((RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_) && true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{	//�տ� ��ֹ��� ���ٸ�
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
		}

		//else
		//{
		//	MoveDir.y = 0.0f;
		//	ChangeState(PlayerState::Idle);
		//	return;
		//}
	}


	//{	//�վƷ� ������ üũ
	//	RightBotCheck();
	//	//�ٴ��� ������(255,0,0)
	//	if (RGB(55, 55, 55) != Color_ &&
	//		RGB(0, 255, 255) != Color_ &&
	//		RGB(0, 255, 0) != Color_)
	//	{
	//	}

	//	else if (true == GameEngineInput::GetInst()->IsPress("Move Right") ||
	//		true == GameEngineInput::GetInst()->IsPress("Move Left"))
	//	{
	//		//MoveDir.x = 0.0f;//���� ��Ƽ� y�� �Ʒ��� ������ �ʿ䰡 ������ y=0
	//		ChangeState(PlayerState::Fall);
	//		return;
	//	}
	//	else
	//	{
	//		MoveDir.y = 0.0f;
	//		ChangeState(PlayerState::Idle);
	//		return;
	//	}
	//}

	{	//�߹ٴ� üũ
		FootCheck();

		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)
		{	//����� ���ִ�
			//������� �����϶��� ��� ���ӵǱ⿡ �׷��� ���ϵ��� ������ �־��ش�
			MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}

		else if (true == GameEngineInput::GetInst()->IsPress("Move Right") ||
			true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			//MoveDir.y = 0.0f;//���� ��Ƽ� y�� �Ʒ��� ������ �ʿ䰡 ������ y=0
			ChangeState(PlayerState::Fall);
			return;
		}
		else
		{
			MoveDir.y = 0.0f;
			ChangeState(PlayerState::Idle);
			return;
		}
	}

	CameraOutCheck();

}

void Player::FallUpdate()
{
	RightCheck();
	//���� �ٴ�or��ֹ��̸� x�� 0�̵ȴ�.
	if (RGB(255, 0, 0) == Color_ ||
		RGB(55, 55, 55) == Color_ ||
		RGB(0, 255, 255) == Color_ ||
		RGB(0, 255, 0) == Color_)
	{
		MoveDir.x = 0.0f;
	}

	//MoveDir.x = 0.0f;
	MoveDir.y += 1.0f * GameEngineTime::GetDeltaTime() * AccSpeed_;

	FootCheck();

	if (RGB(255, 0, 0) != Color_ &&
		RGB(55, 55, 55) != Color_ &&
		RGB(0, 255, 255) != Color_ &&
		RGB(0, 255, 0) != Color_)
	{	//����� ���ִ�
		//������� �����϶��� ��� ���ӵǱ⿡ �׷��� ���ϵ��� ������ �־��ش�
		MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}

	//else if (MoveDir.y == 0.0f)
	//{
	//	ChangeState(PlayerState::Move);
	//}
	
	else if ((true == GameEngineInput::GetInst()->IsPress("Move Right") ||
		true == GameEngineInput::GetInst()->IsPress("Move Left")) && MoveDir.y==0.0f)
	{
		//MoveDir.y += 1.0f * GameEngineTime::GetDeltaTime()*AccSpeed_;//���� ��Ƽ� y�� �Ʒ��� ������ �ʿ䰡 ������ y=0
		ChangeState(PlayerState::Move);
	}

	else
	{
		MoveDir.y = 0.0f;
		ChangeState(PlayerState::Idle);
	}

	CameraOutCheck();
}


//////////////////////////////////////// State

void Player::IdleStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	// �������� �����̸�

	PlayerAnimationRender->ChangeAnimation("idle-" + DirString);

	// �ִϸ��̼��� �ٲ��.

	// AnimationName = "Idle_"
	//�� �̷���ġ (Speed_�� ���ӷ�)

	// PlayerAnimationRender->ChangeAnimation("idle-L");

}

void Player::MoveStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	PlayerAnimationRender->ChangeAnimation("Walk-" + DirString);
}

void Player::JumpStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		DirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		DirString = 'L';
	}

	PlayerAnimationRender->ChangeAnimation("Jump-" + DirString);
	MoveDir += float4::UP * 40.0f;
}

void Player::FallStart()
{
	PlayerAnimationRender->ChangeAnimation("Jump-" + DirString);
}