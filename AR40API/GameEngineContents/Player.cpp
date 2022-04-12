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

Player::Player()
	:Speed_(150.0f)
	,Gravity_(100.0f)
{

}

Player::~Player()
{

}

//�ƹ�Ű�� ������ �ʾҴٸ� false
//�ƹ�Ű�� ���ȴٸ� ture
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
	//Player��ġ�� �߾����� ����
	//SetPosition(GameEngineWindow::GetScale().Half());
	//������ �� ����� �����ϸ� �ȵ�(�������� �����Ҷ����� �ٸ��ϱ�)
	//SetScale({ 64,64 });

	//PlayerCollision = CreateCollision("PlayerHitBox", {64, 64});

	//�ִϸ��̼��� �ϳ��� ����� �ִϸ��̼ǵ� ����ȴ�
	PlayerAnimationRender = CreateRenderer();
	//0~1�ε��� 0.1�ʸ���(true�� �ݺ�,false�� �ѹ������)
	PlayerAnimationRender->CreateAnimation("walk-R.bmp", "Walk-R", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("walk-L.bmp", "Walk-L", 0, 2, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("idle-R.bmp", "idle-R", 0, 0, 0.0f, false);
	PlayerAnimationRender->CreateAnimation("idle-L.bmp", "idle-L", 0, 0, 0.0f, false);
	PlayerAnimationRender->ChangeAnimation("idle-R");

	CurDir_ = PlayerDir::Start;

	if (false == GameEngineInput::GetInst()->IsKey("Move Left"))
	{	//false�� ������� �� ���� Ű �̴�

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

	{	//�ʰ� ĳ������ �浹������
		//(����)���� BG�� ��ǥ�� �ȸ��� ����
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}

	float4 CheckPos;
	float4 MoveDir = float4::ZERO;

	//{	//������ ����
	//	if (true == GameEngineInput::GetInst()->IsPress("Move Left"))
	//	{
	//		MoveDir = float4::LEFT;

	//		//���� ��ġ + �̵��ϴ� ����
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

	{	//�� �̷���ġ
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		//�� �� �߹ٴ� ��ġ
		float4 CheckPos = NextPos + float4(0.0f, 32.0f);

		int Color = MapColImage_->GetImagePixel(CheckPos);//���� �ֳ� ���� �� üũ

		if (RGB(255,0,0) != Color)
		{	//�������� �ƴ϶�� ���� �̽�
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}	
	}
	//�÷��̾ ī�޶� �߽ɿ� �ֱ� ���ϸ� �׸�ŭ ��ġ�� ���ϰų� ����
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half()-float4(-200.0f, 200.0f));

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
	float MapSizeY = 1920;//�� ���� ��
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

	//WallCheck();
	//DoorCheck();



	//if (true== PlayerCollision->Collision("Door"))//���� �浹 �ߴٸ�
	//{
	//	PlayerCollision->Collision("Door");
	//}

	//{	//�߷� ����
	//	//�� �����ǿ��� (CENTER�߽��̶� �ٴ� �����̴� 32�Ʒ���)
	//int Color = MapColImage_->GetImagePixel(GetPosition() + float4(0.0f, 32.0f));

	//�浹 ���� �������̽�
	//1.�켱 �浹ü�� �����(�������� �Ȱ���)
	//�̵��ϰ� ���� a=0�̵Ƿ��� ���� �̵��ϱ����� �Ϸ��� ������Ʈ��
	//GameEngineCollision* MyCollision;
	//if (true == MyCollision->Collision("Door"))
	//{
	//	int a = 0;
	//}

	//	//�߷�
	//	AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;//���� ���ӵ�
	//	
	//	if (RGB(255, 0, 0)==Color/*���� ��Ҵٸ�(������)*/)
	//	{
	//		AccGravity_ = 0.0f;//����-�߷�0�Ǹ� �ؿ� �̵��� 0�̵Ǽ� ���� ������ �̵�����
	//	}
	//	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);
	//}

	//if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	//{
	//	SetScale({ 32,32 });

	//	Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
	//	Ptr->SetPosition(GetPosition());
	//	
	//	//�÷��̾ ���� �������� �Ѿ˹����� �ٲٰ������ �ȵ�
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


	///*if (2.0f < GameEngineInput::GetInst()->GetTime("Fire")) 2�ʰ� ������� ������
	//{
	//	SetScale({ 32,32 });

	//	Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
	//	Ptr->SetPosition(GetPosition());

	//}*/

}


//�������� �� ���ư��� ������ �ȴ�
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
//			ColList[i]->Death();//���� �浹�� ���� �� �ְ�
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