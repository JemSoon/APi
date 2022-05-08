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
	TBLeftCollision = CreateCollision("TBLeft", { 2, 64 }, { -32,0 });
	TBRightCollision = CreateCollision("TBRight", { 2, 64 }, { 32,0 });
	
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


	{	//맵과 캐릭터의 충돌설정용
		//(참고)실제 BG랑 좌표가 안맞음 현재
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}


	{
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		//내 미래위치
		FootCheck();//발바닥 밑 닿은 색 체크
		Color_ = MapColImage_->GetImagePixel(CheckPos_);
		if (RGB(255, 0, 0) != Color_ &&
			RGB(55, 55, 55) != Color_ &&
			RGB(0, 255, 255) != Color_ &&
			RGB(0, 255, 0) != Color_)//허공에 있다
		{	//빨간색이 아니라면 갈수 이써
			SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * AccSpeed_);
		}
		else//바닥에 닿았다
		{
			MoveDir_.y = 0.0f;
			LeftCheck();//왼쪽 벽체크
			Color_ = MapColImage_->GetImagePixel(CheckPos_);
			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
			{	//빨간색이 아니라면 갈수 이써
				MoveDir_.x = MoveDir_.x;
			}
			else
			{
				MoveDir_.x = MoveDir_.x * -1;
			}

			RightCheck();//오른쪽 벽체크
			Color_ = MapColImage_->GetImagePixel(CheckPos_);
			if (RGB(255, 0, 0) != Color_ &&
				RGB(55, 55, 55) != Color_ &&
				RGB(0, 255, 255) != Color_ &&
				RGB(0, 255, 0) != Color_)
			{	//빨간색이 아니라면 갈수 이써
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
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 48.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::LeftCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(-32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::RightCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(32.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void TurtleBack::PlayerAttack()
{
	std::vector<GameEngineCollision*> ColList;
	//거북이 등껍질이 정지해있고 발로 부딛혔을때=거북이 등껍질이 오른쪽으로 이동
	if (true == TBTopCollision->CollisionResult("PlayerFootHit", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x == 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * 450.0f;
	}
	//거북이 등껍질이 움직이고 발로 부딛혔을때 = 거북이 등껍질이 멈춤
	else if (true == TBTopCollision->CollisionResult("PlayerFootHit", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		MoveDir_ = float4::ZERO;
	}

	//거북이 등껍질이 멈춰있고 등껍질 오른쪽과 플레이어 왼쪽이 부딪혔을떄 = 거북이 등껍질이 밀림
	if (true == TBRightCollision->CollisionResult("PlayerLeft", ColList, CollisionType::Rect, CollisionType::Rect)
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
	//거북이 등껍질이 멈춰있고 등껍질 오른쪽과 큰플레이어 왼쪽이 부딪혔을때=거북이 등껍질이 밀림
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
	//흰플레이어 이하동문
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

	//거북이 등껍질이 움직이고 등껍질 오른쪽과 플레이어 왼쪽이 부딛혔을때=플레이어 죽음
	else if (true == TBRightCollision->CollisionResult("PlayerLeft", ColList, CollisionType::Rect, CollisionType::Rect)
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
	//내가 추가한 빅마리오 충돌 ↓
	//거북이 등껍질이 움직이고 등껍질 오른쪽과 빅플레이어 왼쪽이 부딪혔을때=작은마리오로 퇴화후 2초 무적
	else if (true == TBRightCollision->CollisionResult("BigPlayerLeft", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		BigPlayer::MainBigPlayer->GetDir() = float4::ZERO;
		BigPlayer::MainBigPlayer->ChangeState(BigPlayerState::Idle);
		BigPlayer::MainBigPlayer->Off();
		Player::MainPlayer->SetPosition(BigPlayer::MainBigPlayer->GetPosition());
		Player::MainPlayer->On();
		Player::MainPlayer->NoHit();
	
		//Player::MainPlayer->GetRenderer1()->SetAlpha(122); //내가 이미지 알파 설정을 안함..ㅠ
	
		Player::MainPlayer->HitTimeCheck();
		return;
	}
	else if (true == TBRightCollision->CollisionResult("WhitePlayerLeft", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		WhitePlayer::MainWhitePlayer->GetDir() = float4::ZERO;
		WhitePlayer::MainWhitePlayer->ChangeState(WhitePlayerState::Idle);
		WhitePlayer::MainWhitePlayer->Off();
		BigPlayer::MainBigPlayer->SetPosition(WhitePlayer::MainWhitePlayer->GetPosition());
		BigPlayer::MainBigPlayer->On();
		BigPlayer::MainBigPlayer->NoHit();

		//Player::MainPlayer->GetRenderer1()->SetAlpha(122); //내가 이미지 알파 설정을 안함..ㅠ

		BigPlayer::MainBigPlayer->HitTimeCheck();
		return;
	}

	//=====================여기까지 왼쪽이였고 밑은 오른쪽 ===================================

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

	//===============여기까진 정지되있는 거북이 등껍질 밀어버리는 코드였고 밑에는 움직이는 등껍질에 맞는 코드 =============

	else if (true == TBLeftCollision->CollisionResult("PlayerRight", ColList, CollisionType::Rect, CollisionType::Rect)
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
	//내가 추가한 빅마리오 충돌 ↓
	else if (true == TBLeftCollision->CollisionResult("BigPlayerRight", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		BigPlayer::MainBigPlayer->GetDir() = float4::ZERO;
		BigPlayer::MainBigPlayer->ChangeState(BigPlayerState::Idle);
		BigPlayer::MainBigPlayer->Off();
		Player::MainPlayer->SetPosition(BigPlayer::MainBigPlayer->GetPosition());
		Player::MainPlayer->On();
		Player::MainPlayer->NoHit();

		//Player::MainPlayer->GetRenderer1()->SetAlpha(122); //내가 이미지 알파 설정을 안함..ㅠ

		Player::MainPlayer->HitTimeCheck();
		return;
	}

	else if (true == TBLeftCollision->CollisionResult("WhitePlayerRight", ColList, CollisionType::Rect, CollisionType::Rect)
		&& MoveDir_.x != 0.0f)
	{
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		WhitePlayer::MainWhitePlayer->GetDir() = float4::ZERO;
		WhitePlayer::MainWhitePlayer->ChangeState(WhitePlayerState::Idle);
		WhitePlayer::MainWhitePlayer->Off();
		BigPlayer::MainBigPlayer->SetPosition(BigPlayer::MainBigPlayer->GetPosition());
		BigPlayer::MainBigPlayer->On();
		BigPlayer::MainBigPlayer->NoHit();

		//Player::MainPlayer->GetRenderer1()->SetAlpha(122); //내가 이미지 알파 설정을 안함..ㅠ

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