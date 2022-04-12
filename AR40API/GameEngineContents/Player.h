#pragma once
#include <GameEngine/GameEngineActor.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

enum PlayerState
{
	Idle,
	Attack,
	Move,
	Max
};

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



private:
	float Speed_;
	float Gravity_;
	float AccGravity_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision;

	void Start() override;
	void Render() override;
	void Update() override;

	void DoorCheck();
	void WallCheck();

private:
	PlayerState CurState_;

	bool IsMoveKey();
	void KeyMove();

public:
	void ChangeState(PlayerState _State);
	void StateUpdate();

	//FSM======
	//FSM�� �ݱ� IdelUpdate������ AttackUpdate�� ���� ����Ǽ� �ȵȴ�
	//(�� �ϳ��� ���� �ȵȴ�)
	void IdleUpdate();
	void AttackUpdate();
	void MoveUpdate();
	
	void IdleStart();
	void AttackStart();
	void MoveStart();

};

