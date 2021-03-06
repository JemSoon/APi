#include "TurtleBack.h"
#include "Player.h"
#include "BigPlayer.h"
#include "WhitePlayer.h"
#include "PlayerDie.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

TurtleBack::TurtleBack():
	MoveDir_(float4::ZERO)
{

}

TurtleBack::~TurtleBack()
{

}

void TurtleBack::Start()
{
	TBCollision = CreateCollision("TBHitBox", { 64, 62 });
	TBTopCollision = CreateCollision("TBHead", { 64, 2 }, { 0,-32 });
	//TBTopLeftCollision = CreateCollision("TBHead-L", { 32, 2 }, { -16,-32 });
	//TBTopRightCollision = CreateCollision("TBHead-R", { 32, 2 }, { 16,-32 });
	TBLeftCollision = CreateCollision("TBLeft", { 2, 64 }, { -34,0 });
	TBRightCollision = CreateCollision("TBRight", { 2, 64 }, { 34,0 });
	
	TBAnimationRender = CreateRenderer((int)ORDER::MONSTER);
	TBAnimationRender->CreateAnimation("turtle-back.bmp", "turtle-back", 0, 0, 0.0f, false);
	TBAnimationRender->ChangeAnimation("turtle-back");
}

void TurtleBack::Render()
{
}

void TurtleBack::Update()
{
	PlayerAttack();
	Kill();

	{
		if (false == TBCollision->CollisionCheck("PlayerCamera"))
		{
			return;
		}
	}


	{	//�ʰ� ĳ������ �浹������
		//(����)���� BG�� ��ǥ�� �ȸ��� ����
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}


	{
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		//�� �̷���ġ
		FootCheck();//�߹ٴ� �� ���� �� üũ
		Color_ = MapColImage_->GetImagePixel(CheckPos_);
		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)//����� �ִ�
		{	//�������� �ƴ϶�� ���� �̽�
			SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * AccSpeed_);
		}
		else//�ٴڿ� ��Ҵ�
		{
			MoveDir_.y = 0.0f;
			LeftCheck();//���� ��üũ
			Color_ = MapColImage_->GetImagePixel(CheckPos_);
			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
			{	//�������� �ƴ϶�� ���� �̽�
				MoveDir_.x = MoveDir_.x;
			}
			else
			{
				MoveDir_.x = MoveDir_.x * -1;
			}

			RightCheck();//������ ��üũ
			Color_ = MapColImage_->GetImagePixel(CheckPos_);
			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
			{	//�������� �ƴ϶�� ���� �̽�
				MoveDir_.x = MoveDir_.x;
			}
			else
			{
				MoveDir_.x = MoveDir_.x * -1;
			}
		}

		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	SetMove(MoveDir_);
}

