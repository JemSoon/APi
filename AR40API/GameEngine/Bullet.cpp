#include "Bullet.h"
#include "GameEngineBase/GameEngineTime.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::Start()
{
	CreateRenderer("Bullet.bmp");
}
void Bullet::Update()
{
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.0f);
}