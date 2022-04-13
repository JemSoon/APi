#include "Bullet.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


Bullet::Bullet()
	: Time()
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

	Death(2.0f);//2초뒤에 총알은 사라진다(죽는다)
}
void Bullet::Update()
{


	//대각선 발사(가로+세로)
	SetMove((SetDir(float4::RIGHT) * GameEngineTime::GetDeltaTime() * 450.0f) + (float4::DOWN * GameEngineTime::GetDeltaTime() * 300.0f));
}