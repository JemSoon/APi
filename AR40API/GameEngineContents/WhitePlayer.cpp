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

// �ƹ�Ű�� ������ �ʾҴٸ� false
// �ƹ�Ű�� ���ȴٸ� true
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
	//WhitePlayer��ġ�� �߾����� ����
	//SetPosition(GameEngineWindow::GetScale().Half());
	//������ �� ����� �����ϸ� �ȵ�(�������� �����Ҷ����� �ٸ��ϱ�)
	SetScale({ 64,128 });

	WhitePlayerCollision = CreateCollision("WhitePlayerHitBox", { 50, 128 });

	//�ִϸ��̼��� �ϳ��� ����� �ִϸ��̼ǵ� ����ȴ�
	WhitePlayerAnimationRender = CreateRenderer();
	//0~1�ε��� 0.1�ʸ���(true�� �ݺ�,false�� �ѹ������)
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
	{	//false�� ������� �� ���� Ű �̴�

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
	
	Fire();//�Ѿ� �߻��Լ�
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
			ColList[i]->Death();//���� �浹�� ���� �� �ְ�
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
			ColList[i]->GetActor()->Death();//���� �浹�� ���� �����
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
			ColList[i]->GetActor()->Death();//���� �浹�� ���� �����
		}
	}
}

//�������� �� ���ư��� ������ �ȴ�
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

void WhitePlayer::FootCheck()
{
	//�� �̷���ġ
	NextPos_ = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//�׶� �� �߹ٴ� ��ġ
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
