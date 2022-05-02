#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineImage;
class GameEngineCollision;
class Turtle : public GameEngineActor
{
public:
	//����Ʈ ������
	Turtle();
	//����Ʈ �Ҹ���
	~Turtle();

	void DirCheck();


	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	Turtle(const Turtle& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Turtle(Turtle&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Turtle& operator=(const Turtle& _Other) = delete;
	Turtle& operator=(Turtle&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* TurtleAnimationRender;
	std::string AnimationName;


private:
	float Speed_;
	float AccSpeed_;

	std::string DirString_;

	float4 NextPos_;
	float4 CheckPos_;
	float4 MoveDir_;
	int Color_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* TurtleCollision;
	GameEngineCollision* TurtleTopCollision;
	GameEngineCollision* TurtleLeftCollision;
	GameEngineCollision* TurtleRightCollision;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void WallCheck();
	void FootCheck();
	void LeftCheck();
	void RightCheck();

	void AnotherTurtleCheck();
};

