#include "BigPlayer.h"
#include "Player.h"
#include "WhitePlayer.h"

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

BigPlayer::BigPlayer()
	: Speed_(20.0f)
	, AccSpeed_(40.0f)
	, MoveDir(float4::ZERO)
	, BigPlayerDir_(float4::RIGHT)
	, BigDirString("R")

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

	BigPlayerCameraCollision = CreateCollision("PlayerCamera", { 1, 1280 }, { 200, -50 });

	BigPlayerHeadHitCollision = CreateCollision("BigPlayerHeadHit", { 1, 0 }, { 0,-65 });//박스 충돌용(1개만 충돌하게끔)
	BigPlayerHeadCollision = CreateCollision("PlayerHead", { 64, 1 }, { 0,-64 });
	BigPlayerFootCollision = CreateCollision("PlayerFoot", { 64, 1 }, { 0,64 });
	BigPlayerFootHitCollision = CreateCollision("PlayerFootHit", { 1, 0 }, { 0,65 });//몹 충돌용(1마리만 밟게끔)
	BigPlayerLeftCollision = CreateCollision("PlayerLeft", { 2, 127 }, { -32,0 });//두께 2로해야 탑이나 봇에 안겹쳐용~
	BigPlayerRightCollision = CreateCollision("PlayerRight", { 2, 127 }, { 32,0 });

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
	BigPlayerAnimationRender->ChangeAnimation("Bidle-R");


	if (false == GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false면 만들어진 적 없는 키 이다

		GameEngineInput::GetInst()->CreateKey("Move Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Move Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Move Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", 'X');
		GameEngineInput::GetInst()->CreateKey("Run", 'C');
		GameEngineInput::GetInst()->CreateKey("Fire", 'Z');
	}

	Off();
	MainBigPlayer = this;
	//나는 this 어차피 하나만 만들어지니까
}


void BigPlayer::Update()
{
	//Fire();//총알 발사함수
	StateUpdate();

	WallCheck();
	DoorCheck();
	MushroomCheck();
	FireFlowerCheck();
	MonsterOnCheck();
	MonsterHit();
}


void BigPlayer::WallCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == BigPlayerCollision->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();//나랑 충돌한 벽들 다 주거
		}
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
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 템은 사라짐
		}
		MainBigPlayer->Off();
		WhitePlayer::MainWhitePlayer->SetPosition(GetPosition());
		WhitePlayer::MainWhitePlayer->On();
	}
}

//랜더러가 다 돌아가고 랜더링 된다
void BigPlayer::Render()
{


}

void BigPlayer::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainBigPlayer = this;
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

	float MapSizeX = 13504;//맵 가로 오른쪽 끝
	float MapSizeY = 960;//맵 세로 끝
	float CameraRectY = 720;//카메라 세로 끝
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

void BigPlayer::Fire()
{
	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetDir(CurDir());
	}
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
		MainBigPlayer->JumpStart();
		MoveDir.y = -10.0f;//약간의 높이 조절
		ChangeState(BigPlayerState::Fall);
	}
}

void BigPlayer::MonsterHit()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == BigPlayerCollision->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		
		MainBigPlayer->Off();
		Player::MainPlayer->SetPosition(GetPosition());
		Player::MainPlayer->On();

		Player::MainPlayer->GetCollision();
	}
	
}