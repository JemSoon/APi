#include "BigPlayer.h"
#include "Player.h"
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

#include <GameEngine/GameEngineLevel.h>//레벨을 통해서
#include "Bullet.h"//총알을 만들고 싶다

BigPlayer* BigPlayer::MainBigPlayer = nullptr;
bool BigPlayer::ClearSongOn_ = false;

BigPlayer::BigPlayer()
	: Speed_(20.0f)
	, AccSpeed_(40.0f)
	, MoveDir(float4::ZERO)
	, BigPlayerDir_(float4::RIGHT)
	, BigDirString("R")
	, HitTime_(0.0f)
	, Time_(3.0f)
	, LevelClear_(5.0f)
	, Clear_(false)
	, OneCheck_(false)
{

}

BigPlayer::~BigPlayer()
{

}

// 아무키도 눌리지 않았다면 false
// 아무키든 눌렸다면 true
bool BigPlayer::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("Move Left") &&
		false == GameEngineInput::GetInst()->IsPress("Move Right"))

	{
		return false;
	}

	return true;
}

void BigPlayer::ChangeState(BigPlayerState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case BigPlayerState::Idle:
			IdleStart();
			break;
		case BigPlayerState::Move:
			MoveStart();
			break;
		case BigPlayerState::Jump:
			JumpStart();
			break;
		case BigPlayerState::Fall:
			FallStart();
			break;
		case BigPlayerState::Max:
			break;
		default:
			break;
		}
	}

	CurState_ = _State;
}

void BigPlayer::StateUpdate()
{
	switch (CurState_)
	{
	case BigPlayerState::Idle:
		IdleUpdate();

		break;
	case BigPlayerState::Move:
		MoveUpdate();

		break;
	case BigPlayerState::Jump:
		JumpUpdate();

		break;
	case BigPlayerState::Fall:
		FallUpdate();

		break;
	case BigPlayerState::Max:
		break;
	default:
		break;
	}
}


void BigPlayer::Start()
{
	SetScale({ 64,128 });

	BigPlayerCameraCollision = CreateCollision("PlayerCamera", { 1600, 2048 }, { 200, -50 });

	BigPlayerHeadHitCollision = CreateCollision("BigPlayerHeadHit", { 1, 2 }, { 0,-65 });//박스 충돌용(1개만 충돌하게끔)
	BigPlayerHeadCollision = CreateCollision("PlayerHead", { 64, 1 }, { 0,-64 });
	BigPlayerFootCollision = CreateCollision("PlayerFoot", { 64, 1 }, { 0,64 });
	BigPlayerFootHitCollision = CreateCollision("PlayerFootHit", { 54, 2 }, { 0,65 });//몹 충돌용(1마리만 밟게끔)
	BigPlayerLeftCollision = CreateCollision("BigPlayerLeft", { 2, 127 }, { -34,0 });//두께 2로해야 탑이나 봇에 안겹쳐용~
	BigPlayerRightCollision = CreateCollision("BigPlayerRight", { 2, 127 }, { 34,0 });

	BigPlayerCollision = CreateCollision("BigPlayerHitBox", { 50, 128 });
	BigPlayerDownCollision = CreateCollision("BigPlayerDownHitBox", { 50, 80 },{0,22});

	//애니메이션을 하나라도 만들면 애니메이션도 재생된다
	BigPlayerAnimationRender = CreateRenderer((int)ORDER::PLAYER);
	//0~1인덱스 0.1초마다(true면 반복,false면 한번만재생)
	BigPlayerAnimationRender->CreateAnimation("big-walk-R.bmp", "BWalk-R", 0, 2, 0.1f, true);
	BigPlayerAnimationRender->CreateAnimation("big-walk-L.bmp", "BWalk-L", 0, 2, 0.1f, true);
	BigPlayerAnimationRender->CreateAnimation("big-idle-R.bmp", "Bidle-R", 0, 0, 0.0f, false);
	BigPlayerAnimationRender->CreateAnimation("big-idle-L.bmp", "Bidle-L", 0, 0, 0.0f, false);
	BigPlayerAnimationRender->CreateAnimation("big-jump-L.bmp", "BJump-L", 0, 0, 0.0f, false);
	BigPlayerAnimationRender->CreateAnimation("big-jump-R.bmp", "BJump-R", 0, 0, 0.0f, false);
	BigPlayerAnimationRender->CreateAnimation("big-break-L.bmp", "BBreak-L", 0, 0, 0.0f, false);
	BigPlayerAnimationRender->CreateAnimation("big-break-R.bmp", "BBreak-R", 0, 0, 0.0f, false);
	BigPlayerAnimationRender->CreateAnimation("big-down-R.bmp", "BDown-R", 0, 0, 0.0f, false);
	BigPlayerAnimationRender->CreateAnimation("big-down-L.bmp", "BDown-L", 0, 0, 0.0f, false);
	BigPlayerAnimationRender->CreateAnimation("big-flag.bmp", "Flag", 0, 1, 0.1f, true);
	BigPlayerAnimationRender->ChangeAnimation("Bidle-R");


	if (false == GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false면 만들어진 적 없는 키 이다

		GameEngineInput::GetInst()->CreateKey("Move Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Move Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Move Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", 'X');
		GameEngineInput::GetInst()->CreateKey("NoHit", 'C');
		GameEngineInput::GetInst()->CreateKey("Fire", 'Z');
	}

	Off();
	MainBigPlayer = this;
	//나는 this 어차피 하나만 만들어지니까
}


