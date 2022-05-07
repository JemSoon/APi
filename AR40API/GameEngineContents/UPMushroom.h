#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : Ŀ���� ����
class GameEngineImage;
class GameEngineCollision;
class UPMushroom : public GameEngineActor
{
public:
	//����Ʈ ������
	UPMushroom();
	//����Ʈ �Ҹ���
	~UPMushroom();




	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	UPMushroom(const UPMushroom& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	UPMushroom(UPMushroom&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	UPMushroom& operator=(const UPMushroom& _Other) = delete;
	UPMushroom& operator=(UPMushroom&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* UPMushroomAnimationRender;
	std::string AnimationName;

private:
	float Speed_;
	float AccSpeed_;

	float4 NextPos_;
	float4 CheckPos_;
	float4 MoveDir_;
	int Color_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* UPMushroomCollision;
	GameEngineCollision* UPMushroomBotCollision;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void WallCheck();
	void FootCheck();
	void LeftCheck();
	void RightCheck();
	void ColBotCheck();
	void ColBotCheck2();
};

