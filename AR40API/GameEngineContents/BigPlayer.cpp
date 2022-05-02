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

#include <GameEngine/GameEngineLevel.h>//������ ���ؼ�
#include "Bullet.h"//�Ѿ��� ����� �ʹ�

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

// �ƹ�Ű�� ������ �ʾҴٸ� false
// �ƹ�Ű�� ���ȴٸ� true
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

	BigPlayerHeadHitCollision = CreateCollision("BigPlayerHeadHit", { 1, 0 }, { 0,-65 });//�ڽ� �浹��(1���� �浹�ϰԲ�)
	BigPlayerHeadCollision = CreateCollision("PlayerHead", { 64, 1 }, { 0,-64 });
	BigPlayerFootCollision = CreateCollision("PlayerFoot", { 64, 1 }, { 0,64 });
	BigPlayerFootHitCollision = CreateCollision("PlayerFootHit", { 1, 0 }, { 0,65 });//�� �浹��(1������ ��Բ�)
	BigPlayerLeftCollision = CreateCollision("PlayerLeft", { 2, 127 }, { -32,0 });//�β� 2���ؾ� ž�̳� ���� �Ȱ��Ŀ�~
	BigPlayerRightCollision = CreateCollision("PlayerRight", { 2, 127 }, { 32,0 });

	BigPlayerCollision = CreateCollision("BigPlayerHitBox", { 50, 128 });
	BigPlayerDownCollision = CreateCollision("BigPlayerDownHitBox", { 50, 80 },{0,22});

	//�ִϸ��̼��� �ϳ��� ����� �ִϸ��̼ǵ� ����ȴ�
	BigPlayerAnimationRender = CreateRenderer((int)ORDER::PLAYER);
	//0~1�ε��� 0.1�ʸ���(true�� �ݺ�,false�� �ѹ������)
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
	{	//false�� ������� �� ���� Ű �̴�

		GameEngineInput::GetInst()->CreateKey("Move Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Move Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Move Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", 'X');
		GameEngineInput::GetInst()->CreateKey("Run", 'C');
		GameEngineInput::GetInst()->CreateKey("Fire", 'Z');
	}

	Off();
	MainBigPlayer = this;
	//���� this ������ �ϳ��� ��������ϱ�
}


void BigPlayer::Update()
{
	//Fire();//�Ѿ� �߻��Լ�
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
			ColList[i]->Death();//���� �浹�� ���� �� �ְ�
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
			ColList[i]->GetActor()->Death();//���� �浹�� ���� �����
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
			ColList[i]->GetActor()->Death();//���� �浹�� ���� �����
		}
		MainBigPlayer->Off();
		WhitePlayer::MainWhitePlayer->SetPosition(GetPosition());
		WhitePlayer::MainWhitePlayer->On();
	}
}

//�������� �� ���ư��� ������ �ȴ�
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

void BigPlayer::FootCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(0.0f, 64.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void BigPlayer::HeadCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �Ӹ� ��ġ
	CheckPos_ = NextPos_ + float4(0.0f, -54.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void BigPlayer::LeftCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �߹ٴ� ��ġ
	CheckPos_ = NextPos_ + float4(-26.0f, 0.0f);
	Color_ = MapColImage_->GetImagePixel(CheckPos_);
}

void BigPlayer::RightCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �߹ٴ� ��ġ
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
	{	//���ʿ��� ���������� Ʋ��
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
		//�����ʿ��� �������� Ʋ��
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
			ColList[i]->GetActor()->Death();//���� �浹�� ���� �ְ�
		}
		MainBigPlayer->JumpStart();
		MoveDir.y = -10.0f;//�ణ�� ���� ����
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