void BigPlayer::Update()
{
	SetColImage();
	StateUpdate();

	WallCheck();
	DoorCheck();
	MushroomCheck();
	UPMushroomCheck();
	FireFlowerCheck();
	MonsterOnCheck();
	MonsterHit();
	FallDead();
	TurtleOnCheck();
	TBOnCheck();

	FlagCheck();
	MapClear();

	LevelClear_ -= GameEngineTime::GetDeltaTime();
	HitTime_ -= GameEngineTime::GetDeltaTime();
	if (HitTime_ < 0.0f)
	{
		OnHit();
		//MainBigPlayer->GetRenderer1()->SetAlpha(255);
	}
	Muuzuk();
}


void BigPlayer::WallCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == BigPlayerDownCollision->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect) &&
		true == GameEngineInput::GetInst()->IsPress("Move Down"))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();//콜리젼 사라지고 맵이동
		}
		MoveDir.x = 0.0f;
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		GameEngine::GetInst().ChangeLevel("Pipe1");
		Player::ChangeLevel_ = true;
	}

	if (true == BigPlayerDownCollision->CollisionResult("Wall-L", ColList, CollisionType::Rect, CollisionType::Rect) &&
		true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();//콜리젼 사라지고 맵이동
		}
		MoveDir.x = 0.0f;
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		GameEngine::GetInst().ChangeLevel("Play1");
		Player::ChangeLevel_ = true;
	}
}

void BigPlayer::DoorCheck()
{
	if (true == BigPlayerCollision->CollisionCheck("Door", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Play2");
	}
}

void BigPlayer::MushroomCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == BigPlayerCollision->CollisionResult("Mushroom", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup.wav");
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 템은 사라짐
		}
	}
}

void BigPlayer::FireFlowerCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == BigPlayerCollision->CollisionResult("FireFlower", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup.wav");
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 템은 사라짐
		}
		MainBigPlayer->MoveDir = float4::ZERO;
		MainBigPlayer->ChangeState(BigPlayerState::Idle);
		MainBigPlayer->Off();
		WhitePlayer::MainWhitePlayer->SetPosition(GetPosition());
		WhitePlayer::MainWhitePlayer->On();
	}
}

//랜더러가 다 돌아가고 랜더링 된다
void BigPlayer::Render()
{


}


