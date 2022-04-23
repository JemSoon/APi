#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : Ŀ���� ����
class GameEngineImage;
class GameEngineCollision;
class Mushroom : public GameEngineActor
{
public:
	//����Ʈ ������
	Mushroom();
	//����Ʈ �Ҹ���
	~Mushroom();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Mushroom(const Mushroom& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Mushroom(Mushroom&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Mushroom& operator=(const Mushroom& _Other) = delete;
	Mushroom& operator=(Mushroom&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* MushroomAnimationRender;
	PlayerDir CurDir_;
	std::string AnimationName;

private:
	float Speed_;
	float AccSpeed_;

	float4 NextPos_;
	float4 CheckPos_;
	float4 MoveDir_;
	int Color_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* MushroomCollision;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void WallCheck();
	void FootCheck();
	void LeftCheck();
	void RightCheck();
};

