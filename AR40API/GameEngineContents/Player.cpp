#include "Player.h"
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

Player::Player()
	: Speed_(20.0f)
	, AccSpeed_(40.0f)
	, MoveDir(float4::ZERO)
	, PlayerDir_(float4::RIGHT)
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
		case Idle:
			IdleStart();
			break;
		case Move:
			MoveStart();
			break;
		case Jump:
			JumpStart();
			break;
		case Max:
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
	case Idle:
		IdleUpdate();
		
		break;
	case Move:
		MoveUpdate();
		
		break;
	case Jump:
		JumpUpdate();

		break;
	case Max:
		break;
	default:
		break;
	}
}


void Player::Start()
{
	//Player위치는 중앙으로 고정
	//SetPosition(GameEngineWindow::GetScale().Half());
	//선생님 왈 여기다 지정하면 안됨(스테이지 진입할때마다 다르니까)
	SetScale({ 64,64 });

	PlayerHeadCollision = CreateCollision("PlayerHead", { 50, 2 },{0,-31});
	PlayerCollision = CreateCollision("PlayerHitBox", { 50, 61 });
	PlayerFootCollision = CreateCollision("PlayerFoot", { 50, 2 }, { 0,32 });

	//애니메이션을 하나라도 만들면 애니메이션도 재생된다
	PlayerAnimationRender = CreateRenderer();
	//0~1인덱스 0.1초마다(true면 반복,false면 한번만재생)
	PlayerAnimationRender->CreateAnimation("walk-R.bmp", "Walk-R", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("walk-L.bmp", "Walk-L", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("idle-R.bmp", "idle-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("idle-L.bmp", "idle-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("jump-L.bmp", "Jump-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("jump-R.bmp", "Jump-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("break-L.bmp", "Break-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("break-R.bmp", "Break-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->ChangeAnimation("idle-R");


	if (false == GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false면 만들어진 적 없는 키 이다

		GameEngineInput::GetInst()->CreateKey("Move Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Move Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Move Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", 'X');
		GameEngineInput::GetInst()->CreateKey("Run", 'C');
		GameEngineInput::GetInst()->CreateKey("Fire", 'Z');
	}
}


void Player::Update()
{
	// //식물이 자라는거라고 하면
	// //GetAccTime() 이 오브젝트가 몇초간 살아있었느냐.
	//if (5.0f <= GetAccTime())
	//{
	//	ReSetAccTime();
	//	int a = 0;
	//}

	Fire();//총알 발사함수
	StateUpdate();

	WallCheck();
	DoorCheck();

	//{	//맵과 캐릭터의 충돌설정용
	//	
	//	MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");
	//	

	//	if (nullptr == MapColImage_)
	//	{
	//		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
	//	}
	//}

	//	if (1000.0f <= MoveDir_.Len2D())
	//	{	//속도 최대치 제한
	//		MoveDir_.Range2D(1000.0f);
	//	}

	//	if (MoveDir_.Len2D() >= 100)
	//	{
	//		//속도 최대치 정규화
	//		MoveDir_.Normal2D();
	//	}

}


void Player::WallCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();//나랑 충돌한 벽들 다 주거
		}
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
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();//나랑 충돌한 템은 사라짐
		}
		int a = 0;
	}
}

//랜더러가 다 돌아가고 랜더링 된다
void Player::Render()
{


}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
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

void Player::FootCheck()
{
	//내 미래위치
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//그때 내 발바닥 위치
	CheckPos_ = NextPos_ + float4(0.0f, 32.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Player::Fire()
{
	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetDir(CurDir());
	}
}
