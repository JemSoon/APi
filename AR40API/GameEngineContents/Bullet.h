#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Bullet : public GameEngineActor
{
public:
	//����Ʈ ������
	Bullet();
	//����Ʈ �Ҹ���
	~Bullet();




	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	Bullet(const Bullet& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Bullet(Bullet&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	float Time;

	float4 SetDir(float4 Dir_)
	{
		//SetMove((float4::RIGHT * GameEngineTime::GetDeltaTime() * 450.0f) + (float4::DOWN * GameEngineTime::GetDeltaTime() * 300.0f));
		BulletDir_ = Dir_;
		return BulletDir_;
	}

	void HitToMonster();

protected:

private:
	void Start() override;
	void Update() override;

	float XSpeed;
	float YSpeed;
	float DownSpeed;
	float4 BulletDir_;
	float4 YDir_;
	float4 ResultDir_;

	//�Ѿ� �浹ü ������ ������
	GameEngineCollision* BulletCollision;
	//������ ������ ������
	GameEngineRenderer* BulletRender;
};

