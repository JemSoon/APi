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
	PlayerDir CurDir_;
	std::string AnimationName;

	//void DirAnimationCheck();
	//void MonsterStateUpdate();


private:
	float Speed_;
	float Gravity_;
	float AccGravity_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* MonsterCollision;


	void Start() override;
	void Render() override;
	void Update() override;

	//void DoorCheck();
	void WallCheck();

};

