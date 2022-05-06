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

#include <GameEngine/GameEngineLevel.h>//레벨을 통해서
#include "Bullet.h"//총알을 만들고 싶다

Player* Player::MainPlayer = nullptr;
bool Player::ChangeLevel_ = false;

Player::Player()
	: Speed_(20.0f)
	, AccSpeed_(40.0f)
	, MoveDir(float4::ZERO)
	, PlayerDir_(float4::RIGHT)
	, DirString("R")
	, Time_(0.0f)
	, HitTime_(0.0f)

{

}

Player::~Player()
{

}

// 아무키도 눌리지 않았다면 false
// 아무키든 눌렸다면 true
bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("Move Left") &&
		false == GameEngineInput::GetInst()->IsPress("Move Right"))

	{
		return false;
	}

	return true;
}

void Player::ChangeState(PlayerState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Fall:
			FallStart();
			break;
		case PlayerState::Max:
			break;
		default:
			break;
		}
	}

	CurState_ = _State;
}

void Player::StateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		
		break;
	case PlayerState::Move:
		MoveUpdate();
		
		break;

	case PlayerState::Fall:
		FallUpdate();

		break;
	case PlayerState::Jump:
		JumpUpdate();

		break;
	case PlayerState::Max:
		break;
	default:
		break;
	}
}


void Player::Start()
{
	SetScale({ 64,64 });

	//몬스터 카메라 범위안에 있을때 움직이기용					 1300
	PlayerCameraCollision = CreateCollision("PlayerCamera", {1400, 2048 }, {200, -50});//200,-200이 플레이어 기준 딱 한가운데(-50인 이유는 점프땜에)
	PlayerHeadHitCollision = CreateCollision("PlayerHeadHit", { 1, 0 }, { 0,-33 });//박스 충돌용(1개만 충돌하게끔)
	PlayerHeadCollision = CreateCollision("PlayerHead", { 64, 1 },{0,-32});
	PlayerFootCollision = CreateCollision("PlayerFoot", { 64, 1 }, { 0,32 });
	PlayerFootHitCollision = CreateCollision("PlayerFootHit", { 54, 2 }, { 0,33 });//몹 충돌용(1마리만 밟게끔)
	PlayerLeftCollision = CreateCollision("PlayerLeft", { 2, 63 }, { -32,0 });//두께 2로해야 탑이나 봇에 안겹쳐용~
	PlayerRightCollision = CreateCollision("PlayerRight", { 2, 63 }, { 32,0 });
	PlayerCollision = CreateCollision("PlayerHitBox", { 50, 60 });

	//애니메이션을 하나라도 만들면 애니메이션도 재생된다
	PlayerAnimationRender = CreateRenderer((int)ORDER::PLAYER);
	//0~1인덱스 0.1초마다(true면 반복,false면 한번만재생)
	PlayerAnimationRender->CreateAnimation("walk-R.bmp", "Walk-R", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("walk-L.bmp", "Walk-L", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("idle-R.bmp", "idle-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("idle-L.bmp", "idle-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("jump-L.bmp", "Jump-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("jump-R.bmp", "Jump-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("break-L.bmp", "Break-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("break-R.bmp", "Break-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("die.bmp", "Die", 0, 0, 0.0f, false);
	PlayerAnimationRender->ChangeAnimation("idle-R");


	if (false == GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false면 만들어진 적 없는 키 이다

		GameEngineInput::GetInst()->CreateKey("Move Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Move Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Move Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", 'X');
		GameEngineInput::GetInst()->CreateKey("NoHit", 'C');
		GameEngineInput::GetInst()->CreateKey("OnHit", 'E');
		GameEngineInput::GetInst()->CreateKey("Fire", 'Z');
	}

}


void Player::Update()
{
	//Fire();//총알 발사함수
	SetColImage();
	StateUpdate();

	WallCheck();
	DoorCheck();
	MushroomCheck();
	FireFlowerCheck();
	MonsterOnCheck();
	TurtleOnCheck();
	MonsterHit();
	FallDead();

	HitTime_ -= GameEngineTime::GetDeltaTime();
	
	if (HitTime_ < 0.0f)
	{
		OnHit();
	}
	Muuzuk();
}


void Player::WallCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect)&& 
		true == GameEngineInput::GetInst()->IsPress("Move Down"))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();//콜리젼 사라지고 맵이동
		}
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		GameEngine::GetInst().ChangeLevel("Pipe1");
		ChangeLevel_ = true;
	}

	if (true == PlayerCollision->CollisionResult("Wall-L", ColList, CollisionType::Rect, CollisionType::Rect) &&
		true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();//콜리젼 사라지고 맵이동
		}
		GameEngineSound::SoundPlayOneShot("smb_pipe.wav");
		GameEngine::GetInst().ChangeLevel("Play1");
		ChangeLevel_ = true;
	}
}

