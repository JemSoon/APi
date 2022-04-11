#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include "GameEngineImage.h"
#include <map>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
//class GameEngineImage;
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	//����Ʈ ������
	GameEngineCollision();
	//����Ʈ �Ҹ���
	~GameEngineCollision();




	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;



	inline void SetPivot(const float4& _Pos)
	{
		Pivot_ = _Pos;
	}

	inline void SetScale(const float4& _Scale)
	{
		Scale_ = _Scale;
	}

	inline float4 GetCollisionPos()
	{
		return GetActor()->GetPosition() + Pivot_;
	}

	inline GameEngineRect GetRect()
	{
		return GameEngineRect(GetActor()->GetPosition() + Pivot_, Scale_);
	}

	//�浹�� ����� �����ϸ� ture�����ϴ� �Լ�(�浹�� ����� �ִ��� �������� üũ�ϴ� �Լ�)
	bool CollisionCheck(
		const std::string& _TargetGroup, 
		CollisionType _This = CollisionType::Circle, 
		CollisionType _Target = CollisionType::Circle);
	//�ε����� ����̶� �浹�Ǻ�, �׸��� ���� ����Ÿ������ ���ų�
	//Player	Bullet
	//����		���� �Ѿ��� ���´�
	//����		���� �Ѿ�
	

private:
	friend class FrameAnimation;

	//����(ex:�÷��̾�)���� {50,0}��ŭ ������ ���� �ְ� �װ� �浹üũ�� �Ѵ�(���ͱ���)
	float4 Pivot_;

	//�� ��ġ���� ���� ũ���
	float4 Scale_;


};

