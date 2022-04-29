#include "Player.h"
#include "BigPlayer.h"
#include "WhitePlayer.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h>//������ ���ؼ�
#include "Bullet.h"//�Ѿ��� ����� �ʹ�

Player* Player::MainPlayer = nullptr;

Player::Player()
	: Speed_(20.0f)
	, AccSpeed_(40.0f)
	, MoveDir(float4::ZERO)
	, PlayerDir_(float4::RIGHT)
	, DirString("R")

{

}

Player::~Player()
{

}

// �ƹ�Ű�� ������ �ʾҴٸ� false
// �ƹ�Ű�� ���ȴٸ� true
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

	PlayerHeadCollision = CreateCollision("PlayerHead", { 20, 2 },{0,-34});
	PlayerFootCollision = CreateCollision("PlayerFoot", { 64, 2 }, { 0,34 });
	PlayerLeftCollision = CreateCollision("PlayerLeft", { 2, -64 }, { -34,0 });
	PlayerRightCollision = CreateCollision("PlayerRight", { 2, 64 }, { 34,0 });
	PlayerCollision = CreateCollision("PlayerHitBox", { 64, 64 });
	//PlayerFootCollision = CreateCollision("PlayerFoot", { 50, 2 }, { 0,32 });

	//�ִϸ��̼��� �ϳ��� ����� �ִϸ��̼ǵ� ����ȴ�
	PlayerAnimationRender = CreateRenderer((int)ORDER::PLAYER);
	//0~1�ε��� 0.1�ʸ���(true�� �ݺ�,false�� �ѹ������)
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
	{	//false�� ������� �� ���� Ű �̴�

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
	Fire();//�Ѿ� �߻��Լ�
	StateUpdate();

	WallCheck();
	DoorCheck();
	MushroomCheck();
	FireFlowerCheck();
	MonsterOnCheck();
}


void Player::WallCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();//���� �浹�� ���� �� �ְ�
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
			ColList[i]->GetActor()->Death();//���� �浹�� ���� �����
		}
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
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//���� �浹�� ���� �����
		}
		MainPlayer->Off();
		WhitePlayer::MainWhitePlayer->SetPosition(GetPosition() + float4{ 0, -32 });
		WhitePlayer::MainWhitePlayer->On();
	}
}

void Player::MonsterOnCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerFootCollision->CollisionResult("MonsterHead", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();//���� �浹�� ���� �� �ְ�
		}
		MainPlayer->JumpStart();
	}
}

//�������� �� ���ư��� ������ �ȴ�
void Player::Render()
{


}


void Player::CameraOutCheck()
{
	CameraPos_.x = GetPosition().x - GameEngineWindow::GetInst().GetScale().Half().x + 200.0f;
	CameraPos_.y = GameEngineWindow::GetInst().GetScale().Half().y;
	//�÷��̾ ī�޶� �߽ɿ� �ֱ� ���ϸ� �׸�ŭ ��ġ�� ���ϰų� ���� ������ y���� ����
	GetLevel()->SetCameraPos(CameraPos_);
	//GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half() - float4(-200.0f, 250.0f));

	if (0 > GetLevel()->GetCameraPos().x)
	{	//ī�޶� ȭ�� �ۿ� �������� 0���ϸ� 0���� ������Ų��
		float4 CameraPos = GetLevel()->GetCameraPos();
		CameraPos.x = 0;
		GetLevel()->SetCameraPos(CameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)
	{	//ī�޶� ȭ�� �ۿ� �������� 0���ϸ� 0���� ������Ų��
		float4 CameraPos = GetLevel()->GetCameraPos();
		CameraPos.y = 0;
		GetLevel()->SetCameraPos(CameraPos);
	}

	float MapSizeX = 13504;//�� ���� ������ ��
	float MapSizeY = 960;//�� ���� ��
	float CameraRectY = 720;//ī�޶� ���� ��
	float CameraRectX = 1280;

	if (MapSizeX <= GetLevel()->GetCameraPos().x + CameraRectX)
	{	//ī�޶� ȭ�� �ۿ� ��������
		float4 CameraPos = GetLevel()->GetCameraPos();
		CameraPos.x = (GetLevel()->GetCameraPos().x) - (GetLevel()->GetCameraPos().x + CameraRectX - MapSizeX);
		GetLevel()->SetCameraPos(CameraPos);
	}
	if (MapSizeY <= GetLevel()->GetCameraPos().y + CameraRectY)
	{	//ī�޶� ȭ�� �ۿ� �������� 0���ϸ� 0���� ������Ų��
		float4 CameraPos = GetLevel()->GetCameraPos();
		CameraPos.y = (GetLevel()->GetCameraPos().y) - (GetLevel()->GetCameraPos().y + CameraRectY - MapSizeY);
		GetLevel()->SetCameraPos(CameraPos);
	}
}

void Player::FootCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(0.0f, 32.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Player::HeadCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �Ӹ� ��ġ
	CheckPos_ = NextPos_ + float4(0.0f, -22.0f);//�Ӹ��� �����̹��� -10�ȼ� �ؾ� �� �ε����°Ű���
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void Player::LeftCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(-26.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_ /*+ float4{ -1.0f,0.0f }*/);
}

void Player::RightCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(26.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);//���ȼ� ���� üũ����..�������ȵ�..
}

//void Player::RightBotCheck()
//{
//	//�� �̷���ġ
//	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
//	//�׶� �� �߹ٴ� ��ġ
//	CheckPos_ = NextPos_ + float4(26.0f, 32.0f);
//	Color_ = MapColImage_->GetImagePixel(CheckPos_);
//}



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

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}

void Player::HeadHitCheck()
{	
	//�� �̷���ġ
	NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos_ = NextPos_;//�浹ü�� �̹� �׷��� �����ϱ�..?���� �߰��� ���Ұ� ����..?

	if (true == PlayerHeadCollision->NextPosCollisionCheck("BoxBot", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{	//�ڽ��� �Ӹ��� �浹�ϸ�
		MoveDir.y=0.0f;
		ChangeState(PlayerState::Fall);
		return;
	}
	
	//�̰� ��ڽ�
	if (true == PlayerHeadCollision->NextPosCollisionCheck("EmptyBox", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{	
		MoveDir.y = 0.0f;
		ChangeState(PlayerState::Fall);
		return;
	}

	//if (true == PlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	//{
	//	MoveDir.y = 0.0f;
	//	if (false == GameEngineInput::GetInst()->IsPress("Move Left") &&
	//		false == GameEngineInput::GetInst()->IsPress("Move Right"))
	//	{
	//		ChangeState(PlayerState::Idle);
	//		return;
	//	}
	//	else
	//	{
	//		ChangeState(PlayerState::Move);
	//		return;
	//	}
	//}

	if (true == PlayerLeftCollision->NextPosCollisionCheck("BoxRight", NextPos_, CollisionType::Rect, CollisionType::Rect) ||
		true == PlayerRightCollision->NextPosCollisionCheck("BoxLeft", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.x = 0.0f;
		return;
	}

}

void Player::FootHitCheck()
{
	NextPos_ = (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos_ = NextPos_;

	if (true == PlayerFootCollision->NextPosCollisionCheck("BoxTop", NextPos_, CollisionType::Rect, CollisionType::Rect))
	{
		MoveDir.y = 0.0f;
		if (true == GameEngineInput::GetInst()->IsPress("Move Left") ||
			true == GameEngineInput::GetInst()->IsPress("Move Right"))
		{
			ChangeState(PlayerState::Move);
			return;
		}
		else
		{
			ChangeState(PlayerState::Idle);
			return;
		}
	}
	
}