void Player::DoorCheck()
{
	if (true == PlayerCollision->CollisionCheck("Door", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Play2");
	}
}

void Player::MushroomCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == PlayerCollision->CollisionResult("Mushroom", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup.wav");
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 템은 사라짐
		}
		MainPlayer->MoveDir = float4::ZERO;
		MainPlayer->ChangeState(PlayerState::Idle);
		MainPlayer->Off();
		BigPlayer::MainBigPlayer->SetPosition(GetPosition() + float4{ 0, -32 });
		BigPlayer::MainBigPlayer->On();
	}
}

void Player::FireFlowerCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == PlayerCollision->CollisionResult("FireFlower", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup.wav");
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 템은 사라짐
		}
		MainPlayer->MoveDir = float4::ZERO;
		MainPlayer->ChangeState(PlayerState::Idle);
		MainPlayer->Off();
		WhitePlayer::MainWhitePlayer->SetPosition(GetPosition() + float4{ 0, -32 });
		WhitePlayer::MainWhitePlayer->On();
	}
}

void Player::MonsterOnCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerFootHitCollision->CollisionResult("MonsterHead", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 몬스터 주겅
		}
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		//MainPlayer->JumpStart();//점프소리나는 문제
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		MoveDir.y = -10.0f;//약간의 높이 조절
		ChangeState(PlayerState::Fall);
	}
}

void Player::TurtleOnCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerFootHitCollision->CollisionResult("TurtleHead", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		//MainPlayer->JumpStart();//점프소리나는 문제
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		MoveDir.y = -10.0f;//약간의 높이 조절
		ChangeState(PlayerState::Fall);
	}
}

void Player::TBOnCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerFootHitCollision->CollisionResult("TBHead-L", ColList, CollisionType::Rect, CollisionType::Rect)||
		true == PlayerFootHitCollision->CollisionResult("TBHead-R", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_kick.wav");
		//MainPlayer->JumpStart();//점프소리나는 문제
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
		MoveDir.y = -10.0f;//약간의 높이 조절
		ChangeState(PlayerState::Fall);
	}
}



//랜더러가 다 돌아가고 랜더링 된다
void Player::Render()
{


}


void Player::CameraOutCheck()
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

void Player::FootCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 32.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Player::HeadCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 머리 위치
	CheckPos_ = NextPos_ + float4(0.0f, -22.0f);//머리는 실제이미지 -10픽셀 해야 좀 부딪히는거같음
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Player::LeftCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(-26.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_ /*+ float4{ -1.0f,0.0f }*/);
}

void Player::RightCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(26.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);//한픽셀 앞을 체크하자..점프가안되..
}


void Player::BreakAnimation()
{
	{	//왼쪽에서 오른쪽으로 틀때
		if (MoveDir.x < 0 && true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			PlayerAnimationRender->ChangeAnimation("Break-L");
		}
		else if (MoveDir.x > 0 && true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			PlayerAnimationRender->ChangeAnimation("Walk-R");
		}
	}

	{
		//오른쪽에서 왼쪽으로 틀때
		if (MoveDir.x > 0 && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			PlayerAnimationRender->ChangeAnimation("Break-R");
		}
		else if (MoveDir.x < 0 && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			PlayerAnimationRender->ChangeAnimation("Walk-L");
		}
	}
}

void Player::MonsterHit()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		PlayerDie* die = GetLevel()->CreateActor<PlayerDie>();
		die->SetPosition(GetPosition());
		MainPlayer->Death();
		MainPlayer = nullptr;
		BigPlayer::MainBigPlayer->Death();
		BigPlayer::MainBigPlayer = nullptr;
		WhitePlayer::MainWhitePlayer->Death();
		WhitePlayer::MainWhitePlayer = nullptr;
		//ChangeState(PlayerState::Dead);
		return;
	}
}


void Player::FallDead()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("Die", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		PlayerDie* die = GetLevel()->CreateActor<PlayerDie>();
		die->SetPosition(GetPosition());
		//PlayerCollision->GetActor()->Death();
		MainPlayer->Death();
		MainPlayer = nullptr;
		BigPlayer::MainBigPlayer->Death();
		BigPlayer::MainBigPlayer = nullptr;
		WhitePlayer::MainWhitePlayer->Death();
		WhitePlayer::MainWhitePlayer = nullptr;
		return;
	}
}

void Player::HitTimeCheck()
{

	MainPlayer->HitTime_ = 3.0f;
}

void Player::Muuzuk()
{
	if (true == GameEngineInput::GetInst()->IsPress("NoHit"))
	{
		PlayerCollision->Off();
	}
}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}