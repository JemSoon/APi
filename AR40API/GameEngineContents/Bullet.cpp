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
	//Time = 4.0f;

	Death(2.0f);
}
void Bullet::Update()
{
	//Time -= GameEngineTime::GetDeltaTime();

	//if (0.0f >= Time)//4초후 총알 삭제
	//{
	//	Death();
	//	return;
	//}

	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.0f);
}