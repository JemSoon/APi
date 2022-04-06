#include "Bullet.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


Bullet::Bullet()
	: Time()
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
	//여기다 Death()를 적으면 계속 업데이트되서 계속 2초 연장되서 안쥬금
	
	//Time -= GameEngineTime::GetDeltaTime();

	//if (0.0f >= Time)//4초후 총알 삭제
	//{
	//	Death();
	//	return;
	//}

	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 400.0f);
}