void TurtleBack::FootCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(0.0f, 48.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::LeftCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::RightCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::PlayerAttack()
{
	std::vector<GameEngineCollision*> ColList;
	//�ź��� ����� �������ְ� �߷� �ε�������=�ź��� ����� ���������� �̵�
	if (true == TBTopCollision->CollisionResult("PlayerFootHit", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x == 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * 450.0f;
	}
	//�ź��� ����� �����̰� �߷� �ε������� = �ź��� ����� ����
	else if (true == TBTopCollision->CollisionResult("PlayerFootHit", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		MoveDir_ = float4::ZERO;
	}

	//�ź��� ����� �����ְ� ��� �����ʰ� �÷��̾� ������ �ε������� = �ź��� ����� �и�
	if ((true == TBRightCollision->CollisionResult("PlayerLeft", ColList, CollisionType::Rect, CollisionType::Rect))
		&& (MoveDir_.x == 0.0f))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			if (MoveDir_.x == 0.0f)
			{
				GameEngineSound::SoundPlayOneShot("smb_kick.wav");
				MoveDir_ += float4::LEFT * GameEngineTime::GetDeltaTime() * 450.0f;
			}
		}
	}
	//�ź��� ����� �����ְ� ��� �����ʰ� ū�÷��̾� ������ �ε�������=�ź��� ����� �и�
	else if (true == TBRightCollision->CollisionResult("BigPlayerLeft", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x == 0.0f)
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			if (MoveDir_.x == 0.0f)
			{
				GameEngineSound::SoundPlayOneShot("smb_kick.wav");
				MoveDir_ += float4::LEFT * GameEngineTime::GetDeltaTime() * 450.0f;
			}
		}
	}
	//���÷��̾� ���ϵ���
	else if (true == TBRightCollision->CollisionResult("WhitePlayerLeft", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x == 0.0f)
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			if (MoveDir_.x == 0.0f)
			{
				GameEngineSound::SoundPlayOneShot("smb_kick.wav");
				MoveDir_ += float4::LEFT * GameEngineTime::GetDeltaTime() * 450.0f;
			}
		}
	}

	//�ź��� ����� �����̰� ��� �����ʰ� �÷��̾� ������ �ε�������=�÷��̾� ����
	else if (true == TBRightCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		PlayerDie* die = GetLevel()->CreateActor<PlayerDie>();
		die->SetPosition(Player::MainPlayer->GetPosition());
		//PlayerCollision->GetActor()->Death();
		Player::MainPlayer->Death();
		Player::MainPlayer = nullptr;
		BigPlayer::MainBigPlayer->Death();
		BigPlayer::MainBigPlayer = nullptr;
		WhitePlayer::MainWhitePlayer->Death();
		WhitePlayer::MainWhitePlayer = nullptr;
		return;
	}
	//���� �߰��� �򸶸��� �浹 ��
	//�ź��� ����� �����̰� ��� �����ʰ� ���÷��̾� ������ �ε�������=������������ ��ȭ�� 2�� ����
	else if (true == TBRightCollision->CollisionResult("BigPlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		BigPlayer::MainBigPlayer->GetDir() = float4::ZERO;
		BigPlayer::MainBigPlayer->ChangeState(BigPlayerState::Idle);
		BigPlayer::MainBigPlayer->Off();
		Player::MainPlayer->SetPosition(BigPlayer::MainBigPlayer->GetPosition());
		Player::MainPlayer->On();
		Player::MainPlayer->NoHit();
	
		//Player::MainPlayer->GetRenderer1()->SetAlpha(122); //���� �̹��� ���� ������ ����..��
	
		Player::MainPlayer->HitTimeCheck();
		return;
	}
	else if (true == TBRightCollision->CollisionResult("WhitePlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		WhitePlayer::MainWhitePlayer->GetDir() = float4::ZERO;
		WhitePlayer::MainWhitePlayer->ChangeState(WhitePlayerState::Idle);
		WhitePlayer::MainWhitePlayer->Off();
		BigPlayer::MainBigPlayer->SetPosition(WhitePlayer::MainWhitePlayer->GetPosition());
		BigPlayer::MainBigPlayer->On();
		BigPlayer::MainBigPlayer->NoHit();

		//Player::MainPlayer->GetRenderer1()->SetAlpha(122); //���� �̹��� ���� ������ ����..��

		BigPlayer::MainBigPlayer->HitTimeCheck();
		return;
	}

	//=====================������� �����̿��� ���� ������ ===================================

	if (true == TBLeftCollision->CollisionResult("PlayerRight", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x == 0.0f)
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			if (MoveDir_.x == 0.0f)
			{
				GameEngineSound::SoundPlayOneShot("smb_kick.wav");
				MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * 450.0f;
			}
		}
	}
	else if (true == TBLeftCollision->CollisionResult("BigPlayerRight", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x == 0.0f)
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			if (MoveDir_.x == 0.0f)
			{
				GameEngineSound::SoundPlayOneShot("smb_kick.wav");
				MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * 450.0f;
			}
		}
	}
	else if (true == TBLeftCollision->CollisionResult("WhitePlayerRight", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x == 0.0f)
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			if (MoveDir_.x == 0.0f)
			{
				GameEngineSound::SoundPlayOneShot("smb_kick.wav");
				MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * 450.0f;
			}
		}
	}

	//===============������� �������ִ� �ź��� ��� �о������ �ڵ忴�� �ؿ��� �����̴� ����� �´� �ڵ� =============

	else if (true == TBLeftCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		PlayerDie* die = GetLevel()->CreateActor<PlayerDie>();
		die->SetPosition(Player::MainPlayer->GetPosition());
		//PlayerCollision->GetActor()->Death();
		Player::MainPlayer->Death();
		Player::MainPlayer = nullptr;
		BigPlayer::MainBigPlayer->Death();
		BigPlayer::MainBigPlayer = nullptr;
		WhitePlayer::MainWhitePlayer->Death();
		WhitePlayer::MainWhitePlayer = nullptr;
		return;
	}
	//���� �߰��� �򸶸��� �浹 ��
	else if (true == TBLeftCollision->CollisionResult("BigPlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		BigPlayer::MainBigPlayer->GetDir() = float4::ZERO;
		BigPlayer::MainBigPlayer->ChangeState(BigPlayerState::Idle);
		BigPlayer::MainBigPlayer->Off();
		Player::MainPlayer->SetPosition(BigPlayer::MainBigPlayer->GetPosition());
		Player::MainPlayer->On();
		Player::MainPlayer->NoHit();

		//Player::MainPlayer->GetRenderer1()->SetAlpha(122); //���� �̹��� ���� ������ ����..��

		Player::MainPlayer->HitTimeCheck();
		return;
	}

	else if (true == TBLeftCollision->CollisionResult("WhitePlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		WhitePlayer::MainWhitePlayer->GetDir() = float4::ZERO;
		WhitePlayer::MainWhitePlayer->ChangeState(WhitePlayerState::Idle);
		WhitePlayer::MainWhitePlayer->Off();
		BigPlayer::MainBigPlayer->SetPosition(WhitePlayer::MainWhitePlayer->GetPosition());
		BigPlayer::MainBigPlayer->On();
		BigPlayer::MainBigPlayer->NoHit();

		//Player::MainPlayer->GetRenderer1()->SetAlpha(122); //���� �̹��� ���� ������ ����..��

		BigPlayer::MainBigPlayer->HitTimeCheck();
		return;
	}
}

void TurtleBack::FallDead()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == TBCollision->CollisionResult("Die", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		TBCollision->GetActor()->Death();
	}
}

void TurtleBack::Kill()
{
	std::vector<GameEngineCollision*> ColList;
	if (MoveDir_.x != 0.0f && true == TBLeftCollision->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect)||
		MoveDir_.x != 0.0f && true == TBRightCollision->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		for (size_t i = 0; i < ColList.size(); i++)
		{
			GameEngineSound::SoundPlayOneShot("smb_kick.wav");
			ColList[i]->GetActor()->Death();
		}
	}

}