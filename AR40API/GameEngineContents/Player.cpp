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

Player::Player()
	:Speed_(150.0f)
	,Gravity_(100.0f)
{

}

Player::~Player()
{

}

//아무키도 눌리지 않았다면 false
//아무키던 눌렸다면 ture
bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsDown("Move Left") &&
		false == GameEngineInput::GetInst()->IsDown("Move Right") &&
		false == GameEngineInput::GetInst()->IsDown("Move Down") &&
		false == GameEngineInput::GetInst()->IsDown("Move Up") &&
		false == GameEngineInput::GetInst()->IsDown("Jump") &&
		false == GameEngineInput::GetInst()->IsDown("Run") &&
		false == GameEngineInput::GetInst()->IsDown("Fire"))
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
		case Attack:
			AttackStart();
			break;
		case Move:
			MoveStart();
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
	case Attack:
		AttackUpdate();
		break;
	case Move:
		MoveUpdate();
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
	//SetScale({ 64,64 });

	//PlayerCollision = CreateCollision("PlayerHitBox", {64, 64});

	//애니메이션을 하나라도 만들면 애니메이션도 재생된다
	PlayerAnimationRender = CreateRenderer();
	//0~1인덱스 0.1초마다(true면 반복,false면 한번만재생)
	PlayerAnimationRender->CreateAnimation("walk-R.bmp", "Walk-R", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("walk-L.bmp", "Walk-L", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("idle-R.bmp", "idle-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("idle-L.bmp", "idle-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->ChangeAnimation("idle-R");

	CurDir_ = PlayerDir::Start;

	if (false == GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false면 만들어진 적 없는 키 이다

		GameEngineInput::GetInst()->CreateKey("Move Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Move Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Move Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Move Up", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Jump", 'X');
		GameEngineInput::GetInst()->CreateKey("Run", 'C');
		GameEngineInput::GetInst()->CreateKey("Fire", 'Z');
	}
}
 

void Player::Update()
{
	DirAnimationCheck();
	PlayerStateUpdate();
	StateUpdate();

	{	//맵과 캐릭터의 충돌설정용
		//(참고)실제 BG랑 좌표가 안맞음 현재
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}

	float4 CheckPos;
	float4 MoveDir = float4::ZERO;

	//{	//움직임 조작
	//	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	//	{
	//		MoveDir = float4::LEFT;

	//		//현재 위치 + 이동하는 방향
	//		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//		if (true == GameEngineInput::GetInst()->IsPress("Run"))
	//		{
	//			Speed_ = 1800.0f;
	//		}
	//		else
	//		{
	//			Speed_ = 150.0f;
	//		}
	//	}

	//	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	//	{
	//		MoveDir = float4::RIGHT;

	//		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//		if (true == GameEngineInput::GetInst()->IsPress("Run"))
	//		{
	//			Speed_ = 1800.0f;
	//		}
	//		else
	//		{
	//			Speed_ = 150.0f;
	//		}
	//	}

	//	if (true == GameEngineInput::GetInst()->IsPress("Move Up"))
	//	{	
	//		MoveDir = float4::UP;

	//		//SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	//		if (true == GameEngineInput::GetInst()->IsPress("Run"))
	//		{
	//			Speed_ = 450.0f;
	//		}
	//		else
	//		{
	//			Speed_ = 150.0f;
	//		}
	//	}

	//	if (true == GameEngineInput::GetInst()->IsPress("Move Down"))
	//	{	
	//		MoveDir = float4::DOWN;

	//		//SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	//		if (true == GameEngineInput::GetInst()->IsPress("Run"))
	//		{
	//			Speed_ = 450.0f;
	//		}
	//		else
	//		{
	//			Speed_ = 150.0f;
	//		}
	//	}
	//}

	{	//내 미래위치
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		//그 때 발바닥 위치
		float4 CheckPos = NextPos + float4(0.0f, 32.0f);

		int Color = MapColImage_->GetImagePixel(CheckPos);//갈수 있냐 없냐 색 체크

		if (RGB(255,0,0) != Color)
		{	//빨간색이 아니라면 갈수 이써
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}	
	}
	//플레이어가 카메라 중심에 있길 원하면 그만큼 위치를 더하거나 뺀다
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half()-float4(-200.0f, 200.0f));

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
	float MapSizeY = 1920;//맵 세로 끝
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

	//WallCheck();
	//DoorCheck();



	//if (true== PlayerCollision->Collision("Door"))//문과 충돌 했다면
	//{
	//	PlayerCollision->Collision("Door");
	//}

	//{	//중력 관련
	//	//내 포지션에서 (CENTER중심이라 바닥 기준이니 32아래로)
	//int Color = MapColImage_->GetImagePixel(GetPosition() + float4(0.0f, 32.0f));

	//충돌 설정 인터페이스
	//1.우선 충돌체를 만든다(랜더러와 똑같음)
	//이동하고 나서 a=0이되려면 여기 이동하기전에 하려면 업데이트에
	//GameEngineCollision* MyCollision;
	//if (true == MyCollision->Collision("Door"))
	//{
	//	int a = 0;
	//}

	//	//중력
	//	AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;//점점 가속됨
	//	
	//	if (RGB(255, 0, 0)==Color/*땅에 닿았다면(빨간색)*/)
	//	{
	//		AccGravity_ = 0.0f;//문제-중력0되면 밑에 이동이 0이되서 땅에 닿으면 이동못함
	//	}
	//	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);
	//}

	//if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	//{
	//	SetScale({ 32,32 });

	//	Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
	//	Ptr->SetPosition(GetPosition());
	//	
	//	//플레이어가 보는 방향으로 총알방향을 바꾸고싶은데 안됨
	//	if (CurDir_ == PlayerDir::Start || CurDir_ == PlayerDir::Right)
	//	{
	//		//Ptr->SetMove((float4::RIGHT * GameEngineTime::GetDeltaTime() * 450.0f) + (float4::DOWN * GameEngineTime::GetDeltaTime() * 300.0f));
	//		Ptr->SetDir();
	//	}

	//	if (CurDir_ == PlayerDir::Left)
	//	{
	//		Ptr->SetMove((float4::LEFT * GameEngineTime::GetDeltaTime() * 450.0f) + (float4::DOWN * GameEngineTime::GetDeltaTime() * 300.0f));
	//	}

	//}


	///*if (2.0f < GameEngineInput::GetInst()->GetTime("Fire")) 2초간 기모으고 연사쏘기
	//{
	//	SetScale({ 32,32 });

	//	Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
	//	Ptr->SetPosition(GetPosition());

	//}*/

}


//랜더러가 다 돌아가고 랜더링 된다
void Player::Render()
{
	
	
}

//void Player::WallCheck()
//{
//	std::vector<GameEngineCollision*> ColList;
//
//	if (true == PlayerCollision->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect))
//	{
//		for (size_t i = 0; i < ColList.size(); i++)
//		{
//			ColList[i]->Death();//나랑 충돌한 벽들 다 주거
//		}
//	}
//}

//void Player::DoorCheck()
//{
//	if (true == PlayerCollision->CollisionCheck("Door", CollisionType::Rect, CollisionType::Rect))
//	{
//		GameEngine::GetInst().ChangeLevel("Play2");
//	}
//}

void Player::DirAnimationCheck()
{
	std::string ChangeName;

	PlayerDir CheckDir_ = CurDir_;
	std::string ChangeDirText = "R";

	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	{
		CheckDir_ = PlayerDir::Right;
		ChangeName = "Walk-";
		ChangeDirText = "R";
	}
	else if (true == GameEngineInput::GetInst()->IsUp("Move Right"))
	{
		CheckDir_ = PlayerDir::Right;
		ChangeName = "idle-";
		ChangeDirText = "R";
	}

	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	{
		CheckDir_ = PlayerDir::Left;
		ChangeName = "Walk-";
		ChangeDirText = "L";
	}
	else if (true == GameEngineInput::GetInst()->IsUp("Move Left"))
	{
		CheckDir_ = PlayerDir::Left;
		ChangeName = "idle-";
		ChangeDirText = "L";
	}

	if (CheckDir_ != CurDir_)
	{
		PlayerAnimationRender->ChangeAnimation(ChangeName + ChangeDirText);
	}
}

void Player::PlayerStateUpdate()
{

}