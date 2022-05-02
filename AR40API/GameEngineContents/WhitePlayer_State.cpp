#include "WhitePlayer.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include "Bullet.h" // �Ѿ��� ����� �ʹ�.
#include "ContentsEnum.h"

void WhitePlayer::IdleUpdate()
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
		WhiteDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		WhiteDirString = 'L';
	}

	if (true == IsMoveKey())
	{
		ChangeState(WhitePlayerState::Move);
		return;
	}

	// �߷�
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	//===============�浹ü�� �߷� ����=================//
	NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos_ = NextPos_;
	//���� �̷� ��ġ�� �÷��̾� �߹ٴ� �浹�� �ڽ�ž �浹�� ������ �߷��� 0�� �ȴ�.
	if (true == WhitePlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.y = 0.0f;
		//MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

		if (true == GameEngineInput::GetInst()->IsDown("Jump"))
		{
			ChangeState(WhitePlayerState::Jump);
		}

		if (true == GameEngineInput::GetInst()->IsPress("Move Down"))
		{
			WhitePlayerCollision->Off();
			WhitePlayerAnimationRender->ChangeAnimation("WDown-" + WhiteDirString);
		}

		else if (true == GameEngineInput::GetInst()->IsUp("Move Down"))
		{
			WhitePlayerCollision->On();
			WhitePlayerAnimationRender->ChangeAnimation("Widle-" + WhiteDirString);
		}

		if (false == IsMoveKey())
		{	//Ű�� �� ������ ������ ����(�극Ű)
			MoveDir.x *= -MoveDir.x * GameEngineTime::GetDeltaTime();
		}

		return;
	}

	//================�÷��浹�� �߷� ����===================//
	else
	{
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
			ChangeState(WhitePlayerState::Jump);
		}

		if (true == GameEngineInput::GetInst()->IsPress("Move Down"))
		{
			WhitePlayerCollision->Off();
			WhitePlayerAnimationRender->ChangeAnimation("BDown-" + WhiteDirString);
		}

		else if (true == GameEngineInput::GetInst()->IsUp("Move Down"))
		{
			WhitePlayerCollision->On();
			WhitePlayerAnimationRender->ChangeAnimation("Bidle-" + WhiteDirString);
		}

		if (false == IsMoveKey())
		{	//Ű�� �� ������ ������ ����(�극Ű)
			MoveDir.x *= -MoveDir.x * GameEngineTime::GetDeltaTime();
		}
	}

	CameraOutCheck();
}

void WhitePlayer::MoveUpdate()
{
	BreakAnimation();

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		WhiteDirString = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		WhiteDirString = 'L';
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
		RGB(0, 255, 0) == Color_) && true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		MoveDir.x = 0.0f;
	}

	LeftCheck();
	//�ڰ� �浹���̰� ��Ű�� ������������ x�� 0�̵ȴ�.
	if ((RGB(255, 0, 0) == Color_ ||
		RGB(55, 55, 55) == Color_ ||
		RGB(0, 255, 255) == Color_ ||
		RGB(0, 255, 0) == Color_) && true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		MoveDir.x = 0.0f;
	}

	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(WhitePlayerState::Jump);
		return;
	}


	{	//������
		if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			// ���ӷ�
			MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			WhitePlayerDir_ = float4::RIGHT;//�Ѿ� �߻� ���� ������
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Right"))
		{
			ChangeState(WhitePlayerState::Idle);//�̰ų����� �ٷ� �������+�����ִµ� ���ӵ��� �����Ǿ�����
			return;
		}
	}

	{	//����
		if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
			WhitePlayerDir_ = float4::LEFT;
		}
		else if (true == GameEngineInput::GetInst()->IsUp("Move Left"))
		{
			ChangeState(WhitePlayerState::Idle);
			return;
		}
	}

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	{
		//===============�浹ü�� �߷� ����=================//
		NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos_ = NextPos_;
		//���� �̷� ��ġ�� �÷��̾� �߹ٴ� �浹�� �ڽ�ž �浹�� ������ �߷��� 0�� �ȴ�.
		if (true == WhitePlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
		{
			MoveDir.y = 0.0f;
			MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());//����
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			return;
		}

		else
		{	//==============�÷��� �߷� ����==================//
			FootCheck();
			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
			{	//����� ��������(���� �ȴ������) �������� ���� ��������
				SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
				ChangeState(WhitePlayerState::Fall);
				return;
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
	}

	//����
	MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());
	//�ٵ� idle���·� �Ѿ�� x�� 0�Ǽ� �� ��

	CameraOutCheck();
}