void BigPlayer::CameraOutCheck()
{
	CameraPos_.x = GetPosition().x - GameEngineWindow::GetInst().GetScale().Half().x + 200.0f;
	CameraPos_.y = GameEngineWindow::GetInst().GetScale().Half().y;
	//플레이어가 카메라 중심에 있길 원하면 그만큼 위치를 더하거나 뺀다 하지만 y축은 고정
	GetLevel()->SetCameraPos(CameraPos_);
	//GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half() - float4(-200.0f, 250.0f));

	if (0 > GetLevel()->GetCameraPos().x)
	{	//카메라가 화면 밖에 못나가게 0이하면 0으로 고정시킨다
		float4 CameraPos = GetLevel()->GetCameraPos();
		CameraPos.x = 0;
		GetLevel()->SetCameraPos(CameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)
	{	//카메라가 화면 밖에 못나가게 0이하면 0으로 고정시킨다
		float4 CameraPos = GetLevel()->GetCameraPos();
		CameraPos.y = 0;
		GetLevel()->SetCameraPos(CameraPos);
	}

	if (GetLevel()->GetNameCopy() == "Play1")
	{
		float MapSizeX = 13504;//맵 가로 오른쪽 끝
		float MapSizeY = 960;//맵 세로 끝
		float CameraRectY = 960;//카메라 세로 끝
		float CameraRectX = 1280;
		if (MapSizeX <= GetLevel()->GetCameraPos().x + CameraRectX)
		{	//카메라가 화면 밖에 못나가게
			float4 CameraPos = GetLevel()->GetCameraPos();
			CameraPos.x = (GetLevel()->GetCameraPos().x) - (GetLevel()->GetCameraPos().x + CameraRectX - MapSizeX);
			GetLevel()->SetCameraPos(CameraPos);
		}
		if (MapSizeY <= GetLevel()->GetCameraPos().y + CameraRectY)
		{	//카메라가 화면 밖에 못나가게 0이하면 0으로 고정시킨다
			float4 CameraPos = GetLevel()->GetCameraPos();
			CameraPos.y = (GetLevel()->GetCameraPos().y) - (GetLevel()->GetCameraPos().y + CameraRectY - MapSizeY);
			GetLevel()->SetCameraPos(CameraPos);
		}
	}

	else if (GetLevel()->GetNameCopy() == "Pipe1")
	{
		float MapSizeX = 1280;//맵 가로 오른쪽 끝
		float MapSizeY = 960;//맵 세로 끝
		float CameraRectY = 960;//카메라 세로 끝
		float CameraRectX = 1280;
		if (MapSizeX <= GetLevel()->GetCameraPos().x + CameraRectX)
		{	//카메라가 화면 밖에 못나가게
			float4 CameraPos = GetLevel()->GetCameraPos();
			CameraPos.x = (GetLevel()->GetCameraPos().x) - (GetLevel()->GetCameraPos().x + CameraRectX - MapSizeX);
			GetLevel()->SetCameraPos(CameraPos);
		}
		if (MapSizeY <= GetLevel()->GetCameraPos().y + CameraRectY)
		{	//카메라가 화면 밖에 못나가게 0이하면 0으로 고정시킨다
			float4 CameraPos = GetLevel()->GetCameraPos();
			CameraPos.y = (GetLevel()->GetCameraPos().y) - (GetLevel()->GetCameraPos().y + CameraRectY - MapSizeY);
			GetLevel()->SetCameraPos(CameraPos);
		}
	}
}

void BigPlayer::FootCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 64.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void BigPlayer::HeadCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 머리 위치
	CheckPos_ = NextPos_ + float4(0.0f, -54.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void BigPlayer::LeftCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(-26.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void BigPlayer::RightCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(26.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void BigPlayer::BreakAnimation()
{
	{	//왼쪽에서 오른쪽으로 틀때
		if (MoveDir.x < 0 && true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			BigPlayerAnimationRender->ChangeAnimation("BBreak-L");
		}
		else if (MoveDir.x > 0 && true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			BigPlayerAnimationRender->ChangeAnimation("BWalk-R");
		}
	}

	{
		//오른쪽에서 왼쪽으로 틀때
		if (MoveDir.x > 0 && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			BigPlayerAnimationRender->ChangeAnimation("BBreak-R");
		}
		else if (MoveDir.x < 0 && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			BigPlayerAnimationRender->ChangeAnimation("BWalk-L");
		}
	}
}

void BigPlayer::MonsterOnCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == BigPlayerFootHitCollision->CollisionResult("MonsterHead", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 몬스터 주겅
		}
		GameEngineSound::SoundPlayOneShot("smb_stomp.wav");
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		MoveDir.y = -10.0f;//약간의 높이 조절
		ChangeState(BigPlayerState::Fall);
	}
}

void BigPlayer::MonsterHit()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == BigPlayerCollision->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		MainBigPlayer->MoveDir = float4::ZERO;
		MainBigPlayer->ChangeState(BigPlayerState::Idle);
		MainBigPlayer->Off();
		Player::MainPlayer->SetPosition(GetPosition());
		Player::MainPlayer->On();
		Player::MainPlayer->NoHit();
	
		//Player::MainPlayer->GetRenderer1()->SetAlpha(122); //내가 이미지 알파 설정을 안함..ㅠ
		//작은마리오 알파값은 죽는순간 Death되서 사라지면서 Renderer와 충돌하므로 뺀다..

		Player::MainPlayer->HitTimeCheck();
	}
	
}

