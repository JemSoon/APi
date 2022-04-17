#include "Bullet.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Player.h"


Bullet::Bullet()
	: Time()
	, YDir_(float4::DOWN * 200.0f)
	//, BulletDir_({1,0})
{

}

Bullet::~Bullet()
{

}

void Bullet::Start()
{
	GameEngineRenderer* Render = CreateRenderer();
	Render->CreateAnimation("Bullet.bmp", "Bullet", 0, 3, 0.1f, true);
	Render->CreateAnimation("Hit.bmp", "Hit", 0, 0, 1.0f, false);
	Render->ChangeAnimation("Bullet");
	//Render->SetIndex(0);

	Death(5.0f);//5�ʵڿ� �Ѿ��� �������(�״´�)

	XSpeed = 500.0f;
	YSpeed = 600.0f;
	DownSpeed = 2000.0f;
}
void Bullet::Update()
{
	ResultDir_ = float4::ZERO;

	// ��� ���� �ᱹ?

	ResultDir_ += BulletDir_ * GameEngineTime::GetDeltaTime() * XSpeed;
	// ->

	// YDir_ -= float4::DOWN * 200.0f;

	ResultDir_ += YDir_ * GameEngineTime::GetDeltaTime();



	//�밢�� �߻�(����+����)
	SetMove(ResultDir_);

	YDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * DownSpeed;

	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");

	int Color = MapColImage_->GetImagePixel(GetPosition());//���� �ֳ� ���� �� üũ

	if (RGB(255, 0, 0) == Color)
	{
		YDir_ = float4::UP * YSpeed;
	}
	if (RGB(0, 255, 0) == Color|| RGB(55, 55, 55) == Color|| RGB(0, 255, 255) == Color)
	{
		//GameEngineRenderer* Render = CreateRenderer();
		//Render->CreateAnimation("Hit.bmp", "Hit", 0, 0, 0.1f, false);
		//Render->ChangeAnimation("Hit");
		//�ٴ� ���� �繰�� �ε����� Hit�̹����� �ٲ��ְ������ �ٷ� ������� �ȵ�
		//�� ������ �̹����� ��� ���Ҵ� ������� �ϰ����
		Death(0.0f);
	}
}