void WhitePlayer::JumpUpdate()
{
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	//if (true == GameEngineInput::GetInst()->IsUp("Jump"))
	//{	//���� ���� �ð��� ���� ���� ���� ��ȭ��
	//	MoveDir.y = 0.0f;
	//	ChangeState(PlayerState::Fall);
	//	return;
	//}

	// ���̵�� �ٲٴ°� �ƴϿ���

	//===============�浹ü�� �߷� ����=================//
	NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos_ = NextPos_;
	//���� �̷� ��ġ�� �÷��̾� �߹ٴ� �浹�� �ڽ�ž �浹�� ������ �߷��� 0�� �ȴ�.
	if (true == WhitePlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.y = 0.0f;
		MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());//����
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);

		if (true == IsMoveKey())
		{
			ChangeState(WhitePlayerState::Move);
		}
		else
		{
			ChangeState(WhitePlayerState::Idle);
		}
		return;
	}

	else if (true == WhitePlayerHeadCollision->NextPosCollisionCheck("BoxBot", NextPos_, CollisionType::Rect, CollisionType::Rect) ||
		true == WhitePlayerHeadHitCollision->NextPosCollisionCheck("BlockBot", NextPos_, CollisionType::Rect, CollisionType::Rect) ||
		true == WhitePlayerHeadCollision->NextPosCollisionCheck("BlockBot", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{	//�ڽ��� �Ӹ��� �浹�ϸ�
		MoveDir.y = 0.0f;
		ChangeState(WhitePlayerState::Fall);
		return;
	}

	else if (true == WhitePlayerLeftCollision->NextPosCollisionCheck("BoxRight", NextPos_, CollisionType::Rect, CollisionType::Rect) ||
		true == WhitePlayerRightCollision->NextPosCollisionCheck("BoxLeft", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.x = 0.0f;
	}

	//===============�÷��� �߷� ����=================//
	else
	{
		//�÷� �浹�� üũ
		//�Ӹ� üũ
		HeadCheck();

		if (RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_)
		{	//��ֹ��� �ε����ٸ� �ٷ� ���� ���·� ����
			MoveDir.y = 0.0f;
			ChangeState(WhitePlayerState::Fall);
			return;
		}

	}

	{	//�� üũ
		RightCheck();

		if ((RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_) && true == GameEngineInput::GetInst()->IsPress("Move Right"))
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

	}

	{	//�� üũ
		LeftCheck();

		if ((RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_) && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{	//������ �տ� ��ֹ��� �ִٸ� x������ 0
			MoveDir.x = 0.0f;
		}

		else if ((RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_) && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{	//�տ� ��ֹ��� ���ٸ�
			MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
		}

	}

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
		{	//���Ͻ����Ҷ� Fall�� �Ǿ������ʳ�..?
			ChangeState(WhitePlayerState::Fall);
			return;
		}
		else
		{
			MoveDir.y = 0.0f;
			ChangeState(WhitePlayerState::Idle);
			return;
		}
	}

	CameraOutCheck();

}

void WhitePlayer::FallUpdate()
{
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		// ���ӷ�
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
		WhitePlayerDir_ = float4::RIGHT;//�Ѿ� �߻� ���� ������
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move LEft"))
	{
		// ���ӷ�
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
		WhitePlayerDir_ = float4::LEFT;//�Ѿ� �߻� ���� ������
	}

	NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos_ = NextPos_;
	//���� �̷� ��ġ�� �÷��̾� �߹ٴ� �浹�� �ڽ�ž �浹�� ������ �߷��� 0�� �ȴ�.
	if (true == WhitePlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.y = 0.0f;
		MoveDir.x += ((-MoveDir.x * 0.9f) * GameEngineTime::GetDeltaTime());//����
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);

		if (true == IsMoveKey())
		{
			ChangeState(WhitePlayerState::Move);
		}
		else
		{
			ChangeState(WhitePlayerState::Idle);
		}
	}

	//������ �Լ�(�ذ�)
	else if (true == WhitePlayerLeftCollision->NextPosCollisionCheck("BoxRight", NextPos_, CollisionType::Rect, CollisionType::Rect) ||
		true == WhitePlayerRightCollision->NextPosCollisionCheck("BoxLeft", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.x = 0.0f;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		if (MoveDir.y == 0)
		{
			ChangeState(WhitePlayerState::Idle);
			return;
		}
	}

	else
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

		LeftCheck();
		//���� �ٴ�or��ֹ��̸� x�� 0�̵ȴ�.
		if (RGB(255, 0, 0) == Color_ ||
			RGB(55, 55, 55) == Color_ ||
			RGB(0, 255, 255) == Color_ ||
			RGB(0, 255, 0) == Color_)
		{
			MoveDir.x = 0.0f;
		}

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
			true == GameEngineInput::GetInst()->IsPress("Move Left")) && MoveDir.y == 0.0f)
		{
			//MoveDir.y += 1.0f * GameEngineTime::GetDeltaTime()*AccSpeed_;//���� ��Ƽ� y�� �Ʒ��� ������ �ʿ䰡 ������ y=0
			ChangeState(WhitePlayerState::Move);
			return;
		}

		else
		{
			MoveDir.y = 0.0f;
			ChangeState(WhitePlayerState::Idle);
			return;
		}
	}

	CameraOutCheck();
}

//////////////////////////////////////// State

void WhitePlayer::IdleStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		WhiteDirString_ = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		WhiteDirString_ = 'L';
	}

	// �������� �����̸�

	WhitePlayerAnimationRender->ChangeAnimation("Widle-" + WhiteDirString_);

	// �ִϸ��̼��� �ٲ��.

	// AnimationName = "Idle_"
	//�� �̷���ġ (Speed_�� ���ӷ�)

	// PlayerAnimationRender->ChangeAnimation("idle-L");

}

void WhitePlayer::MoveStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		WhiteDirString_ = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		WhiteDirString_ = 'L';
	}

	WhitePlayerAnimationRender->ChangeAnimation("WWalk-" + WhiteDirString_);
}

void WhitePlayer::JumpStart()
{
	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		WhiteDirString_ = 'R';
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		WhiteDirString_ = 'L';
	}

	WhitePlayerAnimationRender->ChangeAnimation("WJump-" + WhiteDirString_);
	MoveDir += float4::UP * 35.0f;
}

void WhitePlayer::FallStart()
{
	WhitePlayerAnimationRender->ChangeAnimation("WJump-" + WhiteDirString_);
}
