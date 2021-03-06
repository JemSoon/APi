#include "Bullet.h"
#include "Hit.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
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
	BulletRender = CreateRenderer();
	BulletRender->CreateAnimation("Bullet.bmp", "Bullet", 0, 3, 0.1f, true);
	BulletRender->CreateAnimation("Hit.bmp", "Hit", 0, 0, 1.0f, false);
	BulletRender->ChangeAnimation("Bullet");
	//Render->SetIndex(0);

	BulletCollision = CreateCollision("PlayerAttackBox", { 32, 32 });

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
		Hit* Boom = GetLevel()->CreateActor<Hit>();
		Boom->SetPosition(GetPosition());

		Death(0.0f);
	}

	float4 NextPos = (ResultDir_ * GameEngineTime::GetDeltaTime() * DownSpeed);
	
	if (true == BulletCollision->NextPosCollisionCheck("Box", NextPos, CollisionType::Rect, CollisionType::Rect)||
		true == BulletCollision->NextPosCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
	{
		Hit* Boom = GetLevel()->CreateActor<Hit>();
		Boom->SetPosition(GetPosition());

		Death(0.0f);
	}

	HitToMonster();
}

void Bullet::HitToMonster()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == BulletCollision->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{

		for (size_t i = 0; i < ColList.size(); i++)
		{
			GameEngineSound::SoundPlayOneShot("smb_kick.wav");
			ColList[i]->GetActor()->Death();
		}

		Hit* Boom = GetLevel()->CreateActor<Hit>();
		Boom->SetPosition(GetPosition());

		Death(0.0f);

	}
}