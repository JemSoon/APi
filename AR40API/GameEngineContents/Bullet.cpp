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