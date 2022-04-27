#include "BigPlayer.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include "Bullet.h" // �Ѿ��� ����� �ʹ�.
#include "ContentsEnum.h"

void BigPlayer::IdleUpdate()
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
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	if (true == IsMoveKey())
	{
		ChangeState(BigPlayerState::Move);
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
		ChangeState(BigPlayerState::Jump);
	}

	if (false == IsMoveKey())
	{	//Ű�� �� ������ ������ ����(�극Ű)
		MoveDir.x *= -MoveDir.x * GameEngineTime::GetDeltaTime();
	}

	CameraOutCheck();
}

void BigPlayer::MoveUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	{	//�ʰ� ĳ������ �浹������

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}

	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(BigPlayerState::Jump);
		return;
	}


	{	//������
		if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			// ���ӷ�
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			BigPlayerDir_ = float4::RIGHT;//�Ѿ� �߻� ���� ������
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Right"))
		{
			ChangeState(BigPlayerState::Idle);//�̰ų����� �ٷ� �������+�����ִµ� ���ӵ��� �����Ǿ�����
			return;
		}
	}

	{	//����
		if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			BigPlayerDir_ = float4::LEFT;
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Left"))
		{
			ChangeState(BigPlayerState::Idle);
			return;
		}
	}

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
	
	{	//�� üũ
		RightCheck();

		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)
		{
		}

		else if (true == GameEngineInput::GetInst()->IsPress("Move Right") ||
			true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir.x = 0.0f;//���� ��Ƽ� y�� �Ʒ��� ������ �ʿ䰡 ������ y=0
			ChangeState(BigPlayerState::Move);
		}
		else
		{
			MoveDir.y = 0.0f;
			ChangeState(BigPlayerState::Idle);
		}
	}


	{	//�վƷ� ������ üũ
		RightBotCheck();

		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)
		{
		}

		else if (true == GameEngineInput::GetInst()->IsPress("Move Right") ||
			true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir.x = 0.0f;//���� ��Ƽ� y�� �Ʒ��� ������ �ʿ䰡 ������ y=0
			ChangeState(BigPlayerState::Move);
		}
		else
		{
			MoveDir.y = 0.0f;
			ChangeState(BigPlayerState::Idle);
		}
	}

	

	{
		FootCheck();

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

void BigPlayer::JumpUpdate()
{
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}
	// ���̵�� �ٲٴ°� �ƴϿ���


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
		MoveDir.y = 0.0f;//���� ��Ƽ� y�� �Ʒ��� ������ �ʿ䰡 ������ y=0
		ChangeState(BigPlayerState::Move);
	}
	else
	{
		MoveDir.y = 0.0f;
		ChangeState(BigPlayerState::Idle);
	}

	CameraOutCheck();

}




//////////////////////////////////////// State

void BigPlayer::IdleStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	// �������� �����̸�

	BigPlayerAnimationRender->ChangeAnimation("Bidle-" + BigDirString);

	// �ִϸ��̼��� �ٲ��.

	// AnimationName = "Idle_"
	//�� �̷���ġ (Speed_�� ���ӷ�)

	// PlayerAnimationRender->ChangeAnimation("idle-L");

}

void BigPlayer::MoveStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	BigPlayerAnimationRender->ChangeAnimation("BWalk-" + BigDirString);
}

void BigPlayer::JumpStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		BigDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		BigDirString = 'L';
	}

	BigPlayerAnimationRender->ChangeAnimation("BJump-" + BigDirString);
	MoveDir += float4::UP * 40.0f;
}