void BigPlayer::FallDead()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == BigPlayerCollision->CollisionResult("Die", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		PlayerDie* die = GetLevel()->CreateActor<PlayerDie>();
		die->SetPosition(GetPosition());
		MainBigPlayer->Death();
		MainBigPlayer = nullptr;
		Player::MainPlayer->Death();
		Player::MainPlayer = nullptr;
		WhitePlayer::MainWhitePlayer->Death();
		WhitePlayer::MainWhitePlayer = nullptr;
		return;
	}
}

void BigPlayer::HitTimeCheck()
{
	MainBigPlayer->HitTime_ = 3.0f;
}

void BigPlayer::Muuzuk()
{
	if (true == GameEngineInput::GetInst()->IsPress("NoHit"))
	{
		BigPlayerCollision->Off();
	}
}

void BigPlayer::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainBigPlayer = this;
}

void BigPlayer::TurtleOnCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == BigPlayerFootHitCollision->CollisionResult("TurtleHead", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		//MainPlayer->JumpStart();//점프소리나는 문제
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		MoveDir.y = -10.0f;//약간의 높이 조절
		ChangeState(BigPlayerState::Fall);
	}
}

void BigPlayer::TBOnCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == BigPlayerFootHitCollision->CollisionResult("TBHead", ColList, CollisionType::Rect, CollisionType::Rect) ||
		true == BigPlayerFootHitCollision->CollisionResult("TBHead", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		//MainPlayer->JumpStart();//점프소리나는 문제
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		MoveDir.y = -10.0f;//약간의 높이 조절
		ChangeState(BigPlayerState::Fall);
	}
}

void BigPlayer::UPMushroomCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == BigPlayerCollision->CollisionResult("UPMushroom", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_1-up.wav");
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 템은 사라짐
		}

		//목숨 +1
	}
}

void BigPlayer::FlagCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == BigPlayerCollision->CollisionResult("Flag", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		ClearSongOn_ = true;
		//Player::ClearSongOn_ = true;//기존 음악이 꺼지고 클리어 음악이 켜진다
		Time_ -= GameEngineTime::GetDeltaTime();
		BigPlayerAnimationRender->ChangeAnimation("Flag");
	/*	OneCheck_ = true;
		if (OneCheck_ == true)
		{*/
			GameEngineSound::SoundPlayOneShot("smb_flagpole.wav", 0, 0.1f);
			OneCheck_ = false;
		//}
		MoveDir = float4::DOWN * Speed_;

		if (Time_ <= 1.0f)
		{
			BigPlayerAnimationRender->ChangeAnimation("Bidle-L");
			BigPlayerCollision->GetActor()->SetPosition({ 12768.0f,760.0f });
			Clear_ = true;

		}

	}
}

void BigPlayer::MapClear()
{
	if (Clear_ == true)
	{
		BigPlayerAnimationRender->ChangeAnimation("BWalk-R");
		MoveDir = float4::RIGHT * 10.0f;
	}
}