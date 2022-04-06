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

	Death(2.0f);//2�ʵڿ� �Ѿ��� �������(�״´�)
}
void Bullet::Update()
{
	//����� Death()�� ������ ��� ������Ʈ�Ǽ� ��� 2�� ����Ǽ� �����
	
	//Time -= GameEngineTime::GetDeltaTime();

	//if (0.0f >= Time)//4���� �Ѿ� ����
	//{
	//	Death();
	//	return;
	//}

	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 400.0f);
}