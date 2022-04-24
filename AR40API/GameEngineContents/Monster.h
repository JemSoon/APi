#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineImage;
class GameEngineCollision;
class Monster : public GameEngineActor
{
public:
	//����Ʈ ������
	Monster();
	//����Ʈ �Ҹ���
	~Monster();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Monster(const Monster& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Monster(Monster&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* MonsterAnimationRender;
	std::string AnimationName;


private:
	float Speed_;
	float AccSpeed_;
	
	float4 NextPos_;
	float4 CheckPos_;
	float4 MoveDir_;
	int Color_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* MonsterCollision;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void WallCheck();
	void FootCheck();
	void LeftCheck();
	void RightCheck();
};

