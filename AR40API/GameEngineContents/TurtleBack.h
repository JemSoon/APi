#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineSound.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineImage;
class GameEngineCollision;
class TurtleBack : public GameEngineActor
{
public:
	//����Ʈ ������
	TurtleBack();
	//����Ʈ �Ҹ���
	~TurtleBack();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	TurtleBack(const TurtleBack& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	TurtleBack(TurtleBack&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	TurtleBack& operator=(const TurtleBack& _Other) = delete;
	TurtleBack& operator=(TurtleBack&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* TBAnimationRender;
	std::string AnimationName;

private:
	float Speed_;
	float AccSpeed_;

	float4 NextPos_;
	float4 CheckPos_;
	float4 MoveDir_;
	int Color_;

	void Start() override;
	void Render() override;
	void Update() override;

	GameEngineImage* MapColImage_;
	GameEngineCollision* TBCollision;
	GameEngineCollision* TBTopCollision;
	GameEngineCollision* TBTopLeftCollision;
	GameEngineCollision* TBTopRightCollision;
	GameEngineCollision* TBLeftCollision;
	GameEngineCollision* TBRightCollision;

public:
	void FootCheck();
	void LeftCheck();
	void RightCheck();
	void PlayerAttack();
	void Kill();

	void FallDead();
};

