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
	Death(2.0f);//2초뒤에 총알은 사라진다(죽는다)
}
void Bullet::Update()
{
	//여기다 Death()를 적으면 계속 업데이트되서 계속 2초 연장되서 안쥬금
	
	//Time -= GameEngineTime::GetDeltaTime();

	//if (0.0f >= Time)//4초후 총알 삭제
	//{
	//	Death();
	//	return;
	//}

	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 400.0f);
}