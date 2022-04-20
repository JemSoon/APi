#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include "Bullet.h" // �Ѿ��� ����� �ʹ�.



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

	//�� �̷���ġ (Speed_�� ���ӷ�)
	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	//�� �� �߹ٴ� ��ġ
	float4 CheckPos1 = NextPos + float4(0.0f, 32.0f);

	int Color1 = MapColImage_->GetImagePixel(CheckPos1);//���� �ֳ� ���� �� üũ
	if (RGB(255, 0, 0) != Color1 &&
		RGB(55, 55, 55) != Color1 &&
		RGB(0, 255, 255) != Color1 &&
		RGB(0, 255, 0) != Color1)
	{	//�ش������ �浹ü�� ������ ��� �Ʒ���
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
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
	{	//�ʰ� ĳ������ �浹������

		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}

	//�� �̷���ġ (Speed_�� ���ӷ�)
	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	//�� �� �߹ٴ� ��ġ
	float4 CheckPos1 = NextPos + float4(0.0f, 32.0f);
	int Color1 = MapColImage_->GetImagePixel(CheckPos1);//���� �ֳ� ���� �� üũ


	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		ChangeState(PlayerState::Attck);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		// ���ӷ�
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;

		//�� �̷���ġ (Speed_�� ���ӷ�)
		float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		//�� �� �߹ٴ� ��ġ
		float4 CheckPos1 = NextPos + float4(0.0f, 32.0f);
		int Color1 = MapColImage_->GetImagePixel(CheckPos1);//���� �ֳ� ���� �� üũ
		if (RGB(255, 0, 0) != Color1 &&
			RGB(55, 55, 55) != Color1 &&
			RGB(0, 255, 255) != Color1 &&
			RGB(0, 255, 0) != Color1)
		{	//�ش������ �浹ü�� ������ ��� �Ʒ���
			SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		}

	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_;

		//�� �̷���ġ (Speed_�� ���ӷ�)
		float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		//�� �� �߹ٴ� ��ġ
		float4 CheckPos1 = NextPos + float4(0.0f, 32.0f);

		int Color1 = MapColImage_->GetImagePixel(CheckPos1);//���� �ֳ� ���� �� üũ
		if (RGB(255, 0, 0) != Color1 &&
			RGB(55, 55, 55) != Color1 &&
			RGB(0, 255, 255) != Color1 &&
			RGB(0, 255, 0) != Color1)
		{	//�ش������ �浹ü�� ������ ��� �Ʒ���
			SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		}
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
	// �ִϸ��̼��� �ٲ��.

	// AnimationName = "Idle_"
	//�� �̷���ġ (Speed_�� ���ӷ�)

}

void Player::AttackStart()
{
	// GameEngineTime::SetTimeScale(GameMonster::);

	MoveDir = float4::UP * 500.0f;
}

void Player::MoveStart()
{

}

