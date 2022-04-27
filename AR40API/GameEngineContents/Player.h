#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

enum class PlayerState
{
	Idle,
	Attck,
	Move,
	Jump,
	Dead,
	Max,
};

//���� : 
class GameEngineImage;
class GameEngineCollision;
class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;

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


	float4 CurDir()
	{
		return PlayerDir_;
	}

protected:
	GameEngineRenderer* PlayerAnimationRender;
	
	std::string AnimationName;


	//void PlayerStateUpdate();


private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	static float4 NextLevelPosition;
	GameEngineRenderer* Render1;

	float Speed_;
	float AccSpeed_;
	float4 MoveDir;

	GameEngineImage* MapColImage_;

	GameEngineCollision* PlayerCollision;//�⺻ �浹ü
	GameEngineCollision* PlayerHeadCollision;//�Ӹ�
	GameEngineCollision* PlayerFootCollision;//��

	// bullet �� dir
	float4 PlayerDir_;

	// �ִϸ��̼� ����üũ��
	std::string DirString;//���� ����
	std::string PrevDirString;//������ �ٲ������

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
	void LeftCheck();
	void RightCheck();
	void RightBotCheck();
	void Fire();//�Ѿ� �߻��Լ�
	
	//===�� �߹ٴ� �����ִ� ��ġ �Ǻ��� ��� ����===//
private:
	float4 NextPos_;
	float4 CheckPos_;
	int Color_;
	//������ üũ�� ����������
	PlayerType Type_;
	
	//ī�޶� ��ǥ ������ �������
	float4 CameraPos_;

	// state�� �Լ�
private:
	PlayerState CurState_;

	void ChangeState(PlayerState _State);
	void StateUpdate();

private:
	// FSM���� �ݱⰡ �ֽ��ϴ�.
	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();

	void IdleStart();
	void MoveStart();
	void JumpStart();
};


