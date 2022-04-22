#include "Player.h"
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
	, AccSpeed_(10.0f)
	, MoveDir(float4::ZERO)
	, PlayerDir_(float4::RIGHT)
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
	//Player��ġ�� �߾����� ����
	//SetPosition(GameEngineWindow::GetScale().Half());
	//������ �� ����� �����ϸ� �ȵ�(�������� �����Ҷ����� �ٸ��ϱ�)
	SetScale({ 64,64 });

	PlayerHeadCollision = CreateCollision("PlayerHead", { 50, 2 },{0,-31});
	PlayerCollision = CreateCollision("PlayerHitBox", { 50, 61 });
	PlayerFootCollision = CreateCollision("PlayerFoot", { 50, 2 }, { 0,32 });

	//�ִϸ��̼��� �ϳ��� ����� �ִϸ��̼ǵ� ����ȴ�
	PlayerAnimationRender = CreateRenderer();
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

	CurDir_ = PlayerDir::Start;

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
	//// �Ĺ��� �ڶ�°Ŷ�� �ϸ�
	//// GetAccTime() �� ������Ʈ�� ���ʰ� ����־�����.
	//if (5.0f <= GetAccTime())
	//{
	//	ReSetAccTime();
	//	int a = 0;
	//}

	Fire();//�Ѿ� �߻��Լ�
	StateUpdate();

	WallCheck();
	DoorCheck();

	//DirAnimationCheck();
	//PlayerStateUpdate();

	//{	//�ʰ� ĳ������ �浹������
	//	
	//	MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");
	//	

	//	if (nullptr == MapColImage_)
	//	{
	//		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
	//	}
	//}

	//float4 CheckPos;
	//
	//{	//������ ����
	//	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	//	{
	//		MoveDir_ += float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_;
	//		PlayerDir_ = float4::LEFT;//�Ѿ� �߻� ���� ����
	//		//���� ��ġ + �̵��ϴ� ����
	//		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//		if (true == GameEngineInput::GetInst()->IsPress("Run"))
	//		{
	//			Speed_ = 50.0f;
	//		}
	//		else
	//		{
	//			Speed_ = 20.0f;
	//		}

	//	}

	//	if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	//	{
	//		MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;
	//		PlayerDir_ = float4::RIGHT;//�Ѿ� �߻� ���� ����
	//		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//		if (true == GameEngineInput::GetInst()->IsPress("Run"))
	//		{
	//			Speed_ = 50.0f;
	//		}
	//		else
	//		{
	//			Speed_ = 20.0f;
	//		}
	//	}

	//	if (true == GameEngineInput::GetInst()->IsPress("Move Up"))
	//	{
	//		MoveDir_ = float4::UP;

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
	//		MoveDir_ = float4::DOWN;

	//		//SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	//		if (true == GameEngineInput::GetInst()->IsPress("Run"))
	//		{
	//			Speed_ = 450.0f;
	//		}
	//		else
	//		{
	//			Speed_ = 150.0f;
	//		}
	//	
	//	}

	//	if (true == GameEngineInput::GetInst()->IsPress("Jump"))
	//	{
	//		MoveDir_ = float4::UP;
	//		Speed_ = 450.0f;
	//	}

	//	if (1000.0f <= MoveDir_.Len2D())
	//	{	//�ӵ� �ִ�ġ ����
	//		MoveDir_.Range2D(1000.0f);
	//	}


	//	if (MoveDir_.Len2D() >= 100)
	//	{
	//		//�ӵ� �ִ�ġ ����ȭ
	//		MoveDir_.Normal2D();
	//	}

	//}

	//{	//�� �̷���ġ (Speed_�� ���ӷ�)
	//	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	//	
	//	//�� �� �߹ٴ� ��ġ
	//	float4 CheckPos1 = NextPos + float4(0.0f, 32.0f);
	//	//�� �� �Ӹ� ��ġ
	//	float4 CheckPos2 = NextPos + float4(0.0f, -32.0f);

	//	int Color1 = MapColImage_->GetImagePixel(CheckPos1);//���� �ֳ� ���� �� üũ
	//	int Color2 = MapColImage_->GetImagePixel(CheckPos2);

	//	if (RGB(255, 0, 0) != Color1 &&
	//		RGB(55, 55, 55) != Color1 && 
	//		RGB(0, 255, 255) != Color1 && 
	//		RGB(0, 255, 0) != Color1)
	//	{	
	//		//������+@�� �ƴ϶�� ���� �̽�
	//		//���� �߹ٴ� ��� �����̶� �Ӹ����� �����(��� �ؿ��� ���� �ε�����)
	//		MoveDir_ += ((-MoveDir_ * 0.9f) * GameEngineTime::GetDeltaTime());
	//		//������ if�� �ɸ� �̻������� �ϴ� ��

	//		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

	//		if ((MoveDir_.x < 0.0f && MoveDir_.x>-20.0f) && true == GameEngineInput::GetInst()->IsFree("Move Left")&& (GameEngineInput::GetInst()->IsPress("Run")|| GameEngineInput::GetInst()->IsFree("Run"))
	//			|| (MoveDir_.x > 0.0f && MoveDir_.x < 20.0f) && true == GameEngineInput::GetInst()->IsFree("Move Right")&& (GameEngineInput::GetInst()->IsPress("Run") || GameEngineInput::GetInst()->IsFree("Run")))
	//		{
	//			MoveDir_.x = 0.0f;
	//		}

	//	}
	//}



	////if (true== PlayerCollision->Collision("Door"))//���� �浹 �ߴٸ�
	////{
	////	PlayerCollision->Collision("Door");
	////}



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
void Player::DirAnimationCheck()
{
	std::string ChangeName;

	CheckDir_ = CurDir_;
	std::string ChangeDirText = "R";

	//if (true == GameEngineInput::GetInst()->IsPress("Move Right"))
	//{
	//	CheckDir_ = PlayerDir::Right;
	//	ChangeName = "Walk-";
	//	ChangeDirText = "R";
	//}
	if (true == GameEngineInput::GetInst()->IsUp("Move Right"))
	{
		CheckDir_ = PlayerDir::Right;
		ChangeName = "idle-";
		ChangeDirText = "R";
	}

	//if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	//{
	//	CheckDir_ = PlayerDir::Left;
	//	ChangeName = "Walk-";
	//	ChangeDirText = "L";
	//}
	if (true == GameEngineInput::GetInst()->IsUp("Move Left"))
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

//�������� �� ���ư��� ������ �ȴ�
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
