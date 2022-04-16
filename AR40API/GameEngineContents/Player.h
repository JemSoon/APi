#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�



//���� : 
class GameEngineImage;
class GameEngineCollision;
class Player : public GameEngineActor
{
public:
	//����Ʈ ������
	Player();
	//����Ʈ �Ҹ���
	~Player();




	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	Player(const Player& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Player(Player&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* PlayerAnimationRender;
	PlayerDir CurDir_;
	std::string AnimationName;

	void DirAnimationCheck();
	void PlayerStateUpdate();


private:
	float Speed_;
	//float AccSpeed_;
	float Gravity_;
	float AccGravity_;
	float4 MoveDir_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision;

	//bool IsMoveKey();

	void Start() override;
	void Render() override;
	void Update() override;

	void DoorCheck();
	void WallCheck();



};

