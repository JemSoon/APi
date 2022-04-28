#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

enum class BigPlayerState
{
	Idle,
	Attck,
	Move,
	Jump,
	Fall,
	Dead,
	Max,
};

//���� : 
class GameEngineImage;
class GameEngineCollision;
class BigPlayer : public GameEngineActor
{
public:
	static BigPlayer* MainBigPlayer;

	//����Ʈ ������
	BigPlayer();
	//����Ʈ �Ҹ���
	~BigPlayer();



	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	BigPlayer(const BigPlayer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	BigPlayer(BigPlayer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	BigPlayer& operator=(const BigPlayer& _Other) = delete;
	BigPlayer& operator=(BigPlayer&& _Other) noexcept = delete;


	float4 CurDir()
	{
		return BigPlayerDir_;
	}

protected:
	GameEngineRenderer* BigPlayerAnimationRender;

	std::string AnimationName;


	//void BigPlayerStateUpdate();


private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	static float4 NextLevelPosition;
	GameEngineRenderer* Render1;

	float Speed_;
	float AccSpeed_;
	float4 MoveDir;

	GameEngineImage* MapColImage_;

	GameEngineCollision* BigPlayerCollision;//�⺻ �浹ü
	GameEngineCollision* BigPlayerHeadCollision;//�Ӹ�
	GameEngineCollision* BigPlayerFootCollision;//��

	// bullet �� dir
	float4 BigPlayerDir_;

public:
	void Start() override;
	void Render() override;
	void Update() override;

	void DoorCheck();
	void WallCheck();
	void MushroomCheck();
	void FireFlowerCheck();

	bool IsMoveKey();
	void CameraOutCheck();

	//===���� �߰��� �ۺ� �Լ�===//
	void FootCheck();//�� ��ġ Ȯ�ο�
	void HeadCheck();
	void LeftCheck();
	void RightCheck();
	void Fire();//�Ѿ� �߻��Լ�

	//===�� �߹ٴ� �����ִ� ��ġ �Ǻ��� ��� ����===//
private:
	float4 NextPos_;
	float4 CheckPos_;
	int Color_;
	//������ üũ�� ����������
	//PlayerType Type_;

	//���� ���� ������
	std::string BigDirString;//���� ����

	//ī�޶� ��ǥ ������ �������
	float4 CameraPos_;

	// state�� �Լ�
private:
	BigPlayerState CurState_;

	void ChangeState(BigPlayerState _State);
	void StateUpdate();

private:
	// FSM���� �ݱⰡ �ֽ��ϴ�.
	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void FallUpdate();

	void IdleStart();
	void MoveStart();
	void JumpStart();
	void FallStart();
};


