#include "Bullet.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>


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
	Render->ChangeAnimation("Bullet");
	//Render->SetIndex(0);

	Death(20.0f);//2�ʵڿ� �Ѿ��� �������(�״´�)

	XSpeed = 500.0f;
	YSpeed = 600.0f;
	DownSpeed = 2000.0f;
}
void Bullet::Update()
{
	float4 ResultDir = float4::ZERO;

	// ��� ���� �ᱹ?

	ResultDir += BulletDir_ * GameEngineTime::GetDeltaTime() * XSpeed;
	// ->

	// YDir_ -= float4::DOWN * 200.0f;

	ResultDir += YDir_ * GameEngineTime::GetDeltaTime();



	//�밢�� �߻�(����+����)
	SetMove(ResultDir);

	YDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * DownSpeed;

	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");

	int Color = MapColImage_->GetImagePixel(GetPosition());//���� �ֳ� ���� �� üũ

	if (RGB(255, 0, 0) == Color)
	{
		YDir_ = float4::UP * YSpeed;
	}
}