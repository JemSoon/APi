#include "WhitePlayer.h"
#include "BigPlayer.h"
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

WhitePlayer* WhitePlayer::MainWhitePlayer = nullptr;

WhitePlayer::WhitePlayer()
	: Speed_(20.0f)
	, AccSpeed_(40.0f)
	, MoveDir(float4::ZERO)
	, WhitePlayerDir_(float4::RIGHT)
	, WhiteDirString_("R")
	

{

}

WhitePlayer::~WhitePlayer()
{

}

// 아무키도 눌리지 않았다면 false
// 아무키든 눌렸다면 true
bool WhitePlayer::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("Move Left") &&
		false == GameEngineInput::GetInst()->IsPress("Move Right"))

	{
		return false;
	}

	return true;
}

void WhitePlayer::ChangeState(WhitePlayerState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case WhitePlayerState::Idle:
			IdleStart();
			break;
		case WhitePlayerState::Move:
			MoveStart();
			break;
		case WhitePlayerState::Jump:
			JumpStart();
			break;
		case WhitePlayerState::Fall:
			FallStart();
			break;
		case WhitePlayerState::Max:
			break;
		default:
			break;
		}
	}

	CurState_ = _State;
}

void WhitePlayer::StateUpdate()
{
	switch (CurState_)
	{
	case WhitePlayerState::Idle:
		IdleUpdate();

		break;
	case WhitePlayerState::Move:
		MoveUpdate();

		break;
	case WhitePlayerState::Jump:
		JumpUpdate();

		break;
	case WhitePlayerState::Fall:
		FallUpdate();

		break;
	case WhitePlayerState::Max:
		break;
	default:
		break;
	}
}


void WhitePlayer::Start()
{
	SetScale({ 64,128 });

	WhitePlayerCameraCollision = CreateCollision("PlayerCamera", { 1, 1280 }, { 200, -50 });

	WhitePlayerHeadHitCollision = CreateCollision("WhitePlayerHeadHit", { 1, 0 }, { 0,-65 });//박스 충돌용(1개만 충돌하게끔)
	WhitePlayerHeadCollision = CreateCollision("PlayerHead", { 64, 1 }, { 0,-64 });
	WhitePlayerFootCollision = CreateCollision("PlayerFoot", { 64, 1 }, { 0,64 });
	WhitePlayerFootHitCollision = CreateCollision("PlayerFootHit", { 1, 0 }, { 0,65 });//몹 충돌용(1마리만 밟게끔)
	WhitePlayerLeftCollision = CreateCollision("PlayerLeft", { 2, 127 }, { -32,0 });//두께 2로해야 탑이나 봇에 안겹쳐용~
	WhitePlayerRightCollision = CreateCollision("PlayerRight", { 2, 127 }, { 32,0 });

	WhitePlayerCollision = CreateCollision("WhitePlayerHitBox", { 50, 128 });
	WhitePlayerDownCollision = CreateCollision("WhitePlayerDownHitBox", { 50, 80 }, { 0,22 });

	//애니메이션을 하나라도 만들면 애니메이션도 재생된다
	WhitePlayerAnimationRender = CreateRenderer((int)ORDER::PLAYER);
	//0~1인덱스 0.1초마다(true면 반복,false면 한번만재생)
	WhitePlayerAnimationRender->CreateAnimation("fire-walk-R.bmp", "WWalk-R", 0, 2, 0.1f, true);
	WhitePlayerAnimationRender->CreateAnimation("fire-walk-L.bmp", "WWalk-L", 0, 2, 0.1f, true);
	WhitePlayerAnimationRender->CreateAnimation("fire-idle-R.bmp", "Widle-R", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-idle-L.bmp", "Widle-L", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-jump-L.bmp", "WJump-L", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-jump-R.bmp", "WJump-R", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-break-L.bmp", "WBreak-L", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-break-R.bmp", "WBreak-R", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("FireAttack-L.bmp", "WFire-L", 0, 0, 1.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("FireAttack-R.bmp", "WFire-R", 0, 0, 1.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("white-down-R.bmp", "WDown-R", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("white-down-L.bmp", "WDown-L", 0, 0, 0.0f, false);

	WhitePlayerAnimationRender->ChangeAnimation("Widle-R");


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
	MainWhitePlayer = this;
	//나는 this 어차피 하나만 만들어지니까
}


void WhitePlayer::Update()
{
	Fire();//총알 발사함수
	StateUpdate();

	WallCheck();
	DoorCheck();
	MushroomCheck();
	FireFlowerCheck();
	MonsterOnCheck();
	MonsterHit();

	//HitTime_ -= GameEngineTime::GetDeltaTime();

}


void WhitePlayer::WallCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == WhitePlayerCollision->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();//나랑 충돌한 벽들 다 주거
		}
	}
}

void WhitePlayer::DoorCheck()
{
	if (true == WhitePlayerCollision->CollisionCheck("Door", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Play2");
	}
}

void WhitePlayer::MushroomCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == WhitePlayerCollision->CollisionResult("Mushroom", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 템은 사라짐
		}
	}
}

void WhitePlayer::FireFlowerCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == WhitePlayerCollision->CollisionResult("FireFlower", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 템은 사라짐
		}
		MainWhitePlayer->Off();
		WhitePlayer::MainWhitePlayer->SetPosition(GetPosition());
		WhitePlayer::MainWhitePlayer->On();
	}
}

//랜더러가 다 돌아가고 랜더링 된다
void WhitePlayer::Render()
{


}


void WhitePlayer::CameraOutCheck()
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

void WhitePlayer::FootCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 64.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void WhitePlayer::HeadCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 머리 위치
	CheckPos_ = NextPos_ + float4(0.0f, -54.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void WhitePlayer::LeftCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(-26.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void WhitePlayer::RightCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(26.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void WhitePlayer::Fire()
{
	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetDir(CurDir());

		if (CurState_ == WhitePlayerState::Idle)
		{
			WhitePlayerAnimationRender->ChangeAnimation("WFire-" + WhiteDirString);
		}
	}
}

void WhitePlayer::BreakAnimation()
{
	{	//왼쪽에서 오른쪽으로 틀때
		if (MoveDir.x < 0 && true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			WhitePlayerAnimationRender->ChangeAnimation("WBreak-L");
		}
		else if (MoveDir.x > 0 && true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			WhitePlayerAnimationRender->ChangeAnimation("WWalk-R");
		}
	}

	{
		//오른쪽에서 왼쪽으로 틀때
		if (MoveDir.x > 0 && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			WhitePlayerAnimationRender->ChangeAnimation("WBreak-R");
		}
		else if (MoveDir.x < 0 && true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			WhitePlayerAnimationRender->ChangeAnimation("WWalk-L");
		}
	}
}

void WhitePlayer::MonsterOnCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == WhitePlayerFootHitCollision->CollisionResult("MonsterHead", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//나랑 충돌한 몬스터 주겅
		}
		MainWhitePlayer->JumpStart();
		MoveDir.y = -10.0f;//약간의 높이 조절
		ChangeState(WhitePlayerState::Fall);
	}
}

void WhitePlayer::MonsterHit()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == WhitePlayerCollision->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		MainWhitePlayer->MoveDir = float4::ZERO;
		MainWhitePlayer->ChangeState(WhitePlayerState::Idle);
		MainWhitePlayer->Off();
		BigPlayer::MainBigPlayer->SetPosition(GetPosition());
		BigPlayer::MainBigPlayer->On();

		BigPlayer::MainBigPlayer->NoHit();

		//Player::MainPlayer->GetRenderer1()->SetAlpha(244); //내가 이미지 알파 설정을 안함..ㅠ

		BigPlayer::MainBigPlayer->HitTimeCheck();
	}

}

void WhitePlayer::FallDead()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == WhitePlayerCollision->CollisionResult("Die", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		PlayerDie* die = GetLevel()->CreateActor<PlayerDie>();
		die->SetPosition(GetPosition());
		WhitePlayerCollision->GetActor()->Death();
		//ChangeState(PlayerState::Dead);
		return;
	}
}

//void WhitePlayer::HitTimeCheck()
//{
//	MainWhitePlayer->HitTime_ = 3.0f;
//}


void WhitePlayer::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainWhitePlayer = this;
}

