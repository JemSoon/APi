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

	Death(5.0f);//5초뒤에 총알은 사라진다(죽는다)

	XSpeed = 500.0f;
	YSpeed = 600.0f;
	DownSpeed = 2000.0f;
}
void Bullet::Update()
{
	ResultDir_ = float4::ZERO;

	// 모든 힘은 결국?

	ResultDir_ += BulletDir_ * GameEngineTime::GetDeltaTime() * XSpeed;
	// ->

	// YDir_ -= float4::DOWN * 200.0f;

	ResultDir_ += YDir_ * GameEngineTime::GetDeltaTime();



	//대각선 발사(가로+세로)
	SetMove(ResultDir_);

	YDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * DownSpeed;

	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");

	int Color = MapColImage_->GetImagePixel(GetPosition());//갈수 있냐 없냐 색 체크

	if (RGB(255, 0, 0) == Color)
	{
		YDir_ = float4::UP * YSpeed;
	}
	if (RGB(0, 255, 0) == Color|| RGB(55, 55, 55) == Color|| RGB(0, 255, 255) == Color)
	{
		//GameEngineRenderer* Render = CreateRenderer();
		//Render->CreateAnimation("Hit.bmp", "Hit", 0, 0, 0.1f, false);
		//Render->ChangeAnimation("Hit");
		//바닥 말고 사물에 부딪히면 Hit이미지로 바꿔주고싶은데 바로 사라져서 안됨
		//펑 터지는 이미지만 잠깐 남았다 사라지게 하고싶음
		Death(0.0f);
	}
}