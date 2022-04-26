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

WhitePlayer* WhitePlayer::MainWhitePlayer = nullptr;

WhitePlayer::WhitePlayer()
	: Speed_(20.0f)
	, AccSpeed_(40.0f)
	, MoveDir(float4::ZERO)
	, WhitePlayerDir_(float4::RIGHT)
	, WhiteDirString("R")
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
	case WhitePlayerState::Max:
		break;
	default:
		break;
	}
}


void WhitePlayer::Start()
{
	//WhitePlayer위치는 중앙으로 고정
	//SetPosition(GameEngineWindow::GetScale().Half());
	//선생님 왈 여기다 지정하면 안됨(스테이지 진입할때마다 다르니까)
	SetScale({ 64,128 });

	WhitePlayerCollision = CreateCollision("WhitePlayerHitBox", { 50, 128 });

	//애니메이션을 하나라도 만들면 애니메이션도 재생된다
	WhitePlayerAnimationRender = CreateRenderer();
	//0~1인덱스 0.1초마다(true면 반복,false면 한번만재생)
	WhitePlayerAnimationRender->CreateAnimation("fire-walk-R.bmp", "WWalk-R", 0, 2, 0.1f, true);
	WhitePlayerAnimationRender->CreateAnimation("fire-walk-L.bmp", "WWalk-L", 0, 2, 0.1f, true);
	WhitePlayerAnimationRender->CreateAnimation("fire-idle-R.bmp", "Widle-R", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-idle-L.bmp", "Widle-L", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-jump-L.bmp", "WJump-L", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-jump-R.bmp", "WJump-R", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("FireAttack-L.bmp", "Fire-L", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("FireAttack-R.bmp", "Fire-R", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-break-L.bmp", "WBreak-L", 0, 0, 0.0f, false);
	WhitePlayerAnimationRender->CreateAnimation("fire-break-R.bmp", "WBreak-R", 0, 0, 0.0f, false);
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
}


void WhitePlayer::Update()
{
	
	Fire();//총알 발사함수
	StateUpdate();

	WallCheck();
	DoorCheck();
	MushroomCheck();
	FireFlowerCheck();
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
	}
}

//랜더러가 다 돌아가고 랜더링 된다
void WhitePlayer::Render()
{


}

void WhitePlayer::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainWhitePlayer = this;
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

void WhitePlayer::FootCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 64.0f);
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
	}
}
