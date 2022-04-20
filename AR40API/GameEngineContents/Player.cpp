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
	:Speed_(150.0f)
	, Gravity_(100.0f)
	, MoveDir_(float4::ZERO)
	, PlayerDir_(float4::RIGHT)
{

}

Player::~Player()
{

}

//bool Player::IsMoveKey()
//{
//	if (false == GameEngineInput::GetInst()->IsPress("Move Left") &&
//		false == GameEngineInput::GetInst()->IsPress("Move Right") &&
//		false == GameEngineInput::GetInst()->IsPress("Move Up") &&
//		false == GameEngineInput::GetInst()->IsPress("Move Down"))
//	{
//		return false;
//	}
//
//	return true;
//} 

void Player::Start()
{
	//Player위치는 중앙으로 고정
	//SetPosition(GameEngineWindow::GetScale().Half());
	//선생님 왈 여기다 지정하면 안됨(스테이지 진입할때마다 다르니까)
	SetScale({ 64,64 });

	PlayerCollision = CreateCollision("PlayerHitBox", { 64, 64 });

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
	//// 식물이 자라는거라고 하면
	//// GetAccTime() 이 오브젝트가 몇초간 살아있었느냐.
	//if (5.0f <= GetAccTime())
	//{
	//	ReSetAccTime();
	//	int a = 0;
	//}

	DirAnimationCheck();
	PlayerStateUpdate();

	{	//맵과 캐릭터의 충돌설정용
		//(참고)실제 BG랑 좌표가 안맞음 현재
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");
		

		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}

	float4 CheckPos;
	
	{	//움직임 조작
		if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
		{
			MoveDir_ += float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_;
			PlayerDir_ = float4::LEFT;//총알 발사 방향 잡기용
			//현재 위치 + 이동하는 방향
			//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			if (true == GameEngineInput::GetInst()->IsPress("Run"))
			{
				Speed_ = 50.0f;
			}
			else
			{
				Speed_ = 20.0f;
			}

		}

		if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;
			PlayerDir_ = float4::RIGHT;//총알 발사 방향 잡기용
			//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			if (true == GameEngineInput::GetInst()->IsPress("Run"))
			{
				Speed_ = 50.0f;
			}
			else
			{
				Speed_ = 20.0f;
			}
		}

		if (true == GameEngineInput::GetInst()->IsPress("Move Up"))
		{
			MoveDir_ = float4::UP;

			//SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
			if (true == GameEngineInput::GetInst()->IsPress("Run"))
			{
				Speed_ = 450.0f;
			}
			else
			{
				Speed_ = 150.0f;
			}
		}

		if (true == GameEngineInput::GetInst()->IsPress("Move Down"))
		{
			MoveDir_ = float4::DOWN;

			//SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
			if (true == GameEngineInput::GetInst()->IsPress("Run"))
			{
				Speed_ = 450.0f;
			}
			else
			{
				Speed_ = 150.0f;
			}
		
		}

		if (true == GameEngineInput::GetInst()->IsPress("Jump"))
		{
			MoveDir_ = float4::UP;
			Speed_ = 450.0f;
		}

		if (1000.0f <= MoveDir_.Len2D())
		{	//속도 최대치 제한
			MoveDir_.Range2D(1000.0f);
		}


		if (MoveDir_.Len2D() >= 100)
		{
			//속도 최대치 정규화
			MoveDir_.Normal2D();
		}

	}

	{	//내 미래위치 (Speed_는 가속력)
		float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		
		//그 때 발바닥 위치
		float4 CheckPos1 = NextPos + float4(0.0f, 32.0f);
		//그 때 머리 위치
		float4 CheckPos2 = NextPos + float4(0.0f, -32.0f);

		int Color1 = MapColImage_->GetImagePixel(CheckPos1);//갈수 있냐 없냐 색 체크
		int Color2 = MapColImage_->GetImagePixel(CheckPos2);

		if (RGB(255, 0, 0) != Color1 &&
			RGB(55, 55, 55) != Color1 && 
			RGB(0, 255, 255) != Color1 && 
			RGB(0, 255, 0) != Color1)
		{	
			//빨간색+@이 아니라면 갈수 이써
			//문제 발바닥 가운데 기준이라 머리통은 통과됨(블록 밑에서 위로 부딪힐시)
			MoveDir_ += ((-MoveDir_ * 0.9f) * GameEngineTime::GetDeltaTime());
			//마찰력 if문 걸면 이상해져서 일단 걍

			SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

			if ((MoveDir_.x < 0.0f && MoveDir_.x>-20.0f) && true == GameEngineInput::GetInst()->IsFree("Move Left")&& (GameEngineInput::GetInst()->IsPress("Run")|| GameEngineInput::GetInst()->IsFree("Run"))
				|| (MoveDir_.x > 0.0f && MoveDir_.x < 20.0f) && true == GameEngineInput::GetInst()->IsFree("Move Right")&& (GameEngineInput::GetInst()->IsPress("Run") || GameEngineInput::GetInst()->IsFree("Run")))
			{
				MoveDir_.x = 0.0f;
			}

		}
	}
	//플레이어가 카메라 중심에 있길 원하면 그만큼 위치를 더하거나 뺀다
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half() - float4(-200.0f, 250.0f));

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

	WallCheck();
	DoorCheck();



	//if (true== PlayerCollision->Collision("Door"))//문과 충돌 했다면
	//{
	//	PlayerCollision->Collision("Door");
	//}

	{	//중력 관련
		//내 포지션에서 (CENTER중심이라 바닥 기준이니 32아래로)
	int Color = MapColImage_->GetImagePixel(GetPosition() + float4(0.0f, 32.0f));

		//충돌 설정 인터페이스
		//1.우선 충돌체를 만든다(랜더러와 똑같음)
		//이동하고 나서 a=0이되려면 여기 이동하기전에 하려면 업데이트에
		//GameEngineCollision* MyCollision;
		//if (true == MyCollision->Collision("Door"))
		//{
		//	int a = 0;
		//}

		//중력
		AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;//점점 가속됨
		
		if (RGB(255, 0, 0)==Color/*땅에 닿았다면(빨간색)*/)
		{
			AccGravity_ = 0.0f;//문제-중력0되면 밑에 이동이 0이되서 땅에 닿으면 이동못함
		}
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);
	}

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
 		Ptr->SetDir(CurDir());
	}


	/*if (2.0f < GameEngineInput::GetInst()->GetTime("Fire")) 2초간 기모으고 연사쏘기
	{
		SetScale({ 32,32 });

		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());

	}*/

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
void Player::DirAnimationCheck()
{
	std::string ChangeName;

	CheckDir_ = CurDir_;
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

//랜더러가 다 돌아가고 랜더링 된다
void Player::Render()
{